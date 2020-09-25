/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/19
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "bsp.h"
#include "signals.h"

#include "rkh.h"
#include "rkhfwk_pubsub.h"
#include "rkhfwk_sched.h"

#include "MainControl.h"
#include "SwitchMonitor.h"
#include "SpeedMonitor.h"

/*=====[Definition macros of private constants]==============================*/

#define QSTO_SIZE           4

/*=====[Definitions of private global variables]=============================*/

static RKH_EVT_T *mainControl_qsto[QSTO_SIZE];
static RKH_EVT_T *switchMonitor_qsto[QSTO_SIZE];
static RKH_EVT_T *speedMonitor_qsto[QSTO_SIZE];

/*=====[Prototypes (declarations) of private functions]======================*/

static void setupTraceFilters(void);

/*=====[Implementation of public functions]==================================*/

int main( int argc, char *argv[] )
{
   bsp_init( argc, argv );

   rkh_fwk_init();

   rkh_pubsub_init();
   rkh_pubsub_subscribe( 0, mainControl ); // Subscribe to channel of events number 0

   setupTraceFilters();

   RKH_TRC_OPEN();

   signalsPublishSymbols();

   RKH_ENA_INTERRUPT();

   RKH_SMA_ACTIVATE( mainControl, mainControl_qsto, QSTO_SIZE, 0, 0 );
   RKH_SMA_ACTIVATE( speedMonitor, speedMonitor_qsto, QSTO_SIZE, 0, 0 );
   RKH_SMA_ACTIVATE( switchMonitor, switchMonitor_qsto, QSTO_SIZE, 0, 0 );

   rkh_fwk_enter();

   RKH_TRC_CLOSE();
   return 0;
}

/*=====[Implementation of private functions]=================================*/

static void setupTraceFilters(void) {
   RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
   RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
   RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
   RKH_FILTER_OFF_EVENT( RKH_TE_SMA_FIFO );
   RKH_FILTER_OFF_EVENT( RKH_TE_SMA_LIFO );
   RKH_FILTER_OFF_SMA( mainControl );
   RKH_FILTER_OFF_SMA( speedMonitor );
   RKH_FILTER_OFF_SMA( switchMonitor );
   RKH_FILTER_OFF_ALL_SIGNALS();
}
