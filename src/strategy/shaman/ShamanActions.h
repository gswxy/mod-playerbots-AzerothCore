/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_SHAMANACTIONS_H
#define _PLAYERBOT_SHAMANACTIONS_H

#include "GenericSpellActions.h"
#include "SharedDefines.h"

class PlayerbotAI;

class CastLesserHealingWaveAction : public CastHealingSpellAction
{
    public:
        CastLesserHealingWaveAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "lesser healing wave") { }
};

class CastLesserHealingWaveOnPartyAction : public HealPartyMemberAction
{
    public:
        CastLesserHealingWaveOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "lesser healing wave") { }
};

class CastHealingWaveAction : public CastHealingSpellAction
{
    public:
        CastHealingWaveAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "healing wave") { }
};

class CastHealingWaveOnPartyAction : public HealPartyMemberAction
{
    public:
        CastHealingWaveOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "healing wave") { }
};

class CastChainHealAction : public CastAoeHealSpellAction
{
    public:
        CastChainHealAction(PlayerbotAI* botAI) : CastAoeHealSpellAction(botAI, "chain heal") { }
};

class CastRiptideAction : public CastHealingSpellAction
{
    public:
        CastRiptideAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "riptide") { }
};

class CastRiptideOnPartyAction : public HealPartyMemberAction
{
    public:
        CastRiptideOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "riptide") { }
};

class CastEarthShieldAction : public CastBuffSpellAction
{
    public:
        CastEarthShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "earth shield") { }
};

class CastEarthShieldOnPartyAction : public BuffOnPartyAction
{
    public:
        CastEarthShieldOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(botAI, "earth shield") { }
};

class CastWaterShieldAction : public CastBuffSpellAction
{
    public:
        CastWaterShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "water shield") { }
};

class CastLightningShieldAction : public CastBuffSpellAction
{
	public:
		CastLightningShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "lightning shield") { }
};

class CastEarthlivingWeaponAction : public CastEnchantItemAction
{
    public:
        CastEarthlivingWeaponAction(PlayerbotAI* botAI) : CastEnchantItemAction(botAI, "earthliving weapon") { }
};

class CastRockbiterWeaponAction : public CastEnchantItemAction
{
    public:
        CastRockbiterWeaponAction(PlayerbotAI* botAI) : CastEnchantItemAction(botAI, "rockbiter weapon") { }
};

class CastFlametongueWeaponAction : public CastEnchantItemAction
{
    public:
        CastFlametongueWeaponAction(PlayerbotAI* botAI) : CastEnchantItemAction(botAI, "flametongue weapon") { }
};

class CastFrostbrandWeaponAction : public CastEnchantItemAction
{
    public:
        CastFrostbrandWeaponAction(PlayerbotAI* botAI) : CastEnchantItemAction(botAI, "frostbrand weapon") { }
};

class CastWindfuryWeaponAction : public CastEnchantItemAction
{
    public:
        CastWindfuryWeaponAction(PlayerbotAI* botAI) : CastEnchantItemAction(botAI, "windfury weapon") { }
};

class CastTotemAction : public CastBuffSpellAction
{
    public:
        CastTotemAction(PlayerbotAI* botAI, std::string const spell) : CastBuffSpellAction(botAI, spell) { }

        bool isUseful() override;
};

class CastStoneskinTotemAction : public CastTotemAction
{
    public:
        CastStoneskinTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "stoneskin totem") { }
};

class CastEarthbindTotemAction : public CastTotemAction
{
    public:
        CastEarthbindTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "earthbind totem") { }
};

class CastStrengthOfEarthTotemAction : public CastTotemAction
{
    public:
        CastStrengthOfEarthTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "strength of earth totem") { }
};

class CastManaSpringTotemAction : public CastTotemAction
{
    public:
        CastManaSpringTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "mana spring totem") { }

        bool isUseful() override;
};

class CastManaTideTotemAction : public CastTotemAction
{
	public:
		CastManaTideTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "mana tide totem") { }

		std::string const GetTargetName() override { return "self target"; }
};

class CastHealingStreamTotemAction : public CastTotemAction
{
	public:
		CastHealingStreamTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "healing stream totem") { }
};

class CastCleansingTotemAction : public CastTotemAction
{
    public:
        CastCleansingTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "cleansing totem") { }
};

class CastFlametongueTotemAction : public CastTotemAction
{
    public:
        CastFlametongueTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "flametongue totem") { }

        bool isUseful() override;
};

class CastWindfuryTotemAction : public CastTotemAction
{
    public:
        CastWindfuryTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "windfury totem") { }
};

class CastGraceOfAirTotemAction : public CastTotemAction
{
    public:
        CastGraceOfAirTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "grace of air totem") { }
};

class CastSearingTotemAction : public CastTotemAction
{
    public:
        CastSearingTotemAction(PlayerbotAI* botAI) : CastTotemAction(botAI, "searing totem") { }

        std::string const GetTargetName() override { return "self target"; }
        bool isUseful() override;
};

class CastMagmaTotemAction : public CastMeleeSpellAction
{
    public:
        CastMagmaTotemAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "magma totem") { }

        std::string const GetTargetName() override { return "self target"; }
        bool isUseful() override;
};

class CastFireNovaAction : public CastSpellAction
{
    public:
        CastFireNovaAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "fire nova") { }
};

class CastWindShearAction : public CastSpellAction
{
    public:
        CastWindShearAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "wind shear") { }
};

class CastAncestralSpiritAction : public ResurrectPartyMemberAction
{
	public:
		CastAncestralSpiritAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(botAI, "ancestral spirit") { }
};

class CastPurgeAction : public CastSpellAction
{
	public:
		CastPurgeAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "purge") { }
};

class CastStormstrikeAction : public CastMeleeSpellAction
{
	public:
		CastStormstrikeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "stormstrike") { }
};

class CastLavaLashAction : public CastMeleeSpellAction
{
	public:
		CastLavaLashAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "lava lash") { }
};

class CastWaterBreathingAction : public CastBuffSpellAction
{
    public:
        CastWaterBreathingAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "water breathing") { }
};

class CastWaterWalkingAction : public CastBuffSpellAction
{
    public:
        CastWaterWalkingAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "water walking") { }
};

class CastWaterBreathingOnPartyAction : public BuffOnPartyAction
{
    public:
        CastWaterBreathingOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(botAI, "water breathing") { }
};

class CastWaterWalkingOnPartyAction : public BuffOnPartyAction
{
    public:
        CastWaterWalkingOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(botAI, "water walking") { }
};

class CastCleanseSpiritAction : public CastCureSpellAction
{
    public:
        CastCleanseSpiritAction(PlayerbotAI* botAI) : CastCureSpellAction(botAI, "cleanse spirit") { }
};

class CastCleanseSpiritPoisonOnPartyAction : public CurePartyMemberAction
{
    public:
        CastCleanseSpiritPoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cleanse spirit", DISPEL_POISON) { }

        std::string const getName() override { return "cleanse spirit poison on party"; }
};

class CastCleanseSpiritCurseOnPartyAction : public CurePartyMemberAction
{
    public:
        CastCleanseSpiritCurseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cleanse spirit", DISPEL_CURSE) { }

        std::string const getName() override { return "cleanse spirit curse on party"; }
};

class CastCleanseSpiritDiseaseOnPartyAction : public CurePartyMemberAction
{
    public:
        CastCleanseSpiritDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cleanse spirit", DISPEL_DISEASE) { }

        std::string const getName() override { return "cleanse spirit disease on party"; }
};

class CastFlameShockAction : public CastDebuffSpellAction
{
    public:
        CastFlameShockAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "flame shock") { }
};

class CastEarthShockAction : public CastDebuffSpellAction
{
    public:
        CastEarthShockAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "earth shock") { }
};

class CastFrostShockAction : public CastSnareSpellAction
{
    public:
        CastFrostShockAction(PlayerbotAI* botAI) : CastSnareSpellAction(botAI, "frost shock") { }
};

class CastChainLightningAction : public CastSpellAction
{
    public:
        CastChainLightningAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "chain lightning") { }
};

class CastLightningBoltAction : public CastSpellAction
{
    public:
        CastLightningBoltAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "lightning bolt") { }
};

class CastThunderstormAction : public CastMeleeSpellAction
{
    public:
        CastThunderstormAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "thunderstorm") { }
};

class CastHeroismAction : public CastBuffSpellAction
{
    public:
        CastHeroismAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "heroism") { }
};

class CastBloodlustAction : public CastBuffSpellAction
{
    public:
        CastBloodlustAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "bloodlust") { }
};

class CastWindShearOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
{
    public:
        CastWindShearOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(botAI, "wind shear") { }
};

class CastCurePoisonAction : public CastCureSpellAction
{
    public:
        CastCurePoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(botAI, "cure poison") { }
};

class CastCurePoisonOnPartyAction : public CurePartyMemberAction
{
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cure poison", DISPEL_POISON) { }
};

class CastCureDiseaseAction : public CastCureSpellAction
{
    public:
        CastCureDiseaseAction(PlayerbotAI* botAI) : CastCureSpellAction(botAI, "cure disease") { }
};

class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
{
    public:
        CastCureDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cure disease", DISPEL_DISEASE) { }

        std::string const getName() override { return "cure disease on party"; }
};

#endif
