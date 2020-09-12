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
#include "MainControl.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_MS(100)
#define WaitTime1	RKH_TIME_MS(100)
#define WaitTime2	RKH_TIME_MS(20)
#define WaitTime3	RKH_TIME_MS(20)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
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
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj3.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_ToSwitchOffExt0, "ToSwitchOffExt0");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchOffToSwitchOnExt1, "SwitchOffToSwitchOnExt1");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchOnToSwitchOffExt2, "SwitchOnToSwitchOffExt2");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchOffToSwitchOffLoc0, "SwitchOffToSwitchOffLoc0");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchOnToSwitchOnLoc1, "SwitchOnToSwitchOnLoc1");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchOffToSwitchOn1, "isCondSwitchOffToSwitchOn1");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchOnToSwitchOff2, "isCondSwitchOnToSwitchOff2");
	#endif
	
	switchInit();
}

void 
SwitchMonitor_SwitchOffToSwitchOnExt1(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	rkh_pubsub_publish(0, &evSwitchOnObj, me);
}

void 
SwitchMonitor_SwitchOnToSwitchOffExt2(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	rkh_pubsub_publish(0, &evSwitchOffObj, me);
}

void 
SwitchMonitor_SwitchOffToSwitchOffLoc0(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchUpdate();
}

void 
SwitchMonitor_SwitchOnToSwitchOnLoc1(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	switchUpdate();
}

/* ............................. Entry actions ............................. */
void 
SwitchMonitor_enSwitchOff(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0, WaitTime0);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2, WaitTime2);
}

void 
SwitchMonitor_enSwitchOn(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1, WaitTime1);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3, WaitTime3);
}

/* ............................. Exit actions .............................. */
void 
SwitchMonitor_exSwitchOff(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

void 
SwitchMonitor_exSwitchOn(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
SwitchMonitor_isCondSwitchOffToSwitchOn1(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == true)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchOnToSwitchOff2(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == false)) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
