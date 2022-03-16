/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "StayActions.h"
#include "Event.h"
#include "LastMovementValue.h"
#include "Playerbots.h"

bool StayActionBase::Stay()
{
    AI_VALUE(LastMovement&, "last movement").Set(nullptr);

    //if (!urand(0, 10))
        //botAI->PlaySound(TEXT_EMOTE_YAWN);

    if (bot->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE || bot->IsFlying())
        return false;

    uint32 sitDelay = sPlayerbotAIConfig->sitDelay / 1000;
    time_t stayTime = AI_VALUE(time_t, "stay time");
    time_t now = time(nullptr);
    if (!stayTime)
    {
        stayTime = now - urand(0, sitDelay / 2);
        context->GetValue<time_t>("stay time")->Set(stayTime);
    }

    if (!bot->isMoving())
        return false;

    bot->StopMoving();
	bot->ClearUnitState(UNIT_STATE_CHASE);
	bot->ClearUnitState(UNIT_STATE_FOLLOW);

    return true;
}

bool StayAction::Execute(Event event)
{
    return Stay();
}

bool StayAction::isUseful()
{
    return !AI_VALUE2(bool, "moving", "self target");
}

bool SitAction::Execute(Event event)
{
    if (bot->isMoving())
        return false;

    bot->SetStandState(UNIT_STAND_STATE_SIT);
    return true;
}

bool SitAction::isUseful()
{
    return !AI_VALUE2(bool, "moving", "self target");
}
