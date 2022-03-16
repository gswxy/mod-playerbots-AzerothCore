/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_SUGGESTWHATTODOACTION_H
#define _PLAYERBOT_SUGGESTWHATTODOACTION_H

#include "InventoryAction.h"

class PlayerbotAI;

class SuggestWhatToDoAction : public InventoryAction
{
    public:
        SuggestWhatToDoAction(PlayerbotAI* botAI, std::string const name = "suggest what to do");

        bool Execute(Event event) override;
        bool isUseful() override;

    protected:
        typedef void (SuggestWhatToDoAction::*Suggestion)();
        std::vector<Suggestion> suggestions;
        void instance();
        void specificQuest();
        void grindReputation();
        void something();
        void spam(std::string const msg, uint32 channelId = 1);

        std::vector<uint32> GetIncompletedQuests();

    private:
        static std::map<std::string, uint8> instances;
        static std::map<std::string, uint8> factions;
};

class SuggestTradeAction : public SuggestWhatToDoAction
{
    public:
        SuggestTradeAction(PlayerbotAI* botAI);

        bool Execute(Event event) override;
        bool isUseful() override { return true; }
};

#endif
