/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_NEARESTNPCSVALUE_H
#define _PLAYERBOT_NEARESTNPCSVALUE_H

#include "NearestUnitsValue.h"
#include "PlayerbotAIConfig.h"

class PlayerbotAI;

class NearestNpcsValue : public NearestUnitsValue
{
	public:
        NearestNpcsValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) : NearestUnitsValue(botAI, "nearest npcs", range) { }

    protected:
        void FindUnits(std::list<Unit*>& targets) override;
        bool AcceptUnit(Unit* unit) override;
};

class NearestVehiclesValue : public NearestUnitsValue
{
    public:
        NearestVehiclesValue(PlayerbotAI* botAI, float range = sPlayerbotAIConfig->sightDistance) : NearestUnitsValue(botAI, "nearest vehicles", range) { }

    protected:
        void FindUnits(std::list<Unit*>& targets) override;
        bool AcceptUnit(Unit* unit) override;
};

#endif
