/**
 *  \file       SaltActRequired.h
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
#ifndef __SALTACTREQUIRED_H__
#define __SALTACTREQUIRED_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "SaltActAccess.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
	extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void safetyIsolatedModeDisable(void);
void safetyIsolatedModeEnable(void);
void safetySignalActivateCT(void);
void safetySignalDeactivateCT(void);
void safetySignalActivateFE(void);
void safetySignalDeactivateFE(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
