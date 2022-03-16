/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AiObjectContext.h"
#include "StrategyContext.h"
#include "ActionContext.h"
#include "ChatActionContext.h"
#include "WorldPacketActionContext.h"
#include "ChatTriggerContext.h"
#include "TriggerContext.h"
#include "SharedValueContext.h"
#include "WorldPacketTriggerContext.h"
#include "ValueContext.h"
#include "Playerbots.h"

AiObjectContext::AiObjectContext(PlayerbotAI* botAI) : PlayerbotAIAware(botAI)
{
    strategyContexts.Add(new StrategyContext());
    strategyContexts.Add(new MovementStrategyContext());
    strategyContexts.Add(new AssistStrategyContext());
    strategyContexts.Add(new QuestStrategyContext());

    actionContexts.Add(new ActionContext());
    actionContexts.Add(new ChatActionContext());
    actionContexts.Add(new WorldPacketActionContext());

    triggerContexts.Add(new TriggerContext());
    triggerContexts.Add(new ChatTriggerContext());
    triggerContexts.Add(new WorldPacketTriggerContext());

    valueContexts.Add(new ValueContext());

    valueContexts.Add(sSharedValueContext);
}

void AiObjectContext::Update()
{
    strategyContexts.Update();
    triggerContexts.Update();
    actionContexts.Update();
    valueContexts.Update();
}

void AiObjectContext::Reset()
{
    strategyContexts.Reset();
    triggerContexts.Reset();
    actionContexts.Reset();
    valueContexts.Reset();
}

std::vector<std::string> AiObjectContext::Save()
{
    std::vector<std::string> result;

    std::set<std::string> names = valueContexts.GetCreated();
    for (std::set<std::string>::iterator i = names.begin(); i != names.end(); ++i)
    {
        UntypedValue* value = GetUntypedValue(*i);
        if (!value)
            continue;

        std::string const data = value->Save();
        if (data == "?")
            continue;

        std::string const name = *i;
        std::ostringstream out;
        out << name;

        out << ">" << data;
        result.push_back(out.str());
    }

    return std::move(result);
}

void AiObjectContext::Load(std::vector<std::string> data)
{
    for (std::vector<std::string>::iterator i = data.begin(); i != data.end(); ++i)
    {
        std::string const row = *i;
        std::vector<std::string> parts = split(row, '>');
        if (parts.size() != 2)
            continue;

        std::string const name = parts[0];
        std::string const text = parts[1];

        UntypedValue* value = GetUntypedValue(name);
        if (!value)
            continue;

        value->Load(text);
    }
}

Strategy* AiObjectContext::GetStrategy(std::string const name)
{
    return strategyContexts.GetContextObject(name, botAI);
}

std::set<std::string> AiObjectContext::GetSiblingStrategy(std::string const name)
{
    return strategyContexts.GetSiblings(name);
}

Trigger* AiObjectContext::GetTrigger(std::string const name)
{
    return triggerContexts.GetContextObject(name, botAI);
}

Action* AiObjectContext::GetAction(std::string const name)
{
    return actionContexts.GetContextObject(name, botAI);
}

UntypedValue* AiObjectContext::GetUntypedValue(std::string const name)
{
    return valueContexts.GetContextObject(name, botAI);
}

std::set<std::string> AiObjectContext::GetValues()
{
    return valueContexts.GetCreated();
}

std::set<std::string> AiObjectContext::GetSupportedStrategies()
{
    return strategyContexts.supports();
}

std::set<std::string> AiObjectContext::GetSupportedActions()
{
    return actionContexts.supports();
}

std::string const AiObjectContext::FormatValues()
{
    std::ostringstream out;
    std::set<std::string> names = valueContexts.GetCreated();
    for (std::set<std::string>::iterator i = names.begin(); i != names.end(); ++i, out << "|")
    {
        UntypedValue* value = GetUntypedValue(*i);
        if (!value)
            continue;

        std::string const text = value->Format();
        if (text == "?")
            continue;

        out << "{" << *i << "=" << text << "}";
    }

    return out.str();
}

void AiObjectContext::AddShared(NamedObjectContext<UntypedValue>* sharedValues)
{
    valueContexts.Add(sharedValues);
}
