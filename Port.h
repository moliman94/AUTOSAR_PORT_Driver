 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Soliman
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Dio Module Id */
#define PORT_MODULE_ID    (124U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Software Version checking between Std_Types.h and Port.h files */
#if ((STD_TYPES_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (STD_TYPES_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (STD_TYPES_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init */
#define PORT_INIT_SID                               (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID                  (uint8)0x01

/* Service ID for Port_RefreshPortDirection  */
#define PORT_REFRESH_PORT_DIRECTION_SID             (uint8)0x02

/* Service ID for Port_GetVersionInfo  */
#define PORT_GET_VERSION_INFO_SID                   (uint8)0x03

/* Service ID for Port_SetPinMode  */
#define PORT_SET_PIN_MODE_SID                       (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D

/*  */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                   (uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER            (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Possible directions of a port pin */
typedef enum
{
    PORT_PIN_IN,    /* Sets port pin as input */
    PORT_PIN_OUT    /* Sets port pin as output */
}Port_PinDirectionType;

/* Different port pin modes. */
typedef uint8 Port_PinModeType;

/* Data type for Port numbers */
typedef uint8 Port_IDType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistorType;

/* 
 * Pin Configuration structure
 */
typedef struct 
{
    /* Port Number */
    Port_IDType Port_Num;
    /* Port Pin Number */
    Port_PinType Pin_Num;
    /* Mode of the pin */
    Port_PinModeType Pin_Mode;
    /* Direction of the pin */
    Port_PinDirectionType Pin_Dir;
    /* Internal resistor type of the pin */
    Port_InternalResistorType Pin_Res_Type;
    /* Initial value of the pin */
    uint8 Pin_Initial_Value;
    /* Pin direction changeable during runtime */
    uint8 Pin_Dir_Change;
    /* Pin mode changeable during runtime */
    uint8 Pin_Mode_Change;
}Pin_ConfigType;

/*
 * Type of the external data structure containing 
 * the initialization data for this module.
 */
typedef struct
{
    Pin_ConfigType Pin_Config[PORT_CONFIGURED_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to Initialize the Port Driver module */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Function to Set the port pin direction during runtime */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function to Refreshe port direction */
void Port_RefreshPortDirection(void);

/* Function to Return the version information of this module */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* Function to Set the port pin mode during runtime */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
