/*
 * PortDriver_Types.h
 *
 *  Created on: Jan 1, 2025
 *      Author: mohamed elsharawy
 */

#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_
/*
 * Module version 1.0.0
 */
#define PORT_TYPES_SW_MAJOR_VERSION (1U)
#define PORT_TYPES_DW_MINOR_VERSION (0U)
#define PORT_TYPES_SW_PATCH_VERSION (0U)
/*
 * AUTOSAR version 4.0.2
 */
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_TYPES_AR_RELEASE_PATCH_VERSION (2U)

#include"Std_Types.h"
#if((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
|| (PORT_TYPES_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION))
#error "STD_TYPES version is not compatible "
#endif

#include"Port_Cfg.h"
#if((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION)\
|| (PORT_TYPES_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION))
#error "port CFG version used in port types is not compatible"
#endif

/*
 * Type for pin number and pin ID
 */
typedef uint8 Port_PinType;

/*
 * Type for pin mode
 */
typedef uint8 Port_PinModeType;
/*
 * Type for port ID
 */
typedef uint8 PortType;
/*
 * Type for pin direction
 */
typedef enum
{
PORT_PIN_IN,
PORT_PIN_OUT
}Port_PinDirectionType;

/*
 * structure containing Port Pin data (ex: pin number and Port ID) and configurable parameters
 */
typedef struct
{
Port_PinDirectionType Pin_Direction;
Port_PinType PortPin_Num;
PortType Port_ID;
Port_PinModeType PinMode;
uint8 InternalResistance;
uint8 PortPinDirectionChangeable;
uint8 PortPinModeChangeable;
}PortPin_ConfigType;

typedef struct
{
PortPin_ConfigType PortPins_Configurations[PORT_CONFIGURED_PINS_NUM];
}Port_ConfigType;
#endif /* PORT_TYPES_H_ */
