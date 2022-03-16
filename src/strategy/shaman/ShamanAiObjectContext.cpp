/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ShamanAiObjectContext.h"
#include "CasterShamanStrategy.h"
#include "HealShamanStrategy.h"
#include "MeleeShamanStrategy.h"
#include "ShamanActions.h"
#include "ShamanNonCombatStrategy.h"
#include "ShamanTriggers.h"
#include "TotemsShamanStrategy.h"
#include "NamedObjectContext.h"
#include "Playerbots.h"

class ShamanStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        ShamanStrategyFactoryInternal()
        {
            creators["nc"] = &ShamanStrategyFactoryInternal::nc;
            creators["totems"] = &ShamanStrategyFactoryInternal::totems;
            creators["melee aoe"] = &ShamanStrategyFactoryInternal::melee_aoe;
            creators["caster aoe"] = &ShamanStrategyFactoryInternal::caster_aoe;
            creators["cure"] = &ShamanStrategyFactoryInternal::cure;
        }

    private:
        static Strategy* nc(PlayerbotAI* botAI) { return new ShamanNonCombatStrategy(botAI); }
        static Strategy* totems(PlayerbotAI* botAI) { return new TotemsShamanStrategy(botAI); }
        static Strategy* melee_aoe(PlayerbotAI* botAI) { return new MeleeAoeShamanStrategy(botAI); }
        static Strategy* caster_aoe(PlayerbotAI* botAI) { return new CasterAoeShamanStrategy(botAI); }
        static Strategy* cure(PlayerbotAI* botAI) { return new ShamanCureStrategy(botAI); }
};

class ShamanBuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        ShamanBuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
        {
            creators["bmana"] = &ShamanBuffStrategyFactoryInternal::bmana;
            creators["bdps"] = &ShamanBuffStrategyFactoryInternal::bdps;
        }

    private:
        static Strategy* bmana(PlayerbotAI* botAI) { return new ShamanBuffManaStrategy(botAI); }
        static Strategy* bdps(PlayerbotAI* botAI) { return new ShamanBuffDpsStrategy(botAI); }
};

class ShamanCombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        ShamanCombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
        {
            creators["heal"] = &ShamanCombatStrategyFactoryInternal::heal;
            creators["melee"] = &ShamanCombatStrategyFactoryInternal::dps;
            creators["dps"] = &ShamanCombatStrategyFactoryInternal::dps;
            creators["caster"] = &ShamanCombatStrategyFactoryInternal::caster;
        }

    private:
        static Strategy* heal(PlayerbotAI* botAI) { return new HealShamanStrategy(botAI); }
        static Strategy* dps(PlayerbotAI* botAI) { return new MeleeShamanStrategy(botAI); }
        static Strategy* caster(PlayerbotAI* botAI) { return new CasterShamanStrategy(botAI); }
};

class ShamanATriggerFactoryInternal : public NamedObjectContext<Trigger>
{
    public:
        ShamanATriggerFactoryInternal()
        {
            creators["grace of air totem"] = &ShamanATriggerFactoryInternal::grace_of_air_totem;
            creators["windfury totem"] = &ShamanATriggerFactoryInternal::windfury_totem;
            creators["mana spring totem"] = &ShamanATriggerFactoryInternal::mana_spring_totem;
            creators["flametongue totem"] = &ShamanATriggerFactoryInternal::flametongue_totem;
            creators["strength of earth totem"] = &ShamanATriggerFactoryInternal::strength_of_earth_totem;
            creators["magma totem"] = &ShamanATriggerFactoryInternal::magma_totem;
            creators["searing totem"] = &ShamanATriggerFactoryInternal::searing_totem;
            creators["wind shear"] = &ShamanATriggerFactoryInternal::wind_shear;
            creators["purge"] = &ShamanATriggerFactoryInternal::purge;
            creators["shaman weapon"] = &ShamanATriggerFactoryInternal::shaman_weapon;
            creators["water shield"] = &ShamanATriggerFactoryInternal::water_shield;
            creators["lightning shield"] = &ShamanATriggerFactoryInternal::lightning_shield;
            creators["water breathing"] = &ShamanATriggerFactoryInternal::water_breathing;
            creators["water walking"] = &ShamanATriggerFactoryInternal::water_walking;
            creators["water breathing on party"] = &ShamanATriggerFactoryInternal::water_breathing_on_party;
            creators["water walking on party"] = &ShamanATriggerFactoryInternal::water_walking_on_party;
            creators["cleanse spirit poison"] = &ShamanATriggerFactoryInternal::cleanse_poison;
            creators["cleanse spirit curse"] = &ShamanATriggerFactoryInternal::cleanse_curse;
            creators["cleanse spirit disease"] = &ShamanATriggerFactoryInternal::cleanse_disease;
            creators["party member cleanse spirit poison"] = &ShamanATriggerFactoryInternal::party_member_cleanse_poison;
            creators["party member cleanse spirit curse"] = &ShamanATriggerFactoryInternal::party_member_cleanse_curse;
            creators["party member cleanse spirit disease"] = &ShamanATriggerFactoryInternal::party_member_cleanse_disease;
            creators["shock"] = &ShamanATriggerFactoryInternal::shock;
            creators["frost shock snare"] = &ShamanATriggerFactoryInternal::frost_shock_snare;
            creators["heroism"] = &ShamanATriggerFactoryInternal::heroism;
            creators["bloodlust"] = &ShamanATriggerFactoryInternal::bloodlust;
            creators["maelstrom weapon"] = &ShamanATriggerFactoryInternal::maelstrom_weapon;
            creators["wind shear on enemy healer"] = &ShamanATriggerFactoryInternal::wind_shear_on_enemy_healer;
            creators["cure poison"] = &ShamanATriggerFactoryInternal::cure_poison;
            creators["party member cure poison"] = &ShamanATriggerFactoryInternal::party_member_cure_poison;
            creators["cure disease"] = &ShamanATriggerFactoryInternal::cure_disease;
            creators["party member cure disease"] = &ShamanATriggerFactoryInternal::party_member_cure_disease;
        }

    private:
        static Trigger* maelstrom_weapon(PlayerbotAI* botAI) { return new MaelstromWeaponTrigger(botAI); }
        static Trigger* heroism(PlayerbotAI* botAI) { return new HeroismTrigger(botAI); }
        static Trigger* bloodlust(PlayerbotAI* botAI) { return new BloodlustTrigger(botAI); }
        static Trigger* party_member_cleanse_disease(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritDiseaseTrigger(botAI); }
        static Trigger* party_member_cleanse_curse(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritCurseTrigger(botAI); }
        static Trigger* party_member_cleanse_poison(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritPoisonTrigger(botAI); }
        static Trigger* cleanse_disease(PlayerbotAI* botAI) { return new CleanseSpiritDiseaseTrigger(botAI); }
        static Trigger* cleanse_curse(PlayerbotAI* botAI) { return new CleanseSpiritCurseTrigger(botAI); }
        static Trigger* cleanse_poison(PlayerbotAI* botAI) { return new CleanseSpiritPoisonTrigger(botAI); }
        static Trigger* water_breathing(PlayerbotAI* botAI) { return new WaterBreathingTrigger(botAI); }
        static Trigger* water_walking(PlayerbotAI* botAI) { return new WaterWalkingTrigger(botAI); }
        static Trigger* water_breathing_on_party(PlayerbotAI* botAI) { return new WaterBreathingOnPartyTrigger(botAI); }
        static Trigger* water_walking_on_party(PlayerbotAI* botAI) { return new WaterWalkingOnPartyTrigger(botAI); }
        static Trigger* windfury_totem(PlayerbotAI* botAI) { return new WindfuryTotemTrigger(botAI); }
        static Trigger* grace_of_air_totem(PlayerbotAI* botAI) { return new GraceOfAirTotemTrigger(botAI); }
        static Trigger* mana_spring_totem(PlayerbotAI* botAI) { return new ManaSpringTotemTrigger(botAI); }
        static Trigger* flametongue_totem(PlayerbotAI* botAI) { return new FlametongueTotemTrigger(botAI); }
        static Trigger* strength_of_earth_totem(PlayerbotAI* botAI) { return new StrengthOfEarthTotemTrigger(botAI); }
        static Trigger* magma_totem(PlayerbotAI* botAI) { return new MagmaTotemTrigger(botAI); }
        static Trigger* searing_totem(PlayerbotAI* botAI) { return new SearingTotemTrigger(botAI); }
        static Trigger* wind_shear(PlayerbotAI* botAI) { return new WindShearInterruptSpellTrigger(botAI); }
        static Trigger* purge(PlayerbotAI* botAI) { return new PurgeTrigger(botAI); }
        static Trigger* shaman_weapon(PlayerbotAI* botAI) { return new ShamanWeaponTrigger(botAI); }
        static Trigger* water_shield(PlayerbotAI* botAI) { return new WaterShieldTrigger(botAI); }
        static Trigger* lightning_shield(PlayerbotAI* botAI) { return new LightningShieldTrigger(botAI); }
        static Trigger* shock(PlayerbotAI* botAI) { return new ShockTrigger(botAI); }
        static Trigger* frost_shock_snare(PlayerbotAI* botAI) { return new FrostShockSnareTrigger(botAI); }
        static Trigger* wind_shear_on_enemy_healer(PlayerbotAI* botAI) { return new WindShearInterruptEnemyHealerSpellTrigger(botAI); }
        static Trigger* cure_poison(PlayerbotAI* botAI) { return new CurePoisonTrigger(botAI); }
        static Trigger* party_member_cure_poison(PlayerbotAI* botAI) { return new PartyMemberCurePoisonTrigger(botAI); }
        static Trigger* cure_disease(PlayerbotAI* botAI) { return new CureDiseaseTrigger(botAI); }
        static Trigger* party_member_cure_disease(PlayerbotAI* botAI) { return new PartyMemberCureDiseaseTrigger(botAI); }
};

class ShamanAiObjectContextInternal : public NamedObjectContext<Action>
{
    public:
        ShamanAiObjectContextInternal()
        {
            creators["water shield"] = &ShamanAiObjectContextInternal::water_shield;
            creators["lightning shield"] = &ShamanAiObjectContextInternal::lightning_shield;
            creators["strength of earth totem"] = &ShamanAiObjectContextInternal::strength_of_earth_totem;
            creators["flametongue totem"] = &ShamanAiObjectContextInternal::flametongue_totem;
            creators["searing totem"] = &ShamanAiObjectContextInternal::searing_totem;
            creators["magma totem"] = &ShamanAiObjectContextInternal::magma_totem;
            creators["windfury totem"] = &ShamanAiObjectContextInternal::windfury_totem;
            creators["grace of air totem"] = &ShamanAiObjectContextInternal::grace_of_air_totem;
            creators["mana spring totem"] = &ShamanAiObjectContextInternal::mana_spring_totem;
            creators["mana tide totem"] = &ShamanAiObjectContextInternal::mana_tide_totem;
            creators["earthbind totem"] = &ShamanAiObjectContextInternal::earthbind_totem;
            creators["healing stream totem"] = &ShamanAiObjectContextInternal::healing_stream_totem;
            creators["wind shear"] = &ShamanAiObjectContextInternal::wind_shear;
            creators["wind shear on enemy healer"] = &ShamanAiObjectContextInternal::wind_shear_on_enemy_healer;
            creators["rockbiter weapon"] = &ShamanAiObjectContextInternal::rockbiter_weapon;
            creators["flametongue weapon"] = &ShamanAiObjectContextInternal::flametongue_weapon;
            creators["frostbrand weapon"] = &ShamanAiObjectContextInternal::frostbrand_weapon;
            creators["windfury weapon"] = &ShamanAiObjectContextInternal::windfury_weapon;
            creators["earthliving weapon"] = &ShamanAiObjectContextInternal::earthliving_weapon;
            creators["purge"] = &ShamanAiObjectContextInternal::purge;
            creators["healing wave"] = &ShamanAiObjectContextInternal::healing_wave;
            creators["lesser healing wave"] = &ShamanAiObjectContextInternal::lesser_healing_wave;
            creators["healing wave on party"] = &ShamanAiObjectContextInternal::healing_wave_on_party;
            creators["lesser healing wave on party"] = &ShamanAiObjectContextInternal::lesser_healing_wave_on_party;
            creators["earth shield"] = &ShamanAiObjectContextInternal::earth_shield;
            creators["earth shield on party"] = &ShamanAiObjectContextInternal::earth_shield_on_party;
            creators["chain heal"] = &ShamanAiObjectContextInternal::chain_heal;
            creators["riptide"] = &ShamanAiObjectContextInternal::riptide;
            creators["riptide on party"] = &ShamanAiObjectContextInternal::riptide_on_party;
            creators["stormstrike"] = &ShamanAiObjectContextInternal::stormstrike;
            creators["lava lash"] = &ShamanAiObjectContextInternal::lava_lash;
            creators["fire nova"] = &ShamanAiObjectContextInternal::fire_nova;
            creators["ancestral spirit"] = &ShamanAiObjectContextInternal::ancestral_spirit;
            creators["water walking"] = &ShamanAiObjectContextInternal::water_walking;
            creators["water breathing"] = &ShamanAiObjectContextInternal::water_breathing;
            creators["water walking on party"] = &ShamanAiObjectContextInternal::water_walking_on_party;
            creators["water breathing on party"] = &ShamanAiObjectContextInternal::water_breathing_on_party;
            creators["cleanse spirit"] = &ShamanAiObjectContextInternal::cleanse_spirit;
            creators["cleanse spirit poison on party"] = &ShamanAiObjectContextInternal::cleanse_spirit_poison_on_party;
            creators["cleanse spirit disease on party"] = &ShamanAiObjectContextInternal::cleanse_spirit_disease_on_party;
            creators["cleanse spirit curse on party"] = &ShamanAiObjectContextInternal::cleanse_spirit_curse_on_party;
            creators["flame shock"] = &ShamanAiObjectContextInternal::flame_shock;
            creators["earth shock"] = &ShamanAiObjectContextInternal::earth_shock;
            creators["frost shock"] = &ShamanAiObjectContextInternal::frost_shock;
            creators["chain lightning"] = &ShamanAiObjectContextInternal::chain_lightning;
            creators["lightning bolt"] = &ShamanAiObjectContextInternal::lightning_bolt;
            creators["thunderstorm"] = &ShamanAiObjectContextInternal::thunderstorm;
            creators["heroism"] = &ShamanAiObjectContextInternal::heroism;
            creators["bloodlust"] = &ShamanAiObjectContextInternal::bloodlust;
            creators["cure disease"] = &ShamanAiObjectContextInternal::cure_disease;
            creators["cure disease on party"] = &ShamanAiObjectContextInternal::cure_disease_on_party;
            creators["cure poison"] = &ShamanAiObjectContextInternal::cure_poison;
            creators["cure poison on party"] = &ShamanAiObjectContextInternal::cure_poison_on_party;
        }

    private:
        static Action* heroism(PlayerbotAI* botAI) { return new CastHeroismAction(botAI); }
        static Action* bloodlust(PlayerbotAI* botAI) { return new CastBloodlustAction(botAI); }
        static Action* thunderstorm(PlayerbotAI* botAI) { return new CastThunderstormAction(botAI); }
        static Action* lightning_bolt(PlayerbotAI* botAI) { return new CastLightningBoltAction(botAI); }
        static Action* chain_lightning(PlayerbotAI* botAI) { return new CastChainLightningAction(botAI); }
        static Action* frost_shock(PlayerbotAI* botAI) { return new CastFrostShockAction(botAI); }
        static Action* earth_shock(PlayerbotAI* botAI) { return new CastEarthShockAction(botAI); }
        static Action* flame_shock(PlayerbotAI* botAI) { return new CastFlameShockAction(botAI); }
        static Action* cleanse_spirit_poison_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritPoisonOnPartyAction(botAI); }
        static Action* cleanse_spirit_disease_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritDiseaseOnPartyAction(botAI); }
        static Action* cleanse_spirit_curse_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritCurseOnPartyAction(botAI); }
        static Action* cleanse_spirit(PlayerbotAI* botAI) { return new CastCleanseSpiritAction(botAI); }
        static Action* water_walking(PlayerbotAI* botAI) { return new CastWaterWalkingAction(botAI); }
        static Action* water_breathing(PlayerbotAI* botAI) { return new CastWaterBreathingAction(botAI); }
        static Action* water_walking_on_party(PlayerbotAI* botAI) { return new CastWaterWalkingOnPartyAction(botAI); }
        static Action* water_breathing_on_party(PlayerbotAI* botAI) { return new CastWaterBreathingOnPartyAction(botAI); }
        static Action* water_shield(PlayerbotAI* botAI) { return new CastWaterShieldAction(botAI); }
        static Action* lightning_shield(PlayerbotAI* botAI) { return new CastLightningShieldAction(botAI); }
        static Action* strength_of_earth_totem(PlayerbotAI* botAI) { return new CastStrengthOfEarthTotemAction(botAI); }
        static Action* flametongue_totem(PlayerbotAI* botAI) { return new CastFlametongueTotemAction(botAI); }
        static Action* magma_totem(PlayerbotAI* botAI) { return new CastMagmaTotemAction(botAI); }
        static Action* searing_totem(PlayerbotAI* botAI) { return new CastSearingTotemAction(botAI); }
        static Action* fire_nova(PlayerbotAI* botAI) { return new CastFireNovaAction(botAI); }
        static Action* windfury_totem(PlayerbotAI* botAI) { return new CastWindfuryTotemAction(botAI); }
        static Action* grace_of_air_totem(PlayerbotAI* botAI) { return new CastGraceOfAirTotemAction(botAI); }
        static Action* mana_spring_totem(PlayerbotAI* botAI) { return new CastManaSpringTotemAction(botAI); }
        static Action* mana_tide_totem(PlayerbotAI* botAI) { return new CastManaTideTotemAction(botAI); }
        static Action* earthbind_totem(PlayerbotAI* botAI) { return new CastEarthbindTotemAction(botAI); }
        static Action* healing_stream_totem(PlayerbotAI* botAI) { return new CastHealingStreamTotemAction(botAI); }
        static Action* wind_shear(PlayerbotAI* botAI) { return new CastWindShearAction(botAI); }
        static Action* rockbiter_weapon(PlayerbotAI* botAI) { return new CastRockbiterWeaponAction(botAI); }
        static Action* flametongue_weapon(PlayerbotAI* botAI) { return new CastFlametongueWeaponAction(botAI); }
        static Action* frostbrand_weapon(PlayerbotAI* botAI) { return new CastFrostbrandWeaponAction(botAI); }
        static Action* windfury_weapon(PlayerbotAI* botAI) { return new CastWindfuryWeaponAction(botAI); }
        static Action* earthliving_weapon(PlayerbotAI* botAI) { return new CastEarthlivingWeaponAction(botAI); }
        static Action* purge(PlayerbotAI* botAI) { return new CastPurgeAction(botAI); }
        static Action* healing_wave(PlayerbotAI* botAI) { return new CastHealingWaveAction(botAI); }
        static Action* lesser_healing_wave(PlayerbotAI* botAI) { return new CastLesserHealingWaveAction(botAI); }
        static Action* healing_wave_on_party(PlayerbotAI* botAI) { return new CastHealingWaveOnPartyAction(botAI); }
        static Action* lesser_healing_wave_on_party(PlayerbotAI* botAI) { return new CastLesserHealingWaveOnPartyAction(botAI); }
        static Action* earth_shield(PlayerbotAI* botAI) { return new CastEarthShieldAction(botAI); }
        static Action* earth_shield_on_party(PlayerbotAI* botAI) { return new CastEarthShieldOnPartyAction(botAI); }
        static Action* chain_heal(PlayerbotAI* botAI) { return new CastChainHealAction(botAI); }
        static Action* riptide(PlayerbotAI* botAI) { return new CastRiptideAction(botAI); }
        static Action* riptide_on_party(PlayerbotAI* botAI) { return new CastRiptideOnPartyAction(botAI); }
        static Action* stormstrike(PlayerbotAI* botAI) { return new CastStormstrikeAction(botAI); }
        static Action* lava_lash(PlayerbotAI* botAI) { return new CastLavaLashAction(botAI); }
        static Action* ancestral_spirit(PlayerbotAI* botAI) { return new CastAncestralSpiritAction(botAI); }
        static Action* wind_shear_on_enemy_healer(PlayerbotAI* botAI) { return new CastWindShearOnEnemyHealerAction(botAI); }
        static Action* cure_poison(PlayerbotAI* botAI) { return new CastCurePoisonAction(botAI); }
        static Action* cure_poison_on_party(PlayerbotAI* botAI) { return new CastCurePoisonOnPartyAction(botAI); }
        static Action* cure_disease(PlayerbotAI* botAI) { return new CastCureDiseaseAction(botAI); }
        static Action* cure_disease_on_party(PlayerbotAI* botAI) { return new CastCureDiseaseOnPartyAction(botAI); }
};

ShamanAiObjectContext::ShamanAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new ShamanStrategyFactoryInternal());
    strategyContexts.Add(new ShamanCombatStrategyFactoryInternal());
    strategyContexts.Add(new ShamanBuffStrategyFactoryInternal());
    actionContexts.Add(new ShamanAiObjectContextInternal());
    triggerContexts.Add(new ShamanATriggerFactoryInternal());
}
