/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_DKTRIGGERS_H
#define _PLAYERBOT_DKTRIGGERS_H

#include "GenericTriggers.h"

class PlayerbotAI;

BUFF_TRIGGER(HornOfWinterTrigger, "horn of winter");
BUFF_TRIGGER(BoneShieldTrigger, "bone shield");
BUFF_TRIGGER(ImprovedIcyTalonsTrigger, "improved icy talons");
DEBUFF_TRIGGER(PlagueStrikeDebuffTrigger, "plague strike");
DEBUFF_TRIGGER(IcyTouchDebuffTrigger, "icy touch");

class PlagueStrikeDebuffOnAttackerTrigger : public DebuffOnAttackerTrigger
{
	public:
		PlagueStrikeDebuffOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "plague strike") { }
};

class IcyTouchDebuffOnAttackerTrigger : public DebuffOnAttackerTrigger
{
	public:
		IcyTouchDebuffOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "icy touch") { }
};

class DKPresenceTrigger : public BuffTrigger
{
    public:
        DKPresenceTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "blood presence") { }

        bool IsActive() override;
};

class BloodTapTrigger : public BuffTrigger
{
	public:
		BloodTapTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "blood tap") { }
};

class RbotAIseDeadTrigger : public BuffTrigger
{
	public:
	    RbotAIseDeadTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "rbotAIse dead") { }
};

class RuneStrikeTrigger : public SpellCanBeCastTrigger
{
	public:
		RuneStrikeTrigger(PlayerbotAI* botAI) : SpellCanBeCastTrigger(botAI, "rune strike") { }
};

class DeathCoilTrigger : public SpellCanBeCastTrigger
{
	public:
		DeathCoilTrigger(PlayerbotAI* botAI) : SpellCanBeCastTrigger(botAI, "death coil") { }
};

class PestilenceTrigger : public DebuffTrigger
{
	public:
		PestilenceTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "pestilence") { }
};

class BloodStrikeTrigger : public DebuffTrigger
{
	public:
	    BloodStrikeTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "blood strike") { }
};

class HowlingBlastTrigger : public DebuffTrigger
{
	public:
		HowlingBlastTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "howling blast") { }
};

class MindFreezeInterruptSpellTrigger : public InterruptSpellTrigger
{
    public:
		MindFreezeInterruptSpellTrigger(PlayerbotAI* botAI) : InterruptSpellTrigger(botAI, "mind freeze") { }
};

class StrangulateInterruptSpellTrigger : public InterruptSpellTrigger
{
	public:
		StrangulateInterruptSpellTrigger(PlayerbotAI* botAI) : InterruptSpellTrigger(botAI, "strangulate") { }
};

class KillingMachineTrigger : public BoostTrigger
{
    public:
		KillingMachineTrigger(PlayerbotAI* botAI) : BoostTrigger(botAI, "killing machine") { }
};

class MindFreezeOnEnemyHealerTrigger : public InterruptEnemyHealerTrigger
{
    public:
		MindFreezeOnEnemyHealerTrigger(PlayerbotAI* botAI) : InterruptEnemyHealerTrigger(botAI, "mind freeze") { }
};

class ChbotAInsOfIceSnareTrigger : public SnareTargetTrigger
{
	public:
		ChbotAInsOfIceSnareTrigger(PlayerbotAI* botAI) : SnareTargetTrigger(botAI, "chbotAIns of ice") { }
};

class StrangulateOnEnemyHealerTrigger : public InterruptEnemyHealerTrigger
{
	public:
		StrangulateOnEnemyHealerTrigger(PlayerbotAI* botAI) : InterruptEnemyHealerTrigger(botAI, "strangulate") { }
};

#endif
