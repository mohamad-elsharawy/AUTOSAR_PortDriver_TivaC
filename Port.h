/*
 * PortDriver.h
 *
 *  Created on: Jan 9, 2025
 *      Author: mohamed elsharawy
 */

#ifndef PORT_H_
#define PORT_H_

#define PORT_VENDOR_ID (1000U)
#define PORT_MODULE_ID (124U)
#define PORT_MODULE_INSTANCE (0U)

/*
 * Module version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION (1U)
#define PORT_SW_MINOR_VERSION (0U)
#define PORT_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR version 4.0.2
 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_AR_RELEASE_PATCH_VERSION (2U)
/*
 * include port types
 */
#include"Port_Types.h"
/*
 * Check Port Types SW version
 */
#if((PORT_SW_MAJOR_VERSION!=PORT_TYPES_SW_MAJOR_VERSION)\
||(PORT_SW_MINOR_VERSION!=PORT_TYPES_SW_MINOR_VERSION)\
||(PORT_SW_PATCH_VERSION!=PORT_TYPES_SW_PATCH_VERSION))
#error "Port Types Software version is not compatible"
#endif
/*
 * Check port types AUTOSAR version
 */
#if((PORT_AR_RELEASE_MAJOR_VERSION!=PORT_TYPES_AR_RELEASE_MAJOR_VERSION)\
||(PORT_AR_RELEASE_MINOR_VERSION!=PORT_AR_TYPES_RELEASE_MINOR_VERSION)\
||(PORT_AR_RELEASE_PATCH_VERSION!=PORT_TYPES_AR_RELEASE_PATCH_VERSION))
#error "Port Types AUTOSAR version is not compatible"
#endif
/*
 * Include Port Registers
 */
#include"Port_Registers.h"
/*
 * Check Port Registers SW version
 */
#if((PORT_SW_MAJOR_VERSION!=PORT_REGISTERS_SW_MAJOR_VERSION)\
||(PORT_SW_MINOR_VERSION!=PORT_REGISTERS_SW_MINOR_VERSION)\
||(PORT_SW_PATCH_VERSION!=PORT_REGISTERS_SW_PATCH_VERSION))
#error "Port Registers Software version is not compatible"
#endif
/*
 * Check port Registers AUTOSAR version
 */
#if((PORT_AR_RELEASE_MAJOR_VERSION!=PORT_REGISTERS_AR_RELEASE_MAJOR_VERSION)\
||(PORT_AR_RELEASE_MINOR_VERSION!=PORT_AR_REGISTERS_RELEASE_MINOR_VERSION)\
||(PORT_AR_RELEASE_PATCH_VERSION!=PORT_REGISTERS_AR_RELEASE_PATCH_VERSION))
#error "Port Registers AUTOSAR version is not compatible"
#endif

/*
 * Include Port Configuration header file
 */
#include"Port_Cfg.h"
/*
 * Check Port Configuration SW version
 */
#if((PORT_SW_MAJOR_VERSION!=PORT_CFG_SW_MAJOR_VERSION)\
||(PORT_SW_MINOR_VERSION!=PORT_CFG_SW_MINOR_VERSION)\
||(PORT_SW_PATCH_VERSION!=PORT_CFG_SW_PATCH_VERSION))
#error "Port Configuration Software version is not compatible"
#endif
/*
 * Check Port Configuration AUTOSAR version
 */
#if((PORT_AR_RELEASE_MAJOR_VERSION!=PORT_CFG_AR_RELEASE_MAJOR_VERSION)\
||(PORT_AR_RELEASE_MINOR_VERSION!=PORT_AR_CFG_RELEASE_MINOR_VERSION)\
||(PORT_AR_RELEASE_PATCH_VERSION!=PORT_CFG_AR_RELEASE_PATCH_VERSION))
#error "Port Configuration AUTOSAR version is not compatible"
#endif


/*
 * API services ID Macros
 */
#define PORT_INIT_SID (uint8)0x00
#define PORT_SET_PIN_DIRECTION_SID (uint8)0x01
#define PORT_REFRESH_PORT_DIRECTION_SID (uint8)0x02
#define PORT_GET_VERSION_INFO_SID (uint8)0x03
#define PORT_SET_PIN_MODE_SID (uint8)0x04

/*
 * DET Error codes
 */
#define PORT_E_PARAM_PIN (uint8)0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE (uint8)0x0B
#define PORT_E_PARAM_CONFIG (uint8)0x0C
#define PORT_E_PARAM_INVALID_MODE (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE (uint8)0x0E
#define PORT_E_UNINIT (uint8)0x0F
#define PORT_E_PARAM_POINTER (uint8)0x10

/*
 *Preprocessor Macros
 */
#define PORT_UNINITIALIZED (0U)
#define PORT_INITIALIZED (1U)
#define ZERO (0U)
#define JTAG_CLOCK_PIN_ID (16U)
#define JTAG_MODE_SELECT_PIN_ID (17U)
#define JTAG_DATA_IN_PIN_ID (18U)
#define JTAG_DATA_OUT_PIN_ID (19U)
#define PORTD_LOCKED_PIN_ID (31U)
#define PORTF_LOCKED_PIN_ID (38U)
#define PORTD_LOCKED_PIN_NUM (7U)
#define PORTF_LOCKED_PIN_NUM (0U)
#define GPIO_UNLOCK_VALUE  ((uint32)0x4C4F434B)
#define BITS_ALL_SET_8 (0xFFU)
#define BITS_ALL_SET_32 (0xFFFFFFFFU)
#define BITS_ALL_CLEAR_32 (0x00000000U)

/****************************************************************
 * Function like Macros
 ***************************************************/
/* function like macro to clear the 4 bits of the specific pin in CTL register */
#define CLEAR_PIN_GPIOPCTL_BITS(REG,PIN_NUM) (REG &= ~(0x0000000F<<(PIN_NUM * 4)))

/* function like macro to write a value to the 4 bits of the specific pin in CTL register bits should be cleared before writing */
#define WRITE_PIN_GPIOPCTL_BITS(REG,PIN_NUM,VALUE) (REG |= ((VALUE<<(PIN_NUM * 4))) & (0x0000000F<<(PIN_NUM * 4)))

/* function like macro to unlock and enable commit of pin */
#define PORT_PIN_ENABLE_COMMIT(PORT_BASE_ADDRESS,PIN) {\
        *((volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOLOCK_REG_OFFSET)) = GPIO_UNLOCK_VALUE;\
        (*(volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOCR_REG_OFFSET)) |= (1 << PIN);\
}

/* function like macro to unlock and disable commit of pin */
#define PORT_PIN_DISABLE_COMMIT(PORT_BASE_ADDRESS,PIN) {\
        *((volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOLOCK_REG_OFFSET)) = GPIO_UNLOCK_VALUE;\
        (*(volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOCR_REG_OFFSET)) &= ~(1 << PIN);\
}
/*
 * API Services Prototypes
 */

/*  Function for initializing all Ports */
void Port_Init(
    const Port_ConfigType* ConfigPtr
);

/* Function for setting Pin direction at run time */
void Port_SetPinDirection(
    Port_PinType Pin,
    Port_PinDirectionType Direction
);
/* function to refresh unchangeable pins port direction */
void Port_RefreshPortDirection(
    void
);

/* Function that returns  the version information of this module */
void Port_GetVersionInfo(
    Std_VersionInfoType* versioninfo
);

/* Function to set Pin mode at run time */
void Port_SetPinMode(
    Port_PinType Pin,
    Port_PinModeType Mode
);

/*****************************************************************************************
 * External variables
 *******************************************************************************************/
extern const Port_ConfigType Port_Configurations;

#endif /* PORT_H_ */
