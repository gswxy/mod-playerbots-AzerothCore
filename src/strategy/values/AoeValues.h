/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_AOEVALUES_H
#define _PLAYERBOT_AOEVALUES_H

#include "Object.h"
#include "Value.h"

class PlayerbotAI;

class AoePositionValue : public CalculatedValue<WorldLocation>
{
	public:
        AoePositionValue(PlayerbotAI* botAI) : CalculatedValue<WorldLocation>(botAI, "aoe position") { }

        WorldLocation Calculate() override;
};

class AoeCountValue : public CalculatedValue<uint8>
{
	public:
        AoeCountValue(PlayerbotAI* botAI) : CalculatedValue<uint8>(botAI, "aoe count") { }

        uint8 Calculate() override;
};

#endif
