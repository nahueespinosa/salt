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
#define WaitTime0	RKH_TIME_MS(20)
#define WaitTime1	RKH_TIME_MS(20)
#define WaitTime2	RKH_TIME_MS(500)
#define WaitTime3	RKH_TIME_MS(20)
#define WaitTime4	RKH_TIME_MS(500)
#define WaitTime5	RKH_TIME_MS(20)

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
	RKH_TR_FWK_STATE(me, &SwitchRising);
	RKH_TR_FWK_STATE(me, &SwitchFalling);
	RKH_TR_FWK_SIG(evSwitchOn);
	RKH_TR_FWK_SIG(evSwitchOff);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj3.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj4.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj5.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_ToSwitchOffExt0, "ToSwitchOffExt0");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchRisingToSwitchOnExt3, "SwitchRisingToSwitchOnExt3");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_SwitchFallingToSwitchOffExt5, "SwitchFallingToSwitchOffExt5");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchOffToSwitchRising1, "isCondSwitchOffToSwitchRising1");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchOnToSwitchFalling2, "isCondSwitchOnToSwitchFalling2");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchRisingToSwitchOff4, "isCondSwitchRisingToSwitchOff4");
		RKH_TR_FWK_OBJ_NAME(SwitchMonitor_isCondSwitchFallingToSwitchOn6, "isCondSwitchFallingToSwitchOn6");
	#endif
	
	switchInit();
}

void 
SwitchMonitor_SwitchRisingToSwitchOnExt3(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	rkh_pubsub_publish(0, &evSwitchOnObj, me);
}

void 
SwitchMonitor_SwitchFallingToSwitchOffExt5(SwitchMonitor *const me, RKH_EVT_T *pe)
{
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

void 
SwitchMonitor_enSwitchRising(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3, WaitTime3);
}

void 
SwitchMonitor_enSwitchFalling(SwitchMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj4, evTout4);
	RKH_TMR_INIT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj4), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime4);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj5, evTout5);
	RKH_TMR_INIT(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj5), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime5, WaitTime5);
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

void 
SwitchMonitor_exSwitchRising(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

void 
SwitchMonitor_exSwitchFalling(SwitchMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj4.tmr);
	rkh_tmr_stop(&me->tmEvtObj5.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
SwitchMonitor_isCondSwitchOffToSwitchRising1(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == true)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchOnToSwitchFalling2(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == false)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchRisingToSwitchOff4(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == false)) ? true : false;
}

rbool_t 
SwitchMonitor_isCondSwitchFallingToSwitchOn6(SwitchMonitor *const me, RKH_EVT_T *pe)
{
	return ((switchRead() == true)) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
