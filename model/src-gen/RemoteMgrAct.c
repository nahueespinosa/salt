/**
 *  \file       RemoteMgr.c
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
#include "RemoteMgr.h"
#include "RemoteMgrAct.h"
#include "bsp.h"
#include "RemoteMgrActRequired.h"

/* ----------------------------- Local macros ------------------------------ */
#define WaitTime0	RKH_TIME_SEC(1)
#define WaitTime1	RKH_TIME_MS(10)
#define WaitTime2	RKH_TIME_SEC(10)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
void 
RemoteMgr_ToInitializedExt0(RemoteMgr *const me, RKH_EVT_T *pe)
{
		
	RKH_TR_FWK_AO(me);
	RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
	RKH_TR_FWK_STATE(me, &Initialized);
	RKH_TR_FWK_STATE(me, &Disconnected);
	RKH_TR_FWK_STATE(me, &Connected);
	RKH_TR_FWK_TIMER(&me->tmEvtObj0.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj1.tmr);
	RKH_TR_FWK_TIMER(&me->tmEvtObj2.tmr);
	#if 0
		RKH_TR_FWK_OBJ_NAME(RemoteMgr_ToInitializedExt0, "ToInitializedExt0");
		RKH_TR_FWK_OBJ_NAME(RemoteMgr_DisconnectedToConnectedExt1, "DisconnectedToConnectedExt1");
		RKH_TR_FWK_OBJ_NAME(RemoteMgr_InitializedToInitializedLoc0, "InitializedToInitializedLoc0");
		RKH_TR_FWK_OBJ_NAME(RemoteMgr_ConnectedToConnectedLoc1, "ConnectedToConnectedLoc1");
	#endif
	
	RemoteMgrInit();
}

void 
RemoteMgr_DisconnectedToConnectedExt1(RemoteMgr *const me, RKH_EVT_T *pe)
{
	RemoteMgrConnect();
}

void 
RemoteMgr_InitializedToInitializedLoc0(RemoteMgr *const me, RKH_EVT_T *pe)
{
	RemoteMgrUpdate();
}

void 
RemoteMgr_ConnectedToConnectedLoc1(RemoteMgr *const me, RKH_EVT_T *pe)
{
	RemoteMgrSendStatus();
}

/* ............................. Entry actions ............................. */
void 
RemoteMgr_enInitialized(RemoteMgr *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj1, evTout1);
	RKH_TMR_INIT(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj1), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj1.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime1, WaitTime1);
}

void 
RemoteMgr_enDisconnected(RemoteMgr *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj0, evTout0);
	RKH_TMR_INIT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj0), NULL);
	RKH_TMR_ONESHOT(&me->tmEvtObj0.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime0);
}

void 
RemoteMgr_enConnected(RemoteMgr *const me)
{
	RKH_SET_STATIC_EVENT(&me->tmEvtObj2, evTout2);
	RKH_TMR_INIT(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_EVT_T, &me->tmEvtObj2), NULL);
	RKH_TMR_PERIODIC(&me->tmEvtObj2.tmr, RKH_UPCAST(RKH_SMA_T, me), WaitTime2, WaitTime2);
}

/* ............................. Exit actions .............................. */
void 
RemoteMgr_exInitialized(RemoteMgr *const me)
{
	rkh_tmr_stop(&me->tmEvtObj1.tmr);
}

void 
RemoteMgr_exDisconnected(RemoteMgr *const me)
{
	rkh_tmr_stop(&me->tmEvtObj0.tmr);
}

void 
RemoteMgr_exConnected(RemoteMgr *const me)
{
	rkh_tmr_stop(&me->tmEvtObj2.tmr);
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
