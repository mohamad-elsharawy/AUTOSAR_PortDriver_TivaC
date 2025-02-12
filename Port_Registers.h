/*
 * Port_Registers.h
 *
 *  Created on: Jan 12, 2025
 *      Author: mohamed elsharawy
 */

#ifndef PORT_REGISTERS_H_
#define PORT_REGISTERS_H_
/*
 * Module version 1.0.0
 */
#define PORT_REGISTERS_SW_MAJOR_VERSION (1U)
#define PORT_REGISTERS_DW_MINOR_VERSION (0U)
#define PORT_REGISTERS_SW_PATCH_VERSION (0U)
/*
 * AUTOSAR version 4.0.2
 */
#define PORT_REGISTERS_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_REGISTERS_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_REGISTERS_AR_RELEASE_PATCH_VERSION (2U)

#include"Std_Types.h"
#if((PORT_REGISTERS_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
|| (PORT_REGISTERS_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION))
#error "STD_TYPES version is not compatible "
#endif
/*
 * Port Registers Base Address
 */
#define PORT_A_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40004000)
#define PORT_B_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40005000)
#define PORT_C_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40006000)
#define PORT_D_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40007000)
#define PORT_E_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40024000)
#define PORT_F_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40025000)
/*
 * Offset of Port Registers
 */
#define GPIODIR_REG_OFFSET 0x400
#define GPIOAFSEL_REG_OFFSET 0x420
#define GPIOPUR_REG_OFFSET 0x510
#define GPIOPDR_REG_OFFSET 0x514
#define GPIODEN_REG_OFFSET 0x51C
#define GPIOLOCK_REG_OFFSET 0x520
#define GPIOCR_REG_OFFSET 0x524
#define GPIOAMSEL_REG_OFFSET 0x528
#define GPIOPCTL_REG_OFFSET 0x52C




#endif /* PORT_REGISTERS_H_ */
