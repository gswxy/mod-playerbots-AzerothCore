/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "IsFacingValue.h"
#include "Playerbots.h"

bool IsFacingValue::Calculate()
{
    Unit* target = AI_VALUE(Unit*, qualifier);
    if (!target)
        return false;

    return bot->HasInArc(CAST_ANGLE_IN_FRONT, target, sPlayerbotAIConfig->sightDistance);
}
