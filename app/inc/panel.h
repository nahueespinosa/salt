/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/15
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __PANEL_H__
#define __PANEL_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdbool.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[typedef]================================================*/

//! Enumeraci�n de leds disponibles en el sistema
typedef enum {
   PANEL_LED_ON,
   PANEL_LED_AL,
   PANEL_LED_CT,
   PANEL_LED_FE,
   PANEL_LED_REMOTE,
   PANEL_LED_GPS,
   PANEL_LED_MAX
} ledMap_t;

//! Enumeraci�n de los estados/colores posibles de los leds
typedef enum {
   PANEL_LED_OFF,
   PANEL_LED_RED,
   PANEL_LED_GREEN,
   PANEL_LED_BLUE
} ledColor_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

/**
 * @brief Inicializar m�dulo del panel de leds
 *
 * Inicializa el hardware necesario para la operaci�n de los seis leds del
 * sistema y el display de cuatro d�gitos.
 */
void panelInit( void );

/**
 * @brief Escribir el estado del led seleccionado
 *
 * @param[in]  led      Indicador del led
 * @param[in]  color    Color deseado
 */
void panelLedWrite( ledMap_t led, ledColor_t color );

/**
 * @brief Habilitar el display de cuatro d�gitos
 *
 * Habilita el display pero no muestra ning�n valor hasta que no se llame
 * a la funci�n panelDisplayWrite.
 */
void panelDisplayOn( void );

/**
 * @brief Deshabilitar el display de cuatro d�gitos
 *
 * Apaga todos los segmentos e ignorar� todas los llamados a la funci�n
 * panelDisplayWrite.
 */
void panelDisplayOff( void );

/**
 * @brief Escribir el valor en el display de cuatro d�gitos
 *
 * Muestra el valor pasado como argumento en el display (debe ser menor a 1000).
 * El formato est� fijado a tres d�gitos enteros para las unidades, decenas y
 * centenas m�s un d�gito decimal despu�s del punto.
 *
 * Si el valor pasado como argumento excede el rango m�ximo, muestra "----"
 * en el display.
 */
void panelDisplayWrite( float value );

/**
 * @brief Escribir una l�nea punteada en el display de cuatro d�gitos
 *
 * Muestra "----" en el display.
 */
void panelDisplayDashedLine( void );

/**
 * @brief Realiza una prueba de funcionamiento en los leds y el display
 *
 * Realiza una prueba de cortocircuito seguida de una prueba de circuito
 * abierto en los leds conectados.
 *
 * @return TRUE   La prueba realizada tuvo �xito
 * @return FALSE  Se detect� una falla
 */
bool panelTest( void );

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __PANEL_H__ */
