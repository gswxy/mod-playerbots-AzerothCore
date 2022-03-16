/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "LastMovementValue.h"
#include "Playerbots.h"

LastMovement::LastMovement()
{
    clear();
}

LastMovement::LastMovement(LastMovement& other) : taxiNodes(other.taxiNodes), taxiMaster(other.taxiMaster), lastFollow(other.lastFollow), lastAreaTrigger(other.lastAreaTrigger),
lastMoveToX(other.lastMoveToX), lastMoveToY(other.lastMoveToY), lastMoveToZ(other.lastMoveToZ), lastMoveToOri(other.lastMoveToOri), lastFlee(other.lastFlee)
{
    lastMoveShort = other.lastMoveShort;
    nextTeleport = other.nextTeleport;
    lastPath = other.lastPath;
}

void LastMovement::clear()
{
    lastMoveShort = WorldPosition();
    lastPath.clear();
    lastMoveToMapId = 0;
    lastMoveToX = 0;
    lastMoveToY = 0;
    lastMoveToZ = 0;
    lastMoveToOri = 0;
    lastFollow = nullptr;
    lastAreaTrigger = 0;
    lastFlee = 0;
    nextTeleport = 0;
}

void LastMovement::Set(Unit* follow)
{
    Set(0, 0.0f, 0.0f, 0.0f, 0.0f);
    setShort(WorldPosition());
    setPath(TravelPath());
    lastFollow = follow;
}

void LastMovement::Set(uint32 mapId, float x, float y, float z, float ori)
{
    lastMoveToMapId = mapId;
    lastMoveToX = x;
    lastMoveToY = y;
    lastMoveToZ = z;
    lastMoveToOri = ori;
    lastFollow = nullptr;
    lastMoveShort = WorldPosition(mapId, x, y, z, ori);
}

void LastMovement::setShort(WorldPosition point)
{
    lastMoveShort = point; lastFollow = nullptr;
}

void LastMovement::setPath(TravelPath path)
{
    lastPath = path;
}
