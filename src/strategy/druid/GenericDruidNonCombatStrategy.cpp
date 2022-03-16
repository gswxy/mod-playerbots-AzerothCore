/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericDruidNonCombatStrategy.h"
#include "Playerbots.h"

class GenericDruidNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        GenericDruidNonCombatStrategyActionNodeFactory()
        {
            creators["thorns"] = &thorns;
            creators["thorns on party"] = &thorns_on_party;
            creators["mark of the wild"] = &mark_of_the_wild;
            creators["mark of the wild on party"] = &mark_of_the_wild_on_party;
            creators["innervate"] = &innervate;
        }

    private:
        static ActionNode* thorns(PlayerbotAI* botAI)
        {
            return new ActionNode("thorns",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* thorns_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode("thorns on party",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* mark_of_the_wild(PlayerbotAI* botAI)
        {
            return new ActionNode ("mark of the wild",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* mark_of_the_wild_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("mark of the wild on party",
                /*P*/ NextAction::array(0, new NextAction("caster form"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* innervate(PlayerbotAI* botAI)
        {
            return new ActionNode ("innervate",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("drink"), nullptr),
                /*C*/ nullptr);
        }
};

GenericDruidNonCombatStrategy::GenericDruidNonCombatStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericDruidNonCombatStrategyActionNodeFactory());
}

void GenericDruidNonCombatStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("mark of the wild", NextAction::array(0, new NextAction("mark of the wild", 14.0f), nullptr)));
    triggers.push_back(new TriggerNode("thorns", NextAction::array(0, new NextAction("thorns", 12.0f), nullptr)));
    triggers.push_back(new TriggerNode("cure poison", NextAction::array(0, new NextAction("abolish poison", 21.0f), nullptr)));
    triggers.push_back(new TriggerNode("party member cure poison", NextAction::array(0, new NextAction("abolish poison on party", 20.0f), nullptr)));
	triggers.push_back(new TriggerNode("party member dead", NextAction::array(0, new NextAction("revive", 22.0f), nullptr)));
    triggers.push_back(new TriggerNode("low mana", NextAction::array(0, new NextAction("innervate", ACTION_EMERGENCY + 5), nullptr)));
    triggers.push_back(new TriggerNode("swimming", NextAction::array(0, new NextAction("aquatic form", 1.0f), nullptr)));
    triggers.push_back(new TriggerNode("often", NextAction::array(0, new NextAction("apply oil", 1.0f), nullptr)));
}

GenericDruidBuffStrategy::GenericDruidBuffStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericDruidNonCombatStrategyActionNodeFactory());
}

void GenericDruidBuffStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("mark of the wild on party", NextAction::array(0, new NextAction("mark of the wild on party", 13.0f), nullptr)));
    triggers.push_back(new TriggerNode("thorns on party", NextAction::array(0, new NextAction("thorns on party", 11.0f), nullptr)));
}
