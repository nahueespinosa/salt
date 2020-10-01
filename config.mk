PROGRAM_NAME = salt

VERBOSE=y
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y
LOAD_INRAM=n

# Libraries
USE_LPCOPEN=y
USE_SAPI=y
USE_RKH=y
USE_LWIP=y

#INCLUDE PATHS
INCLUDES += -Iapp/inc
INCLUDES += -Ibsp/inc
INCLUDES += -Imodel/src-gen
INCLUDES += -Imodel/src-gen-interface

#SOURCE FILES
SRC += $(wildcard app/src/*.c)
SRC += $(wildcard bsp/src/*.c)
SRC += $(wildcard model/src-gen/*.c)
SRC += $(wildcard model/src-gen-interface/*.c)

#EXTRA DEFINITIONS
DEFINES+=__EDUCIAA_EID__