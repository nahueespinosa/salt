/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/14
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "as1116.h"

/*=====[Definition macros of private constants]==============================*/

#define AS1116_SSEL_PIN                   GPIO6
#define AS1116_SPI                        SPI0

#define AS1116_REG_MASK                   0x1F
#define AS1116_READ_BIT                   (1<<6)

// register map
#define AS1116_REG_NOP                    0x00
#define AS1116_REG_DIGIT0                 0x01
#define AS1116_REG_DIGIT1                 0x02
#define AS1116_REG_DIGIT2                 0x03
#define AS1116_REG_DIGIT3                 0x04
#define AS1116_REG_DIGIT4                 0x05
#define AS1116_REG_DIGIT5                 0x06
#define AS1116_REG_DIGIT6                 0x07
#define AS1116_REG_DIGIT7                 0x08
#define AS1116_REG_DECODE_MODE            0x09
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

// feature register
#define AS1116_FEATURE_CLK_EN             (1<<0)
#define AS1116_FEATURE_REG_RES            (1<<1)
#define AS1116_FEATURE_DECODE_SEL         (1<<2)
#define AS1116_FEATURE_BLINK_EN           (1<<4)
#define AS1116_FEATURE_BLINK_FREQ_SEL     (1<<5)
#define AS1116_FEATURE_SYNC               (1<<6)
#define AS1116_FEATURE_BLINK_START        (1<<7)

// shutdown register
#define AS1116_SHUTDOWN_OFF_MODE_RESET    (0x00)
#define AS1116_SHUTDOWN_OFF_MODE          (0x80)
#define AS1116_SHUTDOWN_NORMAL_MODE_RESET (0x01)
#define AS1116_SHUTDOWN_NORMAL_MODE       (0x81)

// display test register
#define AS1116_TEST_LED_OPTICAL           (1<<0)
#define AS1116_TEST_LED_SHORT             (1<<1)
#define AS1116_TEST_LED_OPEN              (1<<2)
#define AS1116_TEST_LED_RUNNING           (1<<3)
#define AS1116_TEST_LED_GLOBAL            (1<<4)
#define AS1116_TEST_REXT_OPEN             (1<<5)
#define AS1116_TEST_REXT_SHORT            (1<<6)

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n)  R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n)  R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

/*=====[Definitions of private global variables]=============================*/

static const unsigned char BitReverseTable256[256] = {
   R6(0), R6(2), R6(1), R6(3)
};

static uint8_t as1116Buffer[2];
static bool_t initialized = false;

/*=====[Prototypes (declarations) of private functions]======================*/

void as1116WriteReg( uint8_t reg, uint8_t data );
uint8_t as1116ReadReg( uint8_t reg );

/*=====[Implementation of public functions]==================================*/

void as1116Init( as1116Config_t config ) {

   initialized = true;

   spiInit( AS1116_SPI );
   gpioConfig( AS1116_SSEL_PIN, GPIO_OUTPUT );
   gpioWrite( AS1116_SSEL_PIN, ON );

   as1116WriteReg( AS1116_REG_SHUTDOWN, AS1116_SHUTDOWN_NORMAL_MODE_RESET );
   as1116WriteReg( AS1116_REG_DECODE_MODE, config.decode_enable_mode );
   as1116WriteReg( AS1116_REG_GLOBAL_INTENSITY, config.global_intensity );
   as1116WriteReg( AS1116_REG_SCAN_LIMIT, config.scan_limit );
   as1116WriteReg( AS1116_REG_FEATURE, 0x00 | config.clock_source );

}

void as1116WriteDigit( as1116DigitMap_t digit, uint8_t data ){

   if( digit + AS1116_REG_DIGIT0 > AS1116_REG_DIGIT7 ){
      return;
   }

   as1116WriteReg( digit + AS1116_REG_DIGIT0, data );

}

as1116TestResult_t as1116Test( as1116TestType_t type ) {

   uint8_t cmd;
   uint8_t value;

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

   as1116WriteReg( AS1116_REG_DISPLAY_TEST_MODE, cmd );

   do {
      delay(1);
      value = as1116ReadReg( AS1116_REG_DISPLAY_TEST_MODE );

   } while( value & AS1116_TEST_LED_RUNNING );

   if( value & AS1116_TEST_LED_GLOBAL ) {
      return AS1116_TEST_FAILED;
   }

   return AS1116_TEST_OK;
}

/*=====[Implementation of private functions]=================================*/

void as1116WriteReg( uint8_t reg, uint8_t data ){

   if( !initialized ){
      return;
   }

   as1116Buffer[0] = BitReverseTable256[data];
   as1116Buffer[1] = BitReverseTable256[(reg & AS1116_REG_MASK)];

   gpioWrite( AS1116_SSEL_PIN, OFF );
   spiWrite( AS1116_SPI, as1116Buffer, 2 );
   gpioWrite( AS1116_SSEL_PIN, ON );
}

uint8_t as1116ReadReg( uint8_t reg ){

   if( !initialized ){
      return 0;
   }

   as1116Buffer[0] = BitReverseTable256[(reg & AS1116_REG_MASK) | AS1116_READ_BIT];
   as1116Buffer[1] = 0x00;

   gpioWrite( AS1116_SSEL_PIN, OFF );
   spiWrite( AS1116_SPI, as1116Buffer, 1 );
   gpioWrite( AS1116_SSEL_PIN, ON );
   spiRead( AS1116_SPI, as1116Buffer+1, 1 );

   return as1116Buffer[1];
}
