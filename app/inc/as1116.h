/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/09/14
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __AS1116_H__
#define __AS1116_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

// Posiciones de los segmentos en el registro de cada d�gito
#define AS1116_SEGMENT_G_POS  0
#define AS1116_SEGMENT_F_POS  1
#define AS1116_SEGMENT_E_POS  2
#define AS1116_SEGMENT_D_POS  3
#define AS1116_SEGMENT_C_POS  4
#define AS1116_SEGMENT_B_POS  5
#define AS1116_SEGMENT_A_POS  6
#define AS1116_SEGMENT_DP_POS 7

/*==================[typedef]================================================*/

//! Enumeraci�n de los tipos de decodificador disponibles
typedef enum {
   AS1116_DECODE_MODE_B   = 0,   /* Code: 0 1 2 3 4 5 6 7 8 9 - E H L P blank */
   AS1116_DECODE_MODE_HEX = 1    /* Code: 0 1 2 3 4 5 6 7 8 9 A B C D E F */
} as1116DecodeMode_t;

//! Enumeraci�n del estado del decodificador en cada d�gito
typedef enum {
   AS1116_DECODE_DISABLED = 0,   /* Decode mode disabled */
   AS1116_DECODE_ENABLED  = 1    /* Code-B/HEX decode mode enabled */
} as1116DecodeEnable_t;

//! Enumeraci�n de c�digos en modo Code-B
typedef enum {
   AS1116_DIGIT_CODE_0     = 0x00,
   AS1116_DIGIT_CODE_1     = 0x01,
   AS1116_DIGIT_CODE_2     = 0x02,
   AS1116_DIGIT_CODE_3     = 0x03,
   AS1116_DIGIT_CODE_4     = 0x04,
   AS1116_DIGIT_CODE_5     = 0x05,
   AS1116_DIGIT_CODE_6     = 0x06,
   AS1116_DIGIT_CODE_7     = 0x07,
   AS1116_DIGIT_CODE_8     = 0x08,
   AS1116_DIGIT_CODE_9     = 0x09,
   AS1116_DIGIT_CODE_DASH  = 0x0A,
   AS1116_DIGIT_CODE_E     = 0x0B,
   AS1116_DIGIT_CODE_H     = 0x0C,
   AS1116_DIGIT_CODE_L     = 0x0D,
   AS1116_DIGIT_CODE_P     = 0x0E,
   AS1116_DIGIT_CODE_BLANK = 0x0F,
   AS1116_DIGIT_CODE_DOT   = 0x80
} as1116DigitCode_t;

/**
 * @brief Enumeraci�n de los posibles niveles de intensidad
 *
 * La intensidad se puede controlar globalmente para todos los d�gitos
 * o individualmente para cada d�gito.
 * El modulador escala la corriente en 16 pasos desde un m�ximo de 15/16
 * a 1/16 de la corriente pico ajustada por RSET.
 */
typedef enum {
   AS1116_DUTY_1_16        = 0x00,
   AS1116_DUTY_2_16        = 0x01,
   AS1116_DUTY_3_16        = 0x02,
   AS1116_DUTY_4_16        = 0x03,
   AS1116_DUTY_5_16        = 0x04,
   AS1116_DUTY_6_16        = 0x05,
   AS1116_DUTY_7_16        = 0x06,
   AS1116_DUTY_8_16        = 0x07,
   AS1116_DUTY_9_16        = 0x08,
   AS1116_DUTY_10_16       = 0x09,
   AS1116_DUTY_11_16       = 0x0A,
   AS1116_DUTY_12_16       = 0x0B,
   AS1116_DUTY_13_16       = 0x0C,
   AS1116_DUTY_14_16       = 0x0D,
   AS1116_DUTY_15_16       = 0x0E,
   AS1116_MAX_INTENSITY    = 0x0F
} as1116Intensity_t;

/**
 * @brief Enumeraci�n de valores posibles para el l�mite de escaneo
 *
 * Controla la cantidad de d�gitos que se mostrar�n.
 * Cuando se muestran los 8 d�gitos, la frecuencia de actualizaci�n es
 * t�picamente de 0,8kHz. Si el n�mero de d�gitos se reduce, la frecuencia
 * de actualizaci�n aumenta, por lo tanto influye en el brillo.
 */
typedef enum {
   AS1116_LIMIT_1_DIGITS   = 0x0,
   AS1116_LIMIT_2_DIGITS   = 0x1,
   AS1116_LIMIT_3_DIGITS   = 0x2,
   AS1116_LIMIT_4_DIGITS   = 0x3,
   AS1116_LIMIT_5_DIGITS   = 0x4,
   AS1116_LIMIT_6_DIGITS   = 0x5,
   AS1116_LIMIT_7_DIGITS   = 0x6,
   AS1116_LIMIT_8_DIGITS   = 0x7
} as1116ScanLimit_t;

//! Enumeraci�n para posibles fuentes de clock
typedef enum {
   AS1116_INTERNAL_OSC  = 0,     /* Internal oscillator is used for system clock */
   AS1116_SERIAL_CLK    = 1      /* Pin CLK of the serial interface operates as system clock */
} as1116ClockSource_t;

/**
 * @brief Enumeraci�n de modos de prueba
 *
 * El integrado puede detectar leds en cortocircuito o en circuito abierto
 * seg�n el modo seleccionado.
 */
typedef enum {
   AS1116_TEST_SHORT  = 0,
   AS1116_TEST_OPEN   = 1
} as1116TestType_t;

//! Enumeraci�n de resultados del modo de prueba
typedef enum {
   AS1116_TEST_OK,
   AS1116_TEST_FAILED,
   AS1116_TEST_NO_RESPONSE
} as1116TestResult_t;

//! Enumeraci�n de identificadores para los d�gitos
typedef enum {
   AS1116_DIGIT0,
   AS1116_DIGIT1,
   AS1116_DIGIT2,
   AS1116_DIGIT3,
   AS1116_DIGIT4,
   AS1116_DIGIT5,
   AS1116_DIGIT6,
   AS1116_DIGIT7,
   AS1116_DIGITS_MAX
} as1116DigitMap_t;

//! Estructura de configuraci�n del m�dulo AS1116
typedef struct {
   as1116DecodeMode_t decodeMode;
   as1116Intensity_t globalIntensity;
   as1116ScanLimit_t scanLimit;
   as1116ClockSource_t clockSource;
} as1116Config_t;

//! Estructura de configuraci�n para un d�gito conectado al m�dulo AS1116
typedef struct {
   as1116DecodeEnable_t decodeEnable;
   as1116Intensity_t intensity;
   uint8_t usedMask;
} as1116DigitConfig_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

/**
 * @brief Inicializar driver para m�dulo AS1116
 *
 * Inicializa el m�dulo SPI correspondiente y carga la configuraci�n definida
 * en la estructura del tipo as1116Config_t.
 * Los par�metros que se pueden configurar son: el tipo de decodificador
 * utilizado (decodeMode), la intensidad global de los d�gitos (globalIntensity),
 * la cantidad de d�gitos utilizados (scanLimit) y la fuente de clock del chip (clockSource).
 *
 * @param[in]  config      Estructura de configuraci�n del m�dulo AS1116
 */
void as1116Init( as1116Config_t config );

/**
 * @brief Configurar uno de los d�gitos conectados
 *
 * Configura el d�gito con la estructura del tipo as1116DigitConfig_t.
 * Permite definir los par�metros configurables individuales de cada d�gito
 * como: la intensidad, la habilitaci�n del decodificador, y una m�scara para
 * definir los pines utilizados en el circuito.
 *
 * Si el m�dulo no est� inicializado, no ejecuta ninguna acci�n.
 *
 * @param[in]  digit       Identificador del d�gito
 * @param[in]  config      Estructura de configuraci�n para el d�gito
 */
void as1116DigitConfig( as1116DigitMap_t digit, as1116DigitConfig_t config );

/**
 * @brief Escribir un valor en uno de los d�gitos conectados
 *
 * Si el m�dulo no est� inicializado o el identificador representa un d�gito
 * no utilizado, no ejecuta ninguna acci�n.
 *
 * @param[in]  digit       Identificador del d�gito
 * @param[in]  data        Valor a escribir
 */
void as1116DigitWrite( as1116DigitMap_t digit, uint8_t data );

/**
 * @brief Ejecutar una prueba para diagnosticar el estado de los leds conectados
 *
 * Inicia un diagn�stico de los leds conectados al m�dulo, espera que termine y
 * devuelve el resultado de la prueba.
 *
 * Si se detecta una falla global, se leen los registros de diagn�stico de todos
 * los d�gitos utilizando la m�scara configurada para cada uno (usedMask) para
 * no reportar errores en leds no conectados.
 *
 * Si el m�dulo no est� inicializado, devuelve AS1116_TEST_FAILED.
 *
 * @param[in]  type                    Tipo de prueba a ejecutar (cortocircuito o circuito abierto)
 * @return     AS1116_TEST_FAILED      Se detect� por lo menos una falla en un d�gito
 * @return     AS1116_TEST_NO_RESPONSE No hubo respuesta despues de una cantidad definida de intentos
 * @return     AS1116_TEST_OK          No se detect� ninguna falla
 */
as1116TestResult_t as1116Test( as1116TestType_t type );

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif
