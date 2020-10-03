/**
 *  \file       remoteMgr.c
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
#include "RemoteMgr.h"
#include "RemoteMgrAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(Disconnected, RemoteMgr_enDisconnected, RemoteMgr_exDisconnected, &Initialized, NULL);
RKH_CREATE_BASIC_STATE(Connected, RemoteMgr_enConnected, RemoteMgr_exConnected, &Initialized, NULL);

RKH_CREATE_COMP_REGION_STATE(Initialized, RemoteMgr_enInitialized, RemoteMgr_exInitialized, RKH_ROOT, &Disconnected, NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);

RKH_CREATE_TRANS_TABLE(Initialized)
	RKH_TRINT(evTout1, NULL, RemoteMgr_InitializedToInitializedLoc0),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Disconnected)
	RKH_TRREG(evTout0, NULL, RemoteMgr_DisconnectedToConnectedExt1, &Connected),
RKH_END_TRANS_TABLE

RKH_CREATE_TRANS_TABLE(Connected)
	RKH_TRINT(evTout2, NULL, RemoteMgr_ConnectedToConnectedLoc1),
RKH_END_TRANS_TABLE



/* ............................. Active object ............................. */
RKH_SMA_CREATE(RemoteMgr, remoteMgr, RemoteMgrPrio, HCAL, &Initialized, RemoteMgr_ToInitializedExt0, NULL);
RKH_SMA_DEF_PTR(remoteMgr);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
