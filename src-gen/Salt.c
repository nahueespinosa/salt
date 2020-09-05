/**
 *  \file       salt.c
 *  \brief      Active object implementation.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhsma.h"
#include "signals.h"
#include "Salt.h"
#include "SaltAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(Disabled, Salt_enDisabled, NULL, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(PreventiveBrake, Salt_enPreventiveBrake, Salt_exPreventiveBrake, &Enabled, NULL);
RKH_CREATE_BASIC_STATE(TotalStop, Salt_enTotalStop, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(TotalIsolation, Salt_enTotalIsolation, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(Drift, Salt_enDrift, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionEnabled, Salt_enIntermittentTractionEnabled, Salt_exIntermittentTractionEnabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionDisabled, Salt_enIntermittentTractionDisabled, Salt_exIntermittentTractionDisabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentBrake, Salt_enIntermittentBrake, Salt_exIntermittentBrake, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(Exiting, Salt_enExiting, Salt_exExiting, &Remote, NULL);
RKH_CREATE_BASIC_STATE(TimerCounting, Salt_enTimerCounting, Salt_exTimerCounting, &Remote, NULL);
RKH_CREATE_BASIC_STATE(TractionEnabled, Salt_enTractionEnabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(TractionDisabled, Salt_enTractionDisabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(EmergencyBrake, Salt_enEmergencyBrake, Salt_exEmergencyBrake, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionEnabled, Salt_enIntermittentTractionEnabled, Salt_exIntermittentTractionEnabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionDisabled, Salt_enIntermittentTractionDisabled, Salt_exIntermittentTractionDisabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentBrake, Salt_enIntermittentBrake, Salt_exIntermittentBrake, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(SpeedMissing, Salt_enSpeedMissing, Salt_exSpeedMissing, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingHaslerSpeed, Salt_enUsingHaslerSpeed, Salt_exUsingHaslerSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingPulseGenSpeed, Salt_enUsingPulseGenSpeed, Salt_exUsingPulseGenSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingGPSSpeed, Salt_enUsingGPSSpeed, Salt_exUsingGPSSpeed, RKH_ROOT, NULL);

RKH_CREATE_COMP_REGION_STATE(Enabled, Salt_enEnabled, NULL, RKH_ROOT, &Salt_C4, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Remote, NULL, NULL, &Enabled, &Salt_C0, Salt_ToSalt_C0Ext7, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Intermittent, NULL, NULL, &Remote, &IntermittentTractionEnabled, Salt_ToIntermittentTractionEnabledExt13, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Limited, NULL, NULL, &Enabled, &Salt_C3, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Automatic, NULL, NULL, &Limited, &TractionEnabled, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Intermittent, NULL, NULL, &Limited, &IntermittentTractionEnabled, Salt_ToIntermittentTractionEnabledExt31, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);

RKH_CREATE_TRANS_TABLE(Disabled)
	RKH_TRREG(evSwitchOn, NULL, NULL, &Enabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Enabled)
	RKH_TRREG(evSwitchOff, NULL, NULL, &Disabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(PreventiveBrake)
	RKH_TRREG(evTout0, NULL, NULL, &Limited),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Remote)
	RKH_TRREG(evRemoteCmd, Salt_isCondRemoteToLimited6, NULL, &Limited),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TotalStop)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TotalIsolation)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Drift)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Intermittent)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionEnabled)
	RKH_TRREG(evTout1, NULL, NULL, &IntermittentTractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionDisabled)
	RKH_TRREG(evTout2, NULL, Salt_IntermittentTractionDisabledToSalt_C1Ext15, &Salt_C1),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentBrake)
	RKH_TRREG(evTout3, NULL, Salt_IntermittentBrakeToIntermittentTractionEnabledExt16, &IntermittentTractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Exiting)
	RKH_TRREG(evTout4, NULL, NULL, &// TODO for Exit),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TimerCounting)
	RKH_TRREG(evRemoteCmd, Salt_isCondTimerCountingToTimerCounting22, Salt_TimerCountingToTimerCountingExt22, &TimerCounting),
	RKH_TRINT(evTout12, NULL, Salt_TimerCountingToTimerCountingLoc10),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Limited)
	RKH_TRREG(evRemoteCmd, Salt_isCondLimitedToRemote23, NULL, &Remote),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Automatic)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionEnabled)
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionEnabledToTractionDisabled26, NULL, &TractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionDisabled)
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionDisabledToEmergencyBrake27, NULL, &EmergencyBrake),
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionDisabledToTractionEnabled28, NULL, &TractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(EmergencyBrake)
	RKH_TRREG(evTout5, NULL, NULL, &TractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Intermittent)
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionEnabled)
	RKH_TRREG(evTout6, NULL, NULL, &IntermittentTractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionDisabled)
	RKH_TRREG(evTout7, NULL, Salt_IntermittentTractionDisabledToSalt_C2Ext33, &Salt_C2),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentBrake)
	RKH_TRREG(evTout8, NULL, Salt_IntermittentBrakeToIntermittentTractionEnabledExt34, &IntermittentTractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SpeedMissing)
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRINT(evTout13, NULL, Salt_SpeedMissingToSpeedMissingLoc21),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingHaslerSpeed)
	RKH_TRREG(evTout9, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingPulseGenSpeed)
	RKH_TRREG(evTout10, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingGPSSpeed)
	RKH_TRREG(evTout11, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(Salt_C0);
RKH_CREATE_CHOICE_STATE(Salt_C1);
RKH_CREATE_CHOICE_STATE(Salt_C2);
RKH_CREATE_CHOICE_STATE(Salt_C3);
RKH_CREATE_CHOICE_STATE(Salt_C4);

RKH_CREATE_BRANCH_TABLE(Salt_C0)
	RKH_BRANCH(Salt_isCondSalt_C0ToTotalStop8, NULL, &TotalStop),
	RKH_BRANCH(Salt_isCondSalt_C0ToTotalIsolation9, NULL, &TotalIsolation),
	RKH_BRANCH(Salt_isCondSalt_C0ToDrift10, NULL, &Drift),
	RKH_BRANCH(Salt_isCondSalt_C0ToIntermittent11, NULL, &Intermittent),
	RKH_BRANCH(ELSE, NULL, &Exiting),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C1)
	RKH_BRANCH(Salt_isCondSalt_C1ToIntermittentTractionEnabled17, NULL, &IntermittentTractionEnabled),
	RKH_BRANCH(ELSE, NULL, &IntermittentBrake),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C2)
	RKH_BRANCH(Salt_isCondSalt_C2ToIntermittentTractionEnabled35, NULL, &IntermittentTractionEnabled),
	RKH_BRANCH(ELSE, NULL, &IntermittentBrake),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C3)
	RKH_BRANCH(Salt_isCondSalt_C3ToAutomatic38, NULL, &Automatic),
	RKH_BRANCH(ELSE, NULL, &Intermittent),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C4)
	RKH_BRANCH(Salt_isCondSalt_C4ToLimited41, NULL, &Limited),
	RKH_BRANCH(ELSE, NULL, &PreventiveBrake),
RKH_END_BRANCH_TABLE


/* ............................. Active object ............................. */
RKH_SMA_CREATE(Salt, salt, SaltPrio, HCAL, &Disabled, Salt_ToSalt_C0Ext7, NULL);
RKH_SMA_DEF_PTR(salt);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
