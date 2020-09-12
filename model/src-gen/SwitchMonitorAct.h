/**
 *  \file       SwitchMonitor.h
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
#ifndef __SWITCHMONITORACT_H__
#define __SWITCHMONITORACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "SwitchMonitor.h"

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
void SwitchMonitor_ToSwitchOffExt0(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchOffToSwitchOnExt1(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchOnToSwitchOffExt2(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchOffToSwitchOffLoc0(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchOnToSwitchOnLoc1(SwitchMonitor *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void SwitchMonitor_enSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_enSwitchOn(SwitchMonitor *const me);

/* ......................... Declares exit actions ......................... */
void SwitchMonitor_exSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_exSwitchOn(SwitchMonitor *const me);

/* ............................ Declares guards ............................ */
rbool_t SwitchMonitor_isCondSwitchOffToSwitchOn1(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchOnToSwitchOff2(SwitchMonitor *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
