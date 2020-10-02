ifeq ($(USE_LWIP),y)

LWIP_BASE = libs/lwip

#INCLUDES PATHS
INCLUDES += -I$(LWIP_BASE)/src/include/

#SOURCE FILES
SRC+=$(wildcard $(LWIP_BASE)/src/apps/mqtt/mqtt.c)
SRC+=$(wildcard $(LWIP_BASE)/src/api/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/core/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/core/ipv4/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/netif/*.c)
SRC+=$(wildcard $(LWIP_BASE)/src/arch/*.c)


endif
