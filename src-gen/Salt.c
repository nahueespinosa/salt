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
RKH_CREATE_BASIC_STATE(PreventiveBrake, Salt_enPreventiveBrake, NULL, &Enabled, NULL);
RKH_CREATE_BASIC_STATE(TotalStop, Salt_enTotalStop, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(TotalIsolation, Salt_enTotalIsolation, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(Drift, Salt_enDrift, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionEnabled, Salt_enIntermittentTractionEnabled, Salt_exIntermittentTractionEnabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionDisabled, Salt_enIntermittentTractionDisabled, Salt_exIntermittentTractionDisabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentBrake, Salt_enIntermittentBrake, Salt_exIntermittentBrake, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(UnknownCmd, Salt_enUnknownCmd, Salt_exUnknownCmd, &Remote, NULL);
RKH_CREATE_BASIC_STATE(ActiveCmd, Salt_enActiveCmd, Salt_exActiveCmd, &Remote, NULL);
RKH_CREATE_BASIC_STATE(TractionEnabled, Salt_enTractionEnabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(TractionDisabled, Salt_enTractionDisabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(EmergencyBrake, Salt_enEmergencyBrake, Salt_exEmergencyBrake, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionEnabled, Salt_enIntermittentTractionEnabled, Salt_exIntermittentTractionEnabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionDisabled, Salt_enIntermittentTractionDisabled, Salt_exIntermittentTractionDisabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentBrake, Salt_enIntermittentBrake, Salt_exIntermittentBrake, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(Waiting2, NULL, NULL, &Limited, NULL);
RKH_CREATE_BASIC_STATE(Waiting1, NULL, NULL, &Enabled, NULL);

RKH_CREATE_COMP_REGION_STATE(Enabled, Salt_enEnabled, NULL, RKH_ROOT, &Waiting1, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Remote, NULL, NULL, &Enabled, &Salt_C0, Salt_ToSalt_C0Ext7, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Intermittent, NULL, NULL, &Remote, &IntermittentTractionEnabled, Salt_ToIntermittentTractionEnabledExt13, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Limited, NULL, NULL, &Enabled, &Waiting2, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Automatic, NULL, NULL, &Limited, &TractionEnabled, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Intermittent, NULL, NULL, &Limited, &IntermittentTractionEnabled, Salt_ToIntermittentTractionEnabledExt33, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);

RKH_CREATE_TRANS_TABLE(Disabled)
	RKH_TRREG(evSwitchOn, NULL, NULL, &Enabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Enabled)
	RKH_TRREG(evSwitchOff, NULL, NULL, &Disabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(PreventiveBrake)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Limited),
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
	RKH_TRREG(evTout0, NULL, NULL, &IntermittentTractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionDisabled)
	RKH_TRREG(evTout1, NULL, Salt_IntermittentTractionDisabledToSalt_C1Ext15, &Salt_C1),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentBrake)
	RKH_TRREG(evTout2, NULL, Salt_IntermittentBrakeToIntermittentTractionEnabledExt16, &IntermittentTractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UnknownCmd)
	RKH_TRREG(evTout3, NULL, NULL, &// TODO for Exit),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(ActiveCmd)
	RKH_TRREG(evRemoteCmd, Salt_isCondActiveCmdToActiveCmd21, Salt_ActiveCmdToActiveCmdExt21, &ActiveCmd),
	RKH_TRREG(evTout4, NULL, Salt_ActiveCmdToSalt_C2Ext22, &Salt_C2),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Limited)
	RKH_TRREG(evRemoteCmd, Salt_isCondLimitedToRemote25, NULL, &Remote),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Automatic)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionEnabled)
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionEnabledToTractionDisabled28, NULL, &TractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionDisabled)
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionDisabledToEmergencyBrake29, NULL, &EmergencyBrake),
	RKH_TRREG(evSpeedAvailable, Salt_isCondTractionDisabledToTractionEnabled30, NULL, &TractionEnabled),
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
	RKH_TRREG(evTout7, NULL, Salt_IntermittentTractionDisabledToSalt_C3Ext35, &Salt_C3),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentBrake)
	RKH_TRREG(evTout8, NULL, Salt_IntermittentBrakeToIntermittentTractionEnabledExt36, &IntermittentTractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Waiting2)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Waiting1)
	RKH_TRREG(evSpeedLost, NULL, NULL, &PreventiveBrake),
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(Salt_C0);
RKH_CREATE_CHOICE_STATE(Salt_C1);
RKH_CREATE_CHOICE_STATE(Salt_C2);
RKH_CREATE_CHOICE_STATE(Salt_C3);

RKH_CREATE_BRANCH_TABLE(Salt_C0)
	RKH_BRANCH(Salt_isCondSalt_C0ToTotalStop8, NULL, &TotalStop),
	RKH_BRANCH(Salt_isCondSalt_C0ToTotalIsolation9, NULL, &TotalIsolation),
	RKH_BRANCH(Salt_isCondSalt_C0ToDrift10, NULL, &Drift),
	RKH_BRANCH(Salt_isCondSalt_C0ToIntermittent11, NULL, &Intermittent),
	RKH_BRANCH(ELSE, NULL, &UnknownCmd),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C1)
	RKH_BRANCH(Salt_isCondSalt_C1ToIntermittentTractionEnabled17, NULL, &IntermittentTractionEnabled),
	RKH_BRANCH(ELSE, NULL, &IntermittentBrake),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C2)
	RKH_BRANCH(Salt_isCondSalt_C2To// TODO for Exit23, NULL, &// TODO for Exit),
	RKH_BRANCH(ELSE, NULL, &ActiveCmd),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(Salt_C3)
	RKH_BRANCH(Salt_isCondSalt_C3ToIntermittentTractionEnabled37, NULL, &IntermittentTractionEnabled),
	RKH_BRANCH(ELSE, NULL, &IntermittentBrake),
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
