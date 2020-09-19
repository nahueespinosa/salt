/**
 *  \file       speedMonitor.c
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
#include "SpeedMonitor.h"
#include "SpeedMonitorAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(SpeedMissing, SpeedMonitor_enSpeedMissing, SpeedMonitor_exSpeedMissing, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingHaslerSpeed, SpeedMonitor_enUsingHaslerSpeed, SpeedMonitor_exUsingHaslerSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingPulseGenSpeed, SpeedMonitor_enUsingPulseGenSpeed, SpeedMonitor_exUsingPulseGenSpeed, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(UsingGPSSpeed, SpeedMonitor_enUsingGPSSpeed, SpeedMonitor_exUsingGPSSpeed, RKH_ROOT, NULL);


RKH_CREATE_TRANS_TABLE(SpeedMissing)
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRINT(evTout3, NULL, SpeedMonitor_SpeedMissingToSpeedMissingLoc0),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingHaslerSpeed)
	RKH_TRREG(evTout0, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingPulseGenSpeed)
	RKH_TRREG(evTout1, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(UsingGPSSpeed)
	RKH_TRREG(evTout2, NULL, NULL, &SpeedMissing),
	RKH_TRREG(evPulseGenSpeedValid, NULL, NULL, &UsingPulseGenSpeed),
	RKH_TRREG(evGPSSpeedValid, NULL, NULL, &UsingGPSSpeed),
	RKH_TRREG(evHaslerSpeedValid, NULL, NULL, &UsingHaslerSpeed),
RKH_END_TRANS_TABLE



/* ............................. Active object ............................. */
RKH_SMA_CREATE(SpeedMonitor, speedMonitor, SpeedMonitorPrio, HCAL, &SpeedMissing, SpeedMonitor_ToSpeedMissingExt0, NULL);
RKH_SMA_DEF_PTR(speedMonitor);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
