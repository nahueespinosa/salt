/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp.c
 *  \brief      BSP for Cortex-M3 EDU-CIAA LPC4337 ARM-GCC
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.06.23  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Bali\F1a       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "bsp.h"

#include "rkh.h"
#include "panel.h"
#include "relay.h"
#include "switch.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TS_T tstamp;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void bsp_timeTick( void )
{
    ++tstamp;
}

RKH_TS_T rkh_trc_getts( void )
{
    return tstamp;
}

void bsp_init( int argc, char *argv[] )
{
    int i;
    float number;
    ledColor_t color = 0;
    ledMap_t led = 0;

    ( void )argc;
    ( void )argv;

    boardConfig();

    gpioConfig( 0, GPIO_ENABLE );
    gpioConfig( LED1, GPIO_OUTPUT );

    switchInit();
    relayInit();
    panelInit();
    panelTest();

    panelDisplayOn();

    // Juego de leds para mostrar el funcionamiento del panel
    for( i = 0 ; i < 100000 ; i++ ) {
       number = (float)i / 100;

       panelDisplayWrite(number);

       if( i < 25000 ) color = PANEL_LED_OFF;
       else if( i < 50000 ) color = PANEL_LED_RED;
       else if( i < 75000 ) color = PANEL_LED_GREEN;
       else color = PANEL_LED_BLUE;

       if( i % 25000 == 0 ) {
          for( led = 0 ; led < PANEL_LED_MAX ; led++ ) {
             panelLedWrite(led, color);
             delay(100);
          }
       }
    }

    panelLedWrite( PANEL_LED_ON, PANEL_LED_GREEN );
}

/* ------------------------------ End of file ------------------------------ */
