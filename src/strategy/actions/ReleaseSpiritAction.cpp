/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ReleaseSpiritAction.h"
#include "Event.h"
#include "GameGraveyard.h"
#include "Playerbots.h"
#include "ServerFacade.h"

bool ReleaseSpiritAction::Execute(Event event)
{
    if (bot->IsAlive())
    {
        botAI->TellMasterNoFacing("I am not dead, will wait here");
        botAI->ChangeStrategy("-follow,+stay", BOT_STATE_NON_COMBAT);
        return false;
    }

    if (bot->GetCorpse() && bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
    {
        botAI->TellMasterNoFacing("I am already a spirit");
        return false;
    }

    WorldPacket& p = event.getPacket();
    if (!p.empty() && p.GetOpcode() == CMSG_REPOP_REQUEST)
        botAI->TellMasterNoFacing("Releasing...");
    else
        botAI->TellMasterNoFacing("Meet me at the graveyard");

    // Death Count to prevent skeleton piles
    Player* master = GetMaster();
    if (!master || (master && GET_PLAYERBOT_AI(master)))
    {
        uint32 dCount = AI_VALUE(uint32, "death count");
        context->GetValue<uint32>("death count")->Set(dCount + 1);
    }

    LOG_INFO("playerbots", "Bot {} {}:{} <{}> released", bot->GetGUID().ToString().c_str(), bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str());

    WorldPacket packet(CMSG_REPOP_REQUEST);
    packet << uint8(0);
    bot->GetSession()->HandleRepopRequestOpcode(packet);

    // add waiting for ress aura
    if (bot->InBattleground() && !botAI->HasAura(2584, bot))
    {
        // cast Waiting for Resurrect
        bot->CastSpell(bot, 2584, true);
    }

    // add waiting for ress aura
    if (bot->InBattleground())
        bot->CastSpell(bot, 2584, true);

    return true;
}

bool AutoReleaseSpiritAction::Execute(Event event)
{
    //Death Count to prevent skeleton piles
    Player* master = GetMaster();
    if (!master || (master && GET_PLAYERBOT_AI(master)))
    {
        uint32 dCount = AI_VALUE(uint32, "death count");
        context->GetValue<uint32>("death count")->Set(dCount + 1);
    }

    LOG_INFO("playerbots", "Bot {} {}:{} <{}> auto released", bot->GetGUID().ToString().c_str(), bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str());

    WorldPacket packet(CMSG_REPOP_REQUEST);
    packet << uint8(0);
    bot->GetSession()->HandleRepopRequestOpcode(packet);

    LOG_INFO("playerbots", "Bot {} {}:{} <{}> releases spirit", bot->GetGUID().ToString().c_str(), bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str());

    if (bot->InBattleground() && !botAI->HasAura(2584, bot))
    {
        // cast Waiting for Resurrect
        bot->CastSpell(bot, 2584, true);
    }

    return true;
}

bool AutoReleaseSpiritAction::isUseful()
{
    if (!bot->isDead())
        return false;

    if (bot->InArena())
        return false;

    if (bot->InBattleground())
        return !bot->GetCorpse();

    if (bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        return false;

    if (!bot->GetGroup())
        return true;

    if (!botAI->GetGroupMaster())
        return true;

    if (botAI->GetGroupMaster() == bot)
        return true;

    if (!botAI->HasActivePlayerMaster())
        return true;

    if (botAI->HasActivePlayerMaster() && botAI->GetGroupMaster()->GetMapId() == bot->GetMapId() && bot->GetMap() && (bot->GetMap()->IsRaid() || bot->GetMap()->IsDungeon()))
        return false;

    if (botAI->GetGroupMaster()->isDead())
        return true;

    if (sServerFacade->IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig->sightDistance))
        return true;

    return false;
}

bool RepopAction::Execute(Event event)
{
    LOG_INFO("playerbots", "Bot {} {}:{} <{}> repops at graveyard", bot->GetGUID().ToString().c_str(), bot->GetTeamId() == TEAM_ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName().c_str());

    int64 deadTime;

    Corpse* corpse = bot->GetCorpse();
    if (corpse)
        deadTime = time(nullptr) - corpse->GetGhostTime();
    else if (bot->isDead())
        deadTime = 0;
    else
        deadTime = 60 * MINUTE;

    uint32 dCount = AI_VALUE(uint32, "death count");

    GraveyardStruct const* ClosestGrave = GetGrave(dCount > 10 || deadTime > 30 * MINUTE);
    if (!ClosestGrave)
        return false;

    bot->TeleportTo(ClosestGrave->Map, ClosestGrave->x, ClosestGrave->y, ClosestGrave->z, 0.f);

    RESET_AI_VALUE(bool, "combat::self target");
    RESET_AI_VALUE(WorldPosition, "current position");

    return true;
}

bool RepopAction::isUseful()
{
    if (bot->InBattleground())
        return false;

    return true;
}
