/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "switch.h"

/*=====[Definition macros of private constants]==============================*/

//! GPIO de entrada de la llave rotativa
#define SWITCH_GPIO           GPIO8

/*=====[Definitions of private global variables]=============================*/

/*=====[Implementation of public functions]==================================*/

void switchInit(void) {
   gpioConfig(SWITCH_GPIO, GPIO_INPUT_PULLUP);
}

rbool_t switchRead(void) {
   return !gpioRead(SWITCH_GPIO);
}
