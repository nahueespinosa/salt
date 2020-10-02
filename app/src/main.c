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

#include "lwip/init.h"
#include "lwip/ip_addr.h"
#include "lwip/timeouts.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "netif/mchdrv.h"
#include "enc28j60.h"
#include "testapp.h"

#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

#define QSTO_SIZE           4

/*=====[Definitions of private global variables]=============================*/

static RKH_EVT_T *mainControl_qsto[QSTO_SIZE];
static RKH_EVT_T *switchMonitor_qsto[QSTO_SIZE];
static RKH_EVT_T *speedMonitor_qsto[QSTO_SIZE];

ip_addr_t mch_myip_addr = IPADDR4_INIT(0xc801a8c0UL); /* 192.168.1.200 */
ip_addr_t gw_addr = IPADDR4_INIT(0x0101a8c0UL); /* 192.168.1.1 */
ip_addr_t netmask = IPADDR4_INIT(0x00ffffffUL); /* 255.255.255.0 */

static struct netif mchdrv_netif;

static enc_device_t mchdrv_hw;

/*=====[Prototypes (declarations) of private functions]======================*/

static void setupTraceFilters(void);

void mch_net_init(void)
{
    // Initialize LWIP
    lwip_init();

    mchdrv_netif.hwaddr_len = 6;
    /* demo mac address */
    mchdrv_netif.hwaddr[0] = 0;
    mchdrv_netif.hwaddr[1] = 1;
    mchdrv_netif.hwaddr[2] = 2;
    mchdrv_netif.hwaddr[3] = 3;
    mchdrv_netif.hwaddr[4] = 4;
    mchdrv_netif.hwaddr[5] = 5;

    // Add our netif to LWIP (netif_add calls our driver initialization function)
    if (netif_add(&mchdrv_netif, &mch_myip_addr, &netmask, &gw_addr, &mchdrv_hw,
                mchdrv_init, ethernet_input) == NULL) {
        LWIP_ASSERT("mch_net_init: netif_add (mchdrv_init) failed\n", 0);
    }

    netif_set_up(&mchdrv_netif);
    netif_set_default(&mchdrv_netif);
}

void mch_net_poll(void)
{
    mchdrv_poll(&mchdrv_netif);
}

uint32_t sys_now(void)
{
   return tickRead();
}

/*=====[Implementation of public functions]==================================*/

int main( int argc, char *argv[] )
{
   bsp_init( argc, argv );

   gpioConfig(LED1, GPIO_OUTPUT);
   gpioConfig(LED2, GPIO_OUTPUT);
   gpioWrite(LEDB, OFF);
   gpioWrite(LEDR, OFF);
   gpioWrite(LED1, ON);
   gpioWrite(LED2, ON);

   uartInit( UART_USB, 115200 );

   LWIP_DEBUGF(NETIF_DEBUG, ("Prueba de %s\r\n", "ENC28J60"));

   mch_net_init();

   testapp_init();

   gpioWrite(LED1, OFF);
   gpioWrite(LED2, OFF);

   while (1) {
       gpioWrite(LEDB, ON);
       mch_net_poll();
       sys_check_timeouts();
       delay(10);
   }

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
