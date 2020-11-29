/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/14
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "as1116.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

#define AS1116_SSEL_PIN                   GPIO6
#define AS1116_SPI                        SPI0

#define AS1116_REG_MASK                   0x1F
#define AS1116_READ_BIT                   (1<<6)

#define AS1116_CLOCK_FREQUENCY            500000

/* Cantidad de intentos de lectura del registro de pruebas hasta leer
 * una respuesta v�lida */
#define AS1116_TEST_TIMEOUT               100

// Register map
#define AS1116_REG_NOP                    0x00
#define AS1116_REG_DIGIT0                 0x01
#define AS1116_REG_DIGIT1                 0x02
#define AS1116_REG_DIGIT2                 0x03
#define AS1116_REG_DIGIT3                 0x04
#define AS1116_REG_DIGIT4                 0x05
#define AS1116_REG_DIGIT5                 0x06
#define AS1116_REG_DIGIT6                 0x07
#define AS1116_REG_DIGIT7                 0x08
#define AS1116_REG_DECODE_MODE_ENABLE     0x09
#define AS1116_REG_GLOBAL_INTENSITY       0x0A
#define AS1116_REG_SCAN_LIMIT             0x0B
#define AS1116_REG_SHUTDOWN               0x0C
#define AS1116_REG_FEATURE                0x0E
#define AS1116_REG_DISPLAY_TEST_MODE      0x0F
#define AS1116_REG_DIG01_INTENSITY        0x10
#define AS1116_REG_DIG23_INTENSITY        0x11
#define AS1116_REG_DIG45_INTENSITY        0x12
#define AS1116_REG_DIG67_INTENSITY        0x13
#define AS1116_REG_DIG0_DIAGNOSTIC        0x14
#define AS1116_REG_DIG1_DIAGNOSTIC        0x15
#define AS1116_REG_DIG2_DIAGNOSTIC        0x16
#define AS1116_REG_DIG3_DIAGNOSTIC        0x17
#define AS1116_REG_DIG4_DIAGNOSTIC        0x18
#define AS1116_REG_DIG5_DIAGNOSTIC        0x19
#define AS1116_REG_DIG6_DIAGNOSTIC        0x1A
#define AS1116_REG_DIG7_DIAGNOSTIC        0x1B

// Decode Mode register
#define AS1116_DECODE_MODE_DISABLE_ALL    0x00
#define AS1116_DECODE_MODE_ENABLE_ALL     0xFF

// Feature register
#define AS1116_FEATURE_CLK_EN             (1<<0)
#define AS1116_FEATURE_REG_RES            (1<<1)
#define AS1116_FEATURE_DECODE_SEL         (1<<2)
#define AS1116_FEATURE_BLINK_EN           (1<<4)
#define AS1116_FEATURE_BLINK_FREQ_SEL     (1<<5)
#define AS1116_FEATURE_SYNC               (1<<6)
#define AS1116_FEATURE_BLINK_START        (1<<7)

// Shutdown register
#define AS1116_SHUTDOWN_OFF_MODE_RESET    (0x00)
#define AS1116_SHUTDOWN_OFF_MODE          (0x80)
#define AS1116_SHUTDOWN_NORMAL_MODE_RESET (0x01)
#define AS1116_SHUTDOWN_NORMAL_MODE       (0x81)

// Display test register
#define AS1116_TEST_LED_OPTICAL           (1<<0)
#define AS1116_TEST_LED_SHORT             (1<<1)
#define AS1116_TEST_LED_OPEN              (1<<2)
#define AS1116_TEST_LED_RUNNING           (1<<3)
#define AS1116_TEST_LED_GLOBAL            (1<<4)
#define AS1116_TEST_REXT_OPEN             (1<<5)
#define AS1116_TEST_REXT_SHORT            (1<<6)

// Definiciones necesarias para construir la tabla de consulta
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n)  R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n)  R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

/*=====[Definitions of private global variables]=============================*/

//! Tabla interna para invertir los bits necesaria para transmisi�n y recepci�n
static const unsigned char bitReverseTable[256] = {
   R6(0), R6(2), R6(1), R6(3)
};

//! Buffer interno de transmisi�n y recepci�n de datos
static uint8_t as1116Buffer[2];

//! Indicador para saber si el m�dulo est� inicializado
static bool_t initialized = false;

//! Indicador para saber la cantidad de d�gitos utilizados
static bool_t usedDigits = 0;

//! Tabla interna para almacenar la configuraci�n de los d�gitos
static as1116DigitConfig_t digitConfig[AS1116_DIGITS_MAX];

/*=====[Prototypes (declarations) of private functions]======================*/

/**
 * @brief Escribir un valor en un registro del integrado AS1116
 *
 * Si el m�dulo no est� inicializado, no ejecuta ninguna acci�n.
 *
 * @param[in]  reg         Direcci�n del registro
 * @param[in]  data        Valor a escribir
 */
static void as1116RegisterWrite( uint8_t reg, uint8_t data );

/**
 * @brief Leer un valor de un registro del integrado AS1116
 *
 * Si el m�dulo no est� inicializado, no ejecuta ninguna acci�n.
 *
 * @param[in]  reg         Direcci�n del registro
 * @return                 Valor leido
 */
static uint8_t as1116RegisterRead( uint8_t reg );

/*=====[Implementation of public functions]==================================*/

void as1116Init( as1116Config_t config ) {
   initialized = true;

   Chip_SCU_PinMuxSet( 0xF, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // SSP1_SCK
   Chip_SCU_PinMuxSet( 0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // SSP1_MISO
   Chip_SCU_PinMuxSet( 0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); // SSP1_MOSI

   /* Inicializa el perif�rico SSP */
   Chip_SSP_Init(LPC_SSP1);
   Chip_SSP_Set_Mode(LPC_SSP1, SSP_MODE_MASTER);
   Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHA0_CPOL0);
   Chip_SSP_SetBitRate(LPC_SSP1, AS1116_CLOCK_FREQUENCY);
   Chip_SSP_Enable( LPC_SSP1 );

   gpioConfig( AS1116_SSEL_PIN, GPIO_OUTPUT );
   gpioWrite( AS1116_SSEL_PIN, ON );

   /* Inicializa la cantidad de d�gitos a utilizar */
   usedDigits = config.scanLimit + 1;

   as1116RegisterWrite( AS1116_REG_SHUTDOWN, AS1116_SHUTDOWN_NORMAL_MODE_RESET );
   as1116RegisterWrite( AS1116_REG_DECODE_MODE_ENABLE, AS1116_DECODE_MODE_DISABLE_ALL );
   as1116RegisterWrite( AS1116_REG_GLOBAL_INTENSITY, config.globalIntensity );
   as1116RegisterWrite( AS1116_REG_SCAN_LIMIT, config.scanLimit );
   as1116RegisterWrite( AS1116_REG_FEATURE, 0x00 | config.clockSource | (config.decodeMode << 2) );
   as1116RegisterWrite( AS1116_REG_DISPLAY_TEST_MODE, 0x00);
}

void as1116DigitConfig( as1116DigitMap_t digit, as1116DigitConfig_t config ) {
   uint8_t index;
   uint8_t value;
   uint8_t reg;

   if( !initialized ){
      return;
   }

   if( digit >= usedDigits ){
      return;
   }

   digitConfig[digit] = config;

   /* Prepara el valor del registro DECODE_MODE_ENABLE de acuerdo a si est� o
    * no habilitada la decodificaci�n para cada d�gito particular */
   value = 0x00;
   for( index = 0 ; index < AS1116_DIGITS_MAX ; index++ ) {
      value |= digitConfig[index].decodeEnable << index;
   }

   as1116RegisterWrite( AS1116_REG_DECODE_MODE_ENABLE, value );

   /* Prepara el valor del registro de intensidad correspondiente */
   switch(digit) {
      case AS1116_DIGIT0:
      case AS1116_DIGIT1:
         reg = AS1116_REG_DIG01_INTENSITY;
         value = digitConfig[AS1116_DIGIT0].intensity |
                (digitConfig[AS1116_DIGIT1].intensity << 4);
         break;
      case AS1116_DIGIT2:
      case AS1116_DIGIT3:
         reg = AS1116_REG_DIG23_INTENSITY;
         value = digitConfig[AS1116_DIGIT2].intensity |
                (digitConfig[AS1116_DIGIT3].intensity << 4);
         break;
      case AS1116_DIGIT4:
      case AS1116_DIGIT5:
         reg = AS1116_REG_DIG45_INTENSITY;
         value = digitConfig[AS1116_DIGIT4].intensity |
                (digitConfig[AS1116_DIGIT5].intensity << 4);
         break;
      case AS1116_DIGIT6:
      case AS1116_DIGIT7:
         reg = AS1116_REG_DIG67_INTENSITY;
         value = digitConfig[AS1116_DIGIT6].intensity |
                (digitConfig[AS1116_DIGIT7].intensity << 4);
         break;
   }

   as1116RegisterWrite( reg, value );
}

void as1116DigitWrite( as1116DigitMap_t digit, uint8_t data ){

   if( !initialized ){
      return;
   }

   if( digit >= usedDigits ){
      return;
   }

   as1116RegisterWrite( digit + AS1116_REG_DIGIT0, data );
}

as1116TestResult_t as1116Test( as1116TestType_t type ) {
   uint8_t cmd;
   uint8_t value;
   uint32_t timeout;
   as1116DigitMap_t digit;

   if( !initialized ){
      return AS1116_TEST_FAILED;
   }

   switch( type ) {
      case AS1116_TEST_SHORT:
         cmd = AS1116_TEST_LED_SHORT;
         break;
      case AS1116_TEST_OPEN:
         cmd = AS1116_TEST_LED_OPEN;
         break;
   }

   /* Comando de inicio de prueba */
   as1116RegisterWrite( AS1116_REG_DISPLAY_TEST_MODE, cmd );

   /* Lee el registro de estado hasta que comienza la prueba */
   timeout = 0;

   do {
      value = as1116RegisterRead( AS1116_REG_DISPLAY_TEST_MODE );
      timeout++;

      if( timeout >= AS1116_TEST_TIMEOUT ) {
         return AS1116_TEST_NO_RESPONSE;
      }

   } while( (value & AS1116_TEST_LED_RUNNING) == 0 );

   /* Lee el registro de estado hasta que termina la prueba */
   timeout = 0;

   do {
      value = as1116RegisterRead( AS1116_REG_DISPLAY_TEST_MODE );
      timeout++;

      if( timeout >= AS1116_TEST_TIMEOUT ) {
         return AS1116_TEST_NO_RESPONSE;
      }

   } while( (value & AS1116_TEST_LED_RUNNING) != 0 );

   /* Si se detect� una falla global se leen los registros de diagn�stico
    * de cada d�gito */
   if( (value & AS1116_TEST_LED_GLOBAL) != 0 ) {
      for( digit = 0 ; digit < usedDigits ; digit++ ) {
         value = as1116RegisterRead( digit + AS1116_REG_DIG0_DIAGNOSTIC );

         if( (value & digitConfig[digit].usedMask) != 0 ) {
            return AS1116_TEST_FAILED;
         }
      }
   }

   return AS1116_TEST_OK;
}

/*=====[Implementation of private functions]=================================*/

void as1116RegisterWrite( uint8_t reg, uint8_t data ){
   if( !initialized ){
      return;
   }

   /* Se invierten los bits de valor del registro */
   as1116Buffer[0] = bitReverseTable[data];
   /* Se invierten los bits de direcci�n del registro */
   as1116Buffer[1] = bitReverseTable[(reg & AS1116_REG_MASK)];

   gpioWrite( AS1116_SSEL_PIN, OFF );
   spiWrite( AS1116_SPI, as1116Buffer, 2 );
   delayInaccurateUs(1);
   gpioWrite( AS1116_SSEL_PIN, ON );
}

uint8_t as1116RegisterRead( uint8_t reg ){
   if( !initialized ){
      return 0;
   }

   /* Se invierten los bits de direcci�n del registro */
   as1116Buffer[0] = bitReverseTable[(reg & AS1116_REG_MASK) | AS1116_READ_BIT];
   as1116Buffer[1] = 0x00;

   gpioWrite( AS1116_SSEL_PIN, OFF );
   spiWrite( AS1116_SPI, as1116Buffer, 1 );

   /* Cambia el formato a detecci�n en flanco descendente porque el AS1116 cambia
    * el estado del pin MISO sobre el flanco ascendente */
   Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHA1_CPOL0);
   delayInaccurateUs(1);

   gpioWrite( AS1116_SSEL_PIN, ON );
   spiRead( AS1116_SPI, as1116Buffer+1, 1 );

   /* Vuelve al formato normal para escritura sobre el flanco ascendente */
   Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHA0_CPOL0);

   /* Devuelve el valor le�do del registro, no es necesario invertir los bit */
   return as1116Buffer[1];
}
