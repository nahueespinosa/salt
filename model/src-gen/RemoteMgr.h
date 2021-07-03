/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __REMOTEMGR_H__
#define __REMOTEMGR_H__

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
RKH_SMA_DCLR(remoteMgr);

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE Disconnected, Connected;
RKH_DCLR_COMP_STATE Initialized;

/* ------------------------------- Data types ------------------------------ */
/* ............................. Active object ............................. */
typedef struct RemoteMgr RemoteMgr;
struct RemoteMgr
{
    RKH_SMA_T sma;      /* base structure */
    RKHTmEvt tmEvtObj0;
    RKHTmEvt tmEvtObj1;
    RKHTmEvt tmEvtObj2;
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
