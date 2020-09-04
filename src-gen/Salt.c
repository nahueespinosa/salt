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
RKH_CREATE_BASIC_STATE(Remote, Salt_enRemote, Salt_exRemote, &Enabled, NULL);
RKH_CREATE_BASIC_STATE(Automatic, NULL, NULL, &Limited, NULL);
RKH_CREATE_BASIC_STATE(Intermittent, NULL, NULL, &Limited, NULL);
RKH_CREATE_BASIC_STATE(SpeedMissing, Salt_enSpeedMissing, Salt_exSpeedMissing, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingHaslerSpeed, Salt_enUsingHaslerSpeed, Salt_exUsingHaslerSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingPulseGenSpeed, Salt_enUsingPulseGenSpeed, Salt_exUsingPulseGenSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingGPSSpeed, Salt_enUsingGPSSpeed, Salt_exUsingGPSSpeed, RKH_ROOT, NULL);

RKH_CREATE_COMP_REGION_STATE(Enabled, Salt_enEnabled, NULL, RKH_ROOT, &Salt_C1, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Limited, NULL, NULL, &Enabled, &Salt_C0, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);

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
	RKH_TRREG(evTout1, NULL, NULL, &Limited),
	RKH_TRREG(evRemoteCmd, NULL, NULL, &Remote),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Limited)
	RKH_TRREG(evRemoteCmd, NULL, NULL, &Remote),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Automatic)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Intermittent)
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SpeedMissing)
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRINT(evTout5, NULL, Salt_SpeedMissingToSpeedMissingLoc5),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingHaslerSpeed)
	RKH_TRREG(evTout2, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingPulseGenSpeed)
	RKH_TRREG(evTout3, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingGPSSpeed)
	RKH_TRREG(evTout4, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(Salt_C0);
RKH_CREATE_CHOICE_STATE(Salt_C1);

RKH_CREATE_BRANCH_TABLE(Salt_C0)
	RKH_BRANCH(Salt_isCondSalt_C0ToAutomatic11, NULL, &Automatic),
	RKH_BRANCH(ELSE, NULL, &Intermittent),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C1)
	RKH_BRANCH(Salt_isCondSalt_C1ToLimited14, NULL, &Limited),
	RKH_BRANCH(ELSE, NULL, &PreventiveBrake),
RKH_END_BRANCH_TABLE


/* ............................. Active object ............................. */
RKH_SMA_CREATE(Salt, salt, SaltPrio, HCAL, &Disabled, NULL, NULL);
RKH_SMA_DEF_PTR(salt);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
