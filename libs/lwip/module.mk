ifeq ($(USE_LWIP),y)

LWIP_BASE = libs/lwip

#INCLUDES PATHS
INCLUDES += -I$(LWIP_BASE)/lwip_2_1_2/src/include/
INCLUDES += -I$(LWIP_BASE)

#SOURCE FILES
SRC+=$(wildcard $(LWIP_BASE)/lwip_2_1_2/src/apps/mqtt/*.c)
SRC+=$(wildcard $(LWIP_BASE)/lwip_2_1_2/src/api/*.c)
SRC+=$(wildcard $(LWIP_BASE)/lwip_2_1_2/src/netif/*.c)
SRC+=$(wildcard $(LWIP_BASE)/lwip_2_1_2/src/core/*.c)
SRC+=$(wildcard $(LWIP_BASE)/lwip_2_1_2/src/core/ipv4/*.c)
SRC+=$(wildcard $(LWIP_BASE)/arch/*.c)
SRC+=$(wildcard $(LWIP_BASE)/netif/*.c)

endif
