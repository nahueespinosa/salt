/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __SAFETY_H__
#define __SAFETY_H__

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Prototypes (declarations) of public functions]=======================*/

/**
 * @brief Inicializar el componente de se�ales de seguridad
 *
 * Inicializa los m�dulos de bajo nivel para el control de los rel�s.
 */
void safetyInit(void);

/**
 * @brief Habilitar el modo aislado limitado
 *
 * Acciona los rel�s correspondientes e informa al registrador de eventos.
 */
void safetyIsolatedModeEnable(void);

/**
 * @brief Deshabilitar el modo aislado limitado
 *
 * Acciona los rel�s correspondientes e informa al registrador de eventos.
 */
void safetyIsolatedModeDisable(void);

/**
 * @brief Activar la se�al de corte de tracci�n
 *
 * S�lo acciona el rel� correspondiente si puede verificar que el resto est�
 * en el estado adecuado.
 *
 * Informa al registrador de eventos en caso de �xito.
 */
void safetySignalActivateCT(void);

/**
 * @brief Desactivar la se�al de corte de tracci�n
 *
 * S�lo acciona el rel� correspondiente si puede verificar que el resto est�
 * en el estado adecuado.
 *
 * Informa al registrador de eventos en caso de �xito.
 */
void safetySignalDeactivateCT(void);

/**
 * @brief Activar la se�al de freno de emergencia
 *
 * S�lo acciona el rel� correspondiente si puede verificar que el resto est�
 * en el estado adecuado.
 *
 * Informa al registrador de eventos en caso de �xito.
 */
void safetySignalActivateFE(void);

/**
 * @brief Desactivar la se�al de freno de emergencia
 *
 * S�lo acciona el rel� correspondiente si puede verificar que el resto est�
 * en el estado adecuado.
 *
 * Informa al registrador de eventos en caso de �xito.
 */
void safetySignalDeactivateFE(void);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SAFETY_H__ */
