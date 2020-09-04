/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SALT_H__
#define __SALT_H__

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
RKH_SMA_DCLR(salt);

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE Disabled, PreventiveBrake, Remote, Automatic, Intermittent, SpeedMissing, UsingHaslerSpeed, UsingPulseGenSpeed, UsingGPSSpeed;
RKH_DCLR_COMP_STATE Enabled, Limited;
RKH_DCLR_CHOICE_STATE Salt_C0, Salt_C1;

/* ------------------------------- Data types ------------------------------ */
/* ............................. Active object ............................. */
typedef struct Salt Salt;
struct Salt
{
    RKH_SMA_T sma;      /* base structure */
    RKHTmEvt tmEvtObj0;
    RKHTmEvt tmEvtObj1;
    RKHTmEvt tmEvtObj2;
    RKHTmEvt tmEvtObj3;
    RKHTmEvt tmEvtObj4;
    RKHTmEvt tmEvtObj5;
    rInt PREV_BRAKE_TIMEOUT;
    rInt REMOTE_CMD_TIMEOUT;
    rInt SPEED_HASLER_TIMEOUT;
    rInt SPEED_PULSE_TIMEOUT;
    rInt SPEED_GPS_TIMEOUT;
    rInt SPEED_MISSING_TIME;
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
