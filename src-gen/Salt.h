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
RKH_DCLR_BASIC_STATE Disabled, PreventiveBrake, TotalStop, TotalIsolation, Drift, IntermittentTractionEnabled, IntermittentTractionDisabled, IntermittentBrake, UnknownCmd, ActiveCmd, TractionEnabled, TractionDisabled, EmergencyBrake, IntermittentTractionEnabled, IntermittentTractionDisabled, IntermittentBrake, SpeedMissing, UsingHaslerSpeed, UsingPulseGenSpeed, UsingGPSSpeed;
RKH_DCLR_COMP_STATE Enabled, Remote, Intermittent, Limited, Automatic, Intermittent;
RKH_DCLR_CHOICE_STATE Salt_C0, Salt_C1, Salt_C2, Salt_C3, Salt_C4, Salt_C5;

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
    RKHTmEvt tmEvtObj6;
    RKHTmEvt tmEvtObj7;
    RKHTmEvt tmEvtObj8;
    RKHTmEvt tmEvtObj9;
    RKHTmEvt tmEvtObj10;
    RKHTmEvt tmEvtObj11;
    RKHTmEvt tmEvtObj12;
    RKHTmEvt tmEvtObj13;
    rInt PREVENTIVE_BRAKE_TIMEOUT;
    rInt EMERGENCY_BRAKE_TIMEOUT;
    rInt REMOTE_CMD_TIMEOUT;
    rInt SPEED_HASLER_TIMEOUT;
    rInt SPEED_PULSE_TIMEOUT;
    rInt SPEED_GPS_TIMEOUT;
    rInt SPEED_MISSING_TIME;
    rInt REMOTE_CMD_STOP;
    rInt REMOTE_CMD_ISOLATE;
    rInt REMOTE_CMD_DRIFT;
    rInt REMOTE_CMD_INTERMITTENT;
    rInt REMOTE_CMD_EXIT;
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
