/**
 *  \file       RemoteMgrActRequired.c
 *  \brief      This file implements the required operations for RemoteMgr
 *              active object.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "bsp.h"
#include "signals.h"
#include "rkhtrc_record.h"
#include "RemoteMgr.h"

#include "lwip/init.h"
#include "lwip/ip_addr.h"
#include "lwip/timeouts.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "netif/mchdrv.h"

#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"

#include "enc28j60.h"

#include "sapi.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
ip_addr_t mch_myip_addr = IPADDR4_INIT_BYTES(192,168,0,200);
ip_addr_t gw_addr = IPADDR4_INIT_BYTES(192,168,0,1);
ip_addr_t netmask = IPADDR4_INIT_BYTES(255,255,255,0);
ip_addr_t dest_addr = IPADDR4_INIT_BYTES(3,121,33,50);

static struct netif enc_netif;
static enc_device_t enc_device;
static mqtt_client_t static_client;
struct mqtt_connect_client_info_t ci;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
  err_t err;
  if(status == MQTT_CONNECT_ACCEPTED) {
    printf("mqtt_connection_cb: Successfully connected\n");

    /* Setup callback for incoming publish requests */
    // mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);

    /* Subscribe to a topic named "subtopic" with QoS level 1, call mqtt_sub_request_cb with result */
    // err = mqtt_subscribe(client, "subtopic", 1, mqtt_sub_request_cb, arg);

    if(err != ERR_OK) {
      printf("mqtt_subscribe return: %d\n", err);
    }

    gpioWrite(LEDB, ON);

  } else {
    printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);

    /* Its more nice to be connected, so try to reconnect */
    //example_do_connect(client);
    gpioWrite(LEDR, ON);
  }
}

/* Called when publish is complete either with sucess or failure */
static void mqtt_pub_request_cb(void *arg, err_t result)
{
  if(result != ERR_OK) {
    printf("Publish result: %d\n", result);
  }
}

/* ---------------------------- Global functions --------------------------- */
void RemoteMgrInit(void) {
   // Initialize LWIP
   lwip_init();

   enc_netif.hwaddr_len = 6;
   /* demo mac address */
   enc_netif.hwaddr[0] = 0;
   enc_netif.hwaddr[1] = 1;
   enc_netif.hwaddr[2] = 2;
   enc_netif.hwaddr[3] = 3;
   enc_netif.hwaddr[4] = 4;
   enc_netif.hwaddr[5] = 5;

   // Add our netif to LWIP (netif_add calls our driver initialization function)
   if( netif_add(&enc_netif, &mch_myip_addr, &netmask, &gw_addr, &enc_device,
               mchdrv_init, ethernet_input) == NULL ) {
       LWIP_ASSERT("mch_net_init: netif_add (mchdrv_init) failed\n", 0);
   }

   netif_set_up(&enc_netif);
   netif_set_default(&enc_netif);

   ci.client_id = "lwip_test";
   ci.client_pass = 0;
   ci.client_user = 0;
   ci.keep_alive = 0;
   ci.will_msg = 0;
   ci.will_qos = 0;
   ci.will_retain = 0;
   ci.will_topic = 0;

   gpioConfig(LEDB, GPIO_OUTPUT);
   gpioConfig(LEDR, GPIO_OUTPUT);
}

void RemoteMgrUpdate(void) {
   mchdrv_poll(&enc_netif);
   sys_check_timeouts();
}

void RemoteMgrConnect(void) {
   mqtt_client_connect(&static_client, &dest_addr, MQTT_PORT, mqtt_connection_cb, 0, &ci);
}

void RemoteMgrSendStatus(void) {
   mqtt_publish(&static_client, "/salt/", "{\"test\":\"ok\"}", 13, 2, 0, mqtt_pub_request_cb, NULL);
   // mqtt_disconnect(&static_client);
}

/* ------------------------------ End of file ------------------------------ */
