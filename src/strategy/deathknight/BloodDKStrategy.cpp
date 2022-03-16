/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "BloodDKStrategy.h"
#include "Playerbots.h"

class BloodDKStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        BloodDKStrategyActionNodeFactory()
        {
            //creators["melee"] = &melee;
		    //creators["blood strike"] = &blood_strike;
		    creators["rune strike"] = &rune_strike;
		    creators["heart strike"] = &heart_strike;
		    creators["death strike"] = &death_strike;
		    //creators["death grip"] = &death_grip;
		    //creators["plague strike"] = &plague_strike;
		    //creators["pestilence"] = &pestilence;
		    //creators["icy touch"] = &icy_touch;
		    //creators["obliterate"] = &obliterate;
		    //creators["blood boil"] = &blood_boil;
		    //creators["mark of_blood"] = &mark_of_blood;
		    //creators["blood presence"] = &blood_presence;
		    //creators["rune tap"] = &rune_tap;
		    //creators["vampiric blood"] = &vampiric_blood;
		    //creators["death pact"] = &death_pact;
		    //creators["death rune_mastery"] = &death_rune_mastery;
		    //creators["hysteria"] = &hysteria;
		    //creators["dancing weapon"] = &dancing_weapon;
		    //creators["dark command"] = &dark_command;
        }

    private:
	    static ActionNode* rune_strike(PlayerbotAI* botAI)
	    {
		    return new ActionNode("rune strike",
			    /*P*/ NextAction::array(0, new NextAction("frost presence"), nullptr),
			    /*A*/ NextAction::array(0, new NextAction("death coil"), nullptr),
			    /*C*/ nullptr);
	    }

	    static ActionNode* heart_strike(PlayerbotAI* botAI)
        {
            return new ActionNode ("heart strike",
                /*P*/ NextAction::array(0, new NextAction("frost presence"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("death strike"), nullptr),
                /*C*/ nullptr);
	    }

	    static ActionNode* death_strike(PlayerbotAI* botAI)
	    {
		    return new ActionNode("death strike",
			    /*P*/ NextAction::array(0, new NextAction("frost presence"), nullptr),
			    /*A*/ nullptr,
			    /*C*/ nullptr);
	    }
};

BloodDKStrategy::BloodDKStrategy(PlayerbotAI* botAI) : GenericDKStrategy(botAI)
{
    actionNodeFactories.Add(new BloodDKStrategyActionNodeFactory());
}

NextAction** BloodDKStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("melee", ACTION_NORMAL + 2), new NextAction("heart strike", ACTION_NORMAL + 5),
        new NextAction("death strike", ACTION_NORMAL + 4), new NextAction("rune strike", ACTION_NORMAL + 3), nullptr);
}

void BloodDKStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericDKStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode("rune strike", NextAction::array(0, new NextAction("rune strike", ACTION_NORMAL + 3), nullptr)));
    triggers.push_back(new TriggerNode("blood tap", NextAction::array(0, new NextAction("blood tap", ACTION_HIGH + 5), nullptr)));
    triggers.push_back(new TriggerNode("lose aggro", NextAction::array(0, new NextAction("dark command", ACTION_HIGH + 3), nullptr)));
    triggers.push_back(new TriggerNode("low health", NextAction::array(0, new NextAction("blood tap", ACTION_HIGH + 5),
        new NextAction("vampiric blood", ACTION_HIGH + 3), new NextAction("death strike", ACTION_HIGH + 4), nullptr)));
}
