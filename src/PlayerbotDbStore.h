/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PLAYERBOTDBSTORE_H
#define _PLAYERBOT_PLAYERBOTDBSTORE_H

#include "Common.h"

#include <vector>

class PlayerbotAI;

class PlayerbotDbStore
{
    public:
        PlayerbotDbStore() { }
        virtual ~PlayerbotDbStore() { }
        static PlayerbotDbStore* instance()
        {
            static PlayerbotDbStore instance;
            return &instance;
        }

        void Save(PlayerbotAI* botAI);
        void Load(PlayerbotAI* botAI);
        void Reset(PlayerbotAI* botAI);

    private:
        void SaveValue(uint32 guid, std::string const key, std::string const value);
        std::string const FormatStrategies(std::string const type, std::vector<std::string> strategies);
};

#define sPlayerbotDbStore PlayerbotDbStore::instance()

#endif
