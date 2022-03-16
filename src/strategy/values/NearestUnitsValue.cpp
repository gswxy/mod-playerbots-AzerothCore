/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NearestUnitsValue.h"
#include "Playerbots.h"

GuidVector NearestUnitsValue::Calculate()
{
    std::list<Unit*> targets;
    FindUnits(targets);

    GuidVector results;
    for (Unit* unit : targets)
    {
        if ((ignoreLos || bot->IsWithinLOSInMap(unit)) && AcceptUnit(unit))
            results.push_back(unit->GetGUID());
    }

    return results;
}
