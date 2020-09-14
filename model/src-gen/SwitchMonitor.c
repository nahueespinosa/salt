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
RKH_CREATE_BASIC_STATE(SwitchRising, SwitchMonitor_enSwitchRising, SwitchMonitor_exSwitchRising, RKH_ROOT, NULL);
RKH_CREATE_BASIC_STATE(SwitchFalling, SwitchMonitor_enSwitchFalling, SwitchMonitor_exSwitchFalling, RKH_ROOT, NULL);


RKH_CREATE_TRANS_TABLE(SwitchOff)
	RKH_TRREG(evTout0, SwitchMonitor_isCondSwitchOffToSwitchRising1, NULL, &SwitchRising),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SwitchOn)
	RKH_TRREG(evTout1, SwitchMonitor_isCondSwitchOnToSwitchFalling2, NULL, &SwitchFalling),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SwitchRising)
	RKH_TRREG(evTout2, NULL, SwitchMonitor_SwitchRisingToSwitchOnExt3, &SwitchOn),
	RKH_TRREG(evTout3, SwitchMonitor_isCondSwitchRisingToSwitchOff4, NULL, &SwitchOff),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SwitchFalling)
	RKH_TRREG(evTout4, NULL, SwitchMonitor_SwitchFallingToSwitchOffExt5, &SwitchOff),
	RKH_TRREG(evTout5, SwitchMonitor_isCondSwitchFallingToSwitchOn6, NULL, &SwitchOn),
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
