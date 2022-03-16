/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_ATTACKERWITHOUTAURATARGETVALUE_H
#define _PLAYERBOT_ATTACKERWITHOUTAURATARGETVALUE_H

#include "NamedObjectContext.h"
#include "Value.h"

class PlayerbotAI;
class Unit;

class AttackerWithoutAuraTargetValue : public UnitCalculatedValue, public Qualified
{
	public:
        AttackerWithoutAuraTargetValue(PlayerbotAI* botAI) : UnitCalculatedValue(botAI, "attacker without aura") { }

    protected:
        Unit* Calculate() override;
};

#endif
