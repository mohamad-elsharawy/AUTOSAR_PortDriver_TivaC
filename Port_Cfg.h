/*
 * Port_Cfg.h
 *
 *  Created on: Jan 11, 2025
 *      Author: mohamed elsharawy
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/*
 * Module version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION (1U)
#define PORT_CFG_DW_MINOR_VERSION (0U)
#define PORT_CFG_SW_PATCH_VERSION (0U)
/*
 * AUTOSAR version 4.0.2
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION (2U)
/*
 * include std_CFGs.h and check its version
 */
#include"Std_Types.h"
#if((PORT_CFGS_AR_RELEASE_MAJOR_VERSION != STD_CFG_AR_RELEASE_MAJOR_VERSION)\
|| (PORT_CFGS_AR_RELEASE_MINOR_VERSION != STD_CFG_AR_RELEASE_MINOR_VERSION))
#error "STD_Types version is not compatible "
#endif

/*
 * Port General container sub containers and parameters
 */

/* pre compile option for dev error detect */
#define PORT_DEV_ERROR_DETECT (STD_ON)

/* pre compile option to enable or disable PortSetPinDirectionApi  */
#define PORT_SET_PIN_DIRECTION_API (STD_ON)
/* pre compile option to enable or disable PortSetPinModeApi */
#define PORT_SET_PIN_MODE_API (STD_ON)

/* pre compile option to enable or disable PortVersionInfoApi */
#define PORT_VERSION_INFO_API (STD_ON)

/* Tiva c number of pins*/
#define PORT_CONFIGURED_PINS_NUM (43U)

/*
 * Port ID Macros
 */
#define PORT_A_ID (0U)
#define PORT_B_ID (1U)
#define PORT_C_ID (2U)
#define PORT_D_ID (3U)
#define PORT_E_ID (4U)
#define PORT_F_ID (5U)
/*
 * Port Pins Macros
 */
#define PORT_PIN0 (0U)
#define PORT_PIN1 (1U)
#define PORT_PIN2 (2U)
#define PORT_PIN3 (3U)
#define PORT_PIN4 (4U)
#define PORT_PIN5 (5U)
#define PORT_PIN6 (6U)
#define PORT_PIN7 (7U)
/*
 *  Internal Resistance Macros
 */
#define INTERNAL_RESISTANCE_OFF (0U)
#define PULL_UP_RESISTANCE (1U)
#define PULL_DOWN_RESISTANCE (2U)

/*
 * changeable and unchangeable configuration Macros
 */

#define CFG_UNCHANGEABLE (0U)
#define CFG_CHANGEABLE (1U)
/*
 * pin mode Macros used in MCU registers
 */
#define PORT_PIN_ADC_MODE (0U)
#define PORT_PIN_ALT1 (1U)
#define PORT_PIN_ALT2 (2U)
#define PORT_PIN_ALT3 (3U)
#define PORT_PIN_ALT4 (4U)
#define PORT_PIN_ALT5 (5U)
#define PORT_PIN_ALT6 (6U)
#define PORT_PIN_ALT7 (7U)
#define PORT_PIN_ALT8 (8U)
#define PORT_PIN_ALT9 (9U)
#define PORT_PIN_ALT14 (14U)
#define PORT_PIN_GPIO_MODE (15U)

#endif /* PORT_CFG_H_ */
