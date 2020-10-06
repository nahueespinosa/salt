/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/15
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "panel.h"
#include "as1116.h"

/*=====[Definition macros of private constants]==============================*/

#define DIGIT_RED       AS1116_DIGIT0
#define DIGIT_BLUE      AS1116_DIGIT1
#define DIGIT_GREEN     AS1116_DIGIT2
#define DIGIT0          AS1116_DIGIT3
#define DIGIT1          AS1116_DIGIT4
#define DIGIT2          AS1116_DIGIT5
#define DIGIT3          AS1116_DIGIT6

/*=====[Definitions of private global variables]=============================*/

/**
 * Tabla interna para almacenar la relación entre los leds del sistema y
 * su posición dentro del dígito correpondiente
 */
static const uint8_t ledPosition[PANEL_LED_MAX] = {
   AS1116_SEGMENT_A_POS,
   AS1116_SEGMENT_F_POS,
   AS1116_SEGMENT_E_POS,
   AS1116_SEGMENT_C_POS,
   AS1116_SEGMENT_DP_POS,
   AS1116_SEGMENT_D_POS
};

//! Valor interno del dígito conectado al los leds rojos
static uint8_t digitRed;

//! Valor interno del dígito conectado al los leds verdes
static uint8_t digitGreen;

//! Valor interno del dígito conectado al los leds azules
static uint8_t digitBlue;

//! Estado interno que indica si el display está habilitado
static bool_t displayEnabled = false;

/*=====[Implementation of public functions]==================================*/

void panelInit(void) {
   as1116Config_t config;
   as1116DigitConfig_t digitConfig;

   config.clockSource = AS1116_INTERNAL_OSC;
   config.globalIntensity = AS1116_DUTY_7_16;
   config.scanLimit = AS1116_LIMIT_7_DIGITS;
   config.decodeMode = AS1116_DECODE_MODE_B;

   as1116Init(config);

   digitRed = 0;
   digitGreen = 0;
   digitBlue = 0;

   digitConfig.intensity = AS1116_DUTY_7_16;
   digitConfig.decodeEnable = AS1116_DECODE_DISABLED;
   digitConfig.usedMask = 0 |
         (1 << ledPosition[PANEL_LED_ON])     | (1 << ledPosition[PANEL_LED_AL]) |
         (1 << ledPosition[PANEL_LED_CT])     | (1 << ledPosition[PANEL_LED_FE]) |
         (1 << ledPosition[PANEL_LED_REMOTE]) | (1 << ledPosition[PANEL_LED_GPS]);

   as1116DigitConfig( DIGIT_RED, digitConfig );
   as1116DigitConfig( DIGIT_GREEN, digitConfig );
   as1116DigitConfig( DIGIT_BLUE, digitConfig );

   as1116DigitWrite( DIGIT_RED, digitRed );
   as1116DigitWrite( DIGIT_GREEN, digitGreen );
   as1116DigitWrite( DIGIT_BLUE, digitBlue );

   digitConfig.decodeEnable = AS1116_DECODE_ENABLED;
   digitConfig.usedMask = 0xFF;

   as1116DigitConfig( DIGIT0, digitConfig );
   as1116DigitConfig( DIGIT1, digitConfig );
   as1116DigitConfig( DIGIT2, digitConfig );
   as1116DigitConfig( DIGIT3, digitConfig );

   panelDisplayOff();
}

void panelLedWrite( ledMap_t led, ledColor_t color ) {
   uint8_t value = 0;

   value = (1 << ledPosition[led]);

   digitRed &= (~value);
   digitGreen &= (~value);
   digitBlue &= (~value);

   switch( color ) {
      case PANEL_LED_RED:
         digitRed |= value;
         break;
      case PANEL_LED_GREEN:
         digitGreen |= value;
         break;
      case PANEL_LED_BLUE:
         digitBlue |= value;
         break;
   }

   as1116DigitWrite( DIGIT_RED, digitRed );
   as1116DigitWrite( DIGIT_GREEN, digitGreen );
   as1116DigitWrite( DIGIT_BLUE, digitBlue );
}

void panelDisplayOn( void ) {
   displayEnabled = true;
}

void panelDisplayOff( void ) {
   displayEnabled = false;
   as1116DigitWrite( DIGIT0, AS1116_DIGIT_CODE_BLANK );
   as1116DigitWrite( DIGIT1, AS1116_DIGIT_CODE_BLANK );
   as1116DigitWrite( DIGIT2, AS1116_DIGIT_CODE_BLANK );
   as1116DigitWrite( DIGIT3, AS1116_DIGIT_CODE_BLANK );
}

void panelDisplayWrite( float value ) {
   uint8_t digitValues[4];

   if( displayEnabled == false ) {
      return;
   }

   if( value >= 1000 || value < 0 ) {
      panelDisplayDashedLine();
      return;
   }

   digitValues[3] = value / 100;
   value -= digitValues[3] * 100;
   digitValues[2] = value / 10;
   value -= digitValues[2] * 10;
   digitValues[1] = value / 1;
   value -= digitValues[1] * 1;
   digitValues[0] = value * 10;

   as1116DigitWrite( DIGIT3, digitValues[3] );
   as1116DigitWrite( DIGIT2, digitValues[2] );
   as1116DigitWrite( DIGIT1, digitValues[1] | AS1116_DIGIT_CODE_DOT);
   as1116DigitWrite( DIGIT0, digitValues[0] );
}

void panelDisplayDashedLine( void ) {
   if( displayEnabled == true ) {
      as1116DigitWrite( DIGIT0, AS1116_DIGIT_CODE_DASH );
      as1116DigitWrite( DIGIT1, AS1116_DIGIT_CODE_DASH );
      as1116DigitWrite( DIGIT2, AS1116_DIGIT_CODE_DASH );
      as1116DigitWrite( DIGIT3, AS1116_DIGIT_CODE_DASH );
   }
}

bool_t panelTest( void ) {
   bool_t retVal = TRUE;

   switch( as1116Test(AS1116_TEST_SHORT) ) {
      case AS1116_TEST_FAILED:
         gpioWrite(LEDR, ON);
         retVal = FALSE;
         break;
      case AS1116_TEST_OK:
         gpioWrite(LEDG, ON);
         break;
      case AS1116_TEST_NO_RESPONSE:
         gpioWrite(LEDB, ON);
         retVal = FALSE;
         break;
   }

   delay(200);
   gpioWrite(LEDR, OFF);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, OFF);
   delay(200);

   switch( as1116Test(AS1116_TEST_OPEN) ) {
      case AS1116_TEST_FAILED:
         gpioWrite(LEDR, ON);
         retVal = FALSE;
         break;
      case AS1116_TEST_OK:
         gpioWrite(LEDG, ON);
         break;
      case AS1116_TEST_NO_RESPONSE:
         gpioWrite(LEDB, ON);
         retVal = FALSE;
         break;
   }

   delay(200);
   gpioWrite(LEDR, OFF);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, OFF);
   delay(200);

   return retVal;
}
