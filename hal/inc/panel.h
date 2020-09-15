/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/15
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __PANEL_H__
#define __PANEL_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[typedef]================================================*/

typedef enum {
   PANEL_LED_ON,
   PANEL_LED_AL,
   PANEL_LED_CT,
   PANEL_LED_FE,
   PANEL_LED_REMOTE,
   PANEL_LED_GPS,
   PANEL_LED_MAX
} ledMap_t;

typedef enum {
   PANEL_LED_OFF,
   PANEL_LED_RED,
   PANEL_LED_GREEN,
   PANEL_LED_BLUE
} ledColor_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void panelInit( void );
void panelLedWrite( ledMap_t led, ledColor_t color );
void panelDisplayOn( void );
void panelDisplayOff( void );
void panelDisplayWrite( float value );
void panelDisplayDashedLine( void );

bool_t panelTest( void );

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PANEL_H__ */
