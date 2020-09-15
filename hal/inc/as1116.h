/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/14
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __AS1116_H__
#define __AS1116_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

#define AS1116_DIGITS_MAX                 8

// segment positions
#define AS1116_SEGMENT_G_POS              0
#define AS1116_SEGMENT_F_POS              1
#define AS1116_SEGMENT_E_POS              2
#define AS1116_SEGMENT_D_POS              3
#define AS1116_SEGMENT_C_POS              4
#define AS1116_SEGMENT_B_POS              5
#define AS1116_SEGMENT_A_POS              6
#define AS1116_SEGMENT_DP_POS             7

/*==================[typedef]================================================*/

typedef enum {
   AS1116_DECODE_DISABLED = 0,   /* Decode mode disabled */
   AS1116_DECODE_ENABLED  = 1    /* Code-B/HEX decode mode enabled */
} as1116DecodeEnable_t;

typedef enum {
   AS1116_DECODE_CODE_B = 0,
   AS1116_DECODE_HEX    = 1
} as1116DecodeMode_t;

typedef enum {
   AS1116_DUTY_1_16  = 0x00,
   AS1116_DUTY_2_16  = 0x01,
   AS1116_DUTY_3_16  = 0x02,
   AS1116_DUTY_4_16  = 0x03,
   AS1116_DUTY_5_16  = 0x04,
   AS1116_DUTY_6_16  = 0x05,
   AS1116_DUTY_7_16  = 0x06,
   AS1116_DUTY_8_16  = 0x07,
   AS1116_DUTY_9_16  = 0x08,
   AS1116_DUTY_10_16 = 0x09,
   AS1116_DUTY_11_16 = 0x0A,
   AS1116_DUTY_12_16 = 0x0B,
   AS1116_DUTY_13_16 = 0x0C,
   AS1116_DUTY_14_16 = 0x0D,
   AS1116_DUTY_15_16 = 0x0E,
   AS1116_DUTY_16_16 = 0x0F,
   AS1116_MAX_INTENSITY = 0x0F
} as1116Intensity_t;

typedef enum {
   AS1116_LIMIT_1_DIGITS = 0x0,
   AS1116_LIMIT_2_DIGITS = 0x1,
   AS1116_LIMIT_3_DIGITS = 0x2,
   AS1116_LIMIT_4_DIGITS = 0x3,
   AS1116_LIMIT_5_DIGITS = 0x4,
   AS1116_LIMIT_6_DIGITS = 0x5,
   AS1116_LIMIT_7_DIGITS = 0x6,
   AS1116_LIMIT_8_DIGITS = 0x7
} as1116ScanLimit_t;

typedef enum {
   AS1116_INTERNAL_OSC  = 0,     /* Internal oscillator is used for system clock */
   AS1116_SERIAL_CLK    = 1      /* Pin CLK of the serial interface operates as system clock */
} as1116ClockSource_t;

typedef struct {
   as1116DecodeMode_t decodeMode;
   as1116Intensity_t globalIntensity;
   as1116ScanLimit_t scanLimit;
   as1116ClockSource_t clockSource;
} as1116Config_t;

typedef struct {
   as1116DecodeEnable_t decodeEnable;
   as1116Intensity_t intensity;
   uint8_t usedMask;
} as1116DigitConfig_t;

typedef enum {
   DIGIT0,
   DIGIT1,
   DIGIT2,
   DIGIT3,
   DIGIT4,
   DIGIT5,
   DIGIT6,
   DIGIT7,
} as1116DigitMap_t;

typedef enum {
   AS1116_TEST_FAILED = 0,
   AS1116_TEST_OK     = 1
} as1116TestResult_t;

typedef enum {
   AS1116_TEST_SHORT  = 0,
   AS1116_TEST_OPEN   = 1
} as1116TestType_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void as1116Init( as1116Config_t config );
void as1116DigitConfig( as1116DigitMap_t digit, as1116DigitConfig_t config );
void as1116DigitWrite( as1116DigitMap_t digit, uint8_t data );
as1116TestResult_t as1116Test( as1116TestType_t type );

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif
