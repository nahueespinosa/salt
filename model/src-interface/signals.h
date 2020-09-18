/**
 *  \file       signals.h
 *  \brief      Event signal definitions.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SIGNALS_H__
#define __SIGNALS_H__

/* ----------------------------- Include files ----------------------------- */
#include "priorities.h"
#include "rkhfwk_pubsub.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ................................ Signals ................................ */
typedef enum Signals
{
   evSwitchOn,
   evSwitchOff,
   evRemoteStop,
   evRemoteIsolate,
   evRemoteDrift,
   evRemoteExit,
   evSpeedAvailable,
   evSpeedLost,
   evHaslerSpeedValid,
   evPulseGenSpeedValid,
   evGPSSpeedValid,
   evTout0,
   evTout1,
   evTout2,
   evTout3,
   evTout4,
   evTout5,
   TERMINATE
} Signals;

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void signals_publishSymbols(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
