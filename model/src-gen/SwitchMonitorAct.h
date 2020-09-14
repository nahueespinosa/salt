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
void SwitchMonitor_SwitchRisingToSwitchOnExt3(SwitchMonitor *const me, RKH_EVT_T *pe);
void SwitchMonitor_SwitchFallingToSwitchOffExt5(SwitchMonitor *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void SwitchMonitor_enSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_enSwitchOn(SwitchMonitor *const me);
void SwitchMonitor_enSwitchRising(SwitchMonitor *const me);
void SwitchMonitor_enSwitchFalling(SwitchMonitor *const me);

/* ......................... Declares exit actions ......................... */
void SwitchMonitor_exSwitchOff(SwitchMonitor *const me);
void SwitchMonitor_exSwitchOn(SwitchMonitor *const me);
void SwitchMonitor_exSwitchRising(SwitchMonitor *const me);
void SwitchMonitor_exSwitchFalling(SwitchMonitor *const me);

/* ............................ Declares guards ............................ */
rbool_t SwitchMonitor_isCondSwitchOffToSwitchRising1(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchOnToSwitchFalling2(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchRisingToSwitchOff4(SwitchMonitor *const me, RKH_EVT_T *pe);
rbool_t SwitchMonitor_isCondSwitchFallingToSwitchOn6(SwitchMonitor *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
