/**
 * @file    Port.c
 * @brief   **Specification of Port Driver**
 *
 * This PORT driver module shall complete the overall configuration and initialization of the port
 * structure which is used in the DIO driver module. Therefore, the DIO driver works on pins and
 * ports which are configured by the PORT driver.
 *
 * The PORT driver shall be initialized prior to the use of the DIO functions. Otherwise, DIO
 * functions will exhibit undefined behavior. The diagram below identifies the PORT driver functions
 * and the structure of the PORT driver and DIO driver within the MCAL software layer.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Port.h"
#include "Bfx.h"

/* clang-format off */
Port_RegisterType *PortRegisters[PORT_PIN_NUMBER_OF_PORTS] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
/* clang-format on */

/* This data is pointer to actually used configuration set */
static const Port_ConfigType *Port_ConfigDataPtr = NULL_PTR;

/**
 * @brief   Initializes the Port Driver module with the configuration set pointed to by ConfigPtr.
 *
 * The function initializes all ports and port pins using the configuration set specified by the input
 * parameter ConfigPtr. By default, each port pin will be configured in analog mode. The function will
 * configure all the microcontroller pins defined on each port according to what was set by the
 * configuration tool.
 *
 * @param[in]  ConfigPtr  Pointer to the configuration set to be used for initialization.
 *
 * @code
 *      Port_Init( &PortsConfiguration );
 * @endcode
 */
void Port_Init( const Port_ConfigType *ConfigPtr )
{
    uint8 Port;
    uint8 Ports;

    /*Rollover all the ports to configure*/
    for( Ports = 0u; Ports < ConfigPtr->PortNumbers; Ports++ )
    {
        /* Get the pin to configure */
        Port = ConfigPtr->PortsConfig[ Ports ].PortNumber;

        /*Set mode in all corresponding pins*/
        PortRegisters[ Port ]->MODER = ConfigPtr->PortsConfig[ Ports ].PortPinInitialMode;
        /*Set ouput drive in all corresponding pins*/
        PortRegisters[ Port ]->PUPDR = ConfigPtr->PortsConfig[ Ports ].PortPinOuputDrive;
        /*Set output speed in all corresponding pins*/
        PortRegisters[ Port ]->OSPEEDR = ConfigPtr->PortsConfig[ Ports ].PortPinSpeed;
        /*Set pull resistors in all corresponding pins*/
        PortRegisters[ Port ]->PUPDR = ConfigPtr->PortsConfig[ Ports ].PortPinResistor;
        /*Set output speed in all corresponding pins*/
        PortRegisters[ Port ]->PUPDR = ConfigPtr->PortsConfig[ Ports ].PortPinResistor;
        /*Set intial output level value*/
        PortRegisters[ Port ]->ODR = ConfigPtr->PortsConfig[ Ports ].PortPinLevelValue;
        /*Set altern mode for the most significant pins*/
        PortRegisters[ Port ]->AFR[ 1u ] = ConfigPtr->PortsConfig[ Ports ].PortPinAltH;
        /*Set altern mode for the less significant pins*/
        PortRegisters[ Port ]->AFR[ 0u ] = ConfigPtr->PortsConfig[ Ports ].PortPinAltL;
    }

    Port_ConfigDataPtr = ConfigPtr;
}


#if PORT_SET_PIN_DIRECTION_API == STD_ON
/**
 * @brief  Sets the port pin direction.
 *
 * This function sets or changes the direction of a previously configured port pin. It is only applicable
 * for pins configured as GPIO and if the DirectionChangeable flag for the pin is set to TRUE. However,
 * the function does not perform any validation to check if the pin has the correct configuration.
 *
 * @param  Pin Pin Port pin identifier.
 * @param  Direction Direction Desired direction for the port pin.
 *
 * @note The function does not perform any validation to ensure that the provided Pin parameter is
 *      valid or that the direction change is allowed. The responsibility to ensure the validity of the
 *      input lies with the caller.
 *
 * @code
 *      Port_SetPinDirection( PORT_PIN_CHIP_SELECT, PORT_PIN_OUT );
 * @endcode
 */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    uint8 PortPin = Pin;
    uint8 Port    = Pin;

    /* Get the pin to configure */
    Bfx_ClrBitMask_u8u8( &PortPin, 0xf0u );
    /* Get the port where the pin to configure is set */
    Bfx_ShiftBitRt_u8u8( &Port, 4u );
    /*Set the new direction into the appropiate Mcu register*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortRegisters[ Port ]->MODER, ( PortPin << 2u ), 2u, Direction );
}
#endif /*PORT_SET_PIN_DIRECTION_API == STD_ON*/


/**
 * @brief  Refreshes the direction of all the configured ports.
 *
 * This function updates the direction of all the ports to their configured direction, but only for
 * the pins that are not configured as changeable during runtime. The function ensures that the direction
 * of the port is updated to its intended state, especially after a system reset or power-up scenario.
 *
 * @code
 *      Port_RefreshPortDirection( );
 * @endcode
 */
void Port_RefreshPortDirection( void )
{
    uint8 Pin;
    uint8 Port;

    /*Roll over all hte pins to configure*/
    for( Port = 0u; Port < Port_ConfigDataPtr->PortNumbers; Port++ )
    {
        /*Roll over all the pins in the port*/
        for( Pin = 0u; Pin < 16u; Pin++ )
        {
            /*inquire if the pin is set to not changeable and configure as GPIO*/
            if( Bfx_GetBit_u32u8_u8( Port_ConfigDataPtr->PortsConfig[ Port ].DirectionChangeable, Pin ) == FALSE )
            {
                /*inquire if th pin is configure as regualr GPIO*/
                if( Bfx_TstBitMask_u32u32_u8( Port_ConfigDataPtr->PortsConfig[ Port ].PortPinInitialMode, ( 0x10u << ( Pin << 2 ) ) ) == FALSE )
                {
                    /*refresh the port direction as stablished in the initial configuration*/
                    Bfx_CopyBit_u32u8u32u8( (uint32 *)&PortRegisters[ Port ]->MODER, ( Pin << 2u ), Port_ConfigDataPtr->PortsConfig[ Port ].PortPinInitialMode, ( Pin << 2u ) );
                }
            }
        }
    }
}


#if PORT_SET_PIN_MODE_API == STD_ON
/**
 * @brief  Sets the port pin mode.
 *
 * The function sets the mode of the specified pin during runtime, but only if the pin is configured
 * to allow mode changes at runtime. The new mode must be defined in the auto-generated file Port_Cfg.h,
 * otherwise unexpected behavior may occur.
 *
 * @param  Pin Port Pin ID number
 * @param  Mode New Port Pin mode to be set on port pin
 *
 * @code
 *      Port_SetPinMode( PORT_PIN_CHIP_SELECT, PORT_PIN_SPI_MODE );
 * @endcode
 *
 */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    uint8 PortPin        = Pin;
    uint8 Port           = Pin;
    uint8 PinMode        = Mode;
    uint8 AlternFunction = Mode;

    /* Get the pin to configure */
    Bfx_ClrBitMask_u8u8( &PortPin, 0xf0u );
    /* Get the port where the pin to configure is set */
    Bfx_ShiftBitRt_u8u8( &Port, 4u );
    /* Get the pin to configure */
    Bfx_ClrBitMask_u8u8( &Mode, 0xf0u );
    /* Get the port where the pin to configure is set */
    Bfx_ShiftBitRt_u8u8( &AlternFunction, 4u );

    /*Set Altern mode*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortRegisters[ Port ]->MODER, ( PortPin << 2u ), 2u, PinMode );
    /*set the new altern mode*/
    if( Port < 8u )
    {
        /*Set the new altern mode for the less significant pins*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortRegisters[ Port ]->AFR[ 0u ], ( PortPin << 4u ), 4u, AlternFunction );
    }
    else
    {
        /*Set the new altern mode for the most significant pins*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortRegisters[ Port ]->AFR[ 1u ], ( PortPin << 4u ), 4u, AlternFunction );
    }
}
#endif /*PORT_SET_PIN_MODE_API == STD_ON*/


#if PORT_VERSION_INFO_API == STD_ON
/**
 * @brief  Returns the version information of this module.
 *
 * The function returns the version information of this module. The version information includes:
 * Module Id, Vendor Id, Vendor specific version numbers.
 *
 * @param  versioninfo Pointer to where to store the version information of this module.
 */
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    (void *)versioninfo;
}
#endif /*PORT_VERSION_INFO_API == STD_ON*/
