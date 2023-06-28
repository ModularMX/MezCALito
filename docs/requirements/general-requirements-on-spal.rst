General Requirements on SPAL
============================

This document specifies general requirements on Basic Software Modules of the following software layers:

- Microcontroller Abstraction Layer
- ECU Abstraction Layer

Those modules are of the following type:

- Drivers for μC-internal and external peripherals
- Handlers
- Interfaces

The selection of modules is derived from the WP Architecture BSW Module List and Layered Architecture. 
The following modules are in scope:

- Memory drivers and interfaces (internal/external EEPROM, Flash, Flash EEPROM Emulation)
- I/O drivers (PORT, ADC, DIO, PWM, ICU, OCU)
- I/O Hardware Abstraction
- ECU onboard communication drivers and handlers (SPI)
- System drivers (internal/external Watchdog, MCU, GPT, RAM test) 

**Constraints**

First scope for specification of requirements on basic software modules are systems
which are not safety relevant. For this reason safety requirements are assigned to
medium priority.

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SRS_SPALGeneral.pdf


4 Conceptual Issues
-------------------

4.1 General Rules
^^^^^^^^^^^^^^^^^

1. Don't do anything within our callbacks that exceeds 50 μs runtime this will affect the system 
   performance too much.
2. Each driver specification is designed so that the driver itself will take care of atomicity and 
   data integrity for data inside of the driver.
3. Application buffers shall be passed as pointers from the user to the driver.

4.2 List of drivers not affected by the clock frequency
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The clock frequency is a parameter that has a very large influence to most of the drivers included 
in WP “Specification / Standardization of BSW”. Below is a list of the software modules that do not 
have a direct dependency on the clock frequency:

- PORT
- DIO
- RAM test

Conclusion: Most of the drivers have a strong dependency of the clock frequency therefore it is very 
important to carefully consider the influence across the whole system when configuring each software 
component.

4.3 MCAL relevant ECU Power Modes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The drivers included in WP “Specification / Standardization of BSW” shall support the ECU power modes 
defined in the Specification of ECU State Manager. Different clock modes have to be supported. All 
drivers shall support re-initialization with different configuration settings. Please refer to the 
document “ECU State Manager”.

4.4 Wake-up Scenarios
^^^^^^^^^^^^^^^^^^^^^

Due to different timing requirements (e.g. ECUs that wake up cyclically and only check some inputs 
and go to sleep again as fast as possible) different initialization procedures are necessary. Examples:

- Initialization after Wake-up
- Initialization after Power On Reset

Conclusion: It is not possible to have a standard wake-up sequence. This sequence depends on the 
microcontroller hardware and the system requirements. Current specified concept allows for a 
standardized way to handle wake-up signaling and offers the possibility to customize the actual 
wake-up sequence


4.5 Scheduling and integration of drivers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Today, 90% of the functions of known ECUs are scheduled cooperatively. Reasons are:

- Technical: Lower overhead (task switch time and task stack consumption) in comparison to pre-emptive 
  systems
- Technical: Better possibility to create a deterministic behavior
- Technical: It is easier to reach stable 95% system load with a cooperative system than with a full 
  pre-emptive
- Historical: Many ECUs are using a cooperative scheduling concept

For this reason, all drivers shall allow to be used within a cooperatively scheduled system. They shall 
not implement blocking code and expect that they are pre-empted by the operating system. Implementation 
hint: use state machines instead of linear code


6 Requirement Specification
---------------------------

6.1 Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^

6.1.1 General Requirements
""""""""""""""""""""""""""

This chapter contains general requirements which apply to all modules of the Microcontroller and ECU 
Abstraction Layers, but not necessarily to Basic Software Modules of other layers.

**6.1.1.1 Configuration**

.. req:: The implementation of all driver modules shall allow the configuration of specific module 
         parameter types at link time
    :id: SRS_SPAL_12263
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12264

    The implementation of all driver modules shall allow the configuration of the following module 
    parameter types at link time:
    
    - values written to hardware registers
    - values used within the driver module (e.g. timings)
    - callback functions

    Those parameters shall be placed in a module external initialization data structure.

    **Rationale:** Delivery of driver modules as object code

    **Use Case:** Internal development models of e.g. SVDO and Hella

    **Supporting Material:** Sophisticated software design techniques are necessary to achieve similar
    scalability and resource efficiency like source code


.. req:: All driver modules shall allow the static configuration of notification mechanism
    :id: SRS_SPAL_12056
    :status: open
    :tags: bsw
    
    All driver modules shall allow the static configuration of notification mechanisms.
    Pointers to callback functions shall not be passed via the API.

    **Rationale:** Flexibility and scalability

    **Use Case:** Give the possibility to run a driver within a protected operating system.
    Callbacks passed by the API and “pointing anywhere” cannot be used within a protected OS.
    MISRA recommends avoiding dynamic pointers to functions.


.. req:: Wakeup sources shall be initialized by MCAL drivers and/or the MCU driver
    :id: SRS_SPAL_12267
    :status: open
    :tags: bsw
    
    Wakeup sources shall be initialized by MCAL drivers and/or the MCU driver.
    Possible wake-up sources are e.g. reset, watchdog, NMI, interrupt etc.

    **Rationale:** Allow the configuration of MCU to wake-up.

    **Use Case:** The GPT interrupt is enabled by the GPT driver and should wake-up the
    MCU from Idle/Sleep/Stop mode


**6.1.1.2 Initialization**

.. req:: All driver modules shall implement an interface for initialization
    :id: SRS_SPAL_12057
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12125

    All driver modules shall implement an interface for initialization. This service shall 
    initialize all module global variables and those SFRs that are used by this module.

    **Rationale:** Basic functionality


.. req:: All driver modules shall implement an interface for initialization
    :id: SRS_SPAL_12125
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12057

    All driver modules shall only initialize the configured resources. Resources that are not 
    configured in the configuration file shall not be touched.

    **Rationale:** Allow integration with complex drivers without resource conflicts.

    **Use Case:** Timer channels 0..3 are used by the GPT driver, timer channels 4..6 are used by 
    complex drivers


.. req:: All driver modules shall implement an interface for de-initialization
    :id: SRS_SPAL_12163
    :status: open
    :tags: bsw

    All driver modules shall implement an interface for de-initialization. This service shall reset 
    all module global variables and all SFRs that are used by this module to their default reset value.
    Values of registers which are not writeable are excluded.

    **Rationale:** Shut down the module. Create the same conditions like before initialization.
    Empty queues


.. req:: Specific rules regarding initialization of controller registers shall apply to all driver 
         implementations
    :id: SRS_SPAL_12461
    :status: open
    :tags: bsw

    The following rules regarding initialization of controller registers shall apply to all driver 
    implementations:

    1. If the hardware allows for only one usage of the register, the driver module implementing that 
       functionality is responsible for initializing the register
    2. If the register can affect several hardware modules and if it is an I/O register it shall be 
       initialized by the PORT driver
    3. If the register can affect several hardware modules and if it is not an I/O register it shall 
       be initialized by the MCU driver
    4. One-time writable registers that require initialization directly after reset shall be initialized 
       by the startup code
    
    **Rationale:** Unambiguous initialization of controller registers, no changes in driver implementation 
    needed for different configurations.

    **Use Case:** 
    
    1. All registers concerning the flash module shall be initialized by the flash driver
    2. I/O Registers that can be used either for CAN, ADC or DIO shall be initialized by the PORT 
       driver
    3. Registers that affect the clock settings of different hardware modules shall be initialized 
       by the MCU driver
    4. Registers affecting the mapping of the register set, RAM or EEPROM shall be initialized in 
       the startup code

    **Supporting Material:** I/O register: Everything that can affect the functionality of a port pin.


.. req:: The register initialization settings shall be published
    :id: SRS_SPAL_12462
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461

    The implementers of the respective driver modules have to publish all register initialization 
    settings in the driver modules documentation.

    **Rationale:** The configurator (human or tool responsible for configuring the software)
    needs to get the register settings of the register that are not initialized directly by the drive


.. req:: The register initialization settings shall be combined and forwarded
    :id: SRS_SPAL_12463
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12461, SRS_SPAL_12462

    The configurator shall combine all initialization settings from different drivers and check them 
    for consistency (dependency and conflict).

    If this check is successful it shall forward those combined settings to the module that is 
    responsible for initializing the hardware.

    If there are any inconsistencies, the configurator has to raise an error and the system build 
    process has to be restarted.

    **Rationale:** Make sure all controller registers are used in a consistent way and all driver
    requirements on register initialization settings are fulfilled.    


.. req:: The modules of the MCAL shall be initialized in a defined sequence
    :id: SRS_SPAL_12068
    :status: open
    :tags: bsw
    
    The modules of the MCAL shall be initialized in the following sequence:
    
    1. disable global interrupts
    2. initialize overall registers (MCAL system module)
    3. initialize all drivers
    4. global interrupts may be enabled

    **Rationale:** Defined initialization sequence without side effects.

    **Use Case:** Power On Reset


.. req:: All drivers of the SPAL that wake up from a wakeup interrupt shall report the wake-up reason
    :id: SRS_SPAL_12069
    :status: open
    :tags: bsw
    
    All drivers of the SPAL that wake up from a wake-up interrupt shall report the wake-up reason 
    to the ECU State Manager via the IO hardware abstraction.

    Notifications come from SPAL-drivers and shall be handled within the IO hardware abstraction 
    module before the wake up reason is sent to the ECU state manager.

    Implementation hint: Usually this notification is done from the ISR of the wake-up.

    **Rationale:** The ECU State Manager needs the wake-up reason. It allows guaranteeing low 
    consumption. For the ICU for instance, it avoids the report of non valid wake-up reasons (spikes).

    **Use Case:** The ISR of the associated wake-up interrupt calls the wake-up report function of 
    the ECU State Manager if wake-up occurs.
    

**6.1.1.3 Normal Operation**


.. req:: All drivers and handlers of the AUTOSAR Basic Software shall implement notification mechanisms 
         of drivers and handlers
    :id: SRS_SPAL_00157
    :status: open
    :tags: bsw
    
    All drivers and handlers of the AUTOSAR Basic Software shall implement the following notification 
    mechanisms (configurable per module) for use within the Basic Software:

    - Polling (by reading a status information)
    - Callback functions
    - Error reporting function of the Default Error Tracer
    - Event reporting function of the Diagnostic Event Manager

    **Rationale:** Flexible integration Avoidance of strong coupling and dependencies

    **Use Case:** The completion of an EEPROM write command can be signaled via a callback function 
    or by setting status information (which is accessible via the module interface).

    A fault occurred during EEPROM writing (cell defective) can be signaled to the Diagnostic Event 
    Manager.


.. req:: All driver modules that provide different operation modes shall provide a service for mode 
         selection
    :id: SRS_SPAL_12169
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12064
    
    All driver modules that provide different operation modes shall provide a service for mode selection.

    This service allows switching from one operation mode to another operation mode without the need 
    of de-initialization and new initialization.

    **Rationale:** Allow operation mode changes where a full de-initialization and a new initialization 
    would cause not desired artifacts.

    **Use Case:** Switch EEPROM driver from normal mode to burst mode


.. req:: All driver modules shall only support raw value mode
    :id: SRS_SPAL_12063
    :status: open
    :tags: bsw
    
    All driver modules shall only support raw value mode. In this mode values passed via the API 
    services are used directly without further scaling.

    **Rationale:** Scaling and adaptation to physical values is task of the ECU Abstraction Layer.

    Raw value mode provides the highest performance.

    **Use Case:** The I/O Hardware Abstraction converts a raw ADC value to a scaled value
    (e.g. voltage) and the other way round


.. req:: All drivers with random streaming capabilities shall use application buffers
    :id: SRS_SPAL_12075
    :status: open
    :tags: bsw
    
    All drivers with random streaming capabilities (memory drivers) shall use application buffers. 
    The caller shall not change the data during job processing of the driver.

    **Rationale:** Minimal RAM consumption, runtime efficiency

    **Use Case:** The EEPROM write service gets a pointer to the source data to be written.
    During EEPROM write operation the driver reads data from the application buffer. The EEPROM 
    driver does not provide an own data buffer.


.. req:: The ISRs shall be responsible for resetting the interrupt flags and calling the according 
         notification function
    :id: SRS_SPAL_12129
    :status: open
    :tags: bsw
    
    The ISRs shall be responsible for resetting the interrupt flags and calling the according 
    notification function.

    **Rationale:** The notification functions can be user defined and therefore not allowed to
    have direct access to hardware.


**6.1.1.4 Fault Operation**

.. req:: All driver modules shall raise an error if the change of the operation mode leads to 
         degradation of running operations
    :id: SRS_SPAL_12064
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12169
    
    All driver modules shall raise an error if the change of the operation mode leads to degradation 
    of running operations. The running operation shall be maintained.

    Further comment: This error condition shall never happen in correct system designs.

    **Use Case:** The SPI EEPROM operation mode is valid during a running SPI communication sequence


.. req:: All driver modules shall have a specific behavior after a development error detection
    :id: SRS_SPAL_12448
    :status: open
    :tags: bsw
    :links: SRS_SPAL_00157
    
    In case of a development error detection, all driver modules shall

    - report the error to the Default Error Tracer (DET)
    - skip the desired functionality (leave service without any action)
    - in case of standard return value return E_NOT_OK
    - in case of arbitrary return values (e.g. Dio_ReadPort) return 0

    **Rationale:** Uniform behavior of all SPAL modules. Avoid processing of wrong API parameters 
    and thus avoid damage to hardware or dangerous system behavior.

    **Use Case:** The development error detection is enabled for a Driver.

    The driver service is called with a faulty input parameter value. The service shall NOT process 
    the command (which might result in a serious malfunction).


**6.1.1.5 Shutdown Operation**

.. req:: All driver modules shall set their wake-up conditions depending on the selected operation
         mode
    :id: SRS_SPAL_12067
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12169
    
    All driver modules shall set their wake-up conditions depending on the selected operation mode.

    **Rationale:** Allow enabling of module specific wake-up interrupts.

    **Use Case:** Example:

    The ECU state manager switches the ECU power mode to ECU_POWERMODE_SLEEP.

    The modules GPT and ICU enable specific wake-up interrupts according to their configuration 
    related to ECU_POWERMODE_SLEEP.


6.2 Non-Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

6.2.1 Timing requirements
"""""""""""""""""""""""""

.. req:: All drivers shall provide a non blocking implementation
    :id: SRS_SPAL_12077
    :status: open
    :tags: bsw
    
    All drivers shall provide a non blocking implementation.

    Note: blocking implementation in this requirement means insensible, uncooperative usage of 
    processor time like long term loops.

    **Rationale:** Avoid undetermined waiting times. Allow all drivers to be used within a cooperatively 
    scheduled system.

    **Use Case:** The waiting loop for the ADC Conversion Ready Flag shall have an additional 
    timeout condition.


6.2.2 Software design requirements
""""""""""""""""""""""""""""""""""

.. req:: The driver's API shall be accessed by its handler or manager
    :id: SRS_SPAL_12092
    :status: open
    :tags: bsw
    
    If a driver is controlled by a handler or a manager, it is not allowed to bypass the handler/
    manager and access the driver's API directly.

    If a driver does not have a handler/manager above, it may be accessed directly.

    **Rationale:** Consistent access. Handlers and Managers shall not be bypassed.

    **Use Case:** The EEPROM driver is controlled exclusively by the NVRAM Manager via the EEPROM 
    Abstraction module and the Memory Abstraction Interface.\

    No other form of access to the EEPROM driver's API shall be allowed.


.. req:: Configuration data shall be kept constant
    :id: SRS_SPAL_12265
    :status: open
    :tags: bsw
    
    The contents of the init structure passed to the module via the init function shall be kept 
    constant and available during runtime.

    Comment: Usually, this init data structure is located in ROM.

    **Rationale:** The module could access this structure at any time.


6.2.3 Process requirements
""""""""""""""""""""""""""

.. req:: Specification of configuration items shall be provided
    :id: SRS_SPAL_12264
    :status: open
    :tags: bsw
    :links: SRS_SPAL_12263
    
    The SWS (software specification) shall specify for each configuration element

    - whether it is configurable before or after compile time
    - where this configuration item is located (init data structure, configuration header file _Cfg.h)

    **Rationale:** Enable correct implementation of configuration parameters that allow for
    object code delivery

