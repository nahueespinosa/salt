/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/19
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "bsp.h"
#include "rkh.h"
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

/*=====[Implementation of public functions]==================================*/

int main( int argc, char *argv[] )
{
    bsp_init( argc, argv );

    RKH_SMA_ACTIVATE( mainControl, mainControl_qsto, QSTO_SIZE, 0, 0 );
    RKH_SMA_ACTIVATE( speedMonitor, speedMonitor_qsto, QSTO_SIZE, 0, 0 );
    RKH_SMA_ACTIVATE( switchMonitor, switchMonitor_qsto, QSTO_SIZE, 0, 0 );

    rkh_fwk_enter();

    RKH_TRC_CLOSE();
    return 0;
}
