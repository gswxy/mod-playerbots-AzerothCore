/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ShamanTriggers.h"
#include "Playerbots.h"

std::vector<std::string> ShamanWeaponTrigger::spells;

bool ShamanWeaponTrigger::IsActive()
{
    if (spells.empty())
    {
        spells.push_back("frostbrand weapon");
        spells.push_back("rockbiter weapon");
        spells.push_back("flametongue weapon");
        spells.push_back("earthliving weapon");
        spells.push_back("windfury weapon");
    }

    for (std::vector<std::string>::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
        if (!spellId)
            continue;

        if (AI_VALUE2(Item*, "item for spell", spellId))
            return true;
    }

    return false;
}

bool ShockTrigger::IsActive()
{
    return SpellTrigger::IsActive() && !botAI->HasAnyAuraOf(GetTarget(), "frost shock", "earth shock", "flame shock", nullptr);
}

bool TotemTrigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") >= attackerCount && !AI_VALUE2(bool, "has totem", name);
}

bool ManaSpringTotemTrigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") >= attackerCount && !AI_VALUE2(bool, "has totem", "mana tide totem") && !AI_VALUE2(bool, "has totem", name);
}

bool WaterWalkingTrigger::IsActive()
{
    return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
}

bool WaterBreathingTrigger::IsActive()
{
    return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
}

bool WaterWalkingOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
}

bool WaterBreathingOnPartyTrigger::IsActive()
{
    return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
}
