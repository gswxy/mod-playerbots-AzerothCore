/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MeleeDruidStrategy.h"
#include "Playerbots.h"

MeleeDruidStrategy::MeleeDruidStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI)
{
}

NextAction** MeleeDruidStrategy::getDefaultActions()
{
    return NextAction::array(0,
            new NextAction("faerie fire", ACTION_NORMAL + 1),
            new NextAction("melee", ACTION_NORMAL),
            nullptr);
}

void MeleeDruidStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("omen of clarity", NextAction::array(0, new NextAction("omen of clarity", ACTION_HIGH + 9), nullptr)));

    CombatStrategy::InitTriggers(triggers);
}
