#MODULES= app lpc_chip_43xx lpc_board_ciaa_edu_4337 sapi rkh bsp
#DEFINES=CORE_M4 __USE_LPCOPEN __USE_NEWLIB __EDUCIAA_EID__

VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y

# Libraries
USE_LPCOPEN=y
USE_SAPI=y
USE_RKH=y

#EXTRA INCLUDE PATHS
INCLUDES += -Iapp/inc
INCLUDES += -Ibsp/inc
INCLUDES += -Imodel/src-gen
INCLUDES += -Imodel/src-gen-interface

#EXTRA SOURCE FILES
SRC += $(wildcard app/src/*.c)
SRC += $(wildcard bsp/src/*.c)
SRC += $(wildcard model/src-gen/*.c)
SRC += $(wildcard model/src-gen-interface/*.c)

#EXTRA DEFINITIONS
DEFINES+=__EDUCIAA_EID__