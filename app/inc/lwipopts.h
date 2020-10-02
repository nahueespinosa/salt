#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/** 
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                          1

/* Disable the more complex APIs */
#define LWIP_SOCKET                     0
#define LWIP_NETCONN                    0
#define LWIP_TCP                        1

/* Disable subsystems that eat memory and are not needed in this example */
#define IP_REASSEMBLY                   0
#define PBUF_POOL_SIZE                  0

#define SYS_LIGHTWEIGHT_PROT            0

#define LWIP_DEBUG
#define LWIP_DBG_MIN_LEVEL             LWIP_DBG_LEVEL_ALL
// #define NETIF_DEBUG                    LWIP_DBG_ON
// #define UDP_DEBUG                      LWIP_DBG_ON
#define MQTT_DEBUG                     LWIP_DBG_ON

/* add one timeout for testapp.c to the default timeouts */
#define MEMP_NUM_SYS_TIMEOUT            (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_SUPPORT + 1)

#endif /* MY__LWIPOPTS_H__ */
