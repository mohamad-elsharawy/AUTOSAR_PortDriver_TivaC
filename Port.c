/*
 * Port.c
 *
 *  Created on: Jan 13, 2025
 *      Author: mohamed elsharawy
 */

#include"Port.h"
#if (PORT_DEV_ERROR_DETECT ==STD_ON)
#include"Det.h"
#if((PORT_AR_RELEASE_MAJOR_VERSION!=DET_AR_MAJOR_VERSION)\
        || (PORT_AR_RELEASE_MINOR_VERSION!=DET_AR_MINOR_VERSION))
#error "DET version is not compatible with port driver"
#endif
#endif
/* including common macros header file and there is no checking since it not an AUTOSAR module */
#include"Common_Macros.h"
/* Global Variables */

/* variable that stores Port state */
uint8 Port_status=PORT_UNINITIALIZED;

/* global variable for pins configurations array */
const PortPin_ConfigType* PortPins_Config=NULL_PTR;

/****************************************************************************************
 *  Service name: Port_ApplyPinMode
 *  Service ID[hex]: 0x01
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): Port_BaseAddress (Pointer to the port base address)
 *                   Pin (The pin number to configure)
 *                   Mode (The mode to be applied to the pin)
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Configures the mode of a specific pin in the given port.
 *****************************************************************************************/

/* MISRA Deviation: Rule 1 (Use of Inline Function)
 * Justification: Used for performance optimization by reducing function call overhead.
 * This usage is safe as it does not alter program behavior and it is supported by compiler.
 */

static inline void Port_ApplyPinMode(
        volatile uint32* Port_BaseAddress,
        Port_PinType Pin,
        Port_PinModeType Mode
)
{
    /* check the required pin mode and configure alternate function,digital enable,analog mode select  and write the required pin mode in CTL register */
    if(PORT_PIN_GPIO_MODE==Mode)
    {
        /* MISRA Deviation: Rule 45 (Pointer Casting)
         * Justification: Required to add register base address and offset correctly.
         * The cast is safe as the address is casted back to original type after addition.
         */

        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
        CLEAR_PIN_GPIOPCTL_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET))),Pin);
        SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
    }
    else if(PORT_PIN_ADC_MODE==Mode)
    {
        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
        CLEAR_PIN_GPIOPCTL_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET))),Pin);
        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
        SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
    }
    else
    {
        SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
        CLEAR_PIN_GPIOPCTL_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET))),Pin);
        WRITE_PIN_GPIOPCTL_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET))),Pin,Mode);
        SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
    }
}

/****************************************************************************************
 *  Service name: Port_ApplyPinDirection
 *  Service ID[hex]: 0x02
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): Port_BaseAddress (Pointer to the port base address)
 *                   Pin (The pin number to configure)
 *                   Direction (The direction to be applied to the pin)
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Configures the direction of a specific pin in the given port.
 *****************************************************************************************/

/* MISRA Deviation: Rule 1 (Use of Inline Function)
 * Justification: Used for performance optimization by reducing function call overhead.
 * This usage is safe as it does not alter program behavior and it is supported by compiler.
 */

static inline Port_ApplyPinDirection(
        volatile uint32* Port_BaseAddress,
        Port_PinType Pin,
        Port_PinDirectionType Direction
)
{
    /* configuring pin direction */
    if (PORT_PIN_IN==Direction)
    {
        /* MISRA Deviation: Rule 45 (Pointer Casting)
         * Justification: Required to add register base address and offset correctly.
         * The cast is safe as the address is casted back to original type after addition.
         */

        CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress+GPIODIR_REG_OFFSET))),Pin);
    }
    else
    {
        SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress+GPIODIR_REG_OFFSET))),Pin);
    }
}

/****************************************************************************************
 *  Service name: Get_Port_BaseAddress
 *  Service ID[hex]: 0x03
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): Port_ID (The ID of the port whose base address is required)
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: Pointer to the base address of the requested port
 *  Description: Retrieves the base address of the specified port.
 *****************************************************************************************/

/* MISRA Deviation: Rule 1 (Use of Inline Function)
 * Justification: Used for performance optimization by reducing function call overhead.
 * This usage is safe as it does not alter program behavior and it is supported by compiler.
 */

static inline volatile uint32* Get_Port_BaseAddress(
        PortType Port_ID
)
{ /* function to get the base address of the required   port */
    volatile uint32 * Port_BaseAddress = NULL_PTR ;
    switch (Port_ID)
    {
    case PORT_A_ID: Port_BaseAddress = PORT_A_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_B_ID: Port_BaseAddress = PORT_B_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_C_ID: Port_BaseAddress = PORT_C_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_D_ID: Port_BaseAddress = PORT_D_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_E_ID: Port_BaseAddress = PORT_E_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_F_ID: Port_BaseAddress = PORT_F_REGISTERS_BASE_ADDRESS;
    }
    return Port_BaseAddress;
}
/***************************************************************************************
 Service name: Port_Init
Service ID[hex]: 0x00
Sync/Async: Synchronous
Reentrancy: Non Reentrant
Parameters (in): ConfigPtr (Pointer to configuration set)
Parameters (inout): None
Parameters (out): None
Return value: None
Description: Initializes the Port Driver module.
 *****************************************************************************************/
void Port_Init(
        const Port_ConfigType* ConfigPtr
)
{
    /* variable used in loops */
    uint8 counter;
    /* variable for the required port base address */
    volatile uint32* Port_BaseAddress;
#if (PORT_DEV_ERROR_DETECT==STD_ON)
    /* report error if configuration pointer equals NULL */
    if(NULL_PTR==ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_INIT_SID,PORT_E_PARAM_POINTER );
        return;
    }
    else
#endif
    {
        /* unlocking and committing port pins that are not committed except for JTAG pins */

        PORT_PIN_ENABLE_COMMIT(PORT_D_REGISTERS_BASE_ADDRESS,PORTD_LOCKED_PIN_NUM);
        PORT_PIN_ENABLE_COMMIT(PORT_F_REGISTERS_BASE_ADDRESS,PORTF_LOCKED_PIN_NUM);



        /*assigning the configuration array containing pins configurations to PortPins_Config variable  */
        PortPins_Config=ConfigPtr->PortPins_Configurations;
        /* loop over all pins in configuration pointer */
        for(counter=ZERO;counter<PORT_CONFIGURED_PINS_NUM;counter++)
        {
            /* avoid configuring JTAG pins */
            if((JTAG_CLOCK_PIN_ID == counter) || (JTAG_MODE_SELECT_PIN_ID == counter) || (JTAG_DATA_IN_PIN_ID == counter) || (JTAG_DATA_OUT_PIN_ID == counter))
            {

            }
            else
            {
                /* Port_BaseAddress equals the base address of the port of the required pin to configure */
                Port_BaseAddress=Get_Port_BaseAddress(PortPins_Config[counter].Port_ID);

                /* configuring pin direction */
                Port_ApplyPinDirection(Port_BaseAddress,PortPins_Config[counter].PortPin_Num,PortPins_Config[counter].Pin_Direction);


                /* check required pin mode and configure Digital,Analog and Alternate function enables and writing the required pin mode */
                Port_ApplyPinMode(Port_BaseAddress,PortPins_Config[counter].PortPin_Num,PortPins_Config[counter].PinMode);

                /* configuring the required internal resistance mode */
                if(INTERNAL_RESISTANCE_OFF == PortPins_Config[counter].InternalResistance)
                {
                    /* MISRA Deviation: Rule 45 (Pointer Casting)
                     * Justification: Required to add register base address and offset correctly.
                     * The cast is safe as the address is casted back to original type after addition.
                     */

                    CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPUR_REG_OFFSET))),PortPins_Config[counter].PortPin_Num);
                    CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPDR_REG_OFFSET))),PortPins_Config[counter].PortPin_Num);
                }
                else if(PULL_UP_RESISTANCE == PortPins_Config[counter].InternalResistance)
                {
                    SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPUR_REG_OFFSET))),PortPins_Config[counter].PortPin_Num);
                }
                else
                {
                    SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPDR_REG_OFFSET))),PortPins_Config[counter].PortPin_Num);
                }


            }
        }
        /*  disable commit for critical pins */

        PORT_PIN_DISABLE_COMMIT(PORT_D_REGISTERS_BASE_ADDRESS,PORTD_LOCKED_PIN_NUM);
        PORT_PIN_DISABLE_COMMIT(PORT_F_REGISTERS_BASE_ADDRESS,PORTF_LOCKED_PIN_NUM);

        /* setting port status as initialized */

        Port_status=PORT_INITIALIZED;
    }
}

/**********************************************************************************************
Service name:Port_SetPinDirection
Service ID[hex]: 0x01
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Pin (Port Pin ID number),Direction(Port Pin Direction)
Parameters(inout): None
Parameters (out): None
Return value: None
Description: Sets the port pin direction
 ********************************************************************************************/

#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(
        Port_PinType Pin,
        Port_PinDirectionType Direction
)
{
    /* variable for the required port base address */
    volatile uint32* Port_BaseAddress;
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* check if Port was initialized */
    if(PORT_UNINITIALIZED == Port_status)
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
        return;
    }
    else
    {
        /* no action required */
    }

    /* check if Pin index is correct and is not a JTAG pin */
    if((JTAG_CLOCK_PIN_ID == Pin) || (JTAG_MODE_SELECT_PIN_ID == Pin) || (JTAG_DATA_IN_PIN_ID == Pin) || (JTAG_DATA_OUT_PIN_ID == Pin)\
            || (PORT_CONFIGURED_PINS_NUM >= Pin))
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
        return;
    }
    else
    {
        /* no action required */
    }

    /* check if Port Pin direction is changeable */
    if(CFG_UNCHANGEABLE == PortPins_Config->PortPinDirectionChangeable)
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_DIRECTION_SID,PORT_E_DIRECTION_UNCHANGEABLE);
        return;
    }
    else
    {
        /* no action required */
    }
#endif

    Port_BaseAddress=Get_Port_BaseAddress(PortPins_Config[Pin].Port_ID);

    /* check if pin is locked */
    if( (PORTD_LOCKED_PIN_ID == Pin) || (PORTF_LOCKED_PIN_ID == Pin))
    {
        /* unlock and commit the required pin */
        PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,PortPins_Config->PortPin_Num);
    }
    else
    {
        /* no action required */
    }
    /* configure pin direction */
    Port_ApplyPinDirection(Port_BaseAddress,PortPins_Config[Pin].PortPin_Num,PortPins_Config[Pin].Pin_Direction);
    /* check if pin is locked */
    if( (PORTD_LOCKED_PIN_ID == Pin) || (PORTF_LOCKED_PIN_ID == Pin))
    {
        /* unlock and and disable commit from pin */
        PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,PortPins_Config->PortPin_Num);
    }
    else
    {
        /* no action required */
    }

}
#endif

/**********************************************************************************************
Service name:Port_RefreshPortDirection
Service ID[hex]: 0x02
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): None
Parameters(inout): None
Parameters (out): None
Return value: None
Description: Refreshes port direction
 ********************************************************************************************/

void Port_RefreshPortDirection(
        void
)
{

    /* variable used in loops */
    uint8 counter;
    /* variable for the required port base address */
    volatile uint32* Port_BaseAddress;

#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* check if Port was initialized */
    if(PORT_UNINITIALIZED == Port_status)
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
        return;
    }
    else
    {
        /* no action required */
    }
#endif

    /* unlocking and committing port pins that are not committed except for JTAG pins */

    PORT_PIN_ENABLE_COMMIT(PORT_D_REGISTERS_BASE_ADDRESS,PORTD_LOCKED_PIN_NUM);
    PORT_PIN_ENABLE_COMMIT(PORT_F_REGISTERS_BASE_ADDRESS,PORTF_LOCKED_PIN_NUM);

    /* loop over all pins in configuration pointer */
    for(counter=ZERO;counter<PORT_CONFIGURED_PINS_NUM;counter++)
    {
        /* avoid refreshing JTAG pins or changeable pin directions*/
        if((JTAG_CLOCK_PIN_ID == counter) || (JTAG_MODE_SELECT_PIN_ID == counter) || (JTAG_DATA_IN_PIN_ID == counter) || (JTAG_DATA_OUT_PIN_ID == counter)\
                || (CFG_CHANGEABLE == PortPins_Config[counter].PortPinDirectionChangeable))
        {
            /* no action */
        }
        else
        {
            /* Port_BaseAddress equals the base address of the port of the required pin to configure */

            Port_BaseAddress=Get_Port_BaseAddress(PortPins_Config[counter].Port_ID);

            /* configuring pin direction */
            Port_ApplyPinDirection(Port_BaseAddress,PortPins_Config[counter].PortPin_Num,PortPins_Config[counter].Pin_Direction);

            /*  disable commit and unlock commit for the unlocked pins */

            PORT_PIN_DISABLE_COMMIT(PORT_D_REGISTERS_BASE_ADDRESS,PORTD_LOCKED_PIN_NUM);
            PORT_PIN_DISABLE_COMMIT(PORT_F_REGISTERS_BASE_ADDRESS,PORTF_LOCKED_PIN_NUM);


        }
    }
}

/**********************************************************************************************
Service name:Port_GetVersionInfo
Service ID[hex]: 0x03
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): None
Parameters(inout): None
Parameters (out): versioninfo (Pointer to where to store the version information of this module.)
Return value: None
Description: Returns the version information of this module.
 ********************************************************************************************/

#if(PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(
        Std_VersionInfoType* versioninfo
)
{
    /* check if development errors are on */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input pointer is not NULL pointer */
    if(NULL_PTR == versioninfo)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
        return;
    }
    else
    {
        /* no action required */
    }
#endif
    versioninfo->moduleID=PORT_MODULE_ID;
    versioninfo->sw_major_version=PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version=PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version=PORT_SW_PATCH_VERSION;
    versioninfo->vendorID=PORT_VENDOR_ID;
}
#endif


/**********************************************************************************************
Service name:Port_RefreshPortDirection
Service ID[hex]: 0x04
Sync/Async: Synchronous
Reentrancy: Reentrant
Parameters (in): Pin (Port Pin ID number),Direction(Port Pin Direction)
Parameters(inout): None
Parameters (out): None
Return value: None
Description: Sets the port pin mode
 ********************************************************************************************/

#if(PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(
        Port_PinType Pin,
        Port_PinModeType Mode
)
{
    /* variable for the required port base address */
    volatile uint32* Port_BaseAddress;
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* check if Port was initialized */
    if(PORT_UNINITIALIZED == Port_status)
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_MODE_SID,PORT_E_UNINIT);
        return;
    }
    else
    {
        /* no action required */
    }

    /* check if Pin index is correct and is not a JTAG pin */
    if((JTAG_CLOCK_PIN_ID == Pin) || (JTAG_MODE_SELECT_PIN_ID == Pin) || (JTAG_DATA_IN_PIN_ID == Pin) || (JTAG_DATA_OUT_PIN_ID == Pin)\
            || (PORT_CONFIGURED_PINS_NUM >= Pin))
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_MODE_SID,PORT_E_PARAM_PIN);
        return;
    }
    else
    {
        /* no action required */
    }

    /* check if Port Pin direction is changeable */
    if(CFG_UNCHANGEABLE == PortPins_Config->PortPinDirectionChangeable)
    {
        /* report error to DET */
        Det_ReportError(PORT_MODULE_ID,PORT_MODULE_INSTANCE,PORT_SET_PIN_MODE_SID,PORT_E_DIRECTION_UNCHANGEABLE);
        return;
    }
    else
    {
        /* no action required */
    }
#endif
    /* Port_BaseAddress equals the base address of the port of the required pin to configure */
    Port_BaseAddress=Get_Port_BaseAddress(PortPins_Config[Pin].Port_ID);

    /* check if pin is locked */
    if( (PORTD_LOCKED_PIN_ID == Pin) || (PORTF_LOCKED_PIN_ID == Pin))
    {
        /* unlock and commit the required pin */
        PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,PortPins_Config->PortPin_Num);
    }
    else
    {
        /* no action required */
    }

    /* check required pin mode and configure Digital,Analog and Alternate function enables and writing the required pin mode */
    Port_ApplyPinMode(Port_BaseAddress,PortPins_Config[Pin].PortPin_Num,PortPins_Config[Pin].PinMode);
    /* check if pin is locked */
    if( (PORTD_LOCKED_PIN_ID == Pin) || (PORTF_LOCKED_PIN_ID == Pin))
    {
        /* unlock and and disable commit from pin */
        PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,PortPins_Config->PortPin_Num);
    }
    else
    {
        /* no action required */
    }


}
#endif
