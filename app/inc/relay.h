/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __RELAY_H__
#define __RELAY_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdbool.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

#define RELAY_ON	true
#define RELAY_OFF	false

//! Intervalo de actualizaci�n del estado de los rel�s en milisegundos
#define RELAY_UPDATE_TIME  20

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

//! Enumeraci�n de rel�s disponibles
typedef enum {
   RELAY_CT_1,
   RELAY_CT_2,
   RELAY_CT_3,
   RELAY_FE_1,
   RELAY_FE_2,
   RELAY_FE_3,
   RELAY_REG_1,
   RELAY_REG_2,
   RELAY_REG_3,
   RELAY_REG_4,
   RELAY_NUM,
} relay_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

//! Inicializar las entradas/salidas y el estado de los rel�s
void relayInit(void);

/**
 * @brief Escribir el valor del pin de control del rel�
 *
 * @param[in]   relay    Identificador del rel�
 * @param[in]   value    Valor l�gico alto o bajo (ON, OFF)
 */
void relayWrite(relay_t relay, bool value);

/**
 * @brief Leer el valor del pin de estado del rel�
 *
 * @param[in]   relay    Identificador del rel�
 * @return      ON       El pin est� en un estado l�gico bajo (rel� activado)
 * @return      OFF      El pin est� en un estado l�gico alto (rel� desactivado)
 */
bool relayRead(relay_t relay);

/**
 * @brief Revisar estado del rel�
 *
 * Si se detect� una determinada cantidad de inconsistencias (RELAY_ERROR_THR)
 * se considera que hay una falla en el rel�.
 *
 * @return      FALSE    Si el rel� presenta una falla
 * @return      TRUE     Si el rel� est� funcionando con normalidad
 */
bool relayCheck(relay_t relay);

/**
 * @brief Revisar estado de todos los rel�s
 *
 * @return      FALSE    Si alg�n rel� presenta una falla
 * @return      TRUE     Si todos los rel�s est�n funcionando con normalidad
 */
bool relayCheckAll(void);

/**
 * @brief Actualizar el estado de la llave rotativa
 *
 * Por cada rel�, compara el pin de control con el pin de estado del mismo.
 * Si se detecta una inconsistencia se incrementa un contador interno de
 * errores.
 *
 * Hay algunos rel�s que est�n acoplados el�ctricamente a la llave rotativa,
 * en ese caso puede ocurrir que la llave est� deshabilitada y eso provoque
 * que el rel� se desactive independientemente del valor del pin de control.
 * En ese caso se ignoran esos errores.
 */
void relayUpdate(void);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __RELAY_H__ */
