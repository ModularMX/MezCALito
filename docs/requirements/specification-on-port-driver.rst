Specification of Port Driver
============================

This specification specifies the functionality, API and the configuration of the AUTOSAR Basic 
Software module PORT Driver.

This driver specification is applicable for on-chip ports and port pins.

This module shall provide the service for initializing the whole PORT structure of the microcontroller. 
Many ports and port pins can be assigned to various functionalities, e.g.

- General purpose I/O
- ADC
- SPI
- SCI
- PWM
- CAN
- LIN
- etc

For this reason, there shall be an overall configuration and initialization of this port structure. 
The configuration and mode of these port pins is microcontroller and ECU dependent.

Port initialisation data shall be written to each port as efficiently as possible.

This PORT driver module shall complete the overall configuration and initialisation of the port 
structure which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports 
which are configured by the PORT driver.

The PORT driver shall be initialised prior to use of the DIO functions. Otherwise DIO functions will 
exhibit undefined behaviour.

The diagram below identifies the PORT driver functions, and the structure of the PORT driver and DIO 
driver within the MCAL software layer

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SWS_PortDriver.pdf


+-------------+------------------------+----------------------------+------------------------+
| Driver:     | Name for a Port Pin:   | Name for Subset of         | Name for a whole port: |
|             |                        | Adjacent pins on one port: |                        |
+-------------+------------------------+----------------------------+------------------------+
| DIO Driver  | Channel                | Channel Group              | Port                   |
+-------------+------------------------+----------------------------+------------------------+ 
| PORT Driver | Port pin               | -                          | Port                   |
+-------------+------------------------+----------------------------+------------------------+


4 Constraints and assumptions
-----------------------------

4.1 Limitations
^^^^^^^^^^^^^^^

Limitations for the PORT driver are specified as followed:

- It is the user's responsibility to ensure that the same Port/Port pin is not being accessed in 
  parallel by different entities in the same system, e.g. by two tasks configuring the same port 
  or two tasks configuring the same pin, or two tasks configuring different pins on the same port.


5 Dependencies to other modules
-------------------------------

Other driver modules may be dependent on the PORT driver depending on the available functionality 
of individual port pins on an MCU. For example, an MCU pin may be configurable as a DIO or SPI pin. 
Therefore, the DIO and/or the SPI driver modules may be dependent on the PORT module to configure 
the pin for the desired functionality.


7 Functional specification
--------------------------

7.1 General Behaviour
^^^^^^^^^^^^^^^^^^^^^

7.1.1 Background & Rationale
""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00001
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101

    The PORT Driver module shall initialize the whole port structure of the microcontroller

    Note: Defining the order in which the ports and port pins are configured is the task of the 
    configuration tool.


7.1.2 Requirements
""""""""""""""""""

**7.1.2.1 Configuration of Port Pin Properties**

.. req:: None
    :id: SWS_Port_00004
    :status: open
    :tags: bsw
    :links: SRS_BSW_00159, SRS_Port_12001

    The PORT Driver module shall allow the configuration of different functionality for each port 
    and port pin, e.g. ADC, SPI, DIO etc

    The configuration of the port (i.e. whole port or single port pin) is microcontroller dependent.


.. req:: None
    :id: SWS_Port_00079
    :status: open
    :tags: bsw
    :links: SRS_Port_12001

    The PORT Driver module shall provide additional configurations for the MCU port/port pins:

    - Pin direction (input/output)
    - Pin level initial value
    - Pin direction changeable during runtime (yes/no).
    - Port mode changeable during runtime.


.. req:: None
    :id: SWS_Port_00081
    :status: open
    :tags: bsw

    The PORT Driver module shall provide a number of optional configurations for the MCU ports and 
    port pins (if supported by hardware):
    
    - Slew rate control
    - Activation of internal pull-ups
    - Input Thresholds
    - Pin driven mode (push-pull / open drain).
    - Type of Readback support (pin level, output register value).


.. req:: None
    :id: SWS_Port_00082
    :status: open
    :tags: bsw

    The PORT Driver module shall not provide the facility to configure pin level inversion. The 
    default value shall be set (i.e. not inverted)

    Note: The IO Hardware Abstraction layer shall carry out level inversion


**7.1.2.2 Switch port pin direction**

.. req:: None
    :id: SWS_Port_00137
    :status: open
    :tags: bsw


    For the port pins configured as changeable using the configuration tool, the PORT driver shall 
    allow the user to change the direction of port pins during runtime


.. req:: None
    :id: SWS_Port_00138
    :status: open
    :tags: bsw
    :links: SRS_Port_12405

    If the MCU port control hardware provides an output latch for setting the output level on a port 
    pin, switching the port pin direction shall not alter the level set in this output latch


**7.1.2.3 Refresh port direction**

.. req:: None
    :id: SWS_Port_00066
    :status: open
    :tags: bsw
    
    For refreshing of the port on the microcontroller, the PORT driver shall allow the user to 
    refresh the direction of those port pins whose direction is set by configuration and cannot be 
    changed dynamically


**7.1.2.4 Configuration of unused Ports and Port Pins**

.. req:: None
    :id: SWS_Port_00005
    :status: open
    :tags: bsw
    :links: SRS_Port_12300
    
    The PORT Driver module shall configure all ports and port pins that are not used (neither as 
    GPIO nor special purpose IO) to be set to a defined state by the PORT Driver module configuration
    

**7.1.2.5 Configuration of symbolic names**

.. req:: None
    :id: SWS_Port_00006
    :status: open
    :tags: bsw
    :links: SRS_Port_12302

    The user of the PORT Driver module shall configure the symbolic names of the port pins of the MCU


.. req:: None
    :id: SWS_Port_00207
    :status: open
    :tags: bsw

    These symbolic names for the individual port pins (e.g. PORT_A_PIN_0) shall be defined in the 
    configuration tool


.. req:: None
    :id: SWS_Port_00208
    :status: open
    :tags: bsw

    The PORT Driver module's implementer shall publish the symbolic names through the file Port.h


**7.1.2.6 Atomicity of port access**

.. req:: None
    :id: SWS_Port_00075
    :status: open
    :tags: bsw

    The PORT Driver module shall provide atomic access to all ports and port pins.

    Note: An atomic access is a non interruptible access to Microcontroller registers by the use
    of either atomic instructions or the usage of an exclusive area (interrupt disabling for example) 
    provided by the basic software scheduler module.


7.1.3 Version Check
"""""""""""""""""""

**7.1.3.1 Background and Rationale**

The integration of incompatible files shall be avoided. Minimum implementation is the version check 
of the header file inside the .c file (version numbers of .c and .h files shall be identical).

**7.1.3.2 Requirements**

The Port module shall avoid the integration of incompatible files by the following preprocessor checks:

For details refer to the chapter 5.1.8 "Version Check" in [4, SWS BSW General].


7.2 Error classification
^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Port_00051
    :status: open
    :tags: bsw
    :links: SRS_BSW_00327, SRS_BSW_00337, SRS_BSW_00385, SRS_BSW_00406

    +-----------------------------------------+-------------------------------+-------------+
    | Type of error                           | Related error code            | Error value |
    +-----------------------------------------+-------------------------------+-------------+
    | Invalid Port Pin ID requested           | PORT_E_PARAM_PIN              | 0x0A        |
    +-----------------------------------------+-------------------------------+-------------+
    | Port Pin not configured as changeable   | PORT_E_DIRECTION_UNCHANGEABLE | 0x0B        |
    +-----------------------------------------+-------------------------------+-------------+
    | API Port_Init service called with wrong | PORT_E_INIT_FAILED            | 0x0C        |
    | parameter                               |                               |             |
    +-----------------------------------------+-------------------------------+-------------+
    | API Port_SetPinMode service called when | PORT_E_PARAM_INVALID_MODE     | 0x0D        |
    | mode is unchangeable.                   |                               |             |
    +-----------------------------------------+-------------------------------+-------------+
    | API Port_SetPinMode service called when | PORT_E_MODE_UNCHANGEABLE      | 0x0E        |
    | mode is unchangeable.                   |                               |             |
    +-----------------------------------------+-------------------------------+-------------+
    | API service called without module       | PORT_E_UNINIT                 | 0x0F        |
    | initialization                          |                               |             |
    +-----------------------------------------+-------------------------------+-------------+
    | APIs called with a Null Pointer         | PORT_E_PARAM_POINTER          | 0x10        |
    +-----------------------------------------+-------------------------------+-------------+
    

7.3 API Parameter checking
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Port_00077
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12448

    If development error detection is enabled the Port Driver module shall check the function 
    parameters in the order in which they are passed and skip further parameter checking if one check 
    fails.

    Example: For the function `Port_SetPinDirection`, the first parameter to be passed is the pin ID. 
    This parameter shall identify the relevant port pin of the MCU's port. The second parameter passed 
    corresponds to the direction to change on the port pin.c


.. req:: None
    :id: SWS_Port_00087
    :status: open
    :tags: bsw
    :links: SRS_BSW_00323, SRS_BSW_00406

    If development error detection is enabled and the Port Driver module has detected an error, the 
    desired functionality shall be skipped and the requested service shall return without any action
    
    See table below for a list of the Det errors reported by each function.

    +-------------------+-----------------------------------------+-------------------------------+
    | Function:         | Error Condition:                        | Realted error value:          |  
    +-------------------+-----------------------------------------+-------------------------------+
    | `Port_-           | Incorrect Port Pin ID passed            | PORT_E_PARAM_PIN              |  
    | SetPinDirection`  | Port Pin not configured as changeable   | PORT_E_DIRECTION_UNCHANGEABLE |  
    +-------------------+-----------------------------------------+-------------------------------+
    | `Port_Init`       | Port_Init service called with wrong     | PORT_E_INIT_FAILED            |  
    |                   | parameter                               |                               |  
    +-------------------+-----------------------------------------+-------------------------------+
    | `Port_SetPinMode` | Incorrect Port Pin ID passed            | PORT_E_PARAM_PIN              |  
    |                   | Port Pin Mode passed not valid          | PORT_E_PARAM_INVALID_MODE     |  
    |                   | Port_SetPinMode service called when the | PORT_E_MODE_UNCHANGEABLE      |  
    |                   | mode is unchangeable                    |                               |  
    +-------------------+-----------------------------------------+-------------------------------+
    | `Port_-           | API service called prior to module      | PORT_E_UNINIT                 |  
    | SetPinDirection,  | initialization                          |                               |    
    | Port_SetPinMode   |                                         |                               |       
    | Port_RefreshPort- |                                         |                               |      
    | Direction`        |                                         |                               |      
    +-------------------+-----------------------------------------+-------------------------------+
    | `Port_-           | Api called with a NULL Pointer Parameter| PORT_E_PARAM_POINTER          |      
    | GetVersionInfo`   |                                         |                               |
    +-------------------+-----------------------------------------+-------------------------------+
    

8 API specification
-------------------

8.1 Imported types
^^^^^^^^^^^^^^^^^^

In this chapter, all types included from the following modules are listed:

.. req:: None
    :id: SWS_Port_00129
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------+-------------------------------+
    | **Module:**       | **Header File:**                        | **Imported Type:**            |  
    +-------------------+-----------------------------------------+-------------------------------+
    | Std               | Std_Types.h                             | Std_ReturnType                |
    |                   +-----------------------------------------+-------------------------------+
    |                   | Std_Types.h                             | Std_VersionInfoType           |
    +-------------------+-----------------------------------------+-------------------------------+


8.2 Type definitions
^^^^^^^^^^^^^^^^^^^^

8.2.1 Port_ConfigType
"""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00228
    :status: open
    :tags: bsw

    +-------------------+-------------------------------------------------------------------------+
    | **Name**          | Port_ConfigType                                                         |  
    +-------------------+-------------------------------------------------------------------------+
    | **Kind**          | Structure                                                               |  
    +-------------------+-------------------------------------------------------------------------+
    | **Elements**      | Hardware Dependent Structure                                            |
    |                   +----------------+--------------------------------------------------------+
    |                   | Types          |                                                        |
    |                   +----------------+--------------------------------------------------------+
    |                   | Comment        | The contents of the initialization data structure are  |
    |                   |                | specific to the microcontroller                        |
    +-------------------+----------------+--------------------------------------------------------+
    | **Description**   | Type of the external data structure containing the initialization data  |
    |                   | for this module.                                                        |
    +-------------------+-------------------------------------------------------------------------+
    | **Available via** | Port.h                                                                  |
    +-------------------+-------------------------------------------------------------------------+
    

8.2.2 Port_PinType
""""""""""""""""""

.. req:: None
    :id: SWS_Port_00229
    :status: open
    :tags: bsw

    +-------------------+-------------------------------------------------------------------------+
    | **Name**          | Port_PinType                                                            |  
    +-------------------+-------------------------------------------------------------------------+
    | **Kind**          | Type                                                                    |  
    +-------------------+-------------------------------------------------------------------------+
    | **Derived from**  | uint                                                                    |  
    +-------------------+------------------------+------------------------------------------------+
    | **Range**         | 0 -                    | Shall cover all available port pins.           |
    |                   | <number of port pins:> | The type should be chosen for the specific MCU |
    |                   |                        | platform (best performance)                    |
    +-------------------+------------------------+------------------------------------------------+
    | **Description**   | Data type for the symbolic name of a port pin                           |
    +-------------------+-------------------------------------------------------------------------+
    | **Available via** | Port.h                                                                  |
    +-------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00013
    :status: open
    :tags: bsw

    The type `Port_PinType` shall be used for the symbolic name of a Port Pin.


.. req:: None
    :id: SWS_Port_00219
    :status: open
    :tags: bsw

    The type `Port_PinType` shall be `uint8`, `uint16` or `uint32` based on the specific MCU platform

    Note: The user shall use the symbolic names provided by the configuration tool.


8.2.3 Port_PinDirectionType
"""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00230
    :status: open
    :tags: bsw

    +-------------------+-------------------------------------------------------------------------+
    | **Name**          | Port_PinDirectionType                                                   |  
    +-------------------+-------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                             |  
    +-------------------+---------------+-------+-------------------------------------------------+
    | **Range**         | PORT_PIN_IN   | 0x00  | Sets port pin as input.                         |
    |                   | PORT_PIN_OUT  | 0x01  | Sets port pin as output.                        |
    +-------------------+------------------------+------------------------------------------------+
    | **Description**   | Possible directions of a port pin                                       |
    +-------------------+-------------------------------------------------------------------------+
    | **Available via** | Port.h                                                                  |
    +-------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00046
    :status: open
    :tags: bsw

    The type `Port_PinDirectionType` is a type for defining the direction of a Port Pin


.. req:: None
    :id: SWS_Port_00220
    :status: open
    :tags: bsw

    The type `Port_PinDirectionType` shall be of enumeration type having range as `PORT_PIN_IN` and 
    `PORT_PIN_OUT`


8.2.2 Port_PinModeType
""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00231
    :status: open
    :tags: bsw

    +-------------------+-------------------------------------------------------------------------+
    | **Name**          | Port_PinModeType                                                        |  
    +-------------------+-------------------------------------------------------------------------+
    | **Kind**          | Type                                                                    |  
    +-------------------+-------------------------------------------------------------------------+
    | **Derived from**  | uint                                                                    |  
    +-------------------+------------------------+------------------------------------------------+
    | **Range**         | Implementation         | As several port pin modes shall be configurable|
    |                   | specific               | on one pin, the range shall be determined by   |
    |                   |                        | the implementation                             |
    +-------------------+------------------------+------------------------------------------------+
    | **Description**   | Different port pin modes.                                               |
    +-------------------+-------------------------------------------------------------------------+
    | **Available via** | Port.h                                                                  |
    +-------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00124
    :status: open
    :tags: bsw

    A port pin shall be configurable with a number of port pin modes (type `Port_PinModeType`)


.. req:: None
    :id: SWS_Port_00212
    :status: open
    :tags: bsw

    The type `Port_PinModeType` shall be used with the function call `Port_SetPinMode`


.. req:: None
    :id: SWS_Port_00221
    :status: open
    :tags: bsw

    The type `Port_PinModeType` shall be `uint8`, `uint16` or `uint32`


8.3 Function definitions
^^^^^^^^^^^^^^^^^^^^^^^^

This is a list of functions provided for upper layer modules.

8.3.1 Port_Init
"""""""""""""""

.. req:: None
    :id: SWS_Port_00140
    :status: open
    :tags: bsw
    :links: SRS_BSW_00358

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Port_Init                                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Port_Init (                                                    |
    |                       |          const Port_ConfigType* ConfigPtr                               |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x00                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Non Reentrant                                                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ConfigPtr             | Pointer to configuration set.                   |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | Initializes the Port Driver module.                                     |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Port.h                                                                  |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00041
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101, SRS_BSW_00404, SRS_SPAL_12263, SRS_SPAL_12057, SRS_SPAL_12125

    The function `Port_Init` shall initialize ALL ports and port pins with the configuration set 
    pointed to by the parameter `ConfigPtr`


.. req:: None
    :id: SWS_Port_00078
    :status: open
    :tags: bsw

    The Port Driver module's environment shall call the function `Port_Init`` first in order to 
    initialize the port for use.


.. req:: None
    :id: SWS_Port_00213
    :status: open
    :tags: bsw

    If `Port_Init`` function is not called first, then no operation can occur on the MCU ports and 
    port pins


.. req:: None
    :id: SWS_Port_00042
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101, SRS_SPAL_12057, SRS_SPAL_12125

    The function `Port_Init` shall initialize all configured resources.
    
    The function `Port_Init` shall apply the following rules regarding initialisation of controller 
    registers


.. req:: None
    :id: SWS_Port_00113
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    If the hardware allows for only one usage of the register, the driver module implementing that 
    functionality is responsible for initializing the register


.. req:: None
    :id: SWS_Port_00214
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    If the register can affect several hardware modules and if it is an I/O register it shall be 
    initialised by this PORT driver


.. req:: None
    :id: SWS_Port_00215
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    If the register can affect several hardware modules and if it is not an I/O register, it shall 
    be initialised by the MCU driver


.. req:: None
    :id: SWS_Port_00217
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    One-time writable registers that require initialisation directly after reset shall be initialised 
    by the startup code


.. req:: None
    :id: SWS_Port_00218
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    All the other registers not mentioned before, shall be initialised by the start-up code.


.. req:: None
    :id: SWS_Port_00043
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12057

    The function `Port_Init` shall avoid glitches and spikes on the affected port pins


.. req:: None
    :id: SWS_Port_00071
    :status: open
    :tags: bsw

    The Port Driver module's environment shall call the function `Port_Init` after a reset in order 
    to reconfigure the ports and port pins of the MCU


.. req:: None
    :id: SWS_Port_00002
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101

    The function `Port_Init` shall initialize all variables used by the PORT driver module to an 
    initial state


.. req:: None
    :id: SWS_Port_00003
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12163

    The Port Driver module's environment may also uses the function `Port_Init` to initialize the 
    driver software and reinitialize the ports and port pins to another configured state depending 
    on the configuration set passed to this function

    Note: In some cases, MCU port control hardware provides an output latch for setting the output 
    level on a port pin that may be used as a DIO port pin.


.. req:: None
    :id: SWS_Port_00055
    :status: open
    :tags: bsw

    The function `Port_Init` shall set the port pin output latch to a default level (defined during 
    configuration) before setting the port pin direction to output

    Requirement [SWS_Port_00055] ensures that the default level is immediately output on the port pin 
    when it is set to an output port pin.

    Example: On some MCU's, after a power-on-reset, a DIO configurable port pin will be configured as 
    an input pin. If the required configuration of the port pin is an output pin, then the function 
    `Port_Init` shall ensure that the default level is set before switching the functionality of the 
    port pin from input to output.


.. req:: None
    :id: SWS_Port_00121
    :status: open
    :tags: bsw
    :links: SRS_BSW_00414

    The function Port_Init shall always have a pointer as a parameter, even though for the configuration 
    variant VARIANT-PRE-COMPILE, no configuration set shall be given. In this case, the Port Driver 
    module's environment shall pass a NULL pointer to the function `Port_Init`

    The Port Driver module's environment shall not call the function `Port_Init` during a running 
    operation. This shall only apply if there is more than one caller of the PORT module.

    Configuration of `Port_Init`: All port pins and their functions, and alternate functions shall be 
    configured by the configuration tool.


8.3.2 Port_SetPinDirection
""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00141
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Port_SetPinDirection                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Port_SetPinDirection (                                         |
    |                       |          Port_PinType Pin,                                              |
    |                       |          Port_PinDirectionType Direction                                |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x01                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Pin                   | Port Pin ID number                              |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Direction             | Port Pin Direction                              |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | Sets the port pin direction                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Port.h                                                                  |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00063
    :status: open
    :tags: bsw
    :links: SRS_Port_12405

    The function `Port_SetPinDirection` shall set the port pin direction during runtime


.. req:: None
    :id: SWS_Port_00054
    :status: open
    :tags: bsw

    The function `Port_SetPinDirection` shall be re-entrant if accessing different pins independent 
    of a port.


.. req:: None
    :id: SWS_Port_00086
    :status: open
    :tags: bsw
    :links: SRS_Port_12405

    The function `Port_SetPinDirection` shall only be available to the user if the pre-compile 
    parameter `PortSetPinDirectionApi`` is set to TRUE. If set to FALSE, the function 
    `Port_SetPinDirection` is not available

    Configuration of Port_SetPinDirection: All ports and port pins shall be configured by the 
    configuration tool. See PORT117


8.3.3 Port_RefreshPortDirection
"""""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00142
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Port_RefreshPortDirection                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Port_RefreshPortDirection (                                    |
    |                       |          void                                                           |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x02                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Non Reentrant                                                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(in)**    | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | Refreshes port direction.                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Port.h                                                                  |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00060
    :status: open
    :tags: bsw
    :links: SRS_Port_12406

    The function `Port_RefreshPortDirection` shall refresh the direction of all configured ports to 
    the configured direction (`PortPinDirection`)


.. req:: None
    :id: SWS_Port_00061
    :status: open
    :tags: bsw
    :links: SRS_Port_12406

    The function `Port_RefreshPortDirection` shall exclude those port pins from refreshing that are 
    configured as pin direction changeable during runtime.

    The configuration tool shall provide names for each configured port pin


8.3.4 Port_GetVersionInfo
"""""""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00143
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Port_GetVersionInfo                                                     |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Port_GetVersionInfo (                                          |
    |                       |          Std_VersionInfoType* versioninfo                               |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x02                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(in)**    | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+---------------------+---------------------------------------------------+
    | **Parameters(out)**   | versioninfo         | Pointer to where to store the version information | 
    |                       |                     | of this module                                    |
    +-----------------------+---------------------+---------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | Returns the version information of this module.                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Port.h                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    

.. req:: None
    :id: SWS_Port_00225
    :status: open
    :tags: bsw

    If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error 
    PORT_E_PARAM_POINTER shall be reported in case the value is a NULL pointer.


8.3.5 Port_SetPinMode
"""""""""""""""""""""

.. req:: None
    :id: SWS_Port_00145
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Port_SetPinMode                                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Port_SetPinMode (                                              |
    |                       |          Port_PinType Pin,                                              |
    |                       |          Port_PinModeType Mode                                          |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x04                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Pin                   | Port Pin ID number                              |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Direction             | New Port Pin mode to be set on port pin         |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | Sets the port pin mode                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Port.h                                                                  |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Port_00125
    :status: open
    :tags: bsw

    The function `Port_SetPinMode` shall set the port pin mode of the referenced pin during runtime.


.. req:: None
    :id: SWS_Port_00128
    :status: open
    :tags: bsw

    The function `Port_SetPinMode` shall be re-entrant if accessing different pins, independent of a 
    port


.. req:: None
    :id: SWS_Port_00223
    :status: open
    :tags: bsw

    If Det is enabled, the function `Port_SetPinMode` shall report PORT_E_MODE_UNCHANGEABLE error 
    and return without any other action, if the parameter `PortPinModeChangeable` is set to FALSE

    Configuration of `Port_SetPinMode`: All ports and port pins shall be configured by the configuration 
    tool. See PORT117.


8.4 Call-back notifications
^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are no callback notifications from the PORT driver. The callback notifications are implemented 
in another module (ICU Driver and/or complex drivers).

8.5 Scheduled functions
^^^^^^^^^^^^^^^^^^^^^^^

There are no scheduled functions within the PORT Driver

8.6 Expected Interfaces
^^^^^^^^^^^^^^^^^^^^^^^

In this chapter, all interfaces required from other modules are listed.

8.6.1 Mandatory Interfaces
""""""""""""""""""""""""""
None

8.6.2 Optional Interfaces
"""""""""""""""""""""""""

This chapter defines all interfaces which are required to fulfill an optional functionality
of the module.

.. req:: None
    :id: SWS_Port_00146
    :status: open
    :tags: bsw

    +-------------------+-----------------------+-------------------------------------------------+
    | **API Function**  | **Header File**       | **Description**                                 |  
    +-------------------+-----------------------+-------------------------------------------------+
    | Det_ReportError   | Std_Types.h           | Service to report development errors.           |
    +-------------------+-----------------------+-------------------------------------------------+
