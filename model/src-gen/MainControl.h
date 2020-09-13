/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __MAINCONTROL_H__
#define __MAINCONTROL_H__

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
RKH_SMA_DCLR(mainControl);

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE Disabled, PreventiveBrake, TractionEnabled, TractionDisabled, EmergencyBrake, IntermittentTractionEnabled, IntermittentTractionDisabled, IntermittentBrake, Waiting, Starting, Stopped, Isolated, Adrift;
RKH_DCLR_COMP_STATE Enabled, Limited, Automatic, Intermittent, Remote;
RKH_DCLR_CHOICE_STATE MainControl_C0;

/* ------------------------------- Data types ------------------------------ */
/* ............................. Active object ............................. */
typedef struct MainControl MainControl;
struct MainControl
{
    RKH_SMA_T sma;      /* base structure */
    RKHTmEvt tmEvtObj0;
    RKHTmEvt tmEvtObj1;
    RKHTmEvt tmEvtObj2;
    RKHTmEvt tmEvtObj3;
    RKHTmEvt tmEvtObj4;
    rInt SALT_CT_LIMIT_UP;
    rInt SALT_CT_LIMIT_DOWN;
    rInt SALT_FE_LIMIT;
    rInt SALT_FE_TIMEOUT;
    rInt SALT_INTERMITTENT_TIME_OFF;
    rInt SALT_INTERMITTENT_TIME_ON;
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
