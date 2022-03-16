/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"
#include "PerformanceMonitor.h"
#include "Playerbots.h"

UnitCalculatedValue::UnitCalculatedValue(PlayerbotAI* botAI, std::string const name, int32 checkInterval) : CalculatedValue<Unit*>(botAI, name, checkInterval)
{
    lastCheckTime = time(nullptr) - checkInterval / 2;
}

std::string const UnitCalculatedValue::Format()
{
    Unit* unit = Calculate();
    return unit ? unit->GetName() : "<none>";
}

std::string const UnitManualSetValue::Format()
{
    Unit* unit = Get();
    return unit ? unit->GetName() : "<none>";
}

std::string const Uint8CalculatedValue::Format()
{
    std::ostringstream out;
    out << Calculate();
    return out.str();
}

std::string const Uint32CalculatedValue::Format()
{
    std::ostringstream out;
    out << Calculate();
    return out.str();
}

std::string const FloatCalculatedValue::Format()
{
    std::ostringstream out;
    out << Calculate();
    return out.str();
}

CDPairCalculatedValue::CDPairCalculatedValue(PlayerbotAI* botAI, std::string const name, int32 checkInterval) :
    CalculatedValue<CreatureData const*>(botAI, name, checkInterval)
{
    lastCheckTime = time(nullptr) - checkInterval / 2;
}

std::string const CDPairCalculatedValue::Format()
{
    CreatureData const* creatureData = Calculate();
    CreatureTemplate const* bmTemplate = sObjectMgr->GetCreatureTemplate(creatureData->id1);
    return bmTemplate ? bmTemplate->Name : "<none>";
}

CDPairListCalculatedValue::CDPairListCalculatedValue(PlayerbotAI* botAI, std::string const name, int32 checkInterval) :
    CalculatedValue<std::vector<CreatureData const*>>(botAI, name, checkInterval)
{
    lastCheckTime = time(nullptr) - checkInterval / 2;
}

std::string const CDPairListCalculatedValue::Format()
{
    std::ostringstream out; out << "{";
    std::vector<CreatureData const*> cdPairs = Calculate();
    for (CreatureData const* cdPair : cdPairs)
    {
        out << cdPair->id1 << ",";
    }

    out << "}";
    return out.str();
}

ObjectGuidCalculatedValue::ObjectGuidCalculatedValue(PlayerbotAI* botAI, std::string const name, int32 checkInterval) :
    CalculatedValue<ObjectGuid>(botAI, name, checkInterval)
{
    lastCheckTime = time(nullptr) - checkInterval / 2;
}

std::string const ObjectGuidCalculatedValue::Format()
{
    ObjectGuid guid = Calculate();
    return guid ? std::to_string(guid.GetRawValue()) : "<none>";
}

ObjectGuidListCalculatedValue::ObjectGuidListCalculatedValue(PlayerbotAI* botAI, std::string const name, int32 checkInterval) :
    CalculatedValue<GuidVector>(botAI, name, checkInterval)
{
    lastCheckTime = time(nullptr) - checkInterval / 2;
}

std::string const ObjectGuidListCalculatedValue::Format()
{
    std::ostringstream out;
    out << "{";

    GuidVector guids = Calculate();
    for (GuidVector::iterator i = guids.begin(); i != guids.end(); ++i)
    {
        ObjectGuid guid = *i;
        out << guid.GetRawValue() << ",";
    }
    out << "}";

    return out.str();
}
