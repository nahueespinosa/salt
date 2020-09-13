/**
 *  \file       mainControl.c
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
#include "MainControl.h"
#include "MainControlAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(Disabled, MainControl_enDisabled, NULL, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(PreventiveBrake, MainControl_enPreventiveBrake, MainControl_exPreventiveBrake, &Enabled, NULL);
RKH_CREATE_BASIC_STATE(TractionEnabled, MainControl_enTractionEnabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(TractionDisabled, MainControl_enTractionDisabled, NULL, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(EmergencyBrake, MainControl_enEmergencyBrake, MainControl_exEmergencyBrake, &Automatic, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionEnabled, MainControl_enIntermittentTractionEnabled, MainControl_exIntermittentTractionEnabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentTractionDisabled, MainControl_enIntermittentTractionDisabled, MainControl_exIntermittentTractionDisabled, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(IntermittentBrake, MainControl_enIntermittentBrake, MainControl_exIntermittentBrake, &Intermittent, NULL);
RKH_CREATE_BASIC_STATE(Waiting2, NULL, NULL, &Limited, NULL);
RKH_CREATE_BASIC_STATE(Waiting1, NULL, NULL, &Enabled, NULL);
RKH_CREATE_BASIC_STATE(Stopped, MainControl_enStopped, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(Isolated, MainControl_enIsolated, NULL, &Remote, NULL);
RKH_CREATE_BASIC_STATE(Adrift, MainControl_enAdrift, NULL, &Remote, NULL);

RKH_CREATE_COMP_REGION_STATE(Enabled, MainControl_enEnabled, NULL, RKH_ROOT, &Waiting1, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Limited, NULL, NULL, &Enabled, &Waiting2, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Automatic, NULL, NULL, &Limited, &TractionEnabled, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Intermittent, NULL, NULL, &Limited, &IntermittentTractionEnabled, MainControl_ToIntermittentTractionEnabledExt15, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_COMP_REGION_STATE(Remote, NULL, NULL, &Enabled, NULL, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);

RKH_CREATE_TRANS_TABLE(Disabled)
	RKH_TRREG(evSwitchOn, NULL, NULL, &Enabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Enabled)
	RKH_TRREG(evSwitchOff, NULL, NULL, &Disabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(PreventiveBrake)
	RKH_TRREG(evTout0, NULL, NULL, &Limited),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Limited)
	RKH_TRREG(evRemoteStop, NULL, NULL, &Stopped),
	RKH_TRREG(evRemoteIsolate, NULL, NULL, &Isolated),
	RKH_TRREG(evRemoteDrift, NULL, NULL, &Adrift),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Automatic)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionEnabled)
	RKH_TRREG(evSpeedAvailable, MainControl_isCondTractionEnabledToTractionDisabled10, NULL, &TractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(TractionDisabled)
	RKH_TRREG(evSpeedAvailable, MainControl_isCondTractionDisabledToEmergencyBrake11, NULL, &EmergencyBrake),
	RKH_TRREG(evSpeedAvailable, MainControl_isCondTractionDisabledToTractionEnabled12, NULL, &TractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(EmergencyBrake)
	RKH_TRREG(evTout1, NULL, NULL, &TractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Intermittent)
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionEnabled)
	RKH_TRREG(evTout2, NULL, NULL, &IntermittentTractionDisabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentTractionDisabled)
	RKH_TRREG(evTout3, NULL, MainControl_IntermittentTractionDisabledToMainControl_C0Ext17, &MainControl_C0),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(IntermittentBrake)
	RKH_TRREG(evTout4, NULL, MainControl_IntermittentBrakeToIntermittentTractionEnabledExt18, &IntermittentTractionEnabled),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Waiting2)
	RKH_TRREG(evSpeedLost, NULL, NULL, &Intermittent),
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Waiting1)
	RKH_TRREG(evSpeedLost, NULL, NULL, &PreventiveBrake),
	RKH_TRREG(evSpeedAvailable, NULL, NULL, &Automatic),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Remote)
	RKH_TRREG(evRemoteExit, NULL, NULL, &Limited),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Stopped)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Isolated)
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Adrift)
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(MainControl_C0);

RKH_CREATE_BRANCH_TABLE(MainControl_C0)
	RKH_BRANCH(MainControl_isCondMainControl_C0ToIntermittentTractionEnabled19, NULL, &IntermittentTractionEnabled),
	RKH_BRANCH(ELSE, NULL, &IntermittentBrake),
RKH_END_BRANCH_TABLE


/* ............................. Active object ............................. */
RKH_SMA_CREATE(MainControl, mainControl, MainControlPrio, HCAL, &Disabled, MainControl_ToDisabledExt0, NULL);
RKH_SMA_DEF_PTR(mainControl);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
