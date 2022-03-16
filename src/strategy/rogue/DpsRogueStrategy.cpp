/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DpsRogueStrategy.h"
#include "Playerbots.h"

class DpsRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        DpsRogueStrategyActionNodeFactory()
        {
            creators["riposte"] = &riposte;
            creators["mutilate"] = &mutilate;
            creators["sinister strike"] = &sinister_strike;
            creators["kick"] = &kick;
            creators["kidney shot"] = &kidney_shot;
            creators["rupture"] = &rupture;
            creators["backstab"] = &backstab;
        }

    private:
        static ActionNode* riposte(PlayerbotAI* botAI)
        {
            return new ActionNode ("riposte",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("mutilate"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* mutilate(PlayerbotAI* botAI)
        {
            return new ActionNode ("mutilate",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("sinister strike"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* sinister_strike(PlayerbotAI* botAI)
        {
            return new ActionNode ("sinister strike",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("melee"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* kick(PlayerbotAI* botAI)
        {
            return new ActionNode ("kick",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("kidney shot"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* kidney_shot(PlayerbotAI* botAI)
        {
            return new ActionNode ("kidney shot",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* rupture(PlayerbotAI* botAI)
        {
            return new ActionNode ("rupture",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("eviscerate"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* backstab(PlayerbotAI* botAI)
        {
            return new ActionNode ("backstab",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }
};

DpsRogueStrategy::DpsRogueStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
    actionNodeFactories.Add(new DpsRogueStrategyActionNodeFactory());
}

NextAction** DpsRogueStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("riposte", ACTION_NORMAL), nullptr);
}

void DpsRogueStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("combo points available", NextAction::array(0, new NextAction("rupture", ACTION_HIGH + 2), nullptr)));
	triggers.push_back(new TriggerNode("medium threat", NextAction::array(0, new NextAction("feint", ACTION_HIGH), nullptr)));
	triggers.push_back(new TriggerNode("low health", NextAction::array(0, new NextAction("evasion", ACTION_EMERGENCY), new NextAction("feint", ACTION_EMERGENCY), nullptr)));
    triggers.push_back(new TriggerNode("critical health", NextAction::array(0, new NextAction("blind", ACTION_EMERGENCY), new NextAction("vanish", ACTION_EMERGENCY), nullptr)));
	triggers.push_back(new TriggerNode("kick", NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 2), nullptr)));
	triggers.push_back(new TriggerNode("kick on enemy healer", NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 1), nullptr)));
    triggers.push_back(new TriggerNode("behind target", NextAction::array(0, new NextAction("backstab", ACTION_HIGH + 1), nullptr)));
    triggers.push_back(new TriggerNode("player has flag", NextAction::array(0, new NextAction("sprint", ACTION_EMERGENCY + 2), nullptr)));
    triggers.push_back(new TriggerNode("enemy flagcarrier near", NextAction::array(0, new NextAction("sprint", ACTION_EMERGENCY + 1), nullptr)));
    triggers.push_back(new TriggerNode("in stealth", NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), nullptr)));
    triggers.push_back(new TriggerNode("unstealth", NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), nullptr)));
    triggers.push_back(new TriggerNode("sprint", NextAction::array(0, new NextAction("sprint", ACTION_INTERRUPT), nullptr)));
}

class StealthedRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        StealthedRogueStrategyActionNodeFactory()
        {
            creators["ambush"] = &ambush;
            creators["cheap shot"] = &cheap_shot;
            creators["garrote"] = &garrote;
            creators["sap"] = &sap;
            creators["sinister strike"] = &sinister_strike;
        }

    private:
        static ActionNode* ambush(PlayerbotAI* botAI)
        {
            return new ActionNode("ambush",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("garrote"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* cheap_shot(PlayerbotAI* botAI)
        {
            return new ActionNode("cheap shot",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* garrote(PlayerbotAI* botAI)
        {
            return new ActionNode("garrote",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* sap(PlayerbotAI* botAI)
        {
            return new ActionNode("sap",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* sinister_strike(PlayerbotAI* botAI)
        {
            return new ActionNode("sinister strike",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("cheap shot"), nullptr),
                /*C*/ nullptr);
        }
};

StealthedRogueStrategy::StealthedRogueStrategy(PlayerbotAI* botAI) : Strategy(botAI)
{
    actionNodeFactories.Add(new StealthedRogueStrategyActionNodeFactory());
}

NextAction** StealthedRogueStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("ambush", ACTION_NORMAL + 4), new NextAction("backstab", ACTION_NORMAL + 3), new NextAction("cheap shot", ACTION_NORMAL + 2),
        new NextAction("sinister strike", ACTION_NORMAL + 1),  new NextAction("melee", ACTION_NORMAL), nullptr);
}

void StealthedRogueStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("combo points available", NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode("kick", NextAction::array(0, new NextAction("cheap shot", ACTION_INTERRUPT), nullptr)));
    triggers.push_back(new TriggerNode("kick on enemy healer", NextAction::array(0, new NextAction("cheap shot", ACTION_INTERRUPT), nullptr)));
    triggers.push_back(new TriggerNode("behind target", NextAction::array(0, new NextAction("ambush", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode("not behind target", NextAction::array(0, new NextAction("cheap shot", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode("enemy flagcarrier near", NextAction::array(0, new NextAction("sprint", ACTION_EMERGENCY + 1), nullptr)));
    triggers.push_back(new TriggerNode("unstealth", NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), nullptr)));
    /*triggers.push_back(new TriggerNode("low health", NextAction::array(0, new NextAction("food", ACTION_EMERGENCY + 1), nullptr)));*/
    triggers.push_back(new TriggerNode("no stealth", NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), nullptr)));
    triggers.push_back(new TriggerNode("sprint", NextAction::array(0, new NextAction("sprint", ACTION_INTERRUPT), nullptr)));
}

void StealthStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("stealth", NextAction::array(0, new NextAction("stealth", ACTION_INTERRUPT), nullptr)));
}

void RogueAoeStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("light aoe", NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH), nullptr)));
}

void RogueBoostStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("adrenaline rush", NextAction::array(0, new NextAction("adrenaline rush", ACTION_HIGH + 2), nullptr)));
}

void RogueCcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("sap", NextAction::array(0, new NextAction("stealth", ACTION_INTERRUPT), new NextAction("sap", ACTION_INTERRUPT), nullptr)));
}
