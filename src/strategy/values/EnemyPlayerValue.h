/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_ENEMYPLAYERVALUE_H
#define _PLAYERBOT_ENEMYPLAYERVALUE_H

#include "TargetValue.h"
#include "PossibleTargetsValue.h"

class PlayerbotAI;
class Unit;

class NearestEnemyPlayersValue : public PossibleTargetsValue
{
    public:
        NearestEnemyPlayersValue(PlayerbotAI* botAI, float range = 120.0f) :
            PossibleTargetsValue(botAI, "nearest enemy players", range) { }

    public:
        bool AcceptUnit(Unit* unit) override;
};

class EnemyPlayerValue : public UnitCalculatedValue
{
    public:
        EnemyPlayerValue(PlayerbotAI* botAI, std::string const name = "enemy player") : UnitCalculatedValue(botAI, name) { }

        Unit* Calculate() override;

    private:
        float GetMaxAttackDistance();
};

#endif
