PROGRAM_NAME = salt

VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y
LOAD_INRAM=n

# Libraries
USE_LPCOPEN=y
USE_SAPI=y
USE_RKH=y

#INCLUDE PATHS
INCLUDES += -Iapp/inc
INCLUDES += -Ibsp/inc
INCLUDES += -Imodel/src-gen
INCLUDES += -Imodel/src-gen-interface

INCLUDES += -Isim808_v2/modcmd
INCLUDES += -Isim808_v2/modmgr
INCLUDES += -Isim808_v2/parser/sim900

#SOURCE FILES
SRC += $(wildcard app/src/*.c)
SRC += $(wildcard bsp/src/*.c)
SRC += $(wildcard model/src-gen/*.c)
SRC += $(wildcard model/src-gen-interface/*.c)

SRC += $(wildcard sim808_v2/modcmd/*.c)
SRC += $(wildcard sim808_v2/modmgr/*.c)
SRC += $(wildcard sim808_v2/parser/sim900/*.c)

#EXTRA DEFINITIONS
DEFINES+=__EDUCIAA_EID__