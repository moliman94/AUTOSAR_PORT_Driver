 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Soliman
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for number of specified port pins */
#define PORT_CONFIGURED_PINS                 (43U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Port_SetPinDirection function */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for Port_SetPinMode function */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Pre-compile option for Port_GetVersionInfo function */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Port IDs */
#define PORT_A                              (Port_IDType)0
#define PORT_B                              (Port_IDType)1
#define PORT_C                              (Port_IDType)2
#define PORT_D                              (Port_IDType)3
#define PORT_E                              (Port_IDType)4
#define PORT_F                              (Port_IDType)5

/* Configure Pin IDs */
#define PORT_A_PIN_0                        (Port_PinType)0
#define PORT_A_PIN_1                        (Port_PinType)1
#define PORT_A_PIN_2                        (Port_PinType)2
#define PORT_A_PIN_3                        (Port_PinType)3
#define PORT_A_PIN_4                        (Port_PinType)4
#define PORT_A_PIN_5                        (Port_PinType)5
#define PORT_A_PIN_6                        (Port_PinType)6
#define PORT_A_PIN_7                        (Port_PinType)7

#define PORT_B_PIN_0                        (Port_PinType)0
#define PORT_B_PIN_1                        (Port_PinType)1
#define PORT_B_PIN_2                        (Port_PinType)2
#define PORT_B_PIN_3                        (Port_PinType)3
#define PORT_B_PIN_4                        (Port_PinType)4
#define PORT_B_PIN_5                        (Port_PinType)5
#define PORT_B_PIN_6                        (Port_PinType)6
#define PORT_B_PIN_7                        (Port_PinType)7

#define PORT_C_PIN_0                        (Port_PinType)0
#define PORT_C_PIN_1                        (Port_PinType)1
#define PORT_C_PIN_2                        (Port_PinType)2
#define PORT_C_PIN_3                        (Port_PinType)3
#define PORT_C_PIN_4                        (Port_PinType)4
#define PORT_C_PIN_5                        (Port_PinType)5
#define PORT_C_PIN_6                        (Port_PinType)6
#define PORT_C_PIN_7                        (Port_PinType)7

#define PORT_D_PIN_0                        (Port_PinType)0
#define PORT_D_PIN_1                        (Port_PinType)1
#define PORT_D_PIN_2                        (Port_PinType)2
#define PORT_D_PIN_3                        (Port_PinType)3
#define PORT_D_PIN_4                        (Port_PinType)4
#define PORT_D_PIN_5                        (Port_PinType)5
#define PORT_D_PIN_6                        (Port_PinType)6
#define PORT_D_PIN_7                        (Port_PinType)7

#define PORT_E_PIN_0                        (Port_PinType)0
#define PORT_E_PIN_1                        (Port_PinType)1
#define PORT_E_PIN_2                        (Port_PinType)2
#define PORT_E_PIN_3                        (Port_PinType)3
#define PORT_E_PIN_4                        (Port_PinType)4
#define PORT_E_PIN_5                        (Port_PinType)5

#define PORT_F_PIN_0                        (Port_PinType)0
#define PORT_F_PIN_1                        (Port_PinType)1
#define PORT_F_PIN_2                        (Port_PinType)2
#define PORT_F_PIN_3                        (Port_PinType)3
#define PORT_F_PIN_4                        (Port_PinType)4

/* Configured Modes IDs */
#define DIO_MODE                                 (Port_PinModeType)0
#define ADC_0_MODE                               (Port_PinModeType)1
#define ADC_1_MODE                               (Port_PinModeType)2
#define PWM_0_MODE                               (Port_PinModeType)3
#define PWM_1_MODE                               (Port_PinModeType)4

/* Dio mode set value in PCTL register */
#define PORT_PIN_CONFIG_MODE_DIO_SET                (0x0)
/* ADC 0 mode set value in RCGCADC register */
#define PORT_PIN_CONFIG_MODE_ADC_0_SET              (0x1)
/* ADC 1 mode set value in RCGCADC register */
#define PORT_PIN_CONFIG_MODE_ADC_1_SET              (0x2)
/* PWM 0 mode set value in RCGCPWM register */
#define PORT_PIN_CONFIG_MODE_PWM_0_SET              (0x1)
/* PWM 1 mode set value in RCGCPWM register */
#define PORT_PIN_CONFIG_MODE_PWM_1_SET              (0x2)
/* PWM mode set value in PCTL register */
#define PORT_PIN_CONFIG_MODE_PWM_PCTL_SET         (0x5)


/* Default pin configuratons */
#define DEFAULT_PIN_MODE                    DIO_MODE
#define DEFAULT_PIN_DIR                     (Port_PinDirectionType)PORT_PIN_IN
#define DEFAULT_PIN_RES_TYPE                (Port_InternalResistorType)OFF
#define DEFAULT_PIN_INIT_VALUE              STD_LOW
#define DEFAULT_PIN_DIR_CHANGE              STD_OFF
#define DEFAULT_PIN_MODE_CHANGE             STD_ON

/* Pins Modes */
#define PORT_A_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_1_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_4_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_5_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_6_MODE                   DEFAULT_PIN_MODE
#define PORT_A_PIN_7_MODE                   DEFAULT_PIN_MODE

#define PORT_B_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_1_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_4_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_5_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_6_MODE                   DEFAULT_PIN_MODE
#define PORT_B_PIN_7_MODE                   DEFAULT_PIN_MODE

#define PORT_C_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_1_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_4_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_5_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_6_MODE                   DEFAULT_PIN_MODE
#define PORT_C_PIN_7_MODE                   DEFAULT_PIN_MODE

#define PORT_D_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_1_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_4_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_5_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_6_MODE                   DEFAULT_PIN_MODE
#define PORT_D_PIN_7_MODE                   DEFAULT_PIN_MODE

#define PORT_E_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_E_PIN_1_MODE                   DEFAULT_PIN_MODE
#define PORT_E_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_E_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_E_PIN_4_MODE                   DEFAULT_PIN_MODE
#define PORT_E_PIN_5_MODE                   DEFAULT_PIN_MODE

#define PORT_F_PIN_0_MODE                   DEFAULT_PIN_MODE
#define PORT_F_PIN_1_MODE                   DIO_MODE
#define PORT_F_PIN_2_MODE                   DEFAULT_PIN_MODE
#define PORT_F_PIN_3_MODE                   DEFAULT_PIN_MODE
#define PORT_F_PIN_4_MODE                   DIO_MODE

/* Pin Direction Configurations */
#define PORT_A_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_1_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_4_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_5_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_6_DIR                   DEFAULT_PIN_DIR
#define PORT_A_PIN_7_DIR                   DEFAULT_PIN_DIR

#define PORT_B_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_1_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_4_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_5_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_6_DIR                   DEFAULT_PIN_DIR
#define PORT_B_PIN_7_DIR                   DEFAULT_PIN_DIR

#define PORT_C_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_1_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_4_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_5_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_6_DIR                   DEFAULT_PIN_DIR
#define PORT_C_PIN_7_DIR                   DEFAULT_PIN_DIR

#define PORT_D_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_1_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_4_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_5_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_6_DIR                   DEFAULT_PIN_DIR
#define PORT_D_PIN_7_DIR                   DEFAULT_PIN_DIR

#define PORT_E_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_E_PIN_1_DIR                   DEFAULT_PIN_DIR
#define PORT_E_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_E_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_E_PIN_4_DIR                   DEFAULT_PIN_DIR
#define PORT_E_PIN_5_DIR                   DEFAULT_PIN_DIR

#define PORT_F_PIN_0_DIR                   DEFAULT_PIN_DIR
#define PORT_F_PIN_1_DIR                   (Port_PinDirectionType)PORT_PIN_OUT
#define PORT_F_PIN_2_DIR                   DEFAULT_PIN_DIR
#define PORT_F_PIN_3_DIR                   DEFAULT_PIN_DIR
#define PORT_F_PIN_4_DIR                   (Port_PinDirectionType)PORT_PIN_IN

/* Port pins initial value */
#define PORT_A_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_1_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_4_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_5_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_6_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_A_PIN_7_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE

#define PORT_B_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_1_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_4_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_5_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_6_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_B_PIN_7_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE

#define PORT_C_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_1_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_4_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_5_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_6_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_C_PIN_7_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE

#define PORT_D_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_1_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_4_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_5_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_6_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_D_PIN_7_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE

#define PORT_E_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_E_PIN_1_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_E_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_E_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_E_PIN_4_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_E_PIN_5_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE

#define PORT_F_PIN_0_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_F_PIN_1_INIT_LEVEL                   STD_LOW
#define PORT_F_PIN_2_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_F_PIN_3_INIT_LEVEL                   DEFAULT_PIN_INIT_VALUE
#define PORT_F_PIN_4_INIT_LEVEL                   STD_LOW

/* Pin resistor type */
#define PORT_A_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_1_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_4_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_5_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_6_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_A_PIN_7_RES_LEVEL                   DEFAULT_PIN_RES_TYPE

#define PORT_B_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_1_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_4_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_5_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_6_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_B_PIN_7_RES_LEVEL                   DEFAULT_PIN_RES_TYPE

#define PORT_C_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_1_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_4_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_5_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_6_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_C_PIN_7_RES_LEVEL                   DEFAULT_PIN_RES_TYPE

#define PORT_D_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_1_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_4_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_5_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_6_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_D_PIN_7_RES_LEVEL                   DEFAULT_PIN_RES_TYPE

#define PORT_E_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_E_PIN_1_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_E_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_E_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_E_PIN_4_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_E_PIN_5_RES_LEVEL                   DEFAULT_PIN_RES_TYPE

#define PORT_F_PIN_0_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_F_PIN_1_RES_LEVEL                   (Port_InternalResistorType)OFF
#define PORT_F_PIN_2_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_F_PIN_3_RES_LEVEL                   DEFAULT_PIN_RES_TYPE
#define PORT_F_PIN_4_RES_LEVEL                   (Port_InternalResistorType)PULL_UP

/* Pin change direction during runtime */
#define PORT_A_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_1_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_4_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_5_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_6_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_A_PIN_7_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE

#define PORT_B_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_1_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_4_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_5_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_6_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_B_PIN_7_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE

#define PORT_C_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_1_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_4_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_5_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_6_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_C_PIN_7_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE

#define PORT_D_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_1_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_4_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_5_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_6_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_D_PIN_7_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE

#define PORT_E_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_E_PIN_1_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_E_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_E_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_E_PIN_4_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_E_PIN_5_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE

#define PORT_F_PIN_0_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_F_PIN_1_DIR_CHANGE                   STD_OFF
#define PORT_F_PIN_2_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_F_PIN_3_DIR_CHANGE                   DEFAULT_PIN_DIR_CHANGE
#define PORT_F_PIN_4_DIR_CHANGE                   STD_OFF

/* Pin change mode during runtime */
#define PORT_A_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_1_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_4_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_5_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_6_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_A_PIN_7_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE

#define PORT_B_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_1_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_4_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_5_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_6_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_B_PIN_7_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE

#define PORT_C_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_1_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_4_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_5_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_6_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_C_PIN_7_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE

#define PORT_D_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_1_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_4_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_5_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_6_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_D_PIN_7_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE

#define PORT_E_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_E_PIN_1_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_E_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_E_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_E_PIN_4_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_E_PIN_5_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE

#define PORT_F_PIN_0_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_F_PIN_1_MODE_CHANGE                   STD_OFF
#define PORT_F_PIN_2_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_F_PIN_3_MODE_CHANGE                   DEFAULT_PIN_MODE_CHANGE
#define PORT_F_PIN_4_MODE_CHANGE                   STD_OFF

#endif /* PORT_CFG_H */
