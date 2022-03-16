/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_ROGUEOPENINGACTIONS_H
#define _PLAYERBOT_ROGUEOPENINGACTIONS_H

#include "GenericSpellActions.h"

class PlayerbotAI;
class Unit;

class CastSapAction : public CastMeleeSpellAction
{
	public:
		CastSapAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "sap") { }

        Value<Unit*>* GetTargetValue() override;
        bool isUseful() override { return true; }
};

class CastGarroteAction : public CastMeleeSpellAction
{
	public:
		CastGarroteAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "garrote") { }
};

class CastCheapShotAction : public CastMeleeSpellAction
{
	public:
		CastCheapShotAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "cheap shot") { }
};

class CastAmbushAction : public CastMeleeSpellAction
{
    public:
        CastAmbushAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "ambush") { }
};

#endif
