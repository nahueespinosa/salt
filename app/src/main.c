/**
 *  \file       main.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_sched.h"
#include "bsp.h"

#include "panel.h"

#include "MainControl.h"
#include "SwitchMonitor.h"
#include "SpeedMonitor.h"

/* ----------------------------- Local macros ------------------------------ */
#define QSTO_SIZE           4

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_EVT_T *mainControl_qsto[QSTO_SIZE];
static RKH_EVT_T *switchMonitor_qsto[QSTO_SIZE];
static RKH_EVT_T *speedMonitor_qsto[QSTO_SIZE];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int main( int argc, char *argv[] )
{
    bsp_init( argc, argv );

    panelInit();
    panelLedWrite( PANEL_LED_ON, PANEL_LED_GREEN );

    RKH_SMA_ACTIVATE( mainControl, mainControl_qsto, QSTO_SIZE, 0, 0 );
    RKH_SMA_ACTIVATE( speedMonitor, speedMonitor_qsto, QSTO_SIZE, 0, 0 );
    RKH_SMA_ACTIVATE( switchMonitor, switchMonitor_qsto, QSTO_SIZE, 0, 0 );

    rkh_fwk_enter();

    RKH_TRC_CLOSE();
    return 0;
}

/* ------------------------------ End of file ------------------------------ */
