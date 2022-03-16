/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PlayerbotAIBase.h"
#include "Playerbots.h"

PlayerbotAIBase::PlayerbotAIBase(bool isBotAI) : nextAICheckDelay(0), _isBotAI(isBotAI)
{
}

void PlayerbotAIBase::UpdateAI(uint32 elapsed, bool minimal)
{
    if (nextAICheckDelay > elapsed)
        nextAICheckDelay -= elapsed;
    else
        nextAICheckDelay = 0;

    if (!CanUpdateAI())
        return;

    UpdateAIInternal(elapsed, minimal);
    YieldThread();
}

void PlayerbotAIBase::SetNextCheckDelay(uint32 const delay)
{
    if (nextAICheckDelay < delay)
        LOG_DEBUG("playerbots", "Setting lesser delay {} -> {}", nextAICheckDelay, delay);

    nextAICheckDelay = delay;

    if (nextAICheckDelay > sPlayerbotAIConfig->globalCoolDown)
        LOG_DEBUG("playerbots",  "std::set next check delay: {}", nextAICheckDelay);
}

void PlayerbotAIBase::IncreaseNextCheckDelay(uint32 delay)
{
    nextAICheckDelay += delay;

    if (nextAICheckDelay > sPlayerbotAIConfig->globalCoolDown)
        LOG_DEBUG("playerbots",  "increase next check delay: {}", nextAICheckDelay);
}

bool PlayerbotAIBase::CanUpdateAI()
{
    return nextAICheckDelay < 100;
}

void PlayerbotAIBase::YieldThread(bool delay)
{
    if (nextAICheckDelay < sPlayerbotAIConfig->reactDelay)
        nextAICheckDelay = sPlayerbotAIConfig->reactDelay;

    if (delay && nextAICheckDelay <= sPlayerbotAIConfig->reactDelay * 5)
        nextAICheckDelay = sPlayerbotAIConfig->reactDelay * 5;
}

bool PlayerbotAIBase::IsActive()
{
    return nextAICheckDelay < sPlayerbotAIConfig->maxWaitForMove;
}

bool PlayerbotAIBase::IsBotAI() const
{
    return _isBotAI;
}
