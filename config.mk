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
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/app/inc
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/hal/inc
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/model/src-gen
INCLUDES += -I$(PROGRAM_PATH_AND_NAME)/model/src-interface

#EXTRA SOURCE FILES
SRC += $(wildcard $(PROGRAM_PATH_AND_NAME)/app/src/*.c)
SRC += $(wildcard $(PROGRAM_PATH_AND_NAME)/hal/src/*.c)
SRC += $(wildcard $(PROGRAM_PATH_AND_NAME)/model/src-gen/*.c)
SRC += $(wildcard $(PROGRAM_PATH_AND_NAME)/model/src-interface/*.c)
#SRC +=  $(PROGRAM_PATH_AND_NAME)app/src/*.c
#SRC +=  $(PROGRAM_PATH_AND_NAME)hal/src/*.c 

#EXTRA DEFINITIONS
DEFINES+=__EDUCIAA_EID__