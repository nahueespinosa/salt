/**
 *  \file       signales.c
 *  \brief      Event signal RKH trace publishing.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "../src-interface/signals.h"

#include "rkh.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
signals_publishSymbols(void)
{
    RKH_TR_FWK_SIG(evSwitchOn);
    RKH_TR_FWK_SIG(evSwitchOff);
    RKH_TR_FWK_SIG(evRemoteStop);
    RKH_TR_FWK_SIG(evRemoteIsolate);
    RKH_TR_FWK_SIG(evRemoteDrift);
    RKH_TR_FWK_SIG(evRemoteExit);
    RKH_TR_FWK_SIG(evSpeedAvailable);
    RKH_TR_FWK_SIG(evSpeedLost);
    RKH_TR_FWK_SIG(evHaslerSpeedValid);
    RKH_TR_FWK_SIG(evPulseGenSpeedValid);
    RKH_TR_FWK_SIG(evGPSSpeedValid);
    RKH_TR_FWK_SIG(evTout0);
    RKH_TR_FWK_SIG(evTout1);
    RKH_TR_FWK_SIG(evTout2);
    RKH_TR_FWK_SIG(evTout3);
    RKH_TR_FWK_SIG(evTout4);

    RKH_TR_FWK_SIG(RKH_SM_CREATION_EVENT);
    RKH_TR_FWK_SIG(RKH_COMPLETION_EVENT);
}

/* ------------------------------ End of file ------------------------------ */
