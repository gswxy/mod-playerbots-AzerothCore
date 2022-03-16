/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_CONSERVEMANASTRATEGY_H
#define _PLAYERBOT_CONSERVEMANASTRATEGY_H

#include "Strategy.h"

class PlayerbotAI;

class ConserveManaMultiplier : public Multiplier
{
    public:
        ConserveManaMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "conserve mana") { }

        float GetValue(Action* action) override;
};

class SaveManaMultiplier : public Multiplier
{
    public:
        SaveManaMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "save mana") { }

        float GetValue(Action* action) override;
};

class ConserveManaStrategy : public Strategy
{
    public:
        ConserveManaStrategy(PlayerbotAI* botAI) : Strategy(botAI) { }

        void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
        std::string const getName() override { return "conserve mana"; }
};

#endif
