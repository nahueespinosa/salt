/**
 *  \file       SwitchMonitor.c
 *  \brief      Active object's action implementations.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhtmr.h"
#include "signals.h"
#include "SwitchMonitor.h"
#include "SwitchMonitorAct.h"
#include "bsp.h"
#include "SwitchMonitorActRequired.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_MS(100)
#define WaitTime1	RKH_TIME_MS(100)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rInt switchCounter = 0;

static RKH_STATIC_EVENT(evSwitchOnObj, evSwitchOn);
static RKH_STATIC_EVENT(evSwitchOffObj, evSwitchOff);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
SwitchMonitor_ToSwitchOffExt0(SwitchMonitor *const me, RKH_EVT_T *pe)
{
		
	RKH_TR_FWK_AO(me);
	RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
	RKH_TR_FWK_STATE(me, &SwitchOff);
	RKH_TR_FWK_STATE(me, &SwitchOn);
	RKH_TR_FWK_SIG(evSwitchOn);
	RKH_TR_FWK_SIG(evSwitchOff);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_ToSwitchOffExt0, "ToSwitchOffExt0");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C0ToSwitchMonitor_C1Ext3, "SwitchMonitor_C0ToSwitchMonitor_C1Ext3");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C0ToSwitchOffExt4, "SwitchMonitor_C0ToSwitchOffExt4");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C1ToSwitchOnExt5, "SwitchMonitor_C1ToSwitchOnExt5");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C2ToSwitchMonitor_C3Ext7, "SwitchMonitor_C2ToSwitchMonitor_C3Ext7");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C2ToSwitchOnExt8, "SwitchMonitor_C2ToSwitchOnExt8");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchMonitor_C3ToSwitchOffExt9, "SwitchMonitor_C3ToSwitchOffExt9");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchMonitor_C0ToSwitchMonitor_C13, "isCondSwitchMonitor_C0ToSwitchMonitor_C13");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchMonitor_C1ToSwitchOn5, "isCondSwitchMonitor_C1ToSwitchOn5");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchMonitor_C2ToSwitchMonitor_C37, "isCondSwitchMonitor_C2ToSwitchMonitor_C37");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchMonitor_C3ToSwitchOff9, "isCondSwitchMonitor_C3ToSwitchOff9");
	#endif
	
	switchInit();
	switchCounter = 0;
}

void 
SwitchMonitor_SwitchMonitor_C0ToSwitchMonitor_C1Ext3(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter++;
}

void 
SwitchMonitor_SwitchMonitor_C0ToSwitchOffExt4(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter = 0;
}

void 
SwitchMonitor_SwitchMonitor_C1ToSwitchOnExt5(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter = 0;
	rkh_pubsub_publish(0, &evSwitchOnObj, me);
}

void 
SwitchMonitor_SwitchMonitor_C2ToSwitchMonitor_C3Ext7(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter++;
}

void 
SwitchMonitor_SwitchMonitor_C2ToSwitchOnExt8(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter = 0;
}

void 
SwitchMonitor_SwitchMonitor_C3ToSwitchOffExt9(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchCounter = 0;
	rkh_pubsub_publish(0, &evSwitchOffObj, me);
}

/* ............................. Entry actions ............................. */
void 
SwitchMonitor_enSwitchOff(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0, WaitTime0);
}

void 
SwitchMonitor_enSwitchOn(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1, WaitTime1);
}

/* ............................. Exit actions .............................. */
void 
SwitchMonitor_exSwitchOff(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
SwitchMonitor_exSwitchOn(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
SwitchMonitor_isCondSwitchMonitor_C0ToSwitchMonitor_C13(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == true)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchMonitor_C1ToSwitchOn5(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchCounter >= 5)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchMonitor_C2ToSwitchMonitor_C37(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == false)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchMonitor_C3ToSwitchOff9(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchCounter >= 5)) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
