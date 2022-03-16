/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_SHAMANTRIGGERS_H
#define _PLAYERBOT_SHAMANTRIGGERS_H

#include "CureTriggers.h"
#include "SharedDefines.h"

class PlayerbotAI;

class ShamanWeaponTrigger : public BuffTrigger
{
    public:
        ShamanWeaponTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "rockbiter weapon", 2) { }

        bool IsActive() override;

    private:
        static std::vector<std::string> spells;
};

class TotemTrigger : public Trigger
{
    public:
        TotemTrigger(PlayerbotAI* botAI, std::string const spell, uint32 attackerCount = 0) : Trigger(botAI, spell), attackerCount(attackerCount) { }

        bool IsActive() override;

    protected:
        uint32 attackerCount;
};

class WindfuryTotemTrigger : public TotemTrigger
{
    public:
        WindfuryTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "windfury totem") { }
};

class GraceOfAirTotemTrigger : public TotemTrigger
{
    public:
        GraceOfAirTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "grace of air totem") { }
};

class ManaSpringTotemTrigger : public TotemTrigger
{
    public:
        ManaSpringTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "mana spring totem") { }

        bool IsActive() override;
};

class FlametongueTotemTrigger : public TotemTrigger
{
    public:
        FlametongueTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "flametongue totem") { }
};

class StrengthOfEarthTotemTrigger : public TotemTrigger
{
    public:
        StrengthOfEarthTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "strength of earth totem") { }
};

class MagmaTotemTrigger : public TotemTrigger
{
    public:
        MagmaTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "magma totem", 3) { }
};

class SearingTotemTrigger : public TotemTrigger
{
    public:
        SearingTotemTrigger(PlayerbotAI* botAI) : TotemTrigger(botAI, "searing totem", 1) { }
};

class WindShearInterruptSpellTrigger : public InterruptSpellTrigger
{
    public:
        WindShearInterruptSpellTrigger(PlayerbotAI* botAI) : InterruptSpellTrigger(botAI, "wind shear") { }
};

class WaterShieldTrigger : public BuffTrigger
{
    public:
        WaterShieldTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "water shield") { }
};

class LightningShieldTrigger : public BuffTrigger
{
    public:
        LightningShieldTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "lightning shield") { }
};

class PurgeTrigger : public TargetAuraDispelTrigger
{
    public:
        PurgeTrigger(PlayerbotAI* botAI) : TargetAuraDispelTrigger(botAI, "purge", DISPEL_MAGIC) { }
};

class WaterWalkingTrigger : public BuffTrigger
{
    public:
        WaterWalkingTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "water walking", 7) { }

        bool IsActive() override;
};

class WaterBreathingTrigger : public BuffTrigger
{
    public:
        WaterBreathingTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "water breathing", 5) { }

        bool IsActive() override;
};

class WaterWalkingOnPartyTrigger : public BuffOnPartyTrigger
{
    public:
        WaterWalkingOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(botAI, "water walking on party", 2) { }

        bool IsActive() override;
};

class WaterBreathingOnPartyTrigger : public BuffOnPartyTrigger
{
    public:
        WaterBreathingOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(botAI, "water breathing on party", 2) { }

        bool IsActive() override;
};

class CleanseSpiritPoisonTrigger : public NeedCureTrigger
{
    public:
        CleanseSpiritPoisonTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "cleanse spirit", DISPEL_POISON) { }
};

class PartyMemberCleanseSpiritPoisonTrigger : public PartyMemberNeedCureTrigger
{
    public:
        PartyMemberCleanseSpiritPoisonTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "cleanse spirit", DISPEL_POISON) { }
};

class CleanseSpiritCurseTrigger : public NeedCureTrigger
{
    public:
        CleanseSpiritCurseTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "cleanse spirit", DISPEL_CURSE) { }
};

class PartyMemberCleanseSpiritCurseTrigger : public PartyMemberNeedCureTrigger
{
    public:
        PartyMemberCleanseSpiritCurseTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "cleanse spirit", DISPEL_CURSE) { }
};

class CleanseSpiritDiseaseTrigger : public NeedCureTrigger
{
    public:
        CleanseSpiritDiseaseTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "cleanse spirit", DISPEL_DISEASE) { }
};

class PartyMemberCleanseSpiritDiseaseTrigger : public PartyMemberNeedCureTrigger
{
    public:
        PartyMemberCleanseSpiritDiseaseTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "cleanse spirit", DISPEL_DISEASE) { }
};

class ShockTrigger : public DebuffTrigger
{
    public:
        ShockTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "earth shock") { }

        bool IsActive() override;
};

class FrostShockSnareTrigger : public SnareTargetTrigger
{
    public:
        FrostShockSnareTrigger(PlayerbotAI* botAI) : SnareTargetTrigger(botAI, "frost shock") { }
};

class HeroismTrigger : public BoostTrigger
{
    public:
        HeroismTrigger(PlayerbotAI* botAI) : BoostTrigger(botAI, "heroism") { }
};

class BloodlustTrigger : public BoostTrigger
{
    public:
        BloodlustTrigger(PlayerbotAI* botAI) : BoostTrigger(botAI, "bloodlust") { }
};

class MaelstromWeaponTrigger : public HasAuraTrigger
{
    public:
        MaelstromWeaponTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "maelstrom weapon") { }
};

class WindShearInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
{
    public:
        WindShearInterruptEnemyHealerSpellTrigger(PlayerbotAI* botAI) : InterruptEnemyHealerTrigger(botAI, "wind shear") { }
};

class CurePoisonTrigger : public NeedCureTrigger
{
    public:
        CurePoisonTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "cure poison", DISPEL_POISON) { }
};

class PartyMemberCurePoisonTrigger : public PartyMemberNeedCureTrigger
{
    public:
        PartyMemberCurePoisonTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "cure poison", DISPEL_POISON) { }
};

class CureDiseaseTrigger : public NeedCureTrigger
{
    public:
        CureDiseaseTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "cure disease", DISPEL_DISEASE) { }
};

class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger
{
    public:
        PartyMemberCureDiseaseTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "cure disease", DISPEL_DISEASE) { }
};

#endif
