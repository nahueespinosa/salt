/**
 *  \file       Salt.c
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
#include "Salt.h"
#include "SaltAct.h"
#include "bsp.h"
#include "SaltActRequired.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_SEC(me->PREV_BRAKE_TIMEOUT)
#define WaitTime1	RKH_TIME_SEC(me->REMOTE_CMD_TIMEOUT)
#define WaitTime2	RKH_TIME_SEC(me->SPEED_HASLER_TIMEOUT)
#define WaitTime3	RKH_TIME_SEC(me->SPEED_PULSE_TIMEOUT)
#define WaitTime4	RKH_TIME_SEC(me->SPEED_GPS_TIMEOUT)
#define WaitTime5	RKH_TIME_SEC(me->SPEED_MISSING_TIME)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rbool_t isSpeedAvailable = false;


/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
Salt_SpeedMissingToSpeedMissingLoc5(Salt *const me, RKH_EVT_T *pe)
{
	TODO: class org.yakindu.sct.model.stext.stext.impl.EventRaisingExpressionImpl;
}

/* ............................. Entry actions ............................. */
void 
Salt_enDisabled(Salt *const me)
{
	safetyIsolatedModeDisable();
}

void 
Salt_enEnabled(Salt *const me)
{
	safetyIsolatedModeEnable();
}

void 
Salt_enPreventiveBrake(Salt *const me)
{
	safetySignalActivateCT();
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0);
}

void 
Salt_enRemote(Salt *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1);
}

void 
Salt_enSpeedMissing(Salt *const me)
{
	isSpeedAvailable = false;
	RKH_SET_STATIC_EVENT(&me->tmEvtObj5, evTout5);
	RKH_TMR_INIT(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj5), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime5);
}

void 
Salt_enUsingHaslerSpeed(Salt *const me)
{
	isSpeedAvailable = true;
	TODO: class org.yakindu.sct.model.stext.stext.impl.EventRaisingExpressionImpl;
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2);
}

void 
Salt_enUsingPulseGenSpeed(Salt *const me)
{
	isSpeedAvailable = true;
	TODO: class org.yakindu.sct.model.stext.stext.impl.EventRaisingExpressionImpl;
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3);
}

void 
Salt_enUsingGPSSpeed(Salt *const me)
{
	isSpeedAvailable = true;
	TODO: class org.yakindu.sct.model.stext.stext.impl.EventRaisingExpressionImpl;
	RKH_SET_STATIC_EVENT(&me->tmEvtObj4, evTout4);
	RKH_TMR_INIT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj4), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime4);
}

/* ............................. Exit actions .............................. */
void 
Salt_exPreventiveBrake(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
Salt_exRemote(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

void 
Salt_exSpeedMissing(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj5.tmr);
}

void 
Salt_exUsingHaslerSpeed(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

void 
Salt_exUsingPulseGenSpeed(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

void 
Salt_exUsingGPSSpeed(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj4.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
Salt_isCondSalt_C0ToAutomatic11(Salt *const me, RKH_EVT_T *pe)
{
	return (isSpeedAvailable) ? true : false;
}

rbool_t 
Salt_isCondSalt_C1ToLimited14(Salt *const me, RKH_EVT_T *pe)
{
	return (isSpeedAvailable) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
