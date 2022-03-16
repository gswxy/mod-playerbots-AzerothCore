/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_STRATEGY_H
#define _PLAYERBOT_STRATEGY_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "Multiplier.h"
#include "Trigger.h"
#include "PlayerbotAIAware.h"

enum StrategyType : uint32
{
	STRATEGY_TYPE_GENERIC   = 0,
	STRATEGY_TYPE_COMBAT    = 1,
	STRATEGY_TYPE_NONCOMBAT = 2,
	STRATEGY_TYPE_TANK      = 4,
	STRATEGY_TYPE_DPS       = 8,
	STRATEGY_TYPE_HEAL      = 16,
	STRATEGY_TYPE_RANGED    = 32,
	STRATEGY_TYPE_MELEE     = 64
};

enum ActionPriority
{
	ACTION_IDLE             = 0,
	ACTION_NORMAL           = 10,
	ACTION_HIGH             = 20,
	ACTION_MOVE             = 30,
	ACTION_INTERRUPT        = 40,
	ACTION_DISPEL           = 50,
	ACTION_LIGHT_HEAL       = 60,
	ACTION_MEDIUM_HEAL      = 70,
	ACTION_CRITICAL_HEAL    = 80,
	ACTION_EMERGENCY        = 90
};

class Strategy : public PlayerbotAIAware
{
    public:
        Strategy(PlayerbotAI* botAI);
        virtual ~Strategy() { }

        virtual NextAction** getDefaultActions() { return nullptr; }
        virtual void InitTriggers(std::vector<TriggerNode*> &triggers) { }
        virtual void InitMultipliers(std::vector<Multiplier*> &multipliers) { }
        virtual std::string const getName() = 0;
		virtual uint32 GetType() const { return STRATEGY_TYPE_GENERIC; }
        virtual ActionNode* GetAction(std::string const name);
        void Update() { }
        void Reset() { }

    protected:
        NamedObjectFactoryList<ActionNode> actionNodeFactories;
};

#endif
