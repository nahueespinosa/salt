/**
 *  \file       RemoteMgr.h
 *  \brief      Active object's action specifications.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __REMOTEMGRACT_H__
#define __REMOTEMGRACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "RemoteMgr.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* ........................ Declares effect actions ........................ */
void RemoteMgr_ToInitializedExt0(RemoteMgr *const me, RKH_EVT_T *pe);
void RemoteMgr_DisconnectedToConnectedExt1(RemoteMgr *const me, RKH_EVT_T *pe);
void RemoteMgr_InitializedToInitializedLoc0(RemoteMgr *const me, RKH_EVT_T *pe);
void RemoteMgr_ConnectedToConnectedLoc1(RemoteMgr *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void RemoteMgr_enInitialized(RemoteMgr *const me);
void RemoteMgr_enDisconnected(RemoteMgr *const me);
void RemoteMgr_enConnected(RemoteMgr *const me);

/* ......................... Declares exit actions ......................... */
void RemoteMgr_exInitialized(RemoteMgr *const me);
void RemoteMgr_exDisconnected(RemoteMgr *const me);
void RemoteMgr_exConnected(RemoteMgr *const me);

/* ............................ Declares guards ............................ */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
