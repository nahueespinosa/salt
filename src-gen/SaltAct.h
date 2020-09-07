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
void Salt_ToActiveCmdExt20(Salt *const me, RKH_EVT_T *pe);
void Salt_ActiveCmdToActiveCmdExt21(Salt *const me, RKH_EVT_T *pe);
void Salt_ActiveCmdToSalt_C2Ext22(Salt *const me, RKH_EVT_T *pe);
void Salt_ToIntermittentTractionEnabledExt33(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentTractionDisabledToSalt_C3Ext35(Salt *const me, RKH_EVT_T *pe);
void Salt_IntermittentBrakeToIntermittentTractionEnabledExt36(Salt *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
void Salt_enDisabled(Salt *const me);
void Salt_enEnabled(Salt *const me);
void Salt_enPreventiveBrake(Salt *const me);
void Salt_enStopped(Salt *const me);
void Salt_enIsolated(Salt *const me);
void Salt_enAdrift(Salt *const me);
void Salt_enIntermittentTractionEnabled(Salt *const me);
void Salt_enIntermittentTractionDisabled(Salt *const me);
void Salt_enIntermittentBrake(Salt *const me);
void Salt_enUnknownCmd(Salt *const me);
void Salt_enActiveCmd(Salt *const me);
void Salt_enTractionEnabled(Salt *const me);
void Salt_enTractionDisabled(Salt *const me);
void Salt_enEmergencyBrake(Salt *const me);
void Salt_enIntermittentTractionEnabled(Salt *const me);
void Salt_enIntermittentTractionDisabled(Salt *const me);
void Salt_enIntermittentBrake(Salt *const me);

/* ......................... Declares exit actions ......................... */
void Salt_exPreventiveBrake(Salt *const me);
void Salt_exIntermittentTractionEnabled(Salt *const me);
void Salt_exIntermittentTractionDisabled(Salt *const me);
void Salt_exIntermittentBrake(Salt *const me);
void Salt_exUnknownCmd(Salt *const me);
void Salt_exActiveCmd(Salt *const me);
void Salt_exEmergencyBrake(Salt *const me);
void Salt_exIntermittentTractionEnabled(Salt *const me);
void Salt_exIntermittentTractionDisabled(Salt *const me);
void Salt_exIntermittentBrake(Salt *const me);

/* ............................ Declares guards ............................ */
rbool_t Salt_isCondRemoteToLimited6(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondActiveCmdToActiveCmd21(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondLimitedToRemote25(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionEnabledToTractionDisabled28(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionDisabledToEmergencyBrake29(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondTractionDisabledToTractionEnabled30(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToStopped8(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToIsolated9(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToAdrift10(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C0ToIntermittent11(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C1ToIntermittentTractionEnabled17(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C2To// TODO for Exit23(Salt *const me, RKH_EVT_T *pe);
rbool_t Salt_isCondSalt_C3ToIntermittentTractionEnabled37(Salt *const me, RKH_EVT_T *pe);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
