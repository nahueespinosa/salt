#Allowed modifiers in config.mk
#USE_RKH: y/n  y: allows the rkh framework to be compiled
#Allowed modifiers in config.mk
#USE_FREERTOS: y/n y: uses the FreeRTOS with Dyn Memory Allocation

ifeq ($(USE_LWIP),y)

LWIP_BASE = libs/lwip
DEFINES += USE_RKH

#INCLUDES PATHS
INCLUDES += -I$(LWIP_BASE)/src/include/
INCLUDES += -I$(LWIP_BASE)/src/include/ipv4

#SOURCE FILES
SRC+=$(wildcard $(LWIP_BASE)/src/api/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/core/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/netif/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/arch/*.c)

endif
