/**
 * @file    Port.h
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
#ifndef PORT_H
#define PORT_H

/**
 * @defgroup PORT_modes GPIO Configuration Modes
 * @{ */
#define PORT_MODE_INPUT           0x00u /*!< Low speed       */
#define PORT_MODE_OUTPUT          0x01u /*!< Medium speed    */
#define PORT_MODE_ALTERN          0x02u /*!< High speed      */
#define PORT_MODE_ANALOG          0x03u /*!< Very high speed */
/**
 * @} */


/**
 * @defgroup PORT_speed GPIO Speed Frequencies
 * @{ */
#define PORT_SPEED_FREQ_LOW       0x00u /*!< Low speed       */
#define PORT_SPEED_FREQ_MEDIUM    0x01u /*!< Medium speed    */
#define PORT_SPEED_FREQ_HIGH      0x02u /*!< High speed      */
#define PORT_SPEED_FREQ_VERY_HIGH 0x03u /*!< Very high speed */
/**
 * @} */


/**
 * @defgroup PORT_pull Pull-Up or Pull-Down Activation
 * @{ */
#define PORT_RESISTOR_NOPULL      0x00u /*!< No Pull-up or Pull-down activation  */
#define PORT_RESISTOR_PULLUP      0x01u /*!< Pull-up activation                  */
#define PORT_RESISTOR_PULLDOWN    0x02u /*!< Pull-down activation                */
/**
 * @} */

/**
 * @defgroup PORT_drive Drive output Push-Pull or Open collector
 * @{ */
#define PORT_PUSH_PULL            0x00u /*!< No Pull-up or Pull-down activation  */
#define PORT_OPEN_COLECTOR        0x01u /*!< Pull-up activation                  */
/**
 * @} */


/**
 * @defgroup PORT_alt Alternate Function
 * @{ */
#define PORT_ALT_F0               0x00u /*!< Alternate Function 0 selected       */
#define PORT_ALT_F1               0x01u /*!< Alternate Function 1 selected       */
#define PORT_ALT_F2               0x02u /*!< Alternate Function 2 selected       */
#define PORT_ALT_F3               0x03u /*!< Alternate Function 3 selected       */
#define PORT_ALT_F4               0x04u /*!< Alternate Function 4 selected       */
#define PORT_ALT_F5               0x05u /*!< Alternate Function 5 selected       */
#define PORT_ALT_F6               0x06u /*!< Alternate Function 6 selected       */
#define PORT_ALT_F7               0x07u /*!< Alternate Function 7 selected       */
#define PORT_ALT_F8               0x08u /*!< Alternate Function 8 selected       */
#define PORT_ALT_F9               0x09u /*!< Alternate Function 9 selected       */
#define PORT_ALT_F10              0x0Au /*!< Alternate Function 10 selected      */
/**
 * @} */


/**
 * @brief   Data type for the symbolic name of a port pin.
 *
 * The value of this type is comprised of two parts, with the most significant bits indicating the
 * MCU port and the least significant bits indicating the assigned pin number (values ranging from
 * 0 to 15).
 */
typedef uint8 Port_PinType;

/**
 * @brief  Possible directions of a port pin when confired as Digital pins.
 *
 * The enum is only applicable when the Pin is configures as a digital pin
 */
typedef enum Port_PinDirectionType_Tag
{
    PORT_PIN_IN = 0u, /**< Indicates the pin is configured as digital input */
    PORT_PIN_OUT      /**< Indicates the pin is configured as digital output */
} Port_PinDirectionType;

/**
 * @brief   Data type for holding different port pin modes.
 *
 * This type holds the functionality adopted or to be adopted by the pin. The values are limited
 * by the capabilities of the microcontroller and the specific set of functions that each pin
 * supports. The value is comprised of two parts, with the most significant bits indicating the
 * pin mode (input/output, output, alternate, or analog) and the least significant bits indicating
 * the alternate function (values ranging from 0 to 7).
 */
typedef uint8 Port_PinModeType;

/**
 * @brief Definition of the external data structure containing the initialization data for the Port.
 *
 * The Port_PortsConfigType data structure holds the initialization information for each port available
 * on the microcontroller. An array of these structures must be defined in the Port_Cfg.c file, with
 * each entry representing a specific port.
 *
 * @note It is the responsibility of the user to ensure that the values defined in this structure are
 * valid and appropriate, as the Port Driver does not perform any validation. The values must be generated
 * and validated within the code generation tool.
 */
typedef struct Port_PortsConfigType_Tag
{
    uint8 PortNumber; /**< A microcontroller-specific port name assigned to each available
                          port, ranging from PORT_PA to PORT_PH.*/

    uint16 AvailablePins; /**< A bitwise representation of the implemented pins in the corresponding
                              microcontroller port, where each set bit indicates that the corresponding
                              pin is available.*/

    uint32 PortPinInitialMode; /**< The functional mode to be configured for each pin in the port,
                                   represented by two bits for each pin. The potential values are
                                   PORT_MODE_INPUT (00), PORT_MODE_OUTPUT (01), PORT_MODE_ALTERN (10),
                                   and PORT_MODE_ANALOG (11).*/

    uint32 PortPinOuputDrive; /**< The drive mode for the port pins, represented by a bit for each pin.
                                  The potential values are PORT_PUSH_PULL (0) and PORT_OPEN_COLECTOR (1).*/

    uint32 PortPinSpeed; /**< The frequency configuration for each pin in the port, represented
                             by two bits for each pin. The potential values are PORT_SPEED_FREQ_LOW (00),
                             PORT_SPEED_FREQ_MEDIUM (01), PORT_SPEED_FREQ_HIGH (10), and
                             PORT_SPEED_FREQ_VERY_HIGH (11) */

    uint32 PortPinLevelValue; /**< The initial digital level value for each pin in the port, represented
                                  by a bit for each pin. These values are only applicable when the port
                                  is configured as digital output.*/

    uint32 PortPinResistor; /**< The internal resistor configuration for each pin in the port, represented
                                by two bits for each pin. The potential values are PORT_RESISTOR_NOPULL (00),
                                PORT_RESISTOR_PULLUP (01), and PORT_RESISTOR_PULLDOWN (10)*/

    uint32 PortPinAltH; /**< The altern mode configuration for the most significant port pins,
                            represented by four bits for each pin and up to eight potential altern modes
                            that can be set, all of them microcontroller dependent.*/

    uint32 PortPinAltL; /**< The altern mode configuration for the most significant port pins,
                            represented by four bits for each pin and up to eight potential altern modes
                            that can be set, all of them microcontroller dependent.*/

    uint16 DirectionChangeable; /**< A bitwise representation of the port pins that can have their direction
                                    changed at runtime, where each set bit indicates that the corresponding
                                    pin direction can be changed.*/

    uint16 ModeChangeable; /**< A bitwise representation of the port pins that can have their mode
                               (and altern mode) changed at runtime, where each set bit indicates that
                               the corresponding pin mode can be changed.*/
} Port_PortsConfigType;

/**
 * @brief  Type of the external data structure containing the initialization data for this module.
 *
 * Each pin available in the microcontroller shall be assigned this structure, an array with the
 * initial values must be defined in the Port_Cfg.c file
 */
typedef struct Port_ConfigType_Tag
{
    uint8 PortNumbers;                 /**< the number of ports in the microcontroller*/
    Port_PortsConfigType *PortsConfig; /**< pointer to port configuration array*/
} Port_ConfigType;

/* cppcheck-suppress misra-c2012-20.1 ; it is necesary to include here after the Port_Config definition */
#include "Port_Cfg.h"

void Port_Init( const Port_ConfigType *ConfigPtr );
void Port_RefreshPortDirection( void );

#if PORT_SET_PIN_DIRECTION_API == STD_ON
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif /* PORT_SET_PIN_DIRECTION_API == STD_ON */


#if PORT_SET_PIN_MODE_API == STD_ON
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif /* PORT_SET_PIN_MODE_API == STD_ON */

#if PORT_VERSION_INFO_API == STD_ON
void Port_GetVersionInfo( Std_VersionInfoType *versioninfo );
#endif /* PORT_VERSION_INFO_API == STD_ON */

#endif /* PORT_H */
