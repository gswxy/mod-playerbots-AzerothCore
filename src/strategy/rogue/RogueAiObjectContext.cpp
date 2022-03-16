/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "RogueAiObjectContext.h"
#include "DpsRogueStrategy.h"
#include "GenericRogueNonCombatStrategy.h"
#include "RogueActions.h"
#include "RogueComboActions.h"
#include "RogueFinishingActions.h"
#include "RogueOpeningActions.h"
#include "RogueTriggers.h"
#include "NamedObjectContext.h"
#include "PullStrategy.h"
#include "Playerbots.h"

class RogueStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        RogueStrategyFactoryInternal()
        {
            creators["dps"] = &RogueStrategyFactoryInternal::dps;
            creators["nc"] = &RogueStrategyFactoryInternal::nc;
            creators["pull"] = &RogueStrategyFactoryInternal::pull;
            creators["aoe"] = &RogueStrategyFactoryInternal::aoe;
            creators["boost"] = &RogueStrategyFactoryInternal::boost;
            creators["stealthed"] = &RogueStrategyFactoryInternal::stealthed;
            creators["stealth"] = &RogueStrategyFactoryInternal::stealth;
            creators["cc"] = &RogueStrategyFactoryInternal::cc;
        }

    private:
        static Strategy* boost(PlayerbotAI* botAI) { return new RogueBoostStrategy(botAI); }
        static Strategy* aoe(PlayerbotAI* botAI) { return new RogueAoeStrategy(botAI); }
        static Strategy* dps(PlayerbotAI* botAI) { return new DpsRogueStrategy(botAI); }
        static Strategy* nc(PlayerbotAI* botAI) { return new GenericRogueNonCombatStrategy(botAI); }
        static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(botAI, "shoot"); }
        static Strategy* stealthed(PlayerbotAI* botAI) { return new StealthedRogueStrategy(botAI); }
        static Strategy* stealth(PlayerbotAI* botAI) { return new StealthStrategy(botAI); }
        static Strategy* cc(PlayerbotAI* botAI) { return new RogueCcStrategy(botAI); }
};

class RogueTriggerFactoryInternal : public NamedObjectContext<Trigger>
{
    public:
        RogueTriggerFactoryInternal()
        {
            creators["kick"] = &RogueTriggerFactoryInternal::kick;
            creators["rupture"] = &RogueTriggerFactoryInternal::rupture;
            creators["slice and dice"] = &RogueTriggerFactoryInternal::slice_and_dice;
            creators["expose armor"] = &RogueTriggerFactoryInternal::expose_armor;
            creators["kick on enemy healer"] = &RogueTriggerFactoryInternal::kick_on_enemy_healer;
            creators["unstealth"] = &RogueTriggerFactoryInternal::unstealth;
            creators["sap"] = &RogueTriggerFactoryInternal::sap;
            creators["in stealth"] = &RogueTriggerFactoryInternal::in_stealth;
            creators["no stealth"] = &RogueTriggerFactoryInternal::no_stealth;
            creators["stealth"] = &RogueTriggerFactoryInternal::stealth;
            creators["sprint"] = &RogueTriggerFactoryInternal::sprint;
        }

    private:
        static Trigger* adrenaline_rush(PlayerbotAI* botAI) { return new AdrenalineRushTrigger(botAI); }
        static Trigger* kick(PlayerbotAI* botAI) { return new KickInterruptSpellTrigger(botAI); }
        static Trigger* rupture(PlayerbotAI* botAI) { return new RuptureTrigger(botAI); }
        static Trigger* slice_and_dice(PlayerbotAI* botAI) { return new SliceAndDiceTrigger(botAI); }
        static Trigger* expose_armor(PlayerbotAI* botAI) { return new ExposeArmorTrigger(botAI); }
        static Trigger* kick_on_enemy_healer(PlayerbotAI* botAI) { return new KickInterruptEnemyHealerSpellTrigger(botAI); }
        static Trigger* unstealth(PlayerbotAI* botAI) { return new UnstealthTrigger(botAI); }
        static Trigger* sap(PlayerbotAI* botAI) { return new SapTrigger(botAI); }
        static Trigger* in_stealth(PlayerbotAI* botAI) { return new InStealthTrigger(botAI); }
        static Trigger* no_stealth(PlayerbotAI* botAI) { return new NoStealthTrigger(botAI); }
        static Trigger* stealth(PlayerbotAI* botAI) { return new StealthTrigger(botAI); }
        static Trigger* sprint(PlayerbotAI* botAI) { return new SprintTrigger(botAI); }
};

class RogueAiObjectContextInternal : public NamedObjectContext<Action>
{
    public:
        RogueAiObjectContextInternal()
        {
            creators["riposte"] = &RogueAiObjectContextInternal::riposte;
            creators["mutilate"] = &RogueAiObjectContextInternal::mutilate;
            creators["sinister strike"] = &RogueAiObjectContextInternal::sinister_strike;
            creators["kidney shot"] = &RogueAiObjectContextInternal::kidney_shot;
            creators["rupture"] = &RogueAiObjectContextInternal::rupture;
            creators["slice and dice"] = &RogueAiObjectContextInternal::slice_and_dice;
            creators["eviscerate"] = &RogueAiObjectContextInternal::eviscerate;
            creators["vanish"] = &RogueAiObjectContextInternal::vanish;
            creators["evasion"] = &RogueAiObjectContextInternal::evasion;
            creators["kick"] = &RogueAiObjectContextInternal::kick;
            creators["feint"] = &RogueAiObjectContextInternal::feint;
            creators["backstab"] = &RogueAiObjectContextInternal::backstab;
            creators["expose armor"] = &RogueAiObjectContextInternal::expose_armor;
            creators["kick on enemy healer"] = &RogueAiObjectContextInternal::kick_on_enemy_healer;
            creators["blade flurry"] = &RogueAiObjectContextInternal::blade_flurry;
            creators["adrenaline rush"] = &RogueAiObjectContextInternal::adrenaline_rush;
            creators["ambush"] = &RogueAiObjectContextInternal::ambush;
            creators["stealth"] = &RogueAiObjectContextInternal::stealth;
            creators["sprint"] = &RogueAiObjectContextInternal::sprint;
            creators["garrote"] = &RogueAiObjectContextInternal::garrote;
            creators["cheap shot"] = &RogueAiObjectContextInternal::cheap_shot;
            creators["blind"] = &RogueAiObjectContextInternal::blind;
            creators["unstealth"] = &RogueAiObjectContextInternal::unstealth;
            creators["sap"] = &RogueAiObjectContextInternal::sap;
            creators["check stealth"] = &RogueAiObjectContextInternal::check_stealth;
        }

    private:
        static Action* adrenaline_rush(PlayerbotAI* botAI) { return new CastAdrenalineRushAction(botAI); }
        static Action* blade_flurry(PlayerbotAI* botAI) { return new CastBladeFlurryAction(botAI); }
        static Action* riposte(PlayerbotAI* botAI) { return new CastRiposteAction(botAI); }
        static Action* mutilate(PlayerbotAI* botAI) { return new CastMutilateAction(botAI); }
        static Action* sinister_strike(PlayerbotAI* botAI) { return new CastSinisterStrikeAction(botAI); }
        static Action* kidney_shot(PlayerbotAI* botAI) { return new CastKidneyShotAction(botAI); }
        static Action* rupture(PlayerbotAI* botAI) { return new CastRuptureAction(botAI); }
        static Action* slice_and_dice(PlayerbotAI* botAI) { return new CastSliceAndDiceAction(botAI); }
        static Action* eviscerate(PlayerbotAI* botAI) { return new CastEviscerateAction(botAI); }
        static Action* vanish(PlayerbotAI* botAI) { return new CastVanishAction(botAI); }
        static Action* evasion(PlayerbotAI* botAI) { return new CastEvasionAction(botAI); }
        static Action* kick(PlayerbotAI* botAI) { return new CastKickAction(botAI); }
        static Action* feint(PlayerbotAI* botAI) { return new CastFeintAction(botAI); }
        static Action* backstab(PlayerbotAI* botAI) { return new CastBackstabAction(botAI); }
        static Action* expose_armor(PlayerbotAI* botAI) { return new CastExposeArmorAction(botAI); }
        static Action* kick_on_enemy_healer(PlayerbotAI* botAI) { return new CastKickOnEnemyHealerAction(botAI); }
        static Action* ambush(PlayerbotAI* botAI) { return new CastAmbushAction(botAI); }
        static Action* stealth(PlayerbotAI* botAI) { return new CastStealthAction(botAI); }
        static Action* sprint(PlayerbotAI* botAI) { return new CastSprintAction(botAI); }
        static Action* garrote(PlayerbotAI* botAI) { return new CastGarroteAction(botAI); }
        static Action* cheap_shot(PlayerbotAI* botAI) { return new CastCheapShotAction(botAI); }
        static Action* blind(PlayerbotAI* botAI) { return new CastBlindAction(botAI); }
        static Action* check_stealth(PlayerbotAI* botAI) { return new CheckStealthAction(botAI); }
        static Action* sap(PlayerbotAI* botAI) { return new CastSapAction(botAI); }
        static Action* unstealth(PlayerbotAI* botAI) { return new UnstealthAction(botAI); }
};

RogueAiObjectContext::RogueAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new RogueStrategyFactoryInternal());
    actionContexts.Add(new RogueAiObjectContextInternal());
    triggerContexts.Add(new RogueTriggerFactoryInternal());
}
