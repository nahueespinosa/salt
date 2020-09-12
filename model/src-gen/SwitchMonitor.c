/**
 *  \file       switchMonitor.c
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
#include "SwitchMonitor.h"
#include "SwitchMonitorAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(SwitchOff, SwitchMonitor_enSwitchOff, SwitchMonitor_exSwitchOff, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(SwitchOn, SwitchMonitor_enSwitchOn, SwitchMonitor_exSwitchOn, RKH_ROOT, NULL);


RKH_CREATE_TRANS_TABLE(SwitchOff)
	RKH_TRREG(evTout0, SwitchMonitor_isCondSwitchOffToSwitchOn1, SwitchMonitor_SwitchOffToSwitchOnExt1, &SwitchOn),
	RKH_TRINT(evTout2, NULL, SwitchMonitor_SwitchOffToSwitchOffLoc0),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SwitchOn)
	RKH_TRREG(evTout1, SwitchMonitor_isCondSwitchOnToSwitchOff2, SwitchMonitor_SwitchOnToSwitchOffExt2, &SwitchOff),
	RKH_TRINT(evTout3, NULL, SwitchMonitor_SwitchOnToSwitchOnLoc1),
RKH_END_TRANS_TABLE



/* ............................. Active object ............................. */
RKH_SMA_CREATE(SwitchMonitor, switchMonitor, SwitchMonitorPrio, HCAL, &SwitchOff, SwitchMonitor_ToSwitchOffExt0, NULL);
RKH_SMA_DEF_PTR(switchMonitor);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
