/**
 *  \file       SpeedMonitor.h
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
#ifndef __SPEEDMONITORACT_H__
#define __SPEEDMONITORACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "SpeedMonitor.h"

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
void SpeedMonitor_ToSpeedMissingExt0(SpeedMonitor *const me, RKH_EVT_T *pe);
void SpeedMonitor_SpeedMissingToSpeedMissingLoc0(SpeedMonitor *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void SpeedMonitor_enSpeedMissing(SpeedMonitor *const me);
void SpeedMonitor_enUsingHaslerSpeed(SpeedMonitor *const me);
void SpeedMonitor_enUsingPulseGenSpeed(SpeedMonitor *const me);
void SpeedMonitor_enUsingGPSSpeed(SpeedMonitor *const me);

/* ......................... Declares exit actions ......................... */
void SpeedMonitor_exSpeedMissing(SpeedMonitor *const me);
void SpeedMonitor_exUsingHaslerSpeed(SpeedMonitor *const me);
void SpeedMonitor_exUsingPulseGenSpeed(SpeedMonitor *const me);
void SpeedMonitor_exUsingGPSSpeed(SpeedMonitor *const me);

/* ............................ Declares guards ............................ */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
