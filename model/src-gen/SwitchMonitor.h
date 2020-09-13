/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SWITCHMONITOR_H__
#define __SWITCHMONITOR_H__

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
RKH_SMA_DCLR(switchMonitor);

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE SwitchOff, SwitchOn;
RKH_DCLR_CHOICE_STATE SwitchMonitor_C0, SwitchMonitor_C1, SwitchMonitor_C2, SwitchMonitor_C3;

/* ------------------------------- Data types ------------------------------ */
/* ............................. Active object ............................. */
typedef struct SwitchMonitor SwitchMonitor;
struct SwitchMonitor
{
    RKH_SMA_T sma;      /* base structure */
    RKHTmEvt tmEvtObj0;
    RKHTmEvt tmEvtObj1;
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
