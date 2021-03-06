/**
 *  \file       SpeedMonitor.c
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
#include "SpeedMonitor.h"
#include "SpeedMonitorAct.h"
#include "bsp.h"
#include "SpeedMonitorActRequired.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_SEC(me->SPEED_HASLER_TIMEOUT)
#define WaitTime1	RKH_TIME_SEC(me->SPEED_PULSE_TIMEOUT)
#define WaitTime2	RKH_TIME_SEC(me->SPEED_GPS_TIMEOUT)
#define WaitTime3	RKH_TIME_SEC(1)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_STATIC_EVENT(evSpeedAvailableObj, evSpeedAvailable);
static RKH_STATIC_EVENT(evSpeedLostObj, evSpeedLost);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
SpeedMonitor_ToSpeedMissingExt0(SpeedMonitor *const me, RKH_EVT_T *pe)
{
	me->SPEED_HASLER_TIMEOUT = 10;
	me->SPEED_PULSE_TIMEOUT = 10;
	me->SPEED_GPS_TIMEOUT = 10;
		
	RKH_TR_FWK_AO(me);
	RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
	RKH_TR_FWK_STATE(me, &SpeedMissing);
	RKH_TR_FWK_STATE(me, &UsingHaslerSpeed);
	RKH_TR_FWK_STATE(me, &UsingPulseGenSpeed);
	RKH_TR_FWK_STATE(me, &UsingGPSSpeed);
	RKH_TR_FWK_SIG(evHaslerSpeedValid);
	RKH_TR_FWK_SIG(evPulseGenSpeedValid);
	RKH_TR_FWK_SIG(evGPSSpeedValid);
	RKH_TR_FWK_SIG(evSpeedAvailable);
	RKH_TR_FWK_SIG(evSpeedLost);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj3.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(SpeedMonitor_ToSpeedMissingExt0, "ToSpeedMissingExt0");
		RKH_TR_FWK_OBJ_NAME(SpeedMonitor_SpeedMissingToSpeedMissingLoc0, "SpeedMissingToSpeedMissingLoc0");
		RKH_TR_FWK_OBJ_NAME(SpeedMonitor_enUsingHaslerSpeed, "enUsingHaslerSpeed");
		RKH_TR_FWK_OBJ_NAME(SpeedMonitor_enUsingPulseGenSpeed, "enUsingPulseGenSpeed");
		RKH_TR_FWK_OBJ_NAME(SpeedMonitor_enUsingGPSSpeed, "enUsingGPSSpeed");
	#endif
	
	SpeedMonitorInit();
}

void 
SpeedMonitor_SpeedMissingToSpeedMissingLoc0(SpeedMonitor *const me, RKH_EVT_T *pe)
{
	rkh_pubsub_publish(0, &evSpeedLostObj, me);
	panelDisplayDashedLine();
}

/* ............................. Entry actions ............................. */
void 
SpeedMonitor_enSpeedMissing(SpeedMonitor *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3, WaitTime3);
}

void 
SpeedMonitor_enUsingHaslerSpeed(SpeedMonitor *const me)
{
	rkh_pubsub_publish(0, &evSpeedAvailableObj, me);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0);
}

void 
SpeedMonitor_enUsingPulseGenSpeed(SpeedMonitor *const me)
{
	rkh_pubsub_publish(0, &evSpeedAvailableObj, me);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1);
}

void 
SpeedMonitor_enUsingGPSSpeed(SpeedMonitor *const me)
{
	rkh_pubsub_publish(0, &evSpeedAvailableObj, me);
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2);
}

/* ............................. Exit actions .............................. */
void 
SpeedMonitor_exSpeedMissing(SpeedMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

void 
SpeedMonitor_exUsingHaslerSpeed(SpeedMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
SpeedMonitor_exUsingPulseGenSpeed(SpeedMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

void 
SpeedMonitor_exUsingGPSSpeed(SpeedMonitor *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
