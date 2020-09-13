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
void SwitchMonitor_SwitchMonitor_C0ToSwitchMonitor_C1Ext3(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchMonitor_C0ToSwitchOffExt4(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchMonitor_C1ToSwitchOnExt5(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchMonitor_C2ToSwitchMonitor_C3Ext7(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchMonitor_C2ToSwitchOnExt8(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchMonitor_C3ToSwitchOffExt9(SwitchMonitor *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void SwitchMonitor_enSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_enSwitchOn(SwitchMonitor *const me);

/* ......................... Declares exit actions ......................... */
void SwitchMonitor_exSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_exSwitchOn(SwitchMonitor *const me);

/* ............................ Declares guards ............................ */
rbool_t SwitchMonitor_isCondSwitchMonitor_C0ToSwitchMonitor_C13(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchMonitor_C1ToSwitchOn5(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchMonitor_C2ToSwitchMonitor_C37(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchMonitor_C3ToSwitchOff9(SwitchMonitor *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
