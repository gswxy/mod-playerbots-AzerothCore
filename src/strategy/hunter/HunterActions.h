/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_HUNTERACTIONS_H
#define _PLAYERBOT_HUNTERACTIONS_H

#include "GenericSpellActions.h"

class PlayerbotAI;
class Unit;

BEGIN_RANGED_SPELL_ACTION(CastHuntersMarkAction, "hunter's mark")
END_SPELL_ACTION()

class CastAutoShotAction : public CastSpellAction
{
    public:
        CastAutoShotAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "auto shot") { }

        bool isUseful() override;
};

BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastExplosiveShotAction, "explosive shot")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastAimedShotAction, "aimed shot")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastChimeraShotAction, "chimera shot")
END_SPELL_ACTION()

class CastConcussiveShotAction : public CastSnareSpellAction
{
    public:
        CastConcussiveShotAction(PlayerbotAI* botAI) : CastSnareSpellAction(botAI, "concussive shot") { }
};

BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastVolleyAction, "volley")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastSerpentStingAction, "serpent sting")
bool isUseful() override;
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastWyvernStingAction, "wyvern sting")
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastViperStingAction, "viper sting")
bool isUseful() override;
END_SPELL_ACTION()

BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
END_SPELL_ACTION()

class CastAspectOfTheHawkAction : public CastBuffSpellAction
{
	public:
		CastAspectOfTheHawkAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "aspect of the hawk") { }
};

class CastAspectOfTheWildAction : public CastBuffSpellAction
{
	public:
		CastAspectOfTheWildAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "aspect of the wild") { }
};

class CastAspectOfTheCheetahAction : public CastBuffSpellAction
{
	public:
		CastAspectOfTheCheetahAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "aspect of the cheetah") { }

		bool isUseful() override;
};

class CastAspectOfThePackAction : public CastBuffSpellAction
{
	public:
		CastAspectOfThePackAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "aspect of the pack") { }
};

class CastAspectOfTheViperAction : public CastBuffSpellAction
{
	public:
		CastAspectOfTheViperAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "aspect of the viper") { }
};

class CastCallPetAction : public CastBuffSpellAction
{
	public:
		CastCallPetAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "call pet") { }
};

class CastMendPetAction : public CastAuraSpellAction
{
	public:
		CastMendPetAction(PlayerbotAI* botAI) : CastAuraSpellAction(botAI, "mend pet") { }

		std::string const GetTargetName() override { return "pet target"; }
};

class CastRevivePetAction : public CastBuffSpellAction
{
	public:
		CastRevivePetAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "revive pet") { }
};

class CastTrueshotAuraAction : public CastBuffSpellAction
{
    public:
        CastTrueshotAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "trueshot aura") { }
};

class CastFeignDeathAction : public CastBuffSpellAction
{
    public:
        CastFeignDeathAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "feign death") { }
};

class CastRapidFireAction : public CastBuffSpellAction
{
	public:
		CastRapidFireAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "rapid fire") { }
};

class CastReadinessAction : public CastBuffSpellAction
{
	public:
		CastReadinessAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "readiness") { }
};

class CastBlackArrow : public CastDebuffSpellAction
{
	public:
		CastBlackArrow(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "black arrow") { }
};

class CastFreezingTrap : public CastDebuffSpellAction
{
    public:
        CastFreezingTrap(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "freezing trap") { }

        Value<Unit*>* GetTargetValue() override;
};

class CastWingClipAction : public CastMeleeSpellAction
{
    public:
        CastWingClipAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "wing clip") { }

        bool isUseful() override;
        NextAction** getPrerequisites() override;
};

class CastRaptorStrikeAction : public CastMeleeSpellAction
{
    public:
        CastRaptorStrikeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "raptor strike") { }

        bool isUseful() override;
};

class CastSerpentStingOnAttackerAction : public CastDebuffSpellOnAttackerAction
{
    public:
        CastSerpentStingOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "serpent sting") { }
};

class FeedPetAction : public Action
{
    public:
        FeedPetAction(PlayerbotAI* botAI) : Action(botAI, "feed pet") { }

        bool Execute(Event event) override;
};

class CastBestialWrathAction : public CastBuffSpellAction
{
    public:
        CastBestialWrathAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "bestial wrath") { }
};

class CastScareBeastAction : public CastSpellAction
{
    public:
        CastScareBeastAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "scare beast") { }
};

class CastScareBeastCcAction : public CastSpellAction
{
    public:
        CastScareBeastCcAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "scare beast on cc") { }

        Value<Unit*>* GetTargetValue() override;
        bool Execute(Event event) override;
};

#endif
