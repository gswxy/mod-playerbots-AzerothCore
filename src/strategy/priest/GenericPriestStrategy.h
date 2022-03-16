/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_GENERICPRIESTSTRATEGY_H
#define _PLAYERBOT_GENERICPRIESTSTRATEGY_H

#include "CombatStrategy.h"

class PlayerbotAI;

class GenericPriestStrategy : public CombatStrategy
{
    public:
        GenericPriestStrategy(PlayerbotAI* botAI);

        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class PriestCureStrategy : public Strategy
{
    public:
        PriestCureStrategy(PlayerbotAI* botAI);

        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const getName() override { return "cure"; }
};

class PriestBoostStrategy : public Strategy
{
    public:
        PriestBoostStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const getName() override { return "boost"; }
};

class PriestCcStrategy : public Strategy
{
    public:
        PriestCcStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

        void InitTriggers(std::vector<TriggerNode*>& triggers) override;
        std::string const getName() override { return "cc"; }
};

#endif
