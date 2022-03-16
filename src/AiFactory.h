/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_AIFACTORY_H
#define _PLAYERBOT_AIFACTORY_H

#include "Common.h"

#include <map>

class AiObjectContext;
class Engine;
class Player;
class PlayerbotAI;

enum BotRoles : uint8;

class AiFactory
{
    public:
        static AiObjectContext* createAiObjectContext(Player* player, PlayerbotAI* botAI);
	    static Engine* createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* aiObjectContext);
	    static Engine* createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* aiObjectContext);
        static Engine* createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* aibjectContext);
        static void AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine);
        static void AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine);
        static void AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine);

        static uint8 GetPlayerSpecTab(Player* player);
        static std::map<uint8, uint32> GetPlayerSpecTabs(Player* player);
        static BotRoles GetPlayerRoles(Player* player);
        static std::string GetPlayerSpecName(Player* player);
};

#endif
