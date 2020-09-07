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
#define WaitTime0	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)
#define WaitTime1	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_OFF)
#define WaitTime2	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_ON)
#define WaitTime3	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)
#define WaitTime4	RKH_TIME_SEC(1)
#define WaitTime5	RKH_TIME_SEC(1)
#define WaitTime6	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)
#define WaitTime7	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_OFF)
#define WaitTime8	RKH_TIME_SEC(me->SALT_INTERMITTENT_TIME_ON)
#define WaitTime9	RKH_TIME_SEC(me->SALT_FE_TIMEOUT)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static rInt currentCycle = 0;
static rInt remoteCmdTimer = 0;
static rInt currentCmd = 0;


/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
Salt_ToSalt_C0Ext7(Salt *const me, RKH_EVT_T *pe)
{
	me->REMOTE_CMD_TIMEOUT = 8;
	me->SALT_CT_LIMIT_UP = 30;
	me->SALT_CT_LIMIT_DOWN = 25;
	me->SALT_FE_LIMIT = 36;
	me->SALT_FE_TIMEOUT = 10;
	me->SALT_INTERMITTENT_TIME_OFF = 3;
	me->SALT_INTERMITTENT_TIME_ON = 3;
	me->REMOTE_CMD_EXIT = 0;
	me->REMOTE_CMD_STOP = 1;
	me->REMOTE_CMD_ISOLATE = 2;
	me->REMOTE_CMD_DRIFT = 3;
	me->REMOTE_CMD_INTERMITTENT = 4;
		
	RKH_TR_FWK_AO(me);
	RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
	RKH_TR_FWK_STATE(me, &Disabled);
	RKH_TR_FWK_STATE(me, &Enabled);
	RKH_TR_FWK_STATE(me, &PreventiveBrake);
	RKH_TR_FWK_STATE(me, &Remote);
	RKH_TR_FWK_STATE(me, &TotalStop);
	RKH_TR_FWK_STATE(me, &TotalIsolation);
	RKH_TR_FWK_STATE(me, &Drift);
	RKH_TR_FWK_STATE(me, &Intermittent);
	RKH_TR_FWK_STATE(me, &IntermittentTractionEnabled);
	RKH_TR_FWK_STATE(me, &IntermittentTractionDisabled);
	RKH_TR_FWK_STATE(me, &IntermittentBrake);
	RKH_TR_FWK_STATE(me, &UnknownCmd);
	RKH_TR_FWK_STATE(me, &ActiveCmd);
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
	RKH_TR_FWK_SIG(evSwitchOn);
	RKH_TR_FWK_SIG(evSwitchOff);
	RKH_TR_FWK_SIG(evRemoteCmd);
	RKH_TR_FWK_SIG(evSpeedAvailable);
	RKH_TR_FWK_SIG(evSpeedLost);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj3.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj4.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj5.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj6.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj7.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj8.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj9.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(Salt_ToSalt_C0Ext7, "ToSalt_C0Ext7");
		RKH_TR_FWK_OBJ_NAME(Salt_ToIntermittentTractionEnabledExt13, "ToIntermittentTractionEnabledExt13");
		RKH_TR_FWK_OBJ_NAME(Salt_IntermittentTractionDisabledToSalt_C1Ext15, "IntermittentTractionDisabledToSalt_C1Ext15");
		RKH_TR_FWK_OBJ_NAME(Salt_IntermittentBrakeToIntermittentTractionEnabledExt16, "IntermittentBrakeToIntermittentTractionEnabledExt16");
		RKH_TR_FWK_OBJ_NAME(Salt_ToActiveCmdExt20, "ToActiveCmdExt20");
		RKH_TR_FWK_OBJ_NAME(Salt_ActiveCmdToActiveCmdExt21, "ActiveCmdToActiveCmdExt21");
		RKH_TR_FWK_OBJ_NAME(Salt_ActiveCmdToSalt_C2Ext22, "ActiveCmdToSalt_C2Ext22");
		RKH_TR_FWK_OBJ_NAME(Salt_ToIntermittentTractionEnabledExt33, "ToIntermittentTractionEnabledExt33");
		RKH_TR_FWK_OBJ_NAME(Salt_IntermittentTractionDisabledToSalt_C3Ext35, "IntermittentTractionDisabledToSalt_C3Ext35");
		RKH_TR_FWK_OBJ_NAME(Salt_IntermittentBrakeToIntermittentTractionEnabledExt36, "IntermittentBrakeToIntermittentTractionEnabledExt36");
		RKH_TR_FWK_OBJ_NAME(Salt_enDisabled, "enDisabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enEnabled, "enEnabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enPreventiveBrake, "enPreventiveBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_enTotalStop, "enTotalStop");
		RKH_TR_FWK_OBJ_NAME(Salt_enTotalIsolation, "enTotalIsolation");
		RKH_TR_FWK_OBJ_NAME(Salt_enDrift, "enDrift");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentTractionEnabled, "enIntermittentTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentTractionDisabled, "enIntermittentTractionDisabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentBrake, "enIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_enTractionEnabled, "enTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enTractionEnabled, "enTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enTractionDisabled, "enTractionDisabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enEmergencyBrake, "enEmergencyBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentTractionEnabled, "enIntermittentTractionEnabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentTractionDisabled, "enIntermittentTractionDisabled");
		RKH_TR_FWK_OBJ_NAME(Salt_enIntermittentBrake, "enIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_exIntermittentBrake, "exIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_exEmergencyBrake, "exEmergencyBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_exIntermittentBrake, "exIntermittentBrake");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondRemoteToLimited6, "isCondRemoteToLimited6");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondActiveCmdToActiveCmd21, "isCondActiveCmdToActiveCmd21");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondLimitedToRemote25, "isCondLimitedToRemote25");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondTractionEnabledToTractionDisabled28, "isCondTractionEnabledToTractionDisabled28");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondTractionDisabledToEmergencyBrake29, "isCondTractionDisabledToEmergencyBrake29");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondTractionDisabledToTractionEnabled30, "isCondTractionDisabledToTractionEnabled30");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C0ToTotalStop8, "isCondSalt_C0ToTotalStop8");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C0ToTotalIsolation9, "isCondSalt_C0ToTotalIsolation9");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C0ToDrift10, "isCondSalt_C0ToDrift10");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C0ToIntermittent11, "isCondSalt_C0ToIntermittent11");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C1ToIntermittentTractionEnabled17, "isCondSalt_C1ToIntermittentTractionEnabled17");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C2To// TODO for Exit23, "isCondSalt_C2To// TODO for Exit23");
		RKH_TR_FWK_OBJ_NAME(Salt_isCondSalt_C3ToIntermittentTractionEnabled37, "isCondSalt_C3ToIntermittentTractionEnabled37");
	#endif
	
	currentCmd = TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl;
}

void 
Salt_ToIntermittentTractionEnabledExt13(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
}

void 
Salt_IntermittentTractionDisabledToSalt_C1Ext15(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle++;
}

void 
Salt_IntermittentBrakeToIntermittentTractionEnabledExt16(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
}

void 
Salt_ToActiveCmdExt20(Salt *const me, RKH_EVT_T *pe)
{
	remoteCmdTimer = 0;
}

void 
Salt_ActiveCmdToActiveCmdExt21(Salt *const me, RKH_EVT_T *pe)
{
	remoteCmdTimer = 0;
}

void 
Salt_ActiveCmdToSalt_C2Ext22(Salt *const me, RKH_EVT_T *pe)
{
	remoteCmdTimer++;
}

void 
Salt_ToIntermittentTractionEnabledExt33(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
}

void 
Salt_IntermittentTractionDisabledToSalt_C3Ext35(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle++;
}

void 
Salt_IntermittentBrakeToIntermittentTractionEnabledExt36(Salt *const me, RKH_EVT_T *pe)
{
	currentCycle = 0;
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
Salt_enTotalStop(Salt *const me)
{
	safetySignalActivateCT();
	safetySignalActivateFE();
}

void 
Salt_enTotalIsolation(Salt *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
}

void 
Salt_enDrift(Salt *const me)
{
	safetySignalDeactivateCT();
	safetySignalActivateFE();
}

void 
Salt_enIntermittentTractionEnabled(Salt *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1);
}

void 
Salt_enIntermittentTractionDisabled(Salt *const me)
{
	safetySignalActivateCT();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2);
}

void 
Salt_enIntermittentBrake(Salt *const me)
{
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj3, evTout3);
	RKH_TMR_INIT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj3), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj3.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime3);
}

void 
Salt_enUnknownCmd(Salt *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj4, evTout4);
	RKH_TMR_INIT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj4), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj4.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime4);
}

void 
Salt_enActiveCmd(Salt *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj5, evTout5);
	RKH_TMR_INIT(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj5), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj5.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime5);
}

void 
Salt_enTractionEnabled(Salt *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
}

void 
Salt_enTractionDisabled(Salt *const me)
{
	safetySignalActivateCT();
}

void 
Salt_enEmergencyBrake(Salt *const me)
{
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj6, evTout6);
	RKH_TMR_INIT(&me->tmEvtObj6.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj6), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj6.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime6);
}

void 
Salt_enIntermittentTractionEnabled(Salt *const me)
{
	safetySignalDeactivateCT();
	safetySignalDeactivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj7, evTout7);
	RKH_TMR_INIT(&me->tmEvtObj7.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj7), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj7.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime7);
}

void 
Salt_enIntermittentTractionDisabled(Salt *const me)
{
	safetySignalActivateCT();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj8, evTout8);
	RKH_TMR_INIT(&me->tmEvtObj8.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj8), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj8.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime8);
}

void 
Salt_enIntermittentBrake(Salt *const me)
{
	safetySignalActivateFE();
	RKH_SET_STATIC_EVENT(&me->tmEvtObj9, evTout9);
	RKH_TMR_INIT(&me->tmEvtObj9.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj9), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj9.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime9);
}

/* ............................. Exit actions .............................. */
void 
Salt_exPreventiveBrake(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
Salt_exIntermittentTractionEnabled(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

void 
Salt_exIntermittentTractionDisabled(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

void 
Salt_exIntermittentBrake(Salt *const me)
{
	safetySignalDeactivateFE();
	rkh_tmr_stop(&me->tmEvtObj3.tmr);
}

void 
Salt_exUnknownCmd(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj4.tmr);
}

void 
Salt_exActiveCmd(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj5.tmr);
}

void 
Salt_exEmergencyBrake(Salt *const me)
{
	safetySignalDeactivateFE();
	rkh_tmr_stop(&me->tmEvtObj6.tmr);
}

void 
Salt_exIntermittentTractionEnabled(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj7.tmr);
}

void 
Salt_exIntermittentTractionDisabled(Salt *const me)
{
	rkh_tmr_stop(&me->tmEvtObj8.tmr);
}

void 
Salt_exIntermittentBrake(Salt *const me)
{
	safetySignalDeactivateFE();
	rkh_tmr_stop(&me->tmEvtObj9.tmr);
}

/* ................................ Guards ................................. */
rbool_t 
Salt_isCondRemoteToLimited6(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl == me->REMOTE_CMD_EXIT)) ? true : false;
}

rbool_t 
Salt_isCondActiveCmdToActiveCmd21(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl == currentCmd)) ? true : false;
}

rbool_t 
Salt_isCondLimitedToRemote25(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl != me->REMOTE_CMD_EXIT)) ? true : false;
}

rbool_t 
Salt_isCondTractionEnabledToTractionDisabled28(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl > me->SALT_CT_LIMIT_UP)) ? true : false;
}

rbool_t 
Salt_isCondTractionDisabledToEmergencyBrake29(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl > me->SALT_FE_LIMIT)) ? true : false;
}

rbool_t 
Salt_isCondTractionDisabledToTractionEnabled30(Salt *const me, RKH_EVT_T *pe)
{
	return ((TODO: class org.yakindu.sct.model.stext.stext.impl.EventValueReferenceExpressionImpl < me->SALT_CT_LIMIT_DOWN)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C0ToTotalStop8(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCmd == me->REMOTE_CMD_STOP)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C0ToTotalIsolation9(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCmd == me->REMOTE_CMD_ISOLATE)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C0ToDrift10(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCmd == me->REMOTE_CMD_DRIFT)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C0ToIntermittent11(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCmd == me->REMOTE_CMD_INTERMITTENT)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C1ToIntermittentTractionEnabled17(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCycle < 5)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C2To// TODO for Exit23(Salt *const me, RKH_EVT_T *pe)
{
	return ((remoteCmdTimer == me->REMOTE_CMD_TIMEOUT)) ? true : false;
}

rbool_t 
Salt_isCondSalt_C3ToIntermittentTractionEnabled37(Salt *const me, RKH_EVT_T *pe)
{
	return ((currentCycle < 5)) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
