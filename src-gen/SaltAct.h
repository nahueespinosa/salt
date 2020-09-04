/**
 *  \file       Salt.h
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
#ifndef __SALTACT_H__
#define __SALTACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "Salt.h"

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
void Salt_SpeedMissingToSpeedMissingLoc5(Salt *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void Salt_enDisabled(Salt *const me);
void Salt_enEnabled(Salt *const me);
void Salt_enPreventiveBrake(Salt *const me);
void Salt_enRemote(Salt *const me);
void Salt_enSpeedMissing(Salt *const me);
void Salt_enUsingHaslerSpeed(Salt *const me);
void Salt_enUsingPulseGenSpeed(Salt *const me);
void Salt_enUsingGPSSpeed(Salt *const me);

/* ......................... Declares exit actions ......................... */
void Salt_exPreventiveBrake(Salt *const me);
void Salt_exRemote(Salt *const me);
void Salt_exSpeedMissing(Salt *const me);
void Salt_exUsingHaslerSpeed(Salt *const me);
void Salt_exUsingPulseGenSpeed(Salt *const me);
void Salt_exUsingGPSSpeed(Salt *const me);

/* ............................ Declares guards ............................ */
rbool_t Salt_isCondSalt_C0ToAutomatic11(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C1ToLimited14(Salt *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
