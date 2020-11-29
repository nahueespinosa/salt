/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "relay.h"
#include "switch.h"

/*=====[Definition macros of private constants]==============================*/

//! Umbral de detecci�n para inconsistencias en los rel�s
#define RELAY_ERROR_THR    10

/*=====[Definition macros of private constants]==============================*/

//! Estructura para almacenar los GPIO correspondientes a cada pin y su estado
typedef struct {
   gpioMap_t controlPin;
   gpioMap_t statePin;
   uint32_t  errorCount;
} relayConfig_t;

/*=====[Definitions of private global variables]=============================*/

//! Vector que almacena configuraci�n y el estado de cada rel�
static relayConfig_t relayConfig[RELAY_NUM] = {
// {controlPin, statusPin, errorCount}
   {GPIO1     , GPIO7    , 0},    // RELAY_CT_1
   {LCD1      , GPIO5    , 0},    // RELAY_CT_2
   {LCD2      , GPIO3    , 0},    // RELAY_CT_3
   {ENET_TXD1 , LCD3     , 0},    // RELAY_FE_1
   {ENET_TXD0 , LCDRS    , 0},    // RELAY_FE_2
   {ENET_MDIO , LCD4     , 0},    // RELAY_FE_3
   {T_COL1    , DI7      , 0},    // RELAY_REG_1
   {T_FIL3    , T_FIL0   , 0},    // RELAY_REG_2
   {T_COL0    , T_FIL2   , 0},    // RELAY_REG_3
   {T_COL2    , T_FIL1   , 0},    // RELAY_REG_4
};

/*=====[Prototypes (declarations) of private functions]======================*/

/**
 * @brief Leer el valor del pin de control del rel�
 *
 * @param[in]   relay    Identificador del rel�
 * @return      ON       El pin est� en un estado l�gico alto
 * @return      OFF      El pin est� en un estado l�gico bajo
 */
static bool relayControlRead(relay_t relay);

/*=====[Implementation of public functions]==================================*/

void relayInit(void) {
   int i;

   for( i = 0 ; i < RELAY_NUM ; i++ ) {
      gpioWrite(relayConfig[i].controlPin, OFF);
      gpioConfig(relayConfig[i].controlPin, GPIO_OUTPUT);
      gpioConfig(relayConfig[i].statePin, GPIO_INPUT_PULLUP);
      relayConfig[i].errorCount = 0;
   }
}

void relayWrite(relay_t relay, bool value) {
   gpioWrite(relayConfig[relay].controlPin, value);
}

bool relayRead(relay_t relay) {
   return !gpioRead(relayConfig[relay].statePin);
}

bool relayCheck(relay_t relay) {
   bool retValue = true;

   if( relayConfig[relay].errorCount >= RELAY_ERROR_THR ) {
      retValue = false;
   }

   return retValue;
}

bool relayCheckAll(void) {
   bool retValue = true;
   int i;

   for( i = 0 ; i < RELAY_NUM ; i++ ) {
      if( relayCheck(i) == false ) {
         retValue = false;
      }
   }

   return retValue;
}

void relayUpdate(void) {
   int i;

   for( i = 0 ; i < RELAY_NUM ; i++ ) {
      switch(i) {
      case RELAY_CT_1:
      case RELAY_CT_2:
      case RELAY_FE_1:
      case RELAY_FE_2:
         /* Solo se pueden detectar inconsistencias si la llave est� habilitada,
          * porque de lo contrario estos rel�s se desactivan por hardware. */
         if( relayControlRead(i) != relayRead(i) && switchRead() == ON ) {
            relayConfig[i].errorCount++;
         } else {
            relayConfig[i].errorCount = 0;
         }
         break;
      default:
         if( relayControlRead(i) != relayRead(i) ) {
            relayConfig[i].errorCount++;
         } else {
            relayConfig[i].errorCount = 0;
         }
         break;
      }

      /* Si se supera el RELAY_ERROR_THR se deja al l�mite para que no
       * desborde la variable. */
      if( relayConfig[i].errorCount > RELAY_ERROR_THR ) {
         relayConfig[i].errorCount = RELAY_ERROR_THR;
      }
   }
}

/*=====[Implementation of private functions]=================================*/

static bool relayControlRead(relay_t relay) {
   return gpioRead(relayConfig[relay].controlPin);
}
