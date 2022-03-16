/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericHunterStrategy.h"
#include "Playerbots.h"

class GenericHunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        GenericHunterStrategyActionNodeFactory()
        {
            creators["rapid fire"] = &rapid_fire;
            creators["boost"] = &rapid_fire;
            creators["aspect of the pack"] = &aspect_of_the_pack;
            creators["feign death"] = &feign_death;
            creators["wing clip"] = &wing_clip;
            creators["raptor strike"] = &raptor_strike;
        }

    private:
        static ActionNode* rapid_fire(PlayerbotAI* botAI)
        {
            return new ActionNode ("rapid fire",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("readiness"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* aspect_of_the_pack(PlayerbotAI* botAI)
        {
            return new ActionNode ("aspect of the pack",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* feign_death(PlayerbotAI* botAI)
        {
            return new ActionNode ("feign death",
                /*P*/ nullptr,
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* wing_clip(PlayerbotAI* botAI)
        {
            return new ActionNode("wing clip",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("raptor strike"), nullptr),
                /*C*/ NextAction::array(0, new NextAction("flee"), nullptr));
        }

        static ActionNode* raptor_strike(PlayerbotAI* botAI)
        {
            return new ActionNode("raptor strike",
                /*P*/ NextAction::array(0, new NextAction("melee"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }
};

GenericHunterStrategy::GenericHunterStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
    actionNodeFactories.Add(new GenericHunterStrategyActionNodeFactory());
}

void GenericHunterStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("enemy is close", NextAction::array(0, new NextAction("wing clip", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode("medium threat", NextAction::array(0, new NextAction("feign death", 35.0f), nullptr)));
    triggers.push_back(new TriggerNode("hunters pet low health", NextAction::array(0, new NextAction("mend pet", ACTION_HIGH + 2), nullptr)));
    triggers.push_back(new TriggerNode("switch to melee", NextAction::array(0, new NextAction("switch to melee", ACTION_HIGH + 1), nullptr)));
    triggers.push_back(new TriggerNode("switch to ranged", NextAction::array(0, new NextAction("switch to ranged", ACTION_HIGH), nullptr)));
    triggers.push_back(new TriggerNode("no ammo", NextAction::array(0, new NextAction("switch to melee", ACTION_HIGH + 1), new NextAction("say::no ammo", ACTION_HIGH), nullptr)));
}

NextAction** HunterBoostStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("bestial wrath", 15.0f), nullptr);
}

void HunterBoostStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("rapid fire", NextAction::array(0, new NextAction("rapid fire", 16.0f), nullptr)));
}

void HunterCcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("scare beast", NextAction::array(0, new NextAction("scare beast on cc", ACTION_HIGH + 3), nullptr)));
    triggers.push_back(new TriggerNode("freezing trap", NextAction::array(0, new NextAction("freezing trap on cc", ACTION_HIGH + 3), nullptr)));
}
