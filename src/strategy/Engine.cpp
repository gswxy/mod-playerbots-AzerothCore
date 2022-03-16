/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Engine.h"
#include "Action.h"
#include "Event.h"
#include "Queue.h"
#include "PerformanceMonitor.h"
#include "Playerbots.h"

Engine::Engine(PlayerbotAI* botAI, AiObjectContext* factory) : PlayerbotAIAware(botAI), aiObjectContext(factory)
{
    lastRelevance = 0.0f;
    testMode = false;
}

bool ActionExecutionListeners::Before(Action* action, Event event)
{
    bool result = true;
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        result &= (*i)->Before(action, event);
    }

    return result;
}

void ActionExecutionListeners::After(Action* action, bool executed, Event event)
{
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        (*i)->After(action, executed, event);
    }
}

bool ActionExecutionListeners::OverrideResult(Action* action, bool executed, Event event)
{
    bool result = executed;
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        result = (*i)->OverrideResult(action, result, event);
    }

    return result;
}

bool ActionExecutionListeners::AllowExecution(Action* action, Event event)
{
    bool result = true;
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        result &= (*i)->AllowExecution(action, event);
    }

    return result;
}

ActionExecutionListeners::~ActionExecutionListeners()
{
    for (std::list<ActionExecutionListener*>::iterator i = listeners.begin(); i != listeners.end(); i++)
    {
        delete *i;
    }

    listeners.clear();
}

Engine::~Engine(void)
{
    Reset();

    strategies.clear();
}

void Engine::Reset()
{
    ActionNode* action = nullptr;
    do
    {
        action = queue.Pop();
        if (!action)
            break;

        delete action;
    } while (true);

    for (std::vector<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        TriggerNode* trigger = *i;
        delete trigger;
    }

    triggers.clear();

    for (std::vector<Multiplier*>::iterator i = multipliers.begin(); i != multipliers.end(); i++)
    {
        Multiplier* multiplier = *i;
        delete multiplier;
    }

    multipliers.clear();
}

void Engine::Init()
{
    Reset();

    for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = i->second;
        strategy->InitMultipliers(multipliers);
        strategy->InitTriggers(triggers);

        Event emptyEvent;
        MultiplyAndPush(strategy->getDefaultActions(), 0.0f, false, emptyEvent, "default");
    }

	if (testMode)
	{
        FILE* file = fopen("test.log", "w");
        fprintf(file, "\n");
        fclose(file);
	}
}

bool Engine::DoNextAction(Unit* unit, uint32 depth, bool minimal)
{
    LogAction("--- AI Tick ---");

    if (sPlayerbotAIConfig->logValuesPerTick)
        LogValues();

    bool actionExecuted = false;
    ActionBasket* basket = nullptr;

    time_t currentTime = time(nullptr);
    aiObjectContext->Update();
    ProcessTriggers(minimal);

    uint32 iterations = 0;
    uint32 iterationsPerTick = queue.Size() * (minimal ? 2 : sPlayerbotAIConfig->iterationsPerTick);
    do
    {
        basket = queue.Peek();

        if (basket)
        {
            float relevance = basket->getRelevance(); // just for reference
            bool skipPrerequisites = basket->isSkipPrerequisites();

            if (minimal && (relevance < 100))
                continue;

            Event event = basket->getEvent();
            // NOTE: queue.Pop() deletes basket
            ActionNode* actionNode = queue.Pop();
            Action* action = InitializeAction(actionNode);

            if (action)
                action->setRelevance(relevance);

            if (!action)
            {
                LogAction("A:%s - UNKNOWN", actionNode->getName().c_str());
            }
            else if (action->isUseful())
            {
                for (std::vector<Multiplier*>::iterator i = multipliers.begin(); i!= multipliers.end(); i++)
                {
                    Multiplier* multiplier = *i;
                    relevance *= multiplier->GetValue(action);
                    action->setRelevance(relevance);

                    if (!relevance)
                    {
                        LogAction("Multiplier %s made action %s useless", multiplier->getName().c_str(), action->getName().c_str());
                        break;
                    }
                }

                if (action->isPossible() && relevance)
                {
                    if (!skipPrerequisites)
                    {
                        LogAction("A:%s - PREREQ", action->getName().c_str());

                        if (MultiplyAndPush(actionNode->getPrerequisites(), relevance + 0.02, false, event, "prereq"))
                        {
                            PushAgain(actionNode, relevance + 0.01, event);
                            continue;
                        }
                    }

                    PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_ACTION, action->getName(), &aiObjectContext->performanceStack);
                    actionExecuted = ListenAndExecute(action, event);
                    if (pmo)
                        pmo->finish();

                    if (actionExecuted)
                    {
                        LogAction("A:%s - OK", action->getName().c_str());
                        MultiplyAndPush(actionNode->getContinuers(), 0, false, event, "cont");
                        lastRelevance = relevance;
                        delete actionNode;
                        break;
                    }
                    else
                    {
                        LogAction("A:%s - FAILED", action->getName().c_str());
                        MultiplyAndPush(actionNode->getAlternatives(), relevance + 0.03, false, event, "alt");
                    }
                }
                else
                {
                    LogAction("A:%s - IMPOSSIBLE", action->getName().c_str());
                    MultiplyAndPush(actionNode->getAlternatives(), relevance + 0.03, false, event, "alt");
                }
            }
            else
            {
                lastRelevance = relevance;
                LogAction("A:%s - USELESS", action->getName().c_str());
            }

            delete actionNode;
        }
    }
    while (basket && ++iterations <= iterationsPerTick);

    if (!basket)
    {
        lastRelevance = 0.0f;
        PushDefaultActions();

        if (queue.Peek() && depth < 2)
            return DoNextAction(unit, depth + 1, minimal);
    }

    // MEMORY FIX TEST
    /*
    do
    {
        basket = queue.Peek();
        if (basket)
        {
            // NOTE: queue.Pop() deletes basket
            delete queue.Pop();
        }
    }
    while (basket);
    */

    if (time(nullptr) - currentTime > 1)
    {
        LogAction("too long execution");
    }

    if (!actionExecuted)
        LogAction("no actions executed");

    queue.RemoveExpired();

    return actionExecuted;
}

ActionNode* Engine::CreateActionNode(std::string const name)
{
    for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        if (ActionNode* node = i->second->GetAction(name))
            return node;
    }

    return new ActionNode (name,
        /*P*/ nullptr,
        /*A*/ nullptr,
        /*C*/ nullptr);
}

bool Engine::MultiplyAndPush(NextAction** actions, float forceRelevance, bool skipPrerequisites, Event event, char const* pushType)
{
    bool pushed = false;
    if (actions)
    {
        for (uint32 j = 0; actions[j]; j++)
        {
            if (NextAction* nextAction = actions[j])
            {
                ActionNode* action = CreateActionNode(nextAction->getName());
                InitializeAction(action);

                float k = nextAction->getRelevance();
                if (forceRelevance > 0.0f)
                {
                    k = forceRelevance;
                }

                if (k > 0)
                {
                    LogAction("PUSH:%s - %f (%s)", action->getName().c_str(), k, pushType);
                    queue.Push(new ActionBasket(action, k, skipPrerequisites, event));
                    pushed = true;
                }
                else
                {
                    delete action;
                }

                delete nextAction;
            }
            else
                break;
        }

        delete[] actions;
    }

    return pushed;
}

ActionResult Engine::ExecuteAction(std::string const name, Event event, std::string const qualifier)
{
	bool result = false;

    ActionNode* actionNode = CreateActionNode(name);
    if (!actionNode)
        return ACTION_RESULT_UNKNOWN;

    Action* action = InitializeAction(actionNode);
    if (!action)
    {
        delete actionNode;
        return ACTION_RESULT_UNKNOWN;
    }

    if (!qualifier.empty())
    {
        if (Qualified* q = dynamic_cast<Qualified*>(action))
            q->Qualify(qualifier);
    }

    if (!action->isPossible())
    {
        delete actionNode;
        return ACTION_RESULT_IMPOSSIBLE;
    }

    if (!action->isUseful())
    {
        delete actionNode;
        return ACTION_RESULT_USELESS;
    }

    action->MakeVerbose();

    result = ListenAndExecute(action, event);
    MultiplyAndPush(action->getContinuers(), 0.0f, false, event, "default");

    delete actionNode;

	return result ? ACTION_RESULT_OK : ACTION_RESULT_FAILED;
}

void Engine::addStrategy(std::string const name)
{
    removeStrategy(name);

    if (Strategy* strategy = aiObjectContext->GetStrategy(name))
    {
        std::set<std::string> siblings = aiObjectContext->GetSiblingStrategy(name);
        for (std::set<std::string>::iterator i = siblings.begin(); i != siblings.end(); i++)
            removeStrategy(*i);

        LogAction("S:+%s", strategy->getName().c_str());
        strategies[strategy->getName()] = strategy;
    }

    Init();
}

void Engine::addStrategies(std::string first, ...)
{
	addStrategy(first);

	va_list vl;
	va_start(vl, first);

	const char* cur;
	do
	{
		cur = va_arg(vl, const char*);
		if (cur)
			addStrategy(cur);
	}
	while (cur);

	va_end(vl);
}

bool Engine::removeStrategy(std::string const name)
{
    std::map<std::string, Strategy*>::iterator i = strategies.find(name);
    if (i == strategies.end())
        return false;

    LogAction("S:-%s", name.c_str());
    strategies.erase(i);
    Init();

    return true;
}

void Engine::removeAllStrategies()
{
    strategies.clear();
    Init();
}

void Engine::toggleStrategy(std::string const name)
{
    if (!removeStrategy(name))
        addStrategy(name);
}

bool Engine::HasStrategy(std::string const name)
{
    return strategies.find(name) != strategies.end();
}

void Engine::ProcessTriggers(bool minimal)
{
    std::map<Trigger*, Event> fires;
    for (std::vector<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        TriggerNode* node = *i;
        if (!node)
            continue;

        Trigger* trigger = node->getTrigger();
        if (!trigger)
        {
            trigger = aiObjectContext->GetTrigger(node->getName());
            node->setTrigger(trigger);
        }

        if (!trigger)
            continue;

        if (testMode || trigger->needCheck())
        {
            if (minimal && node->getFirstRelevance() < 100)
                continue;

            PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_TRIGGER, trigger->getName(), &aiObjectContext->performanceStack);
            Event event = trigger->Check();
            if (pmo)
                pmo->finish();

            if (!event)
                continue;

            fires[trigger] = event;
            LogAction("T:%s", trigger->getName().c_str());
        }
    }

    for (std::vector<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        TriggerNode* node = *i;
        Trigger* trigger = node->getTrigger();
        Event event = fires[trigger];
        if (!event)
            continue;

        MultiplyAndPush(node->getHandlers(), 0.0f, false, event, "trigger");
    }

    for (std::vector<TriggerNode*>::iterator i = triggers.begin(); i != triggers.end(); i++)
    {
        if (Trigger* trigger = (*i)->getTrigger())
            trigger->Reset();
    }
}

void Engine::PushDefaultActions()
{
    for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        Strategy* strategy = i->second;
        Event emptyEvent;
        MultiplyAndPush(strategy->getDefaultActions(), 0.0f, false, emptyEvent, "default");
    }
}

std::string const Engine::ListStrategies()
{
    std::string s = "Strategies: ";

    if (strategies.empty())
        return std::move(s);

    for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        s.append(i->first);
        s.append(", ");
    }

    return s.substr(0, s.length() - 2);
}

std::vector<std::string> Engine::GetStrategies()
{
    std::vector<std::string> result;
    for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
    {
        result.push_back(i->first);
    }

    return std::move(result);
}

void Engine::PushAgain(ActionNode* actionNode, float relevance, Event event)
{
    NextAction** nextAction = new NextAction*[2];
    nextAction[0] = new NextAction(actionNode->getName(), relevance);
    nextAction[1] = nullptr;
    MultiplyAndPush(nextAction, relevance, true, event, "again");
    delete actionNode;
}

bool Engine::ContainsStrategy(StrategyType type)
{
	for (std::map<std::string, Strategy*>::iterator i = strategies.begin(); i != strategies.end(); i++)
	{
		if (i->second->GetType() & type)
			return true;
	}
	return false;
}

Action* Engine::InitializeAction(ActionNode* actionNode)
{
    Action* action = actionNode->getAction();
    if (!action)
    {
        action = aiObjectContext->GetAction(actionNode->getName());
        actionNode->setAction(action);
    }

    return action;
}

bool Engine::ListenAndExecute(Action* action, Event event)
{
    bool actionExecuted = false;

    if (actionExecutionListeners.Before(action, event))
    {
        actionExecuted = actionExecutionListeners.AllowExecution(action, event) ? action->Execute(event) : true;
    }

    if (botAI->HasStrategy("debug", BOT_STATE_NON_COMBAT))
    {
        std::ostringstream out;
        out << "do: ";
        out << action->getName();

        if (actionExecuted)
            out << " 1 (";
        else
            out << " 0 (";

        out << action->getRelevance() << ")";

        if (!event.GetSource().empty())
            out << " [" << event.GetSource() << "]";

        botAI->TellMasterNoFacing(out);
    }

    actionExecuted = actionExecutionListeners.OverrideResult(action, actionExecuted, event);
    actionExecutionListeners.After(action, actionExecuted, event);
    return actionExecuted;
}

void Engine::LogAction(char const* format, ...)
{
    char buf[1024];

    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);

    lastAction += "|";
    lastAction += buf;
    if (lastAction.size() > 512)
    {
        lastAction = lastAction.substr(512);
        size_t pos = lastAction.find("|");
        lastAction = (pos == std::string::npos ? "" : lastAction.substr(pos));
    }

    if (testMode)
    {
        FILE* file = fopen("test.log", "a");
        fprintf(file, "'{}'", buf);
        fprintf(file, "\n");
        fclose(file);
    }
    else
    {
        Player* bot = botAI->GetBot();
        if (sPlayerbotAIConfig->logInGroupOnly && !bot->GetGroup())
            return;

        LOG_INFO("playerbots",  "{} {}", bot->GetName().c_str(), buf);
    }
}

void Engine::ChangeStrategy(std::string const names)
{
    std::vector<std::string> splitted = split(names, ',');
    for (std::vector<std::string>::iterator i = splitted.begin(); i != splitted.end(); i++)
    {
        char const* name = i->c_str();
        switch (name[0])
        {
            case '+':
                addStrategy(name+1);
                break;
            case '-':
                removeStrategy(name+1);
                break;
            case '~':
                toggleStrategy(name+1);
                break;
            case '?':
                botAI->TellMaster(ListStrategies());
                break;
        }
    }
}

void Engine::LogValues()
{
    if (testMode)
        return;

    Player* bot = botAI->GetBot();
    if (sPlayerbotAIConfig->logInGroupOnly && !bot->GetGroup())
        return;

    std::string const text = botAI->GetAiObjectContext()->FormatValues();
    LOG_DEBUG("playerbots",  "Values for {}: {}", bot->GetName().c_str(), text.c_str());
}
