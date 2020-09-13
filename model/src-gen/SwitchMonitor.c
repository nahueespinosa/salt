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
	RKH_TRREG(evTout0, NULL, NULL, &SwitchMonitor_C0),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(SwitchOn)
	RKH_TRREG(evTout1, NULL, NULL, &SwitchMonitor_C2),
RKH_END_TRANS_TABLE

RKH_CREATE_CHOICE_STATE(SwitchMonitor_C0);
RKH_CREATE_CHOICE_STATE(SwitchMonitor_C1);
RKH_CREATE_CHOICE_STATE(SwitchMonitor_C2);
RKH_CREATE_CHOICE_STATE(SwitchMonitor_C3);

RKH_CREATE_BRANCH_TABLE(SwitchMonitor_C0)
	RKH_BRANCH(SwitchMonitor_isCondSwitchMonitor_C0ToSwitchMonitor_C13, SwitchMonitor_SwitchMonitor_C0ToSwitchMonitor_C1Ext3, &SwitchMonitor_C1),
	RKH_BRANCH(ELSE, SwitchMonitor_SwitchMonitor_C0ToSwitchOffExt4, &SwitchOff),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(SwitchMonitor_C1)
	RKH_BRANCH(SwitchMonitor_isCondSwitchMonitor_C1ToSwitchOn5, SwitchMonitor_SwitchMonitor_C1ToSwitchOnExt5, &SwitchOn),
	RKH_BRANCH(ELSE, NULL, &SwitchOff),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(SwitchMonitor_C2)
	RKH_BRANCH(SwitchMonitor_isCondSwitchMonitor_C2ToSwitchMonitor_C37, SwitchMonitor_SwitchMonitor_C2ToSwitchMonitor_C3Ext7, &SwitchMonitor_C3),
	RKH_BRANCH(ELSE, SwitchMonitor_SwitchMonitor_C2ToSwitchOnExt8, &SwitchOn),
RKH_END_BRANCH_TABLE

RKH_CREATE_BRANCH_TABLE(SwitchMonitor_C3)
	RKH_BRANCH(SwitchMonitor_isCondSwitchMonitor_C3ToSwitchOff9, SwitchMonitor_SwitchMonitor_C3ToSwitchOffExt9, &SwitchOff),
	RKH_BRANCH(ELSE, NULL, &SwitchOn),
RKH_END_BRANCH_TABLE


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
