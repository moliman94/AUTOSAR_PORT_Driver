 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Soliman
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Pin_ConfigType* Port_pin_config = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

    if (FALSE == error)
    {
        Port_pin_config = ConfigPtr->Pin_Config;
        uint8 pin_idx = 0;
        for (pin_idx = 0; pin_idx < PORT_CONFIGURED_PINS; pin_idx++)
        {
            switch (Port_pin_config[pin_idx].Port_Num)
            {
            case PORT_A:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                break;
            case PORT_B:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                break;
            case PORT_C:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                break;
            case PORT_D:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                break;
            case PORT_E:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                break;
            case PORT_F:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                break;
            default:
                break;
            }

            SYSCTL_REGCGC2_REG |= (1<<Port_pin_config[pin_idx].Port_Num);
            delay = SYSCTL_REGCGC2_REG;

            /*
             * For pins PD7 or PF0,
             * We should unlock GPIOCR register using lock register with the value 0x4C4F434B.
             * then, set the corresponding bit in GPIOCR register to allow changes on this pin.
             */
            if ( ((Port_pin_config[pin_idx].Port_Num == PORT_D) && (Port_pin_config[pin_idx].Pin_Num == PORT_D_PIN_7)) || ((Port_pin_config[pin_idx].Port_Num == PORT_F) && (Port_pin_config[pin_idx].Pin_Num == PORT_F_PIN_0)) )
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            }
            /*
             * For pins PC0 or PC3,
             * These are JTAG pins, we shouldn't use them to avoid problems in JTAG debugger.
             */
            else if ( (Port_pin_config[pin_idx].Port_Num == PORT_C) && (Port_pin_config[pin_idx].Pin_Num <= PORT_C_PIN_3))
            {
                /* Skip this pin and don't configure ...  this is the JTAG pins */
                /* 
                 * Violating Rule 57 in MISRA-C rules 
                 * Justification: if this condition is true, we should skip the rest of 
                 * configuration and move to the next pin.
                 */
                continue;
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            switch (Port_pin_config[pin_idx].Pin_Mode)
            {
            case DIO_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to Dio mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_DIO_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;
                
            case ADC_MODE:
                /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable the corresponding pin as a source ADC trigger */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ADC_CTL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case UART_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to UART mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_UART_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case SSI_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to SSI mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_SSI_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case I2C_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to I2C mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_I2C_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case CAN_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* 
                 * Set the PCMx bits for this pin to CAN mode 
                 * The PCMx value of CAN at (PA0,PA1) and (PB4,PB5) is different from the value at (PF0,PF3).
                 */
                if (Port_pin_config[pin_idx].Port_Num == PORT_A || Port_pin_config[pin_idx].Port_Num == PORT_B)
                {
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_CAN_SET_1 << (Port_pin_config[pin_idx].Pin_Num * 4));
                }
                else if (Port_pin_config[pin_idx].Port_Num == PORT_F)
                {
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_CAN_SET_2 << (Port_pin_config[pin_idx].Pin_Num * 4));
                }
                else
                {
                    /* Do Nothing */
                }
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case M0_PWM_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to M0PWM mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_PWM_M0_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case M1_PWM_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to M1PWM mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_PWM_M1_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case GPT_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to General Purpose Timer mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_GPT_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            case WIDE_GPT_MODE:
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the PCMx bits for this pin to Wide General Purpose Timer mode */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_WIDE_GPT_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
                break;

            default:
                break;
            }

            switch (Port_pin_config[pin_idx].Pin_Dir)
            {
            case PORT_PIN_IN:
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                if (PULL_UP == Port_pin_config[pin_idx].Pin_Res_Type)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if (PULL_DOWN == Port_pin_config[pin_idx].Pin_Res_Type)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
                break;

            case PORT_PIN_OUT:
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                if (STD_HIGH == Port_pin_config[pin_idx].Pin_Initial_Value)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);           /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);         /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
                break;

            default:
                break;
            }

        }
        Port_Status = PORT_INITIALIZED;
    }
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType pin_idx, Port_PinDirectionType Direction)
{
    volatile uint32 * PortDirPtr = NULL_PTR;
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Port driver is not initialized */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if Incorrect Port Pin ID has been passed*/
    if (pin_idx > PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if the Port Pin is not configured as changeable */
    if (STD_OFF == Port_pin_config[pin_idx].Pin_Dir_Change)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

    if (FALSE == error)
    {
        switch (Port_pin_config[pin_idx].Port_Num)
        {
        case PORT_A:
            PortDirPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case PORT_B:
            PortDirPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case PORT_C:
            PortDirPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case PORT_D:
            PortDirPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case PORT_E:
            PortDirPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case PORT_F:
            PortDirPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        
        default:
            break;
        }

        switch (Direction)
        {
        case PORT_PIN_IN:
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortDirPtr + PORT_DIR_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            break;

        case PORT_PIN_OUT:
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortDirPtr + PORT_DIR_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            break;

        default:
            break;
        }
    }

}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    volatile uint32 * PortDirPtr = NULL_PTR;
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Port driver is not initialized */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

    if (FALSE == error)
    {
        uint8 pin_idx = 0;
        for (pin_idx = 0; pin_idx < PORT_CONFIGURED_PINS; pin_idx++)
        {
            switch (Port_pin_config[pin_idx].Port_Num)
            {
            case PORT_A:
                PortDirPtr = &GPIO_PORTA_DIR_REG;
                break;
            case PORT_B:
                PortDirPtr = &GPIO_PORTB_DIR_REG;
                break;
            case PORT_C:
                PortDirPtr = &GPIO_PORTC_DIR_REG;
                break;
            case PORT_D:
                PortDirPtr = &GPIO_PORTD_DIR_REG;
                break;
            case PORT_E:
                PortDirPtr = &GPIO_PORTE_DIR_REG;
                break;
            case PORT_F:
                PortDirPtr = &GPIO_PORTF_DIR_REG;
                break;
            default:
                break;
            }

            /* Refresh the direction only the port pins that are not configured as changeable during runtime */
            if (Port_pin_config[pin_idx].Pin_Dir_Change == STD_OFF)
            {
                switch (Port_pin_config[pin_idx].Pin_Dir)
                {
                case PORT_PIN_IN:
                    CLEAR_BIT(*PortDirPtr , Port_pin_config[pin_idx].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    break;
        
                case PORT_PIN_OUT:
                    SET_BIT(*PortDirPtr , Port_pin_config[pin_idx].Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    break;
        
                default:
                    break;
                }
            }
        }
    }
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == versioninfo)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

    if (FALSE == error)
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType pin_idx, Port_PinModeType Mode)
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Port driver is not initialized */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if Incorrect Port Pin ID has been passed*/
    if (pin_idx > PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if Incorrect Port mode ID has been passed*/
    if (Mode > WIDE_GPT_MODE)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if the Port Pin is not configured as changeable */
    if (STD_OFF == Port_pin_config[pin_idx].Pin_Mode_Change)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

    if (FALSE == error)
    {
        switch (Port_pin_config[pin_idx].Port_Num)
        {
        case PORT_A:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case PORT_B:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case PORT_C:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case PORT_D:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case PORT_E:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case PORT_F:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        
        default:
            break;
        }

        switch (Mode)
        {
        case DIO_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to Dio mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_DIO_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;
            
        case ADC_MODE:
            /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable the corresponding pin as a source ADC trigger */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ADC_CTL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case UART_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to UART mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_UART_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case SSI_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to SSI mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_SSI_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case I2C_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to I2C mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_I2C_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case CAN_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* 
             * Set the PCMx bits for this pin to CAN mode 
             * The PCMx value of CAN at (PA0,PA1) and (PB4,PB5) is different from the value at (PF0,PF3).
             */
            if (Port_pin_config[pin_idx].Port_Num == PORT_A || Port_pin_config[pin_idx].Port_Num == PORT_B)
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_CAN_SET_1 << (Port_pin_config[pin_idx].Pin_Num * 4));
            }
            else if (Port_pin_config[pin_idx].Port_Num == PORT_F)
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_CAN_SET_2 << (Port_pin_config[pin_idx].Pin_Num * 4));
            }
            else
            {
                /* Do Nothing */
            }
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case M0_PWM_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to M0PWM mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_PWM_M0_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case M1_PWM_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to M1PWM mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_PWM_M1_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case GPT_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to General Purpose Timer mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_GPT_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        case WIDE_GPT_MODE:
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the PCMx bits for this pin to Wide General Purpose Timer mode */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_CONFIG_MODE_WIDE_GPT_PCTL_SET << (Port_pin_config[pin_idx].Pin_Num * 4));
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pin_config[pin_idx].Pin_Num);
            break;

        default:
            break;
        }
    }
}
#endif
