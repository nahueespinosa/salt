/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __SWITCH_H__
#define __SWITCH_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include "rkhtype.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

//! Inicializar las entradas de la llave rotativa
void switchInit(void);

/**
 * @brief Leer el estado actual del pin de la llave rotativa
 *
 * @return      ON       Si el pin está en estado bajo (activado)
 * @return      OFF      Si el pin está en estado alto (desactivado)
 */
rbool_t switchRead(void);

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SWITCH_H__ */
