/**
 *  \file       RemoteMgrActRequired.h
 *  \brief
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __REMOTEMGRACTREQUIRED_H__
#define __REMOTEMGRACTREQUIRED_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "RemoteMgrActAccess.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
	extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void RemoteMgrInit(void);
void RemoteMgrUpdate(void);
void RemoteMgrConnect(void);
void RemoteMgrSendStatus(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
