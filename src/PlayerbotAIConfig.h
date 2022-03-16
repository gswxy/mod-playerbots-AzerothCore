/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PLAYERbotAICONFIG_H
#define _PLAYERBOT_PLAYERbotAICONFIG_H

#include "Common.h"
#include "SharedDefines.h"
#include "TalentSpec.h"

#include <mutex>

enum class BotCheatMask : uint32
{
    none    = 0,
    taxi    = 1,
    gold    = 2,
    health  = 4,
    mana    = 8,
    power   = 16,
    maxMask = 32
};

class PlayerbotAIConfig
{
    public:
        PlayerbotAIConfig() { };
        static PlayerbotAIConfig* instance()
        {
            static PlayerbotAIConfig instance;
            return &instance;
        }

        bool Initialize();
        bool IsInRandomAccountList(uint32 id);
        bool IsInRandomQuestItemList(uint32 id);
        bool IsInPvpProhibitedZone(uint32 id);

        bool enabled;
        bool allowGuildBots;
        uint32 globalCoolDown, reactDelay, maxWaitForMove, expireActionTime, dispelAuraDuration, passiveDelay, repeatDelay,
            errorDelay, rpgDelay, sitDelay, returnDelay, lootDelay;
        float sightDistance, spellDistance, reactDistance, grindDistance, lootDistance, shootDistance,
            fleeDistance, tooCloseDistance, meleeDistance, followDistance, whisperDistance, contactDistance,
            aoeRadius, rpgDistance, targetPosRecalcDistance, farDistance, healDistance, aggroDistance;
        uint32 criticalHealth, lowHealth, mediumHealth, almostFullHealth;
        uint32 lowMana, mediumMana;

        uint32 openGoSpell;
        bool randomBotAutologin;
        bool botAutologin;
        std::string randomBotMapsAsString;
        std::vector<uint32> randomBotMaps;
        std::vector<uint32> randomBotQuestItems;
        std::vector<uint32> randomBotAccounts;
        std::vector<uint32> randomBotSpellIds;
        std::vector<uint32> randomBotQuestIds;
        uint32 randomBotTeleportDistance;
        float randomGearLoweringChance;
        float randomBotMaxLevelChance;
        float randomBotRpgChance;
        uint32 minRandomBots, maxRandomBots;
        uint32 randomBotUpdateInterval, randomBotCountChangeMinInterval, randomBotCountChangeMaxInterval;
        uint32 minRandomBotInWorldTime, maxRandomBotInWorldTime;
        uint32 minRandomBotRandomizeTime, maxRandomBotRandomizeTime;
        uint32 minRandomBotChangeStrategyTime, maxRandomBotChangeStrategyTime;
        uint32 minRandomBotReviveTime, maxRandomBotReviveTime;
        uint32 minRandomBotPvpTime, maxRandomBotPvpTime;
        uint32 randomBotsPerInterval;
        uint32 minRandomBotsPriceChangeInterval, maxRandomBotsPriceChangeInterval;
        bool randomBotJoinLfg;
        bool randomBotJoinBG;
        bool randomBotLoginAtStartup;
        uint32 randomBotTeleLevel;
        bool logInGroupOnly, logValuesPerTick;
        bool fleeingEnabled;
        bool summonAtInnkeepersEnabled;
        std::string combatStrategies, nonCombatStrategies;
        std::string randomBotCombatStrategies, randomBotNonCombatStrategies;
        uint32 randomBotMinLevel, randomBotMaxLevel;
        float randomChangeMultiplier;
        uint32 specProbability[MAX_CLASSES][10];
        std::string premadeLevelSpec[MAX_CLASSES][10][91]; //lvl 10 - 100
        ClassSpecs classSpecs[MAX_CLASSES];
        std::string commandPrefix, commandSeparator;
        std::string randomBotAccountPrefix;
        uint32 randomBotAccountCount;
        bool randomBotRandomPassword;
        bool deleteRandomBotAccounts;
        uint32 randomBotGuildCount;
        bool deleteRandomBotGuilds;
        std::vector<uint32> randomBotGuilds;
        std::vector<uint32> pvpProhibitedZoneIds;

        bool randombotsWalkingRPG;
        bool randombotsWalkingRPGInDoors;
        uint32 minEnchantingBotLevel;
        uint32 randombotStartingLevel;
        bool gearscorecheck;
        bool randomBotPreQuests;

        bool guildTaskEnabled;
        uint32 minGuildTaskChangeTime, maxGuildTaskChangeTime;
        uint32 minGuildTaskAdvertisementTime, maxGuildTaskAdvertisementTime;
        uint32 minGuildTaskRewardTime, maxGuildTaskRewardTime;
        uint32 guildTaskAdvertCleanupTime;
        uint32 guildTaskKillTaskDistance;

        uint32 iterationsPerTick;

        std::mutex m_logMtx;
        std::vector<std::string> allowedLogFiles;
        std::unordered_map<std::string, std::pair<FILE*, bool>> logFiles;

        std::vector<std::string> botCheats;
        uint32 botCheatMask = 0;

        struct worldBuff
        {
            uint32 spellId;
            uint32 factionId = 0;
            uint32 classId = 0;
            uint32 minLevel = 0;
            uint32 maxLevel = 0;
        };

        std::vector<worldBuff> worldBuffs;

        uint32 commandServerPort;
        bool perfMonEnabled;

        bool enableGreet;
        bool randomBotShowHelmet;
        bool randomBotShowCloak;
        bool disableRandomLevels;
        uint32 playerbotsXPrate;
        uint32 botActiveAlone;

        std::string autoPickReward;
        bool autoEquipUpgradeLoot;
        bool syncQuestWithPlayer;
        bool syncQuestForPlayer;
        std::string autoTrainSpells;
        std::string autoPickTalents;
        bool autoLearnTrainerSpells;
        bool autoDoQuests;
        bool syncLevelWithPlayers;
        bool autoLearnQuestSpells;
        bool randomBotSayWithoutMaster;
        bool randomBotGroupNearby;
        uint32 tweakValue; //Debugging config

        uint32 randomBotArenaTeamCount;
        bool deleteRandomBotArenaTeams;
        std::vector<uint32> randomBotArenaTeams;

        uint32 selfBotLevel;

        std::string const GetTimestampStr();
        bool hasLog(std::string const fileName) { return std::find(allowedLogFiles.begin(), allowedLogFiles.end(), fileName) != allowedLogFiles.end(); };
        bool openLog(std::string const fileName, char const* mode = "a");
        bool isLogOpen(std::string const fileName) { auto it = logFiles.find(fileName); return it != logFiles.end() && it->second.second; }
        void log(std::string const fileName, const char* str, ...);

        void loadWorldBuf(uint32 factionId, uint32 classId, uint32 minLevel, uint32 maxLevel);

};

#define sPlayerbotAIConfig PlayerbotAIConfig::instance()

#endif
