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
void Salt_ToSalt_C0Ext7(Salt *const me, RKH_EVT_T *pe);
void Salt_ToIntermittentTractionEnabledExt13(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentTractionDisabledToSalt_C1Ext15(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentBrakeToIntermittentTractionEnabledExt16(Salt *const me, RKH_EVT_T *pe);
void Salt_ToTimerCountingExt20(Salt *const me, RKH_EVT_T *pe);
void Salt_TimerCountingToTimerCountingExt22(Salt *const me, RKH_EVT_T *pe);
void Salt_ToIntermittentTractionEnabledExt31(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentTractionDisabledToSalt_C2Ext33(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentBrakeToIntermittentTractionEnabledExt34(Salt *const me, RKH_EVT_T *pe);
void Salt_TimerCountingToTimerCountingLoc10(Salt *const me, RKH_EVT_T *pe);
void Salt_SpeedMissingToSpeedMissingLoc21(Salt *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void Salt_enDisabled(Salt *const me);
void Salt_enEnabled(Salt *const me);
void Salt_enPreventiveBrake(Salt *const me);
void Salt_enTotalStop(Salt *const me);
void Salt_enTotalIsolation(Salt *const me);
void Salt_enDrift(Salt *const me);
void Salt_enIntermittentTractionEnabled(Salt *const me);
void Salt_enIntermittentTractionDisabled(Salt *const me);
void Salt_enIntermittentBrake(Salt *const me);
void Salt_enExiting(Salt *const me);
void Salt_enTimerCounting(Salt *const me);
void Salt_enTractionEnabled(Salt *const me);
void Salt_enTractionDisabled(Salt *const me);
void Salt_enEmergencyBrake(Salt *const me);
void Salt_enIntermittentTractionEnabled(Salt *const me);
void Salt_enIntermittentTractionDisabled(Salt *const me);
void Salt_enIntermittentBrake(Salt *const me);
void Salt_enSpeedMissing(Salt *const me);
void Salt_enUsingHaslerSpeed(Salt *const me);
void Salt_enUsingPulseGenSpeed(Salt *const me);
void Salt_enUsingGPSSpeed(Salt *const me);

/* ......................... Declares exit actions ......................... */
void Salt_exPreventiveBrake(Salt *const me);
void Salt_exIntermittentTractionEnabled(Salt *const me);
void Salt_exIntermittentTractionDisabled(Salt *const me);
void Salt_exIntermittentBrake(Salt *const me);
void Salt_exExiting(Salt *const me);
void Salt_exTimerCounting(Salt *const me);
void Salt_exEmergencyBrake(Salt *const me);
void Salt_exIntermittentTractionEnabled(Salt *const me);
void Salt_exIntermittentTractionDisabled(Salt *const me);
void Salt_exIntermittentBrake(Salt *const me);
void Salt_exSpeedMissing(Salt *const me);
void Salt_exUsingHaslerSpeed(Salt *const me);
void Salt_exUsingPulseGenSpeed(Salt *const me);
void Salt_exUsingGPSSpeed(Salt *const me);

/* ............................ Declares guards ............................ */
rbool_t Salt_isCondRemoteToLimited6(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTimerCountingTo// TODO for Exit21(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTimerCountingToTimerCounting22(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondLimitedToRemote23(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionEnabledToTractionDisabled26(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionDisabledToEmergencyBrake27(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionDisabledToTractionEnabled28(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToTotalStop8(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToTotalIsolation9(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToDrift10(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToIntermittent11(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C1ToIntermittentTractionEnabled17(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C2ToIntermittentTractionEnabled35(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C3ToAutomatic38(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C4ToLimited41(Salt *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
