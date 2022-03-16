/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_NONCOMBATACTIONS_H
#define _PLAYERBOT_NONCOMBATACTIONS_H

#include "UseItemAction.h"

class PlayerbotAI;

class DrinkAction : public UseItemAction
{
    public:
        DrinkAction(PlayerbotAI* botAI) : UseItemAction(botAI, "drink") { }

        bool Execute(Event event) override;
        bool isUseful() override;
};

class EatAction : public UseItemAction
{
    public:
        EatAction(PlayerbotAI* botAI) : UseItemAction(botAI, "food") { }

        bool Execute(Event event) override;
        bool isUseful() override;
};

#endif
