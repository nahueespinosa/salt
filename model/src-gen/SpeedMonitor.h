/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SPEEDMONITOR_H__
#define __SPEEDMONITOR_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhsma.h"
#include "rkhtmr.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(speedMonitor);

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE SpeedMissing, UsingHaslerSpeed, UsingPulseGenSpeed, UsingGPSSpeed;

/* ------------------------------- Data types ------------------------------ */
/* ............................. Active object ............................. */
typedef struct SpeedMonitor SpeedMonitor;
struct SpeedMonitor
{
    RKH_SMA_T sma;      /* base structure */
    RKHTmEvt tmEvtObj0;
    RKHTmEvt tmEvtObj1;
    RKHTmEvt tmEvtObj2;
    RKHTmEvt tmEvtObj3;
    rInt SPEED_HASLER_TIMEOUT;
    rInt SPEED_PULSE_TIMEOUT;
    rInt SPEED_GPS_TIMEOUT;
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
