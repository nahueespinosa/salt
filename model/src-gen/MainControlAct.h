/**
 *  \file       MainControl.h
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
#ifndef __MAINCONTROLACT_H__
#define __MAINCONTROLACT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "MainControl.h"

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
void MainControl_ToDisabledExt0(MainControl *const me, RKH_EVT_T *pe);
void MainControl_ToIntermittentTractionEnabledExt15(MainControl *const me, RKH_EVT_T *pe);
void MainControl_IntermittentTractionDisabledToMainControl_C0Ext17(MainControl *const me, RKH_EVT_T *pe);
void MainControl_IntermittentBrakeToIntermittentTractionEnabledExt18(MainControl *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void MainControl_enDisabled(MainControl *const me);
void MainControl_enEnabled(MainControl *const me);
void MainControl_enPreventiveBrake(MainControl *const me);
void MainControl_enTractionEnabled(MainControl *const me);
void MainControl_enTractionDisabled(MainControl *const me);
void MainControl_enEmergencyBrake(MainControl *const me);
void MainControl_enIntermittentTractionEnabled(MainControl *const me);
void MainControl_enIntermittentTractionDisabled(MainControl *const me);
void MainControl_enIntermittentBrake(MainControl *const me);
void MainControl_enStopped(MainControl *const me);
void MainControl_enIsolated(MainControl *const me);
void MainControl_enAdrift(MainControl *const me);

/* ......................... Declares exit actions ......................... */
void MainControl_exPreventiveBrake(MainControl *const me);
void MainControl_exEmergencyBrake(MainControl *const me);
void MainControl_exIntermittentTractionEnabled(MainControl *const me);
void MainControl_exIntermittentTractionDisabled(MainControl *const me);
void MainControl_exIntermittentBrake(MainControl *const me);

/* ............................ Declares guards ............................ */
rbool_t MainControl_isCondTractionEnabledToTractionDisabled10(MainControl *const me, RKH_EVT_T *pe);
rbool_t MainControl_isCondTractionDisabledToEmergencyBrake11(MainControl *const me, RKH_EVT_T *pe);
rbool_t MainControl_isCondTractionDisabledToTractionEnabled12(MainControl *const me, RKH_EVT_T *pe);
rbool_t MainControl_isCondMainControl_C0ToIntermittentTractionEnabled19(MainControl *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
