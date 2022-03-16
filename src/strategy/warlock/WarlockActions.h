/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_WARLOCKACTIONS_H
#define _PLAYERBOT_WARLOCKACTIONS_H

#include "GenericSpellActions.h"

class PlayerbotAI;
class Unit;

class CastDemonSkinAction : public CastBuffSpellAction
{
	public:
		CastDemonSkinAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "demon skin") { }
};

class CastDemonArmorAction : public CastBuffSpellAction
{
	public:
		CastDemonArmorAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "demon armor") { }
};

class CastFelArmorAction : public CastBuffSpellAction
{
	public:
		CastFelArmorAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "fel armor") { }
};

BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
END_SPELL_ACTION()

class CastDrainSoulAction : public CastSpellAction
{
	public:
		CastDrainSoulAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain soul") { }

        bool isUseful() override;
};

class CastDrainManaAction : public CastSpellAction
{
	public:
		CastDrainManaAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain mana") { }
};

class CastDrainLifeAction : public CastSpellAction
{
	public:
		CastDrainLifeAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain life") { }
};

class CastCurseOfAgonyAction : public CastDebuffSpellAction
{
	public:
		CastCurseOfAgonyAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "curse of agony") { }
};

class CastCurseOfWeaknessAction : public CastDebuffSpellAction
{
	public:
		CastCurseOfWeaknessAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "curse of weakness") { }
};

class CastCorruptionAction : public CastDebuffSpellAction
{
	public:
		CastCorruptionAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "corruption") { }
};

class CastCorruptionOnAttackerAction : public CastDebuffSpellOnAttackerAction
{
	public:
	    CastCorruptionOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "corruption") { }
};

class CastCurseOfAgonyOnAttackerAction : public CastDebuffSpellOnAttackerAction
{
    public:
        CastCurseOfAgonyOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "curse of agony") { }
};

class CastSummonVoidwalkerAction : public CastBuffSpellAction
{
	public:
		CastSummonVoidwalkerAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon voidwalker") { }
};

class CastSummonFelguardAction : public CastBuffSpellAction
{
	public:
		CastSummonFelguardAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon felguard") { }
};

class CastSummonImpAction : public CastBuffSpellAction
{
	public:
		CastSummonImpAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon imp") { }
};

class CastSummonSuccubusAction : public CastBuffSpellAction
{
    public:
        CastSummonSuccubusAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon succubus") { }
};

class CastCreateHealthstoneAction : public CastBuffSpellAction
{
	public:
		CastCreateHealthstoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create healthstone") { }
};

class CastCreateFirestoneAction : public CastBuffSpellAction
{
	public:
		CastCreateFirestoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create firestone") { }
};

class CastCreateSpellstoneAction : public CastBuffSpellAction
{
	public:
		CastCreateSpellstoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create spellstone") { }
};

class CastBanishAction : public CastBuffSpellAction
{
    public:
        CastBanishAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "banish on cc") { }

        Value<Unit*>* GetTargetValue() override;
        bool Execute(Event event) override;
};

class CastSeedOfCorruptionAction : public CastDebuffSpellAction
{
    public:
        CastSeedOfCorruptionAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "seed of corruption") { }
};

class CastRainOfFireAction : public CastSpellAction
{
    public:
        CastRainOfFireAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "rain of fire") { }
};

class CastShadowfuryAction : public CastSpellAction
{
    public:
        CastShadowfuryAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "shadowfury") { }
};

class CastImmolateAction : public CastDebuffSpellAction
{
    public:
        CastImmolateAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "immolate") { }
};

class CastConflagrateAction : public CastSpellAction
{
    public:
        CastConflagrateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "conflagrate") { }
};

class CastIncinirateAction : public CastSpellAction
{
    public:
        CastIncinirateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "incinirate") { }
};

class CastFearAction : public CastDebuffSpellAction
{
    public:
        CastFearAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "fear") { }
};

class CastFearOnCcAction : public CastBuffSpellAction
{
    public:
        CastFearOnCcAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "fear on cc") { }

        Value<Unit*>* GetTargetValue() override;
        bool Execute(Event event) override;
        bool isPossible() override;
        bool isUseful() override;
};

class CastLifeTapAction: public CastSpellAction
{
    public:
        CastLifeTapAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "life tap") { }

        std::string const GetTargetName() override { return "self target"; }
        bool isUseful() override;
};

class CastAmplifyCurseAction : public CastBuffSpellAction
{
    public:
        CastAmplifyCurseAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "amplify curse") { }
};

class CastSiphonLifeAction : public CastDebuffSpellAction
{
    public:
        CastSiphonLifeAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "siphon life") { }
};

class CastSiphonLifeOnAttackerAction : public CastDebuffSpellOnAttackerAction
{
    public:
        CastSiphonLifeOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "siphon life") { }
};

#endif
