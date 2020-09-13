/**
 *  \file       MainControl.c
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
#include "MainControl.h"
#include "MainControlAct.h"
#include "bsp.h"
#include "MainControlActRequired.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)
#define WaitTime1	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)
#define WaitTime2	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_OFF)
#define WaitTime3	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_ON)
#define WaitTime4	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rInt currentCycle = 0;


/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
MainControl_ToDisabledExt0(MainControl *const me, RKH_EVT_T *pe)
{
	me->SALT_CT_LIMIT_UP = 30;
	me->SALT_CT_LIMIT_DOWN = 25;
	me->SALT_FE_LIMIT = 36;
	me->SALT_FE_TIMEOUT = 10;
	me->SALT_INTERMITTENT_TIME_OFF = 3;
	me->SALT_INTERMITTENT_TIME_ON = 3;
		
	RKH_TR_FWK_AO(me);
	RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
	RKH_TR_FWK_STATE(me, &Disabled);
	RKH_TR_FWK_STATE(me, &Enabled);
	RKH_TR_FWK_STATE(me, &PreventiveBrake);
	RKH_TR_FWK_STATE(me, &Limited);
	RKH_TR_FWK_STATE(me, &Automatic);
	RKH_TR_FWK_STATE(me, &TractionEnabled);
	RKH_TR_FWK_STATE(me, &TractionDisabled);
	RKH_TR_FWK_STATE(me, &EmergencyBrake);
	RKH_TR_FWK_STATE(me, &Intermittent);
	RKH_TR_FWK_STATE(me, &IntermittentTractionEnabled);
	RKH_TR_FWK_STATE(me, &IntermittentTractionDisabled);
	RKH_TR_FWK_STATE(me, &IntermittentBrake);
	RKH_TR_FWK_STATE(me, &Waiting2);
	RKH_TR_FWK_STATE(me, &Waiting1);
	RKH_TR_FWK_STATE(me, &Remote);
	RKH_TR_FWK_STATE(me, &Stopped);
	RKH_TR_FWK_STATE(me, &Isolated);
	RKH_TR_FWK_STATE(me, &Adrift);
	RKH_TR_FWK_SIG(evSwitchOn);
	RKH_TR_FWK_SIG(evSwitchOff);
	RKH_TR_FWK_SIG(evRemoteStop);
	RKH_TR_FWK_SIG(evRemoteIsolate);
	RKH_TR_FWK_SIG(evRemoteDrift);
	RKH_TR_FWK_SIG(evRemoteExit);
	RKH_TR_FWK_SIG(evSpeedAvailable);
	RKH_TR_FWK_SIG(evSpeedLost);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj3.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj4.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(MainControl_ToDisabledExt0, "ToDisabledExt0");
		RKH_TR_FWK_OBJ_NAME(MainControl_ToIntermittentTractionEnabledExt15, "ToIntermittentTractionEnabledExt15");
		RKH_TR_FWK_OBJ_NAME(MainControl_IntermittentTractionDisabledToMainControl_C0Ext17, "IntermittentTractionDisabledToMainControl_C0Ext17");
		RKH_TR_FWK_OBJ_NAME(MainControl_IntermittentBrakeToIntermittentTractionEnabledExt18, "IntermittentBrakeToIntermittentTractionEnabledExt18");
		RKH_TR_FWK_OBJ_NAME(MainControl_enDisabled, "enDisabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enEnabled, "enEnabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enPreventiveBrake, "enPreventiveBrake");
		RKH_TR_FWK_OBJ_NAME(MainControl_enTractionEnabled, "enTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enTractionDisabled, "enTractionDisabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enEmergencyBrake, "enEmergencyBrake");
		RKH_TR_FWK_OBJ_NAME(MainControl_enIntermittentTractionEnabled, "enIntermittentTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enIntermittentTractionDisabled, "enIntermittentTractionDisabled");
		RKH_TR_FWK_OBJ_NAME(MainControl_enIntermittentBrake, "enIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(MainControl_enStopped, "enStopped");
		RKH_TR_FWK_OBJ_NAME(MainControl_enIsolated, "enIsolated");
		RKH_TR_FWK_OBJ_NAME(MainControl_enAdrift, "enAdrift");
		RKH_TR_FWK_OBJ_NAME(MainControl_exEmergencyBrake, "exEmergencyBrake");
		RKH_TR_FWK_OBJ_NAME(MainControl_exIntermittentBrake, "exIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(MainControl_isCondTractionEnabledToTractionDisabled10, "isCondTractionEnabledToTractionDisabled10");
		RKH_TR_FWK_OBJ_NAME(MainControl_isCondTractionDisabledToEmergencyBrake11, "isCondTractionDisabledToEmergencyBrake11");
		RKH_TR_FWK_OBJ_NAME(MainControl_isCondTractionDisabledToTractionEnabled12, "isCondTractionDisabledToTractionEnabled12");
		RKH_TR_FWK_OBJ_NAME(MainControl_isCondMainControl_C0ToIntermittentTractionEnabled19, "isCondMainControl_C0ToIntermittentTractionEnabled19");
	#endif
	
	safetyInit();
}

void 
MainControl_ToIntermittentTractionEnabledExt15(MainControl *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
}

void 
MainControl_IntermittentTractionDisabledToMainControl_C0Ext17(MainControl *const me, RKH_EVT_T *pe)
{
	currentCycle++;
}

void 
MainControl_IntermittentBrakeToIntermittentTractionEnabledExt18(MainControl *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
}

/* ............................. Entry actions ............................. */
void 
MainControl_enDisabled(MainControl *const me)
{
	safetyIsolatedModeDisable();
}

void 
MainControl_enEnabled(MainControl *const me)
{
	safetyIsolatedModeEnable();
}

void 
MainControl_enPreventiveBrake(MainControl *const me)
{
	safetySignalActivateCT();
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0);
}

void 
MainControl_enTractionEnabled(MainControl *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
}

void 
MainControl_enTractionDisabled(MainControl *const me)
{
	safetySignalActivateCT();
}

void 
MainControl_enEmergencyBrake(MainControl *const me)
{
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1);
}

void 
MainControl_enIntermittentTractionEnabled(MainControl *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2);
}

void 
MainControl_enIntermittentTractionDisabled(MainControl *const me)
{
	safetySignalActivateCT();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3);
}

void 
MainControl_enIntermittentBrake(MainControl *const me)
{
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj4, evTout4);
	RKH_TMR_INIT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj4), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime4);
}

void 
MainControl_enStopped(MainControl *const me)
{
	safetySignalActivateCT();
	safetySignalActivateFE();
}

void 
MainControl_enIsolated(MainControl *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
}

void 
MainControl_enAdrift(MainControl *const me)
{
	safetySignalActivateCT();
	safetySignalDeactivateFE();
}

/* ............................. Exit actions .............................. */
void 
MainControl_exPreventiveBrake(MainControl *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
MainControl_exEmergencyBrake(MainControl *const me)
{
	safetySignalDeactivateFE();
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

void 
MainControl_exIntermittentTractionEnabled(MainControl *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

void 
MainControl_exIntermittentTractionDisabled(MainControl *const me)
{
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

void 
MainControl_exIntermittentBrake(MainControl *const me)
{
	safetySignalDeactivateFE();
	rkh_tmr_stop(&me->tmEvtObj4.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
MainControl_isCondTractionEnabledToTractionDisabled10(MainControl *const me, RKH_EVT_T *pe)
{
	return ((speedRead() > me->SALT_CT_LIMIT_UP)) ? true : false;
}

rbool_t 
MainControl_isCondTractionDisabledToEmergencyBrake11(MainControl *const me, RKH_EVT_T *pe)
{
	return ((speedRead() > me->SALT_FE_LIMIT)) ? true : false;
}

rbool_t 
MainControl_isCondTractionDisabledToTractionEnabled12(MainControl *const me, RKH_EVT_T *pe)
{
	return ((speedRead() < me->SALT_CT_LIMIT_DOWN)) ? true : false;
}

rbool_t 
MainControl_isCondMainControl_C0ToIntermittentTractionEnabled19(MainControl *const me, RKH_EVT_T *pe)
{
	return ((currentCycle < 5)) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
