General Requirements on Basic Software Modules
==============================================

The goal of this document is to define a common set of basic requirements that apply to all SW modules 
of the AUTOSAR Basic Software.

These requirements shall be adopted and refined for the specification of Basic SW modules.

The functional requirements defined in this document shall be referenced in each Software 
Specification (SWS) document of the AUTOSAR Basic Software.

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SRS_BSWGeneral.pdf


4.2 Functional Requirements
---------------------------

4.2.1 Configuration
^^^^^^^^^^^^^^^^^^^

.. req:: BSW Modules shall support link-time configuration
    :id: SRS_BSW_00344
    :status: open
    :tags: bsw
    :links: SRS_BSW_00342
    
    Link-time configuration phase shall be supported. Link-time parameters are optional.

    **Rationale:** Allow configurable functionality of modules that are deployed as object code. 
    Usually those modules are drivers


.. req:: BSW Modules shall support post-build configuration
    :id: SRS_BSW_00404
    :status: open
    :tags: bsw
    :links: SRS_BSW_00342
    
    Post-build configuration phase shall be supported. Post-build parameters are optional

    **Rationale:** Change ECU configuration after ECU production without an update of the whole 
    application

    **use Case:** 
    
    Type declaration of the config type

    .. code-block:: c

        typedef struct ComM_ConfigType_Tag { ... }
        ComM_ConfigType;
    
    (in ComM.h)
    
    As a forward declaration use:
    
    .. code-block:: c

        typedef struct ComM_ConfigType_Tag ComM_ConfigType;
        extern void ComM(ComM_ConfigType * ComMConfigPtr);

    (in ComM.h)


.. req:: BSW Modules shall support multiple configuration sets
    :id: SRS_BSW_00405
    :status: open
    :tags: bsw
    :links: SRS_BSW_00342
    
    Modules of the AUTOSAR Basic Software shall be able to operate with more than one configuration 
    set, selectable at start-up time

    **Rationale:** Application of the same software to different cars.


.. req:: BSW Modules shall support pre-compile configuration
    :id: SRS_BSW_00345
    :status: open
    :tags: bsw
    
    Static configuration is decoupled from implementation. Separation of configuration dependent 
    data at compile time furthermore enhances flexibility, readability and reduces version management 
    as no source code is affected


.. req:: All modules of the AUTOSAR Basic Software shall support a tool based configuration
    :id: SRS_BSW_00159
    :status: open
    :tags: bsw
    
    All modules of the AUTOSAR Basic Software shall support a tool based configuration.

    **Rationale:** Integration into AUTOSAR methodology

    **use Case:** The NvM can be automatically configured depending on the NV parameters and their 
    corresponding attributes of the software components.


.. req:: All AUTOSAR Basic Software Modules shall provide configuration rules and constraints to 
         enable plausibility checks
    :id: SRS_BSW_00167
    :status: open
    :tags: bsw
    :links: SRS_BSW_00334
    
    All AUTOSAR Basic Software Modules shall provide configuration rules and constraints to enable 
    plausibility checks of configuration during ECU configuration time where possible.

    **Rationale:** 
    
    - Runtime efficiency: Checks can be made by a configuration tool or the preprocessor instead during
      runtime.
    
    - Safety: Detect wrong or missing configurations as early as possible


.. req:: Optional functionality of a Basic-SW component that is not required in the ECU shall be 
         configurable at pre-compile-time
    :id: SRS_BSW_00171
    :status: open
    :tags: bsw
    
    Optional functionality of a Basic-SW component that is not required in the ECU shall be configurable 
    at pre-compile-time (on/off).

    **Rationale:** Optional functionalities of Basic SW components which are disabled by static 
    configuration shall not consume resources (RAM, ROM, runtime). 
    
    Implementation example: in C language, preprocessing directives can be used.

    Ensure optimal resource consumption. There are many requirements marked with high importance but 
    not all are used in each ECU thus resource overhead must be avoided.

    **Use Cases:**
    
    - The development error detection is a statically configurable optional function that can be 
      enabled and disabled.
    
    - The EEPROM write cycle reduction is a statically configurable optional function that can be 
      enabled and disabled.


.. req:: The AUTOSAR SW Components shall provide information about their dependency from faults, 
         signal qualities, driver demands
    :id: SRS_BSW_00170
    :status: open
    :tags: bsw
    
    AUTOSAR SW-Components may depend on the system fault state or configuration demand of OEM or driver. 
    These reconfiguration dependencies must be provided during ECU configuration time. This information 
    must be used for cross checks and functional evaluation at ECU configuration time and for correct 
    shut down/activation behavior at runtime

    **Rationale:** Resolve the interdependencies between AUTOSAR SW-Components

    **Use Cases:** A fault of the steering angle sensor will lead to reduced function of the related
    AUTOSAR SW-Components. Example:

    - Faults (CAN bus off, sensor defective, calibration data checksum error)
    - Signal quality (lambda sensor not yet in operating temperature range)
    - Driver demands (disable ESP)


.. req:: Configuration parameters being stored in memory shall be placed into separate c-files
    :id: SRS_BSW_00380
    :status: open
    :tags: bsw
    
    Configuration parameters being stored in memory shall be placed into separate c-files (effected 
    parameters are those from link-time configuration as well as those from post-build time configuration).

    **Rationale:** Enable the use of different object files.


.. req:: If a pre-compile time configuration parameter is implemented as const it should be placed 
         into a separate c-file
    :id: SRS_BSW_00419
    :status: open
    :tags: bsw
    
    If a pre-compile time configuration parameter is implemented as const it should be placed into 
    a separate c-file.

    **Rationale:** Enabling of object code integration. Separation of configuration from implementation.


.. req:: The Basic Software Module specifications shall specify which other configuration files 
         from other modules they use at least in the description
    :id: SRS_BSW_00383
    :status: open
    :tags: bsw
    
    The Basic Software Module specifications shall specify which other configuration files from other 
    modules they use at least in the description

    **Rationale:** Resolve compatibility issues


.. req:: The Basic Software Module specifications shall specify at least in the description which 
         other modules they require
    :id: SRS_BSW_00384
    :status: open
    :tags: bsw
    
    The Basic Software Module specifications shall specify at least in the description which other 
    modules (in which versions) they require.

    **Rationale:** Resolve compatibility issues


.. req:: Containers shall be used to group configuration parameters that are defined for the same object 
    :id: SRS_BSW_00388
    :status: open
    :tags: bsw
    
    Containers are used to group configuration parameters that are defined for the same object. 
    Containers are to be defined whenever

    1. Several configuration parameters logically belong together.
    2. Configuration must be repeated with different parameter values for several entities of same 
       type (e.g. the NvM has some parameters that are defined once for the whole module, which are 
       collected in one container, and a set of parameters that are defined once per memory block, 
       which are collected in another container. This second container is included in the first 
       container and will be instantiated once for each memory block)
    3. Containers may contain parameters of different configuration classes. This will not map to 
       the software implementation!

    **Rationale:** Cluster the configuration parameters in order to ease the readability of code

    **Use Case:** Header configuration file with sections for each container


.. req:: Containers shall have names
    :id: SRS_BSW_00389
    :status: open
    :tags: bsw
    
    Containers shall have names - these names will map to section headers in the configuration 
    header-files or configuration c-files containing the parameters

    **Rationale:** Enable referencing to the .XML document


.. req:: Parameter content shall be unique within the module
    :id: SRS_BSW_00390
    :status: open
    :tags: bsw
    
    The same intention, logical contents or semantic shall be placed in one parameter only (There 
    must not be several parameters with the same intention, logical contents or semantic )

    **Rationale:** Avoid multitude identical definitions. Ease the maintenance


.. req:: Parameter content shall be unique within the module
    :id: SRS_BSW_00392
    :status: open
    :tags: bsw
    
    Each Parameter shall have a type. Types shall be based on primitive or, complex types defined 
    within AUTOSAR specifications. I.e. they may be combined to structures, arrays etc.

    Parameters based on a "define" are not required to have an explicit cast to their type, they shall 
    have an appropriate C suffix ("U" if of unsigned integer type, "L" if of integer long type and "F" 
    if of single precision floating type).


.. req:: Parameters shall have a range
    :id: SRS_BSW_00393
    :status: open
    :tags: bsw
    
    Each parameter shall have a list of valid values or the minimum as well as maximum values shall 
    be specified.

    **Use Case:** E.g. the range is used to enable the consistency check by a tool.


.. req:: The Basic Software Module specifications shall specify the scope of the configuration parameters
    :id: SRS_BSW_00394
    :status: open
    :tags: bsw
    
    A parameter may only be applicable for the module it is defined in. In this case, the parameter 
    is marked as "local". Alternatively, the parameter may be shared with other modules (i.e. exported).

    **Rationale:** Increase the uniformity of the use of this attribute and let as single entity 
    (BSW UML model) be the source for import information.

    **Use Case:** Importing and exporting could be achieved in different ways: external reference, 
    redefinition in the other module


.. req:: The Basic Software Module specifications shall list all configuration parameter dependencies
    :id: SRS_BSW_00395
    :status: open
    :tags: bsw
    
    The Basic Software Module specifications must specify, via configuration constraint items, all 
    dependencies to this or other modules configuration parameters. A dependency is for example: 
    the value of another parameter influences or invalidates the setting of this parameter. A 
    dependency shall be documented only once, i.e. if a dependency between two Basic Software
    Modules exists, then the configuration constraint item shall be described only in the Basic 
    Software Module specification containing the influenced configuration parameter


    **Use Case:** Specified parameter "Bit timing register" requires other parameters e.g., "input
    clock frequency" which is defined in another module.


.. req:: The Basic Software Module specifications shall specify the supported configuration classes 
         for changing values and multiplicities for each parameter/container
    :id: SRS_BSW_00396
    :status: open
    :tags: bsw
    
    There are three main configuration classes for changing values (applicable only to parameters) 
    and multiplicities (applicable both to parameters and containers). The Basic Software Module 
    specifications shall specify the classes to be supported per parameter/container. The classes are:
    
    - pre- compile time configuration
    - link time configuration
    - post build time configuration

    **Rationale:** Enable optimizing towards different goals of configuration.


.. req:: The Basic Software Module specifications shall specify for each parameter/container whether 
         it supports different values or multiplicity in different configuration sets
    :id: SRS_BSW_00403
    :status: open
    :tags: bsw
    
    For each container, the module shall be able to specify whether the multiplicity may be different 
    in different configuration sets. For each parameter, the module shall be able to specify whether 
    the multiplicity and/or the value may be different in different configuration sets

    **Rationale:** Enable to specify restrictions that are necessary to optimize the implementation.


.. req:: The configuration parameters in pre-compile time are fixed before compilation starts
    :id: SRS_BSW_00397
    :status: open
    :tags: bsw
    :links: SRS_BSW_00345
    
    The configuration parameters in pre-compile time are fixed before compilation starts. The 
    configuration of the SW element is done at source code level.

    **Rationale:** Ease generation of efficient code.


.. req:: The link-time configuration is achieved on object code basis in the stage after compiling 
         and before linking
    :id: SRS_BSW_00398
    :status: open
    :tags: bsw
    :links: SRS_BSW_00344
    
    The link-time configuration is achieved on object code basis in the stage after compiling and 
    before linking (locating).

    **Rationale:** Concept of configuration to support modules delivered as object code.


.. req:: Parameter-sets shall be located in a separate segment and shall be loaded after the code
    :id: SRS_BSW_00399
    :status: open
    :tags: bsw
    
    Parameter-sets are located in a separate segment and can be loaded after the code. (see definition 
    of post-build time configuration in the AUTOSAR glossary). This means as well the memory layout 
    of ext. conf. parameters must be known.

    This set of parameters may be optimized in a way (configuration is always located at the same 
    address) that the pointer indirection is avoided.

    **Use Case:** Loadable CAN configuration or communication matrix


.. req:: Parameter shall be selected from multiple sets of parameters after code has been loaded and started
    :id: SRS_BSW_00400
    :status: open
    :tags: bsw
    
    Parameter will be selected from multiple sets of parameters after code has been loaded and started. 
    During module startup (initialization) one of several configurations is selected. This configuration 
    is typically a data structure that contains the relevant parameter values

    **Use Case:** Reuse of ECUs.


.. req:: Parameter shall be selected from multiple sets of parameters after code has been loaded and started
    :id: SRS_BSW_00438
    :status: open
    :tags: bsw
    
    In case of post-build configuration, or when one of multiple configuration sets shall be selectable 
    at initialization time, the configuration parameters of a BSW module shall be reachable from a 
    single base structure. The pointer to this structure shall be passed to the Init function of 
    the BSW module

    **Rationale:** 
    
    1. Allow selection of one configuration set in case more than one set is available.
    2. Allow moving of configuration in reprogrammable memory in case post-build configuration is applied.

    **Use Case:** Initialization concept for ComM or CanIf.


.. req:: Each module shall provide version information
    :id: SRS_BSW_00402
    :status: open
    :tags: bsw
    :links: SRS_BSW_00407, SRS_BSW_00318
    
    The provided information shall be included in each module. This information shall include: Vendor 
    and module identification numbers, AUTOSAR release version and software module version.

    **Rationale:** The published information contains data defined by the implementer of the SW module 
    that doesn't change when the module is adapted (i.e. configured) to the actual HW/SW environment 
    it is used in. It thus contains version and manufacturer information to ease the integration of 
    different BSW modules.

    **Use Case:** Initialization concept for ComM or CanIf.


4.2.2 Wake-Up
^^^^^^^^^^^^^

.. req:: Basic Software Modules shall report wake-up reasons
    :id: SRS_BSW_00375
    :status: open
    :tags: bsw
    
    All Basic Software Modules that implement wake-up interrupts shall report the wake-up reason to 
    the ECU State Manager.

    Within this notification the ECU State Manager shall store the passed wake-up ID for later evaluation.

    **Rationale:** Allow ECU State Manager to decide which start-up sequence is chosen based on the 
    wake-up reason.

    **Use Case:** A body ECU can wake-up from 3 different wake-up sources. Depending on the wake-up 
    reason, the ECU

    - blinks the door lock indication LEDs
    - performs a full start-up
    - evaluates the received key ID and decides to start-up and unlock or goto sleep again


4.2.3 Initialization
^^^^^^^^^^^^^^^^^^^^

.. req:: The Basic Software Module shall be able to initialize variables and hardware in a separate 
         initialization function
    :id: SRS_BSW_00101
    :status: open
    :tags: bsw
    :links: SRS_BSW_00358, SRS_BSW_00414, SRS_BSW_00406
    
    If a Basic Software Module needs to initialize variables and hardware resources, this should be 
    done in a separate initialization function. This function shall be named `<Module name>_Init()`. 
    This function shall only be called by the BswM or EcuM

    **Rationale:** Interface to EcuM


.. req:: The sequence of modules to be initialized shall be configurable
    :id: SRS_BSW_00416
    :status: open
    :tags: bsw
    :links: SRS_BSW_00406
    
    The sequence of modules to be initialized shall be configurable.

    **Rationale:** To enable the handling of dependencies of Basic SW-modules with the respect to 
    environment, implementation and proprietary functionality the start-up sequence needs to be 
    adaptable

    **use Case:** Start-up sequence is a proprietary functionality. Det dependency shall allow error 
    detection during development.


.. req:: A static status variable denoting if a BSW module is initialized shall be initialized with 
         value 0 before any APIs of the BSW module is called
    :id: SRS_BSW_00406
    :status: open
    :tags: bsw
    :links: SRS_BSW_00407, SRS_BSW_00369, SRS_BSW_00450
    
    If the Default Error Tracer (Det) Error is enabled, module APIs shall check if the module is 
    initialized.

    If the Module is not initialized and Default Error Tracer (Det) is enabled, then the Module shall 
    report respective error to Det.

    Module Initialization and initialization check shall not be performed for
    
    - Init Functions itself
    - Version Check API, because it shall not need module initialization for returning a hard coded 
      value
    - Libraries, because they are generally stateless.
    - BSW Main functions. Reason: They return immediately without performing any functionality when 
      the module is not initialized.
    - If Det not initialized before reporting functions, it shall return immediately without any 
      other action.

    **Rationale:** Wrong control flows shall be detected (and happen only) during integration
    phase. Therefore Det must be called and stop execution if an uninitialized module is called.

    **use Case:** During optimization of init phase for fast startup, wrong init order has been
    configured and needs correction


.. req:: The init/deinit services shall only be called by BswM or Ecu M 
    :id: SRS_BSW_00467
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101
    
    The init/deinit services shall only be called by BswM or EcuM

    **Rationale:** The module does not need to protect itself against untimely calls


.. req:: Memory mapping shall provide the possibility to define RAM segments which are not to be 
         initialized during startup
    :id: SRS_BSW_00437
    :status: open
    :tags: bsw
    
    Memory mapping shall provide the possibility to define RAM segments which are not to be initialized 
    during startup (NoInit-Area).

    This shall be achieved by using/modifying linker and C startup routines.

    **Rationale:** There should be an area in the RAM, which will not be affected by a reset (clearing 
    all memory). This area is used as storage for persistent data which are needed during normal 
    operation (and that will not be stored in EEPROM).

    **Use case:** Reset information is stored in RAM and has to be evaluated after reset.


4.2.4 Normal Operation
^^^^^^^^^^^^^^^^^^^^^^

.. req:: MSW components shall be tested by a function defined in a common API in the Basis-SW
    :id: SRS_BSW_00168
    :status: open
    :tags: bsw
    
    If a SW component above or below RTE has the requirement to be tested by external devices e.g. 
    in the garage, the required function shall be accessed via a common API from diagnostics 
    services in Basic-SW (function, data interface).

    **Rationale:** Ensure less difference in handling and kind of API

    **Use case:** Tester in the garage requires calibration of a certain SW-component e.g. steering 
    angle sensor monitoring in the ESP. The interface must remain to be ready for moving this 
    SW-component.

    This interface can also be used by XCP


.. req:: Each BSW module shall provide a function to read out the version information of a dedicated 
         module implementation
    :id: SRS_BSW_00407
    :status: open
    :tags: bsw
    :links: SRS_BSW_00318, SRS_BSW_00374, SRS_BSW_00411, SRS_BSW_00406
    
    Each BSW module shall provide a function to read out the version information of a dedicated module 
    implementation.

    This API shall be pre-compile time configurable (see [SRS_BSW_00411]).

    It shall be possible to call this function at any time (e.g. before the init function is called).

    **Rationale:** If problems are detected within an ECU during lifetime this enables the garage
    to check the version of the modules.

    The AUTOSAR specification version number is checked during compile time (see [SRS_BSW_00004]) 
    and therefore not required in this API.

    **Use case:** With this API the garage can read out version information which is implemented
    in a dedicated (erroneous) ECU to enable the decision whether a software update might be sufficient, 
    or not.


.. req:: BSW modules with AUTOSAR interfaces shall be describable with the means of the SW-C Template
    :id: SRS_BSW_00423
    :status: open
    :tags: bsw
    
    BSW modules with AUTOSAR interfaces shall be describable with the means of the SW-C Template. 
    The BSW description template shall therefore inherit the concepts of the SW-C Template for 
    those BSW modules

    **Rationale:** AUTOSAR Services are located in the BSW, but have to interact with AUTOSAR SW-Cs 
    (above the RTE) via ports. Therefore the RTE generator shall be able to read the input and shall 
    be able to generate proper RTE

    **Use case:** 
    
    - SW-Cs use the service(s) related to the NvM_Read C-API of the NvM
    - SW-Cs use services of the EcuM in order to request or release the run mode


.. req:: BSW module main processing functions shall not be allowed to enter a wait state
    :id: SRS_BSW_00424
    :status: open
    :tags: bsw
    
    BSW module main processing functions are not allowed to enter a wait state because the function 
    must be able to be allocated to a basic task. (see extended and basic task according to AUTOSAR 
    OS classification).

    **Rationale:** Typically, basic tasks are more efficient then extended tasks. Enables schedule 
    ability analysis and predictability.

    **Use case:** Enabling schedule ability analysis of the ECU.


.. req:: The BSW module description template shall provide means to model the defined trigger 
         conditions of schedulable objects
    :id: SRS_BSW_00425
    :status: open
    :tags: bsw
    
    The BSW module description template shall provide means to model the following trigger conditions 
    of schedulable objects:

    - Cyclic timings (fixed and selectable during runtime)
    - Sporadic events

    **Rationale:** The model of the timing behavior of a BSW module can serve for the purpose of 
    documentation and integration → supports the design of the schedule module.


.. req:: BSW Modules shall ensure data consistency of data which is shared between BSW modules
    :id: SRS_BSW_00426
    :status: open
    :tags: bsw
    
    BSW Modules shall ensure data consistency of data which is shared between BSW modules.

    There are two possible scenarios.

    Scenario 1: the data is defined and managed within one BSW Module. In this case, Exclusive Areas 
    shall be defined and documented in the BSW module description template of the managing module 
    and used in the implementation. The exclusive areas shall be defined with a name and the accessing 
    main functions, API services, callback functions and ISR functions.

    Scenario 2: the data is not managed by a BSW Module. This is only possible in case of special 
    hardware resources like registers. In this case, the accessing modules need to disable and enable 
    interrupts to ensure data consistency
    
    **Rationale:** To allow priority determination for preventing simultaneous access to shared resources.

    **Use Cases:** Stop interrupt handler from corrupting a data buffer in Com due to simultaneous 
    access via the RTE


.. req:: ISR functions shall be defined and documented in the BSW module description template
    :id: SRS_BSW_00427
    :status: open
    :tags: bsw
    
    ISR functions shall be defined and documented in the BSW module description template.

    The ISR functions shall be defined with a name and the category according to the AUTOSAR OS.

    In case of the intention to support memory protection a BSW module implementation shall at least 
    support interrupt category 2.
    
    **Rationale:** Determination of locking scheme for a particular exclusive area.

    **Use Cases:** Stop interrupt handler from corrupting a data buffer in Com due to simultaneous 
    access via the RTE.


.. req:: A BSW module shall state if its main processing function(s) has to be executed in a specific 
         order or sequence
    :id: SRS_BSW_00428
    :status: open
    :tags: bsw
    
    A BSW module shall state if its main processing function(s) has to be executed in a specific 
    order or sequence with respect to other BSW main processing function(s).
    
    **Rationale:** Improved integration of BSW modules.

    **Use Cases:** Improved efficiency in the COM stack by ensuring receive and transmit call sequence.


.. req:: Access to OS is restricted
    :id: SRS_BSW_00429
    :status: open
    :tags: bsw
    
    BSW modules shall only be allowed to use certain OS services. The services and their access shall 
    be defined in SWS_BSW_General
    
    **Rationale:** Simplification of the OS integration of BSW modules

    **Use Cases:** Integration of different BSW modules in one ECU.


.. req:: Modules should have separate main processing functions for read/receive and write/transmit 
         data path
    :id: SRS_BSW_00432
    :status: open
    :tags: bsw
    :links: SRS_BSW_00373
    
    Modules which propagate data up (read, receive) or down (write, transmit) through the different 
    layers of the BSW should have separate main processing functions for the read/receive and write/
    transmit data path.
    
    **Rationale:** Enables efficient scheduling of the main processing functions in a more specific 
    order to reduce execution time and latency

    **Use Cases:** 
    
    .. code-block:: xml
    
        TASK(BSW_Scheduler_Communications) {
            ...
            CanIf_MainFunction_Receive();
            Com_MainFunction_Receive();
            Com_MainFunction_Transmit();
            CanIf_MainFunction_Transmit();
            ...
        }


.. req:: Main processing functions are only allowed to be called from task bodies provided by the 
         BSW Scheduler
    :id: SRS_BSW_00433
    :status: open
    :tags: bsw
    
    Main processing functions are only allowed to be called from task bodies provided by the BSW 
    Scheduler
    
    **Rationale:** Indirect and in-transparent timing dependencies between BSW modules shall
    be prohibited.


.. req:: A Main function of a un-initialized module shall return immediately 
    :id: SRS_BSW_00450
    :status: open
    :tags: bsw
    
    If a Main function of an un-initialized module is called, then it shall return immediately without 
    performing any functionality and without raising any errors.
    
    **Rationale:** Main Function processing of an un-initialized Module may result in undesired and 
    non defined behaviour.


.. req:: Modules called by generic modules shall satisfy all interfaces requested by the generic module
    :id: SRS_BSW_00461
    :status: open
    :tags: bsw
    
    If a generic module (e.g. PduR) requests an interface from an surrounding module, the surrounding 
    module shall offer the interface, unless a configuration parameter exists which suppresses calling 
    the interface.

    In case the respective module does not support the functionality of the interface, the module shall 
    supply an empty function.
    
    **Rationale:** Keep generic modules independent of specification of surrounding Modules.

    **Uase Cases:** Generic NM interface, ComM etc. need no adaptation to specific modules and CDDs


.. req:: Hardware registers shall be protected if concurrent access to these registers occur
    :id: SRS_BSW_00451
    :status: open
    :tags: bsw
    
    In all cases where concurrent access to hardware registers may occur, the caller has to protect 
    manipulation of such registers by disabling interrupts and using read-modify-write functions, 
    unless there is specific hardware support (e.g. atomic instructions) which makes such precautions 
    unnecessary.
    
    **Rationale:** The respective implementation restriction in the SWS General guarantees system 
    consistency with no influence on system functionality. It only applies to BSW modules with direct 
    access to hardware registers

    **Uase Cases:** CompletionOfCDD concept


.. req:: Timing limits of main functions
    :id: SRS_BSW_00478
    :status: open
    :tags: bsw
    
    Basic Software Modules which require a periodic main function shall allow to configure the period 
    time between (0..∞) seconds.
    
    **Rationale:** It should be avoided to standardize different upper limits for main functions. 
    Therefore the upper limit should be open (∞). Also the lower number should exclude 0, since 
    this value does not make sense. An implementation may restrict the upper limit to a reasonable 
    time, but the specifications should not be limited. The lower limit is typically given by the 
    used implementation and hardware.

    **Uase Cases:** Avoid fragmentation of different main functions caused by different upper limits


4.2.5 Shutdown Operation
^^^^^^^^^^^^^^^^^^^^^^^^


.. req:: Basic SW module shall be able to shutdown
    :id: SRS_BSW_00336
    :status: open
    :tags: bsw
    
    If a Basic SW module needs to shutdown functionality (e.g. release hardware resources), this shall 
    be done in a separate API function.
    
    **Rationale:** Interface to EcuM


4.2.6 Fault Operation and Error Detection
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


.. req:: Classification of development errors
    :id: SRS_BSW_00337
    :status: open
    :tags: bsw
    :links: SRS_BSW_00350
    
    All AUTOSAR Basic Software Modules shall report development relevant errors if development error 
    detection is enabled:

    - Errors caused by software bugs
    - Errors caused by incorrect integration by the user
    - Errors caused by invalid configuration
    - Errors caused by bugs in the integration tools

    Development errors are handled like assertions: After calling the configured Det_ReportError hooks, 
    the normal control flow of execution shall not be continued. Det shall stop execution of the entire 
    process.

    This can be done for example with an endless loop or a halt statement or by creating something like 
    an exception stack trace. If there is only one hook function configured, this might also do the 
    exception handling and stop execution

    **Rationale:** Extended error detection for debugging and especially integration.

    **Use Case:** The EEPROM driver provides internal checking of API parameters which is only activated 
    for the first software integration test (development build) and disabled afterwards (deployment build)


.. req:: All AUTOSAR Basic Software Modules shall not return specific development error codes via the API
    :id: SRS_BSW_00369
    :status: open
    :tags: bsw
    :links: SRS_BSW_00337, SRS_BSW_00327, SRS_BSW_00357
    
    All AUTOSAR Basic Software Modules shall not return specific development error codes via the API. 
    In case of a detected development error, the error shall only be reported to the Det

    **Rationale:** The production version of a module shall have a limited number of return values.


.. req:: Reporting of production relevant error status
    :id: SRS_BSW_00339
    :status: open
    :tags: bsw

    .. @todo :links: RS_BSWMD_00069, SRS_Diag_04063
    
    AUTOSAR Basic Software Modules shall report all production errors and extended production errors 
    to the Dem (Diagnostic Event Manager)

    **Rationale:** 
    
    - Central configuration and handling of error events instead of
    - spreading the handling all over the Basic Software.
    - Common reporting to the lamps
    - Common reporting to the garage
    - Centralized fail-safe reactions through FiM

    **Use Cases:** Error events like (e.g CANSM_E_BUS_OFF) are reported to the Dem


.. req:: Pre-de-bouncing of error status information is done within the Dem
    :id: SRS_BSW_00422
    :status: open
    :tags: bsw
    :links: SRS_BSW_00339
    
    Pre-de-bouncing of error status information reported via `Dem_SetEventStatus`` is done within 
    the Dem.

    Pre-de-bouncing is handled inside the Diagnostic Event Manager using AUTOSAR predefined generic 
    signal de-bouncing libraries.

    The Diagnostic Event Manager shall define the interface to the libraries. By defining the interface 
    it is possible for the user to implement further extensions for more complex pre-de-bouncing algorithms.

    **Rationale:** Central configuration and handling of error events instead of spreading the handling 
    all over the Basic Software

    **Use Cases:** Figure 4.1 shows only one of several possible use cases (error detected and notified). 
    The timer function shall be provided (in this example) in the pre-de-bouncing library of the 
    Diagnostic Event Manager

    .. image:: img/general-requirements-on-basic-software-modules-fig4.1.png


.. req:: Software which is not part of the SW-C shall report error events only after the Dem is fully 
         operational
    :id: SRS_BSW_00417
    :status: open
    :tags: bsw
    
    Software which is not part of the SW-C shall report error events only after the Dem is fully 
    operational.

    **Rationale:** It is only possible to store errors in error memory after the Dem is fully 
    operational. To simplify error handling within Dem (and to gain efficiency) this requirement 
    is needed.

    **Use Cases:** Reporting of non plausible sensor values.


.. req:: All AUTOSAR Basic Software Modules shall check passed API parameters for validity
    :id: SRS_BSW_00323
    :status: open
    :tags: bsw
    :links: SRS_BSW_00350, SRS_BSW_00327
    
    All AUTOSAR Basic Software Modules shall check passed API parameters for validity. The (minimum) 
    conditions if a parameter needs to be treated as invalid shall be described for each parameter 
    (e.g. check of reserved values).

    This checking shall be statically configurable (ON/OFF) per module with one single preprocessor 
    switch

    **Rationale:** Ease of debugging for development, efficient code for deployment.

    **Use Cases:** The EEPROM driver provides internal checking of API parameters which is only 
    activated for the first software integration test ('development build') and disabled afterwards 
    ('deployment build').


.. req:: All Basic SW Modules shall perform a pre-processor check of the versions of all imported 
         include files
    :id: SRS_BSW_00004
    :status: open
    :tags: bsw
    :links: SRS_BSW_00003, SRS_BSW_00318, SRS_BSW_00402
    
    All Basic SW Modules shall perform a pre-processor check of the versions of all imported include 
    files (Inter Module Checks).

    **Rationale:** Compatibility enforcement, error avoidance, ease of integration

    **Use Cases:** The integration of incompatible imported files shall be avoided. 
    
    The version numbers of all modules shall be listed in the Basic Software Description Template. 
    During configuration a tool shall check whether the version numbers of all integrated modules 
    belong to the same AUTOSAR major and minor release (same baseline). If not an error shall be 
    reported.

    For the update of Basic Software Modules, version conflicts shall be detected. 
    
    Example: For included files from other modules, the AUTOSAR MAJOR and MINOR Release Version shall 
    be verified. I.e. Can.c includes Dem.h: Only MAJOR and MINOR Release versions shall be verified.


.. req:: All production code error ID symbols are defined by the Dem module and shall be retrieved 
         by the other BSW modules from Dem configuration
    :id: SRS_BSW_00409
    :status: open
    :tags: bsw
    
    All production code error ID symbols are defined by the Dem module and shall be retrieved by the 
    other BSW modules from Dem configuration.

    **Rationale:** The error codes shall be defined in a central file, to simplify the include structure 
    of the Dem.


.. req:: List possible error notifications
    :id: SRS_BSW_00385
    :status: open
    :tags: bsw
    
    The BSW shall document all production errors, extended production errors, development errors, 
    runtime errors and transient faults which are supported by the BSW module.

    **Rationale:** Documentation, overview of errors
    

.. req:: The BSW shall specify the configuration and conditions for detecting an error
    :id: SRS_BSW_00386
    :status: open
    :tags: bsw
    
    The BSW shall specify the configuration for detecting an error. This configuration shall describe 
    criteria and limits how the error is detected and possibly reset. This is applicable for production 
    errors and extended production errors as well as for development errors.

    The BSW shall specify the conditions when the error is detected, this applies to all error types.

    **Use Cases:** 
    
    - configuration of debounce counters (counting up/down), configuration of limits of these debounce 
      counters etc.,
    - specify the library function which is to be used to debounce.
    - specify whether the Diagnostic modules may request to delete errors. If so, specify how and when 
      errors may be reset


.. req:: Classification of runtime errors
    :id: SRS_BSW_00452
    :status: open
    :tags: bsw
    
    AUTOSAR Basic Software Modules may report runtime errors.

    Runtime errors are systematic faults that do not necessarily affect the overall system behavior 
    (e.g. wrong PDU-Ids, wrong post-build configurations).

    Runtime errors are not implementation errors; they will not cause assertions and therefore not 
    cause the abortion of the 'normal' control flow of execution (as Det will do).

    Runtime errors shall only be reported as an event in case of the occurrence (have set conditions 
    only). In contrast to production errors, there is no reset conditions reported to an error handler.

    An error handler of runtime errors is executed synchronously and may only store the corresponding 
    events to a memory, may call Dem and may execute any reasonable action.

    **Rationale:** Catch sporadic error events caused by seldom occurring systematic faults.

    **Use Cases:** `CANNM_E_NET_START_IND`` Reception of NM PDUs in Bus-Sleep Mode


.. req:: Classification of production errors
    :id: SRS_BSW_00458
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall report a production error if this error is caused by any 
    hardware problem, e.g., aging, deterioration, total hardware failure, bad production quality, 
    incorrect assembly, etc.

    - and the same root cause is not detected as a production error by any other BSW module (usually, 
      but not necessarily closer to the hardware)
    - and if at least one of the following criteria is met:
        * The error leads to an increase of emissions and must be detected to fulfill applicable 
          regulations.
        * The error limits the capability of any other OBD relevant diagnostic monitors.
        * The error requires limp-home reactions, e.g. to prevent further damage to the hardware; or 
          customer perceivable properties.
        * The garage shall be pointed to the failed component for repair actions.

    Production errors shall be defined in a granularity of standardized diagnostics trouble codes 
    (e.g., SAE J2012), if possible.

    Note: Production errors are regular operation of the software, but not of the system. It is not 
    any kind of exception handling. Software bugs or software misbehavior are no production errors.

    **Rationale:** Report errors that are useful in the field.

    **Use Cases:** Flash is no longer writable due to aging, emission relevant adaptation maps
    can no longer be stored. The control unit must be replaced

    **Dependencies:** If not specified by AUTOSAR, the real classification of a particular error beeing
    a production error or an extended production error may be selectable by configuration. Dependent 
    of this classification the particular error may cause different reactions within the Dem.


.. req:: Classification of extended production errors
    :id: SRS_BSW_00466
    :status: open
    :tags: bsw
    
    AUTOSAR Basic Software Modules may report extended production errors (to the module Dem) if this 
    error is caused
    
    - by any hardware problem of the ECU itself, e.g., a memory transactions failed,
    - by a misbehavior of the embedding environment, e.g., the loss of messages due to any problem 
      of the communication channel

    AND

    - this error does not comply to any criteria of the production error definition, notably
        * OBD relevance
        * direct limp-home reactions
        * direct repair actions in the garage
    - the error cause is already covered by any other production error

    Extended production errors shall define set and reset conditions.

    Note: Extended production errors are regular operation of the software, but not of the system. 
    It is not any kind of exception handling. Software bugs or software misbehavior are no 'Extended 
    production errors'.

    Note: Extended production errors may not be entered in the primary event memory of the module Dem.

    **Rationale:** Extended production errors may be used

    - to deduce 'real' production errors by tying several values influencing the state of the ECU together
    - to gain more detailed information of the real cause of a production error

    **Dependencies:** If not specified by AUTOSAR, the real classification of a particular error being
    a production error or an extended production error may be selectable by configuration. Dependent 
    of this classification the particular error may cause different reactions within the Dem.


.. req:: Classification of security events
    :id: SRS_BSW_00488
    :status: draft
    :tags: bsw
    
    AUTOSAR Basic Software Modules and SWCs may report security events to the module IdsM. A security 
    event is the identified occurrence of an onboard system, service or network state indicating a 
    possible breach of information security policy or failure of controls, or a previously unknown 
    situation that can be security relevant.

    Note: security events are not any kind of exception handling. Software bugs or software misbehavior 
    are no security events.

    **Rationale:** Security events may be used to support off-board analysis of security incidents
    as part of an incident reponse process


.. req:: Reporting of security events
    :id: SRS_BSW_00489
    :status: draft
    :tags: bsw
    
    AUTOSAR Basic Software Modules shall report the configured security events to the IdsM (Intrusion 
    Detection System Manager).

    **Rationale:** Central configuration and handling of security events instead of spreading the
    handling all over the Basic Software

    **Use Cases:** Security events like the reception of unauthentic PDUs are reported to the IdsM


.. req:: List possible security events
    :id: SRS_BSW_00490
    :status: draft
    :tags: bsw
    
    The BSW shall document security events which are supported by the BSW module in a section "Security 
    events".

    Each security event shall be documented by a "Security Event Short Name", e.g. 
    "KEYM_SEV_INSTALL_ROOT_CERT_FAILED", and a "Security Event Description", e.g. "Attempt to install or 
    update a root certificate has failed".

    **Rationale:** Documentation, overview of security events


.. req:: Specification of trigger conditions and context data
    :id: SRS_BSW_00491
    :status: draft
    :tags: bsw
    
    The BSW module shall specify the trigger conditions and context data for each reported security 
    event

    **Rationale:** Trigger conditions specify which situations lead to the reporting of a security 
    event. The context data specifies which data is reported by the BSW module if the security event 
    is triggered.


.. req:: Reporting of security events during startup
    :id: SRS_BSW_00492
    :status: draft
    :tags: bsw
    
    Software which is not part of a SW-C shall report security events only after the IdsM is fully 
    operational.

    **Rationale:** It is only possible to process security events after the IdsM is fully operational. 
    To simplify error handling within IdsM (and to gain efficiency) this requirement is needed.

    **Use Cases:** Reporting of security events during ECU startup


.. req:: Definition of security event ID symbols
    :id: SRS_BSW_00493
    :status: draft
    :tags: bsw
    
    All security event ID symbols are defined by the IdsM module and shall be retrieved by the other 
    BSW modules from IdsM configuration

    **Rationale:** The security ID symbols shall be defined in a central file, to simplify the include
    structure of the IdsM.


.. req:: Fault detection and healing of production errors and extended production errors
    :id: SRS_BSW_00469
    :status: open
    :tags: bsw
    
    The detection of production errors and extended production errors shall distinguish between fault 
    detection, failure free detection, and undecided state. Only detected faults and explicitly failure 
    free detected states shall be reported.

    **Rationale:** 
    
    - Avoid incorrect healing in case a failure still persists: Do not heal the OBD pending/confirmed 
      state unless the vehicle is failure free.
    - Allow the system to heal if the repair is executed without using a garage tool to clear the error.
    - Heal only if the system is known to work, not in the absense of detected failures, i.e., ensure 
      the correct computation of the OBD readiness information.

    **Use Cases:** The driver re-connects a disconnected sensor, and the system is again working properly, 
    and the production error is healed.


.. req:: Execution frequency of production error detection
    :id: SRS_BSW_00470
    :status: open
    :tags: bsw
    
    State information are detected either by the change of the state or when checked (event-based 
    or cyclic).

    Checks shall be executed as often as possible, at least once per related monitoring cycle (e.g. 
    OBD driving cycle for emission relevant systems), or as often as required by applicable regulations, 
    to the extend feasible.

    **Rationale:** 
    
    - Timely detection of failures
    - Readiness / self-healing in case failures are absent
    - Ensure correct behavior of event handling during the enableconditions are not fulfilled (if 
      enable-conditions are handled in Dem).

    **Use Cases:** If a monitor is required to be continuous according to the regulations (CCR1968-2) 
    the execution cycle shall be at least 2 times per second.


.. req:: Do not cause dead-locks on detection of production errors the ability to heal from previously 
         detected production errors
    :id: SRS_BSW_00471
    :status: open
    :tags: bsw
    
    Production errors shall be able to heal, if a problem no longer persists.

    **Rationale:** Detected production errors may cause fail-safe / limp-home modes, usually through 
    the FiM. During such operation, the detection algorithm may be disabled, preventing the error 
    from healing. Therefore, care must be taken to avoid this situation or provide a means of healing, 
    e.g., by starting without fail-safe / limp-home modes in the next operating cycle.

    **Use Cases:** A component is detected as faulty and the error is reported to the Dem. As a
    consequence, the component is disabled and no further fault or fault free detection is possible. 
    At the next operation cycle, the component is re-tested, and passes the tests, PASS is reported 
    to the Dem


.. req:: Avoid detection of two production errors with the same root cause
    :id: SRS_BSW_00472
    :status: open
    :tags: bsw
    
    Some production errors detect the same root cause as failure. To avoid duplicate error reports 
    to the garage, detection of one error shall be disabled in case of the the other error, by a 
    appropriate configuration of the FiM. Hence, the production error shall only be enabled when a 
    permission is granted

    **Rationale:** The garage will analyze all DTCs (resulting from production errors), possibly
    causing unnecessary repair operations if there was only one root cause.

    **Use Cases:** This situation shall be avoided: 
    
    The garage reads out two production error trouble codes, one pointing to a disconnected wiring 
    harness, and the other to a broken control unit. The control unit is detected as broken due to 
    the disconnected wiring harness. The garage replaces both the control unit and the wiring harness, 
    causing unnecessary repair cost.


.. req:: Classification of transient faults
    :id: SRS_BSW_00473
    :status: open
    :tags: bsw
    
    AUTOSAR Basic Software Modules may report transient faults.

    Transient faults occur in the hardware due to particle passages or thermal noise for instance and 
    may cause software issues. The handling of those transient faults may require use case dependent 
    action that cannot be reasonably decided by the detecting BSW module (most probably drivers) themselves.

    Transient faults are not implementation errors; they will not cause assertions and therefore even 
    not necessarily cause the abortion of the 'normal' control flow of execution (as Det will do). 
    They may heal in a sense that they disappear again or get masked or get corrected by software activity.

    Monitors of transient errors (if any) shall stay in production code (deployment build).

    Transient faults shall only be reported as an event in case of the occurrence (have set conditions 
    only). In contrast to production errors, there is no reset conditions reported to an error handler.

    An error handler of transient faults handles the corresponding transient faults in a synchronous manner.

    **Rationale:** Catch sporadic error events caused by transient hardware faults

    **Use Cases:** 
    
    - CAN controller goes offline due to bit-flip in its control register.
    - Peripheral action lasts accidentally longer than expected (and specified)


4.3 Non-Functional Requirements (Qualities)
-------------------------------------------

4.3.1 Software Architecture Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: The AUTOSAR Basic Software shall provide a microcontroller abstraction layer which provides 
         a standardized interface to higher software layers
    :id: SRS_BSW_00161
    :status: open
    :tags: bsw
    
    The AUTOSAR Basic Software shall provide a microcontroller abstraction layer which provides a 
    standardized interface to higher software layers.

    **Rationale:** Portability and reusability.

    Encapsulate implementation details of a specific microcontroller from higher software layers

    **Use Cases:** Exchange microcontroller ST10 with STAR12 without affecting higher software
    layers interfacing with the microcontroller abstraction layer.


.. req:: The AUTOSAR Basic Software shall provide a hardware abstraction layer
    :id: SRS_BSW_00162
    :status: open
    :tags: bsw
    
    The AUTOSAR Basic Software shall provide a hardware abstraction layer which provides a stable 
    interface to higher software layers which is independent from the ECU hardware layout.

    **Rationale:** Keep the impact of changes in the ECU hardware layout as small as possible.
    Portability and reusability of modules of higher software layers. Flexibility for changes in the 
    ECU hardware layout.

    **Use Cases:** 
    
    - Change the hardware layout of the ECU (e.g. PortA.5 → PortD.7) without affecting 
      software layers interfacing with the hardware abstraction layer.
    - Use the NvM with an internal and/or external EEPROM.
    - Provide uniform access to analog signals using the on-chip ADC or an external ADC ASIC.


.. req:: Modules of the µC Abstraction Layer (MCAL) may not have hard coded horizontal interfaces
    :id: SRS_BSW_00005
    :status: open
    :tags: bsw
    
    Modules of the µC Abstraction Layer (MCAL) may not have hard coded horizontal interfaces.

    Necessary interactions (e.g. GPT triggered ADC conversion) shall be implemented by using statically 
    configurable notifications (callbacks)

    **Rationale:** Avoidance of strong coupling, ease of integration, better structure


.. req:: Interfaces which are provided exclusively for one module shall be separated into a dedicated 
         header file
    :id: SRS_BSW_00415
    :status: open
    :tags: bsw
    :links: SRS_BSW_00346
    
    Interfaces and the corresponding types which are provided exclusively for one module should be 
    separated into a dedicated header file. This should prevent the inclusion of the <ModuleName>.h 
    file.

    The format of the file name shall be: <ModuleName>_<User>.h

    Comment: Common definitions for different interfaces (e.g. types) shall be defined in a common header 
    file (e.g. <Module Name>.h).

    **Rationale:** Encapsulate an interface between modules in an include file

    **Use Cases:** Example: CanIf_Pdur.h, CanIf_Nm.h

    **Supporting Material:** < Module name > shall be derived from "List of Basic Software Modules", [7]
    (2. . . 8 characters). <User> shall be the user module from the same list



4.3.2 Software Integration Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: The Implementation of interrupt service routines shall be done by the Operating System, 
         complex drivers or modules
    :id: SRS_BSW_00164
    :status: open
    :tags: bsw
    
    Only the Operating System, complex drivers and modules of the microcontroller abstraction layer 
    are allowed to implement interrupt service routines.

    If a transition from an interrupt service routine to an operating system task is needed, it shall 
    take place at the lowest level possible of the Basic Software.

    In the case of CAT2 ISRs this shall be at the latest in the RTE.

    In the case of CAT1 ISRs this shall be at the latest in the Interface layer.

    This means: no interrupts on application level.

    **Rationale:** Portability and reusability.
    
    The implementation of interrupt service routines is highly microcontroller dependent.

    **Use Cases:** Exchange microcontroller ST10 with STAR12 without affecting higher software
    layers.


.. req:: The runtime of interrupt service routines and functions that are running in interrupt context 
         shall be kept short
    :id: SRS_BSW_00325
    :status: open
    :tags: bsw
    :links: SRS_BSW_00333

    The runtime of interrupt service routines and functions that are running in interrupt context should 
    be kept short.

    Where an interrupt service routine is likely to take a long time, an operating system task should 
    be used instead

    **Rationale:** Real time behavior, avoid blocking of the whole system.

    **Use Cases:** An ISR calls a callback which is calling other callbacks


.. req:: It shall be possible to create an AUTOSAR ECU out of modules provided as source code and 
         modules provided as object code, even mixed
    :id: SRS_BSW_00342
    :status: open
    :tags: bsw
    :links: SRS_BSW_00344

    It shall be possible to create an AUTOSAR ECU out of modules provided as source code and modules 
    provided as object code, even mixed.

    Allow both:

    - IP protection and guaranteed test coverage : object code
    - High efficiency and configurability at ECU configuration time (by integrator) : source code

    **Rationale:** Some simple drivers could be provided as object code. More complex and configurable 
    modules could be provided as source code or even generated code.


.. req:: The unit of time for specification and configuration of Basic SW modules shall be preferably 
         in physical time unit
    :id: SRS_BSW_00343
    :status: open
    :tags: bsw
    
    The unit of time for specification and configuration of Basic SW modules shall be preferably in 
    physical time unit, not ticks.

    Nevertheless for some module "tick" parameters are accepted

    **Rationale:** The duration of a "tick" varies from system to system

    **Use Cases:** The software specification defines the unit (e.g. µs, s) and software configuration 
    uses these units.

    OS Modules require time parameter values in ticks.


.. req:: Configuration files of AUTOSAR Basic SW module shall be readable for human beings
    :id: SRS_BSW_00160
    :status: open
    :tags: bsw
    
    Files holding configuration data for AUTOSAR Basic SW modules shall have a format that is readable 
    and understandable by human beings.

    **Rationale:** Plausibility checking, comparison of different versions of configuration data.

    **Use Cases:** XML is readable.


.. req:: BSW Modules shall be harmonized
    :id: SRS_BSW_00453
    :status: open
    :tags: bsw
    :links: SRS_BSW_00456
    
    If an SWS of a BSW module is allowed to be linked to more than one implementation of another BSW 
    module into an AUTOSAR binary image, then all involved SWS's shall ensure that all externally 
    visible C identifiers (i.e. types, variables, macros, functions, etc) are defined such that no 
    conflicts can arise for surrounding BSW modules using these multiple implementations at compile
    time and that no ambiguity exists at link time

    **Rationale:** If the rule is not followed, systems with multiple implementations of one BSW Module 
    will mostly get an error at compile time or link time.

    **Use Cases:** In CAN Driver there are 2 type definitions

    - Can_IdType
    - Can_PduType

    which are used in CanIf.

    Can_IdType can be uint16 or uint32 type.

    If there are 2 CAN drivers implemented in one Autosar system by two different vendors and both 
    implementations defines Can_IdType differently, then it will lead to compilation / linking failure 
    in the system.

    Hence it should be made sure that there are no ambiguities


.. req:: A Header file shall be defined in order to harmonize BSW Modules
    :id: SRS_BSW_00456
    :status: open
    :tags: bsw
    
    If more than one implementation of a BSW Module is linked into an Autosar system which results 
    in conflict of externally visible C Identifiers (i.e. types, variables, macros etc ), a common 
    header file may define all the conflicting identifiers.

    The header file shall be named as
    
    .. code-block::
        
        <Module Abbreviation>_GeneralTypes.h

    Module Abbreviation is defined in Basic Software Module List. It refers to BSW Module which has 
    more than one implementation

    **Rationale:** BSW systems with multiple implementations of one BSW Module will mostly get an error 
    at compile time or link time, if they are not harmonized.


.. req:: Callback functions of Application software components shall be invoked by the Basis SW
    :id: SRS_BSW_00457
    :status: open
    :tags: bsw
    
    An AUTOSAR Basic Software module shall only invoke the callback functions of Application Software 
    Components and/or Sensor/Actuator SW-Components through the Client Server communication of the RTE.

    CDDs are not affected by this requirement.

    **Rationale:** RTE shall not be bypassed if AUTOSAR Basic Software Modules are calling callbacks 
    provided by Application SW-Cs and/or Sensor/Actuator SW-Cs, because only these components are 
    restricted to having only AUTOSAR interfaces. This is to support memory partitioning.


.. req:: Interfaces for handling request from external devices
    :id: SRS_BSW_00479
    :status: open
    :tags: bsw
    :links: SRS_BSW_00005
    
    Drivers for external devices shall use and offer the same interfaces as internal drivers when 
    calling or being called by the interface module

    **Rationale:** In general, the driver for external devices shall follow the same SWS specification. 
    For external drivers, when calling Det, use the same module ID as the internal drivers

    **Use Cases:** System which uses an internal and an independent external HW Wdg module


.. req:: BSW Modules shall handle buffer alignments internally
    :id: SRS_BSW_00483
    :status: open
    :tags: bsw
    
    BSW modules which require certain alignment of buffers shall not impose any additional requirements 
    on the users. I.e. Buffers passed as arguments shall be treated as specified by their base types; 
    alignment results from base type and platform specifics.

    **Rationale:** Avoid conflicting alignment requirements within software stack. It shall be possible 
    to allocate RAM buffers without the need to consider alignment requirements throughout the software 
    stack

    **Use Cases:** Interoperability of components; avoid "hidden" restrictions in API usage (imposing 
    stricter alignments limits the value range for pointer parameters).

    Especially drivers shall hide HW/peripheral's alignment requirements from upper layers; they shall 
    not map a HW's/peripheral's alignment requirements to data buffers, which would result in 
    propagating them to upper layers.


4.3.3 Software Module Design Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: All Basic SW Modules written in C language shall conform to the MISRA C 2012 Standard
    :id: SRS_BSW_00007
    :status: open
    :tags: bsw
    
    MISRA C (see [5]) describes programming rules for the C programming language and a process to 
    implement and follow these rules.

    Only in technically reasonable, exceptional cases MISRA violations are permissible. Such 
    violations against MISRA rules shall be clearly identified and documented within comments in 
    the C source code (including rationale why MISRA rule is violated).

    Examples of MISRA rules violations shall look like:
    
    .. code-block:: c

        /* MR12 RULE XX VIOLATION: Reason */
        /* MR12 DIR XX VIOLATION: Reason */

    **Rationale:** Portability, maintainability, error avoidance, safety

    **Use Cases:** Software for safety relevant systems


.. req:: All AUTOSAR Basic Software Modules shall be identified by an unambiguous name
    :id: SRS_BSW_00300
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall be identified by an unambiguous name. The module name 
    is always part of related files.

    Convention for module related files:
    
    - <Module name>_*.*
    - Spelling of module name: First letter of each word upper case, consecutive letters lower case
    - Module name: 2..8 letters, derived from [7]
    - Wildcard replacement according to module related file set (either basic and recommended)

    **Rationale:** The module name serves as an identifier and classification mechanism in order
    to group module related files.

    **Use Cases:** Example: Eep.c, Eep.h


.. req:: An index-based accessing of the instances of BSW modules shall be done
    :id: SRS_BSW_00413
    :status: open
    :tags: bsw
    :links: SRS_BSW_00347
    
    If instances of BSW modules are characterized by:

    - same vendor and
    - same functionality and
    - same hardware device
    
    they shall be accessed index based.


.. req:: A Naming seperation of different instances of BSW drivers shall be in place
    :id: SRS_BSW_00347
    :status: open
    :tags: bsw
    
    Driver modules shall be named according to the following rules (only for implementation, not 
    for the software specification):

    - First the module name has to be listed: <Module Abbreviation>
    - After that the vendor Id defined in the AUTOSAR vendor list has to be given <Vendor Id>
    - At last a vendor specific name (the vendor API infix) follows <Vendor API infix>
    - Only for API names, last name shall be <API Service name>
    - All parts shall be separated by underscores "_".
    - This naming extension applies to the following externally visible elements of the module:
        * File names
        * API names
        * Published parameters
        * Memory allocation keyword
    - For API names, <Vendor specific name> should be followed by "_" and then <API Service Name>.
    - For the creation of file names, no trailing underscore shall be added.
    - For Published parameters and Memory allocation keyword names, <Vendor Specific name> shall 
      have a trailing underscores.

    **Rationale:** Avoidance of name clashes

    **use Case:** Examples:

    - EEPROM (LD): `Eep_21_LDExtEepDriver.c`
    - Published parameters: `EEP_21_LDEXT_SW_MAJOR_VERSION`
    - API: `Eep_21_LDExt_Init`


.. req:: Naming convention for type, macro and function
    :id: SRS_BSW_00441
    :status: open
    :tags: bsw
    :links: SRS_BSW_00331, SRS_BSW_00327, SRS_BSW_00335
    
    All AUTOSAR Basic Software Modules shall label enumeration literals and #defines according to 
    the following scheme:

    - Composition: <Module Abbreviation>_<Specific name>
    - <Module Abbreviation> shall be written in UPPERCASE
    - <Specific name> shall be written in UPPERCASE
    - <Module Abbreviation> and <Specific name> shall be separated by underscore
    - If <Specific name> consists of several words, they shall be separated by underscore

    The `#define E_OK` and `E_NOT_OK` are exceptions to this

    **Rationale:** Enhance readability and unique classification of enumeration literals and
    #defines identifiers.

    **use Case:** Example #define:

    .. code-block:: c
        
        #define EEP_PARAM_CONFIG
        #define EEP_SIZE
        
    Example enumeration literals:
    
    .. code-block:: c
        
        typedef enum
        {
            EEP_DRA_CONFIG = 0,
            EEP_ARE = 1,
            EEP_EV = 2
        } Eep_NotificationType;


.. req:: Data types naming convention
    :id: SRS_BSW_00305
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304
    
    All AUTOSAR Basic Software Modules shall label data types according to the following scheme:
    
    - Composition of type: <Module name>_<Type name>Type
    - Only one underscore between module name and type name
    - < Type name > shall be written in UpperCamelCase.

    Note: Basic AUTOSAR types ([SRS_BSW_00304]) need not support the scheme defined here

    **Rationale:** Enhance readability and unique classification of data type identifiers.


.. req:: Global variables naming convention
    :id: SRS_BSW_00307
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304
    
    All AUTOSAR Basic Software Modules shall label global variables according to the following scheme:
    
    - Composition of name: <Module name>_<Variable name>
    - Only one underscore between module name and variable name
    - Spelling of name: First letter of each word upper case, consecutive letters lower case

    **Rationale:** Enhance readability and unique classification of global variables.


.. req:: API naming convention
    :id: SRS_BSW_00310
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall implement an API based on the following naming rules:

    - Composition of API: <Module name>_ServiceName() <Mip>_<Sn>
    - Where <Mip> is the Module implementation prefix and <Sn> is the API Service name
    - Module name: 2..8 letters, derived from [7]
    - Only one underscore between module name and service name
    - Spelling of API: First letter of each word upper case, consecutive letters lower case
    
    **Rationale:** Avoidance of name clashes, uniform AUTOSAR API; The API shows to which module it 
    belongs

    **UseCases:** 

    .. code-block:: c

        Can_TransmitFrame()
        Nm_RequestBusCommunication()
        Adc_Init()
        Eep_Write()
        Nvm_GetState()


.. req:: ServiceInterface argument with a pointer datatype
    :id: SRS_BSW_00494
    :status: open
    :tags: bsw
    
    A ServiceInterface argument with a pointer datatype (DATA_REFERENCE) shall have a Ptr postfix 
    in its argument type and -name. No other argument type shall use this postfix in its argument 
    type or -name.

    The argument direction of a pointer datatype is always IN.
    
    **Rationale:** A pointer datatype in ServiceInterface has limitations in use, so it should be 
    easily identifiable.

    The argument direction IN is because the RTE just transfers the pointer and not the content 
    behind the pointer. An argument direction other than IN would theoretically allocate a buffer 
    for this pointer in the RTE, wherefore the RTE is rejecting such configurations (according to 
    SWS_Rte_07662).


.. req:: The main processing function of each AUTOSAR Basic Software Module shall be named according 
         the defined convention
    :id: SRS_BSW_00373
    :status: open
    :tags: bsw
    
    The main processing function of each AUTOSAR Basic Software Module shall be named according to 
    the following rule:

    <Module name>_MainFunction_<module specific extension> ()

    Module specific extension shall be used to distinguish between multiple main processing functions 
    of one module (e.g. Cluster index, Rx /Tx . . . ). If only one main processing function exists 
    in one module no module specific extension is required.

    It is responsibility of the modules to either define one main processing function and handle all 
    the processing internally or define multiple main processing functions with appropriate module 
    specific extensions.

    This depends on Module requirements.

    Main processing functions shall have no parameters and no return value.

    Main processing functions shall not be re-entrant.
    
    **Rationale:** Many modules have one or more functions that have to be called cyclically (e.g.
    within an OS Task) and that do the main work of the module. These shall have unique names

    **Use Cases:** Possible main processing function of EEPROM driver:

    .. code-block:: c

        void Eep_MainFunction(void)

    Possible main processing functions of FlexRay driver:

    .. code-block:: c

        void Fr_MainFunction_TxClst1(void)
        void Fr_MainFunction_TxClst2(void)
        void Fr_MainFunction_RxClst1(void)
        void Fr_MainFunction_RxClst2(void)
    
    Please Note: The Use case is no recommendation for the particular Module, it just illustrates 
    Main processing function possibilities.


.. req:: Error values naming convention
    :id: SRS_BSW_00327
    :status: open
    :tags: bsw
    :links: SRS_BSW_00331, SRS_BSW_00369
    
    All AUTOSAR Basic Software Modules shall apply the following naming rules for all error values:
    
    - Error values shall have only CAPITAL LETTERS
    - Naming convention: <MODULENAME>_E_<ERRORNAME>
    - If <ERRORNAME> consists of several words, they shall be separated by underscores
    
    **Rationale:** Avoidance of name clashes, uniform AUTOSAR error values;
    The error shows to which module it belongs.

    **Use Cases:** The EEPROM driver has the following error values:

    .. code-block:: c

        EEP_E_BUSY
        EEP_E_PARAM_ADDRESS
        EEP_E_PARAM_LENGTH
        EEP_E_WRITE_FAILED


.. req:: Status values naming convention
    :id: SRS_BSW_00335
    :status: open
    :tags: bsw
    :links: SRS_BSW_00331
    
    All AUTOSAR Basic Software Modules shall apply the following naming rules for status values that 
    are visible outside of the module:
    
    - Status values shall have only CAPITAL LETTERS
    - If <STATUSNAME> consists of several words, they shall be separated by underscores
    
    **Rationale:** Avoidance of name clashes, uniform AUTOSAR status values; 
    The status value shows to which module it belongs.

    **Use Cases:** The Eeprom driver has the following status values:

    .. code-block:: c

        EEP_UNINIT
        EEP_IDLE
        EEP_BUSY


.. req:: All AUTOSAR Basic Software Modules shall allow the enabling/disabling of detection and 
         reporting of development errors
    :id: SRS_BSW_00350
    :status: open
    :tags: bsw
    :links: SRS_BSW_00337
    
    All AUTOSAR Basic Software Modules shall allow the enabling/disabling of detection and reporting 
    of development errors. It shall be configurable and the default value of the configuration shall 
    be that those error type is disabled.
    
    **Rationale:** Provide module wide debug instrumentation facilities. Each defined keyword has 
    to be properly documented

    **Use Cases:** Example: 
    
    In Eep.h:

    .. code-block:: c

        #define EEP_DEV_ERROR_DETECT STD_ON /* detection module wide enabled */

    In source Eep.c:

    .. code-block:: c
    
        #include "Eep.h"
        ...
        #if ( EEP_DEV_ERROR_DETECT == STD_ON )
        ...
        .. development errors to be detected
        ...
        #endif /* EEP_DEV_ERROR_DETECT */


.. req:: If tracing is enabled, all AUTOSAR Basic Software Modules should allow tracing its entry 
         and exit points
    :id: SRS_BSW_00495
    :status: open
    :tags: bsw
    :links: RS_Main_01026
    
    All AUTOSAR Basic Software Modules should allow the tracing of its entry and exit points to 
    enable run time measurement of the BSW module. It should be configurable and the default value 
    of the configuration shall be that tracing is disabled.
    
    **Rationale:** Run time measurement plays a vital role in verifying correct timing behavior.
    Tracing entry and exit points of BSW modules is necessary for both, measuring the run time of 
    the module itself as well as calculating the net execution time of a software component.

    **Use Cases:** Example:

    .. code-block:: c
    
        ARTI_TRACE_N(USER, AR_CP_BSW_API, SoAd, 0, Bsw_Start, 3, 0x49, TxPduId, PduInfoPtr);


.. req:: All AUTOSAR Basic Software Modules configuration parameters shall be named according to a 
         specific naming rule
    :id: SRS_BSW_00408
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules configuration parameters shall be named according to the 
    following naming rules:

    - Naming convention: <Module Abbreviation><ParameterName>

    < Module Abbreviation > is the prefix derived from [7].
    
    < ParameterName > may consist of several words which may or may not be separated by underscore.

    The configuration parameter name can either be in UpperCamelCase or Uppercase

    **Rationale:** Avoidance of name clashes, uniform AUTOSAR configuration naming.
    
    **Use Cases:** Example:

    .. code-block:: c
    
        CanIfTxConfirmation


.. req:: Compiler switches shall have defined values
    :id: SRS_BSW_00410
    :status: open
    :tags: bsw
    
    Compiler switches shall be compared with defined values. Simple checks if a compiler switch is 
    defined shall not be used.

    In general the symbols which switch functionality on or off are defined in Std_Types.h

    **Rationale:** C-Language allows asking for defined symbols. This shall be avoided.
    
    **Use Cases:** Example:

    Do :

    .. code-block:: c
    
        #if ( EEP_DEV_ERROR_DETECT == STD_ON )
        ..

    Don't:

    .. code-block:: c
    
        #ifdef EEP_DEV_ERROR_DETECT
        ..


.. req:: All AUTOSAR Basic Software Modules shall apply a naming rule for enabling/disabling the 
         existence of the API
    :id: SRS_BSW_00411
    :status: open
    :tags: bsw
    :links: SRS_BSW_00407
    
    All AUTOSAR Basic Software Modules shall apply the following naming rule for enabling/disabling 
    the existence of the API. It shall be configurable and the default value of the configuration 
    shall be that this API is not available

    **Rationale:** Enable/Disable the reading out of version information
    
    **Use Cases:** Example:

    In Eep.h:

    .. code-block:: c
    
        #define EEP_VERSION_INFO_API STD_ON /*API enabled */
        ...


.. req:: Naming convention of callout prototypes
    :id: SRS_BSW_00463
    :status: open
    :tags: bsw
    :links: SRS_BSW_00407
    
    Each callout function shall be mapped to its own memory section and memory class. These memory 
    classes will then be mapped to the actually implemented memory classes at integration time.

    The following naming convention shall be used:
    
    — Start section definition: —

    .. code-block:: c

        #define MSN_START_SEC_CBN_CODE

    — Stop section definition: —

    .. code-block:: c
    
        #define MSN_STOP_SEC_CBN_CODE

    — Function prototype definition: —
    
    .. code-block:: c
    
        void MSN_Cbn (void);

    Where:

    MSN: Module Short Name as officially defined in AUTOSAR (see supporting material).

    CBN: Call Back Name, which shall have the same spelling of the Callback name including module 
    reference but using only capital letters.

    Cbn: Callback name using the conventional Camel Case notation for API names.

    **Rationale:** The memory segment used for a callout is not known to the module developer. 
    The integrator needs the freedom to map callouts independently from the module's design.
    
    **Use Cases:** In order to ensure uniqueness, it is recommended to use the function's name to
    derive the name of the memory section and the name of the memory class.

    For example:

    .. code-block:: c
    
        #define COM_START_SEC_COM_SOMECALLOUT_CODE
        #include "Com_MemMap.h"
        void Com_SomeCallout(void);
        #define COM_STOP_SEC_COM_SOMECALLOUT_CODE
        #include "Com_MemMap.h"


.. req:: File names shall be considered case sensitive regardless of the filesystem in which they 
         are used
    :id: SRS_BSW_00464
    :status: open
    :tags: bsw
    
    File names shall be considered case sensitive regardless of the filesystem in which they are used.

    **Rationale:** Some file systems do not distinguish between file names spelled with the same
    letters but with different cases. Allowing such variability in the definitions can cause 
    ambiguities.
    
    **Use Cases:** If different implementers implement modules using same names with different cases, 
    the compile and link process shall have unpredictable results depending on the file system  on 
    which they are executed, leading eventually to errors (source or object file not found).

    Example of wrong implementation:

    The file name "ModuleAbc.h" is defined in a SWS;
    
    "moduleabc.h" and "ModuleAbc.h" are implemented by two different implementers and then included 
    in modules developed by different implementers.

    If the file "moduleabc.h" is included with the directive
    
    .. code-block:: c
    
        #include <ModuleAbc.h>
    
    on a case sensitive file system, the file won't be found


.. req:: It shall not be allowed to name any two files so that they only differ by the cases of 
         their letters
    :id: SRS_BSW_00465
    :status: open
    :tags: bsw
    :links: SRS_BSW_00464
    
    It shall not be allowed to name any two files so that they only differ by the cases of their 
    letters.

    **Rationale:** Problems deriving potentially ambiguous name definitons must be avoided already 
    in the specification phase
    
    **Use Cases:** In a SWS the include files:

    .. code-block:: c
        
        #include "RTE.h"
        #include "rte.h"

    are defined and they are specified to contain different information.

    At compile time a compiler running in a file system which does not distinguish between cases 
    shall include one or the other in a non predictable order.


.. req:: Null pointer errors shall follow a naming rule
    :id: SRS_BSW_00480
    :status: open
    :tags: bsw
    
    NULL pointer error naming convention. The name for the development errors for NULL pointer 
    violations is `<MIP>_E_PARAM_POINTER`

    **Rationale:** Harmonization of standard


.. req:: Errors for module initialization shall follow a naming rule
    :id: SRS_BSW_00487
    :status: open
    :tags: bsw
    
    The name for the development errors for uninitialized modules is `<MIP>_E_UNINIT`

    **Rationale:** Harmonization of standard


.. req:: BSW Modules shall ensure data consistency of data which is shared between BSW modules 
    :id: SRS_BSW_00481
    :status: open
    :tags: bsw
    
    Invalid configuration set selection error naming convention

    The name for the invalid configuration set selection errors `<MIP>_E_INIT_FAILED`

    **Rationale:** Harmonization of standard


.. req:: Get version information function shall follow a naming rule
    :id: SRS_BSW_00482
    :status: open
    :tags: bsw
    
    The get version information API name follows [SRS_BSW_00310] and has Get VersionInfo as Service 
    name.

    Example:

    .. code-block:: c

        void Eep_21_LDExt_GetVersionInfo ( Std_VersionInfoType *versioninfo)

    **Rationale:** Harmonization of standard


.. req:: All AUTOSAR Basic Software Modules shall provide at least a basic set of module files
    :id: SRS_BSW_00346
    :status: open
    :tags: bsw
    :links: SRS_BSW_00345, SRS_BSW_00347, SRS_BSW_00314, SRS_BSW_00419
    
    All AUTOSAR Basic Software Modules shall provide a standardized set of unique header files which 
    separates source code from configuration. The exact structure shall be defined in [8, SWS BSW 
    General] including the naming convention using the module name

    **Rationale:** Source code and configuration are strictly separated. User defined configurations 
    will not imply a change of the original source code. Other BSW Modules which need to access 
    configuration data can do this without need for source code change.

    **Use Case:** Separate post built configuration data from precompile configuration data, source 
    code from configuration data in general etc..


.. req:: All internal driver modules shall separate the interrupt frame definition from the service 
         routine
    :id: SRS_BSW_00314
    :status: open
    :tags: bsw
    
    All internal driver modules shall separate the interrupt frame definition from the service routine 
    in the following way:

    - <Module name>_Irq.c: implementation of interrupt frame
    - <Module name>.c: implementation of service routine called from interrupt frame

    **Rationale:** Flexibility using different compilers and/or different OS integrations

    **Use Case:** The interrupt could be realized as ISR frame of the operating system or implemented 
    directly without changing the driver code.

    The service routine can be called directly during module test without the need of causing an 
    interrupt.


.. req:: Standardizing Include file structure of BSW Modules Implementing Autosar Service
    :id: SRS_BSW_00447
    :status: open
    :tags: bsw
    
    - A Basic Software Module implementing an Autosar Service shall include its Application Types 
      Header file in the Module Header File.
    - Data Types used in Standard Interface and Standard AUTOSAR Interface shall only be defined in 
      RTE Types Header file only.
    - A Basic Software Module implementing an Autosar Service shall include Rte_<ModuleShortName>.h 
      as AUTOSAR Service Application Header File, providing the interface for interaction with the RTE.
    - A Basic Software Module implementing an Autosar Service shall include its AUTOSAR Service 
      Application Header File in module files, which are using RTE interfaces. The Application Header 
      file shall not be included in module files, which are in included directly or indirectly by other 
      modules.

    Data Type NvM_RequestResultType used in BSW C-API `NvM_GetError_Status` and in the AUTOSAR Interface 
    "NvMService" operation

    .. code-block:: c

        GetErrorStatus (OUT NvM_RequestResultType RequestResultPtr);

    is same.
    
    The proper types shall be generated in Rte_Type.h.

    Rte_Type.h shall be included in BSW module header file via `Rte_"Service"_Type.h`

    Rte_Type.h shall be included in SW-C module header file via `Rte_"Swc"_Type.h`

    **Rationale:** Standardizing Include Header file structure will allow common data types to be 
    defined in RTE Types header files. This will avoid double and inconsistent definition of data 
    types in both BSW and Software Component. This will also avoid type casts if SW-Cs are 
    communicating with Autosar Services.

    **Use Case:** All BSW Services which are called by Application SW-C and share data types. E.g. 
    Asynchronous NvRAM Block request result returned by the operation `GetErrorStatus` and API 
    service `NvM_GetErrorStatus`.


.. req:: All AUTOSAR standard types and constants shall be placed and organized in a standard type 
         header file
    :id: SRS_BSW_00348
    :status: open
    :tags: bsw
    :links: SRS_BSW_00357, SRS_BSW_00353
    
    All AUTOSAR standard types and constants shall be placed and organized in a standard type header 
    file.

    Standard type header file naming convention: Std_Types.h

    This standard type header file shall
    
    - include the Platform specific type header (Platform_Types.h)
    - define the type Std_ReturnType
    - define values for E_OK and E_NOT_OK
    - define values for `STD_ON, STD_OFF, STD_HIGH, STD_LOW, STD_ACTIVE, STD_IDLE`

    **Rationale:** Provide uniform framework wide access to standard types to be used by all modules.

    **Use Case:** Each module that uses AUTOSAR integer data types and/or the standard return type 
    shall include the file Std_Types.h.

    **Supporting Material:** Important note for implementation of this header file:

    Because `E_OK` is already defined within [3, OSEK OS], E_OK has to be checked for being already 
    defined:

    .. code-block:: c

        /* for ISO 17356-3 compliance this typedef has been added*/
        #ifndef STATUSTYPEDEFINED
        #define STATUSTYPEDEFINED
            typedef unsigned char StatusType;
            #define E_OK 0
        #endif


.. req:: All integer type definitions of target and compiler specific scope shall be placed and 
         organized in a single type header
    :id: SRS_BSW_00353
    :status: open
    :tags: bsw
    :links: SRS_BSW_00308, SRS_BSW_00348
    
    All integer type definitions of target and compiler specific scope shall be placed and organized 
    in a single type header.

    Name of platform types header file: Platform_Types.h

    **Rationale:** Separate compiler and µC-specific integer types from standard types.

    **use Case:** Changing the microcontroller and/or compiler shall only affect a limited number 
    of files


.. req:: All AUTOSAR Basic Software Modules shall only import the necessary information
    :id: SRS_BSW_00301
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall only import the necessary information (i.e. header 
    files) that is required to fulfill the modules functional requirements.

    **Rationale:** Promote defensive module layout. Modules shall not import functionality that
    could be misused. Shorten compile times.


.. req:: All AUTOSAR Basic Software Modules shall only export information needed by other modules
    :id: SRS_BSW_00302
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall export only that kind of information in their 
    correspondent header-files explicitly needed by other modules

    **Rationale:** Prevent other modules accessing functionality and data that is 'none of their 
    business'

    **Use Cases:** The NvM shall not know all processor registers because someone has included
    the processor register file in another header file used by the NvM.


.. req:: All AUTOSAR Basic Software Modules shall avoid the duplication of code 
    :id: SRS_BSW_00328
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules should avoid the duplication of code.

    **Rationale:** Avoid bugs during maintenance

    **Use Cases:** A module contains 4 code segments which are equal. During maintenance of the 
    module 3 of them have been updated, 1 has been forgotten → bug.


.. req:: Shared code shall be reentrant
    :id: SRS_BSW_00312
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules implementing shared code shall ensure reentrancy if code is 
    exposed to preemptive or parallel environments. For multi-core systems, reentrancy shall be 
    ensured for unrestricted concurrent execution of that service on several cores (concurrency safety).

    **Rationale:** Shared code eases functional composition, reusability, code size reduction and
    maintainability. As a drawback, shared code shall be implemented reentrant if it is used in 
    preemptive environments or on multiple partitions in parallel. Please note that an implementation 
    that is reentrant on single core systems might not be concurrency safe when used in a Multi-Core 
    environment.

    **Use Cases:** A subroutine or function is reentrant if a single copy of the routine can be called
    from several task contexts simultaneously without conflict. Use the following reentrancy techniques:

    - Avoid use of static and/or global variables
    - Guard static and/or global variables using blocking mechanisms
    - Use dynamic stack variables


.. req:: The source code of software modules above the µC Abstraction Layer (MCAL) shall not be 
         processor and compiler dependent.
    :id: SRS_BSW_00006
    :status: open
    :tags: bsw
    
    Those software modules have to be developed once and shall be compilable for all processor 
    platforms without any changes. Any necessary processor or compiler specific instructions (e.g. 
    memory locators, pragmas, use of atomic bit manipulations etc.) have to be exported to macros 
    and include files

    **Rationale:** Minimize number of variants and development effort

    **Use Cases:** NvM, Network Management, ...


.. req:: Enable BSW modules to handle interrupts
    :id: SRS_BSW_00439
    :status: open
    :tags: bsw
    
    Autosar shall allow BSW modules to define and handle Interrupts.

    **Use Cases:** In the case where the entire driver is delivered as source this isn't a problem.

    In the case where the MCAL BSW module is delivered as object code, the interrupt handler could 
    be written as a pair of small stubs (a cat1 stub and a cat2 stub) that are delivered as source, 
    compiled as necessary, and simply call the main handler.


.. req:: Module SWS shall not contain requirements from other modules 
    :id: SRS_BSW_00448
    :status: open
    :tags: bsw
    
    It shall not be allowed for a module SWS to add requirements from other modules:

    - If a requirement is missing, then raise an Rfc, possibly resulting in a valid requirement within 
      the module.
    - For this valid requirement give reference of the document where original requirement resides

    **Rationale:** Increase consistency between SWS documents, ease change management of documents.

    **Use Cases:** CAN Driver SWS using requirements from MCU Driver SRS. In this case there shall 
    be a valid CAN requirement in SRS which refers to the particular requirement in MCU Driver SRS


.. req:: BSW Service APIs used by Autosar Application Software shall return a Std_ReturnType 
    :id: SRS_BSW_00449
    :status: open
    :tags: bsw
    
    Every BSW Service API called by application software via RTE shall return a Std_ReturnType, 
    return value.

    Refer to the Port Interface Section of the respective module, to confirm if the APIs are accessed 
    by the RTE.

    **Rationale:** RTE call of BSW service always expect a return value of Std_ReturnType

    **Use Cases:** RTE always expects return type of Std_ReturnType for the BSW Service API Call, 
    any other return type or void shall cause incompatibility between the RTE and BSW.


.. req:: For success/failure of an API call a standard return type shall be defined
    :id: SRS_BSW_00357
    :status: open
    :tags: bsw
    :links: SRS_BSW_00348, SRS_BSW_00377, SRS_BSW_00359
    
    For success/failure of an API call, a return type is defined in Std_Types.h which indicates the 
    success or failure of the call.

    **Rationale:** Enforces usage of already defined types instead of attempting to override existing 
    ones.

    If different success states can occur and they are of interest for the caller then different 
    return values need to be defined.


.. req:: A Basic Software Module can return a module specific types
    :id: SRS_BSW_00377
    :status: open
    :tags: bsw
    :links: SRS_BSW_00357
    
    A Basic Software Module can return a module specifictypes

    **Rationale:** Example for possibility 1:

    .. code-block:: c
    
        uint8 Can_Write(. . . )

    return values: `E_OK (0), CAN_BUSY (1), E_OK` is taken from `Std_Types.h`, `CAN_BUSY` is #defines 
    in can.h.

    Note: no strong type checking possible because return type is uint8 and values are only #defines. 
    `E_OK` can be used.

    Example for possibility 2:

    .. code-block:: c

        Can_ReturnType Can_Write(...)

    Return values: CAN_OK, CAN_BUSY, Can_ReturnType is an enumeration type in can.h

    .. code-block:: c
        
        typedef enum
        {
            CAN_OK = 0,
            CAN_BUSY = 2,
        } Can_ReturnType;

    Note: strong type checking possible because only the values of the enumeration may be assigned 
    to variables of type Can_ReturnType. `E_OK` cannot be used here!


.. req:: All AUTOSAR Basic Software Modules shall use only AUTOSAR data types instead of native C 
         data types
    :id: SRS_BSW_00304
    :status: open
    :tags: bsw
    :links: SRS_BSW_00353, SRS_BSW_00007 
    
    All AUTOSAR Basic Software Modules shall not use the native C data types

    **Rationale:** MISRA-C compliance, portability, reusability. The usage of native C-data types
    (e.g. char, int, short, long, float, double, ...) is forbidden as size and/or sign and/ or accuracy 
    are not unambiguously defined and therefore are platform specific.

    **Use Cases:** Portability between different architectures.


.. req:: AUTOSAR shall provide a boolean type
    :id: SRS_BSW_00378
    :status: open
    :tags: bsw
    
    For simple logical values and for API return values (if applicable) AUTOSAR shall provide a boolean 
    type.

    The only allowed operations shall be: assignment, return, test for quality

    **Rationale:** Repeating requests of several WGs to define a boolean data type.

    **Use Cases:** API return value. Example:

    In file Eep.h:

    .. code-block:: c

        #include "Std_Types.h" /* this automatically includes Platform_Types.h */
        boolean Eep_Busy(void) {...}
        In calling module:
        if (Eep_Busy() == FALSE) {...}

    **Supporting Material:** Compiler vendors that provide a boolean data type that cannot be disabled
    have to change their compiler (i.e. make it ANSI C compliant).


.. req:: AUTOSAR Basic Software Modules shall be compiler and platform independent
    :id: SRS_BSW_00306
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall not use compiler or platform specific keywords directly

    **Rationale:** Direct use of not standardized keywords like "_near", "_far", "_pascal" in the
    frameworks source code will create compiler and platform dependencies that must strictly be 
    avoided. If no precautions were made, portability and reusability of influenced code is deteriorated 
    and effective release management is costly and hard to maintain.


.. req:: AUTOSAR Basic Software Modules shall not define global data in their header files, but in 
         the C file
    :id: SRS_BSW_00308
    :status: open
    :tags: bsw
    
    AUTOSAR Basic Software Modules shall not define global data in their header files.

    If global variables have to be used, the definition shall take place in the C file.

    **Rationale:** Avoid multiple definition and uncontrolled spreading of global data, limit 
    visibility of global variables


.. req:: All AUTOSAR Basic Software Modules shall indicate all global data with read-only purposes 
         by explicitly assigning the const keyword
    :id: SRS_BSW_00309
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules shall indicate all global data with read-only purposes by 
    explicitly assigning the const keyword.

    **Rationale:** In principle, all global data shall be avoided due to extra blocking efforts when
    used in preemptive runtime environments. Unforeseen effects are to occur if no precautions were 
    made. If data is intended to serve as constant data, global exposure is permitted only if data 
    is explicitly declared read-only using the const qualifier

    **Use Cases:** 
    
    .. code-block:: c
        
        const uint8 MaxPayload = 0x18;


.. req:: Input parameters of scalar and enum types shall be passed as a value
    :id: SRS_BSW_00484
    :status: open
    :tags: bsw
    
    All input parameters of scalar or enum type shall be passed as a value.

    **Rationale:** For example a function named <Mip>_SomeFunction with a return type of 
    Std_ReturnType and a single parameter named SomeParameter of type uint8 is defined with the 
    following signature: 
    
    .. code-block:: c

        Std_ReturnType <Mip>_SomeFunction(uint8 SomeParameter);


.. req:: Input parameters of structure type shall be passed as a reference to a constant structure
    :id: SRS_BSW_00485
    :status: open
    :tags: bsw
    
    All input parameters of structure type shall be passed as a reference constant structure

    **Rationale:** Passing input parameters of structure type by value would result in additional
    run-time overhead due to efforts for copying the whole structure.

    **Use Cases:** For example a function named <Mip>_SomeFunction with a return type of Std_ReturnType 
    and a single parameter named SomeParameter of type Some Structure (where SomeStructure is a struct) 
    is defined with the following signature:

    .. code-block:: c

        Std_ReturnType <Mip>_SomeFunction(const SomeStructure * SomeParameter);


.. req:: Input parameters of array type shall be passed as a reference to the constant array base type
    :id: SRS_BSW_00486
    :status: open
    :tags: bsw
    
    All input parameters of array type shall be passed as a reference to the constant array base type

    **Rationale:** This effectively matches the behavior specified in the ISO-C:99 namely that a
    "declaration of a parameter as 'array of type' shall be adjusted to 'qualified pointer to type'"

    **Use Cases:** For example a function named <Mip>_SomeFunction with a return type of Std_ReturnType 
    and a single parameter named SomeParameter of type array of uint8 is defined with the following 
    signature:

    .. code-block:: c

        Std_ReturnType <Mip>_SomeFunction(const uint8 * SomeParameter);


.. req:: The return type of init() functions implemented by AUTOSAR Basic Software Modules shall be 
         void
    :id: SRS_BSW_00358
    :status: open
    :tags: bsw
    
    The return type of init() functions implemented by AUTOSAR Basic Software Modules shall be void

    **Rationale:** Errors in initialization data shall be detected during configuration time (e.g. 
    by configuration tool).


.. req:: Init functions shall have a pointer to a configuration structure as single parameter
    :id: SRS_BSW_00414
    :status: open
    :tags: bsw
    :links: SRS_BSW_00101, SRS_BSW_00358, SRS_BSW_00400
    
    For post-build time configuration, or when multiple configuration sets are available, the pointer 
    to the base configuration structure (see [SRS_BSW_00438]) shall be passed to the init function 
    of the BSW module. For pre-compile and link time configuration, when only one configuration set is
    available, a NULL_PTR shall be passed for this parameter.

    <Mip>_ConfigType

    It shall be used for init function argument

    **Use Case:** Example:

    .. code-block:: c

        void Eep_Init (const Eep_ConfigType *ConfigPtr)


.. req:: All AUTOSAR Basic Software Modules callback functions shall avoid return types other than 
         void if possible
    :id: SRS_BSW_00359
    :status: open
    :tags: bsw
    
    All AUTOSAR Basic Software Modules callback functions shall avoid return types other than void 
    if possible.

    Callback functions routed to Software Components (SWCs) via the RTE shall be typed by Std_ReturnType, 
    not void. The caller of the callback function shall consider the case that the environment (RTE) 
    can return infrastructure errors (refer SWS_Rte_02593) e.g. in case the servers' partition is currently 
    not available.

    In case the callback is used as notification only, the caller can assume that always `E_OK` is returned

    **Rationale:** Callbacks could be used for notifications.


.. req:: AUTOSAR Basic Software Modules callback functions are allowed to have parameters
    :id: SRS_BSW_00360
    :status: open
    :tags: bsw
    
    AUTOSAR Basic Software Modules callback functions are allowed to have parameters

    **Rationale:** Enhance flexibility and scope of callback functionality.

    **Use Cases:** If callback functions do serve as simple triggers, no parameter is necessary to
    be passed.

    If additional data is to be passed to the caller within the callback scope, it shall be possible 
    to forward the contents of that data using a parameter


.. req:: The callback function invocation by the BSW module shall follow the signature provided by 
         RTE to invoke servers via Rte_Call API
    :id: SRS_BSW_00440
    :status: open
    :tags: bsw
    :links: SRS_BSW_00359
    
    The callback function invocation by the BSW module, which is routed via RTE shall follow the 
    signature provided by RTE to invoke servers via Rte_Call API.

    **Rationale:** The callback function has to be to be compatible to Rte_Call API of the RTE 
    to enable a type safe configuration and implementation of AUTOSAR Services and IO Hardware 
    Abstraction. Instance pointers are in Basic Software not allowed.


.. req:: It shall be allowed to use macros instead of functions where source code is used and runtime 
         is critical
    :id: SRS_BSW_00330
    :status: open
    :tags: bsw
    :links: SRS_BSW_00359
    
    It shall be allowed to use macros instead of functions where source code is used and runtime is 
    critical.

    It shall be allowed to use inline functions for the same purpose. Inline functions have the advantage 
    (compared to macros) that the compiler can do type checking of function parameters and return values.

    **Rationale:** Improve runtime behavior

    **Dependencies:** Macros as well as inline functions are only possible when source code is delivered.


.. req:: All Basic Software Modules shall strictly separate error and status information
    :id: SRS_BSW_00331
    :status: open
    :tags: bsw
    :links: SRS_BSW_00327, SRS_BSW_00335
    
    All Basic Software Modules shall strictly separate error and status information

    **Rationale:** Common API specification of AUTOSAR Basic Software Modules.

    **Dependencies:** Macros as well as inline functions are only possible when source code is delivered.


.. req:: All Standardized Autosar Interfaces shall have unique requirement Id / number
    :id: SRS_BSW_00462
    :status: open
    :tags: bsw
    
    All Standardized Autosar Interfaces shall have unique requirement Id / number.

    The purpose of the standardized AUTOSAR Interface definition is to provide a standard which has 
    to be considered by Software Components defining Service ports.

    Therefore the Port of the Software Component has to be at least compatible to the definition in 
    the related SWS document.

    **Rationale:** The standardized Autosar Interfaces definitions are not binding without a
    requirement Id.

    **Dependencies:** A SWC deviating from the Operation names will hinder the integration process.
    This is because the Ports of the Service and the Ports of the Service User (SWC) are NOT compatible.


.. req:: An alternative interface without a parameter of category DATA_REFERENCE shall be available
    :id: SRS_BSW_00454
    :status: open
    :tags: bsw
    
    In case an AUTOSAR interface supports a parameter of category DATA_REFERENCE, an alternative 
    interface without such a parameter shall be available

    **Rationale:** A DATA_REFERENCE will show up as a pointer to data at the interface level.

    AUTOSAR BSW can not do a full safety check on the pointer because the size of the data is not known. 
    Therefore, if safety is an issue, the alternative interface needs to be available and to be used.

    In general, to avoid such problems, AUTOSAR Interfaces should not use a DATA_REFERENCE.

    **Dependencies:** ECUs with safety requirements where an application with lower privileges
    passes a DATA_REFERENCE to the BSW with higher privileges


.. req:: The functional interfaces of AUTOSAR BSW modules shall be specified in C99
    :id: SRS_BSW_00477
    :status: open
    :tags: bsw
    
    The specification of functional interfaces of AUTOSAR BSW modules shall be specified in C99 
    according to ISO/IEC 9899:1999.

    This implies that languages, which can interface to C99 can be used for application programming.

    The number of significant characters allowed for external identifier can exceed the specified 
    minimum (31 characters).

    **Rationale:** A useful reduction of programming languages to current programming languages 
    reduces the impacts on AUTOSAR definitions and specifications due to logical and/or technical 
    differences of different programming languages.

    **Dependencies:** AUTOSAR implementation in C, C++


.. req:: It shall be possible to concurrently execute a service offered by a BSW module in different 
         partitions
    :id: SRS_BSW_00459
    :status: open
    :tags: bsw
    :links: SRS_BSW_00426
    
    If a service supports concurrent execution in different partitions , the implementation of the 
    service shall ensure that concurrent handling of calls is performed in a multi-core safe manner, 
    i.e. several calls from different partitions to the same service at the same time do not interfere 
    with each other.

    This can be implemented, for example, by using exclusive areas and re-entrant code.

    **Rationale:** Performance, error avoidance.

    **Dependencies:** BSW running on multi core systems


.. req:: Reentrancy Levels
    :id: SRS_BSW_00460
    :status: open
    :tags: bsw
    :links: SRS_BSW_00426
    
    If BSW is executed in multiple partitions, all functions in a BSW module entity shall conform 
    to the reentrancy level enforced by the API description of the implemented Bsw module entry, or 
    to a stricter level.

    If the description of a module entity contains the optional reentrancy level attribute, this level 
    must be compliant to the reentrancy requirements of the implemented entry, and the implementation 
    must conform to the reentrancy level enforced by the description of the module entity.

    If a module can be invoked locally in multiple partitions, reentrancy also implies safe execution 
    in parallel on multiple cores.

    **Rationale:** Performance, error avoidance.

    **Dependencies:** BSW running on multi core systems


4.3.4 Software Documentation Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: All Basic SW Modules shall be documented according to a common standard
    :id: SRS_BSW_00009
    :status: open
    :tags: bsw
    :links: SRS_BSW_00010, SRS_BSW_00333
    
    The module documentation shall contain at least the following items:

    - Cover sheet with title, version number, date, author, document status, document name
    - Change history with version number, date, author, change description, document status
    - Table of contents (navigable)
    - Functional overview
    - Source file list and description
    - Module requirements
    - Used resources (interrupts, µC peripherals etc.)
    - Integration description (OS, interface to other modules etc.)
    - Configuration description with parameter, description, unit, validrange, default value, 
      relation to other parameters

    The module documentation shall also contain examples for

    - the correct usage of the API
    - the configuration of the module

    **Rationale:** User acceptance, maintainability, usability

    **Dependencies:** Standard Core


.. req:: Documentation of multiple instances of configuration parameters shall be available
    :id: SRS_BSW_00401
    :status: open
    :tags: bsw
    
    "Multiplicity" defines how many times an entity (in this case configuration parameter) is 
    instanciated.

    The multiplicity of each configuration parameter has to be documented.

    It shall be documented what determines the number of entries (e.g. "one per frame").

    **Rationale:** Overall (throughout the complete Basic Software) harmonization of configuration 
    parameter naming

    **use Case:** Id of a PDU is multiple time present dependent on the number of PDUs to be 
    sent/received


.. req:: The scheduling strategy that is built inside the Basic Software Modules shall be compatible 
         with the strategy used in the system
    :id: SRS_BSW_00172
    :status: open
    :tags: bsw
    
    The scheduling strategy that is built inside the Basic Software Modules shall be compatible with 
    the strategy used in the system.

    To achieve this, the following items shall be traced by BSW specific SWS:
    
    - polling / event driven
    - cooperative / pre-emptive
    - for each cyclic function: invocation rate (either fixed value or allowed range)
    - execution order (dependencies to other modules)
    - synchronous / asynchronous processing
    - minimum and maximum function runtime (WCET)
    - maximum interrupt rate

    **Rationale:** Today scheduling mechanisms differ between ECUs. A Basic Software Module provides 
    several entry points to be accessed by the other Basic Software Modules/surrounding system. 
    E.g. a function can react directly on event or by a scheduled polling. The differences may result 
    in difference in real-time requirements, system load, latency etc.!

    **Use Case:** On the one hand it is possible to avoid any direct function call between BSW modules 
    by using only scheduling and data interface - more deterministic. On the other hand it is possible 
    that beside the scheduling additional functional interfaces exists to control BSW modules - less 
    deterministic.

    The integrating SW-system and its SW-architecture might restrict direct function calls between 
    SW-components. Thus not any SW-component will fit in this SW-system.


.. req:: The memory consumption of all Basic SW Modules shall be documented for a defined configuration 
         for all supported platforms
    :id: SRS_BSW_00010
    :status: open
    :tags: bsw
    
    For software integration the following data shall be available for each supported platform:

    - RAM/ROM consumption

    **Rationale:** Due to stability of documentation, this information is provided in a separate
    document for each supported platform. If a further platform is added, the module documentation 
    remains unvalid

    **Use Case:** Microcontroller selection, software integration, configuration of operating system


.. req:: For each callback function it shall be specified if it is called from interrupt context or not
    :id: SRS_BSW_00333
    :status: open
    :tags: bsw
    
    For each callback function it shall be specified if it is called from interrupt context or not

    **Rationale:** User awareness. The code inside a callback function called from an ISR has to
    be kept short.

    **Use Case:** Some notification function is called from an ISR of the CAN driver. The user
    filling this callback function has to know that the function is running in interrupt context!


.. req:: All Basic Software Modules shall provide a readable module vendor identification
    :id: SRS_BSW_00374
    :status: open
    :tags: bsw
    
    All Basic Software Modules shall provide a readable module vendor identification in their published 
    parameters.

    Naming convention:

    .. code-block:: c
    
        <MODULENAME>_VENDOR_ID

    The vendor ID shall be represented in uint16 (16 bit).

    The format of the vendor identification shall be only:

    .. code-block:: c

        #define <MODULENAME>_VENDOR_ID 0x0000u

    without any cast to allow a verification in pre-processor

    **Rationale:** Allow identification of module vendor

    **Use Case:** `EEP_VENDOR_ID`


.. req:: All software modules shall provide a module identifier in the header file and in the module 
         XML description file
    :id: SRS_BSW_00379
    :status: open
    :tags: bsw
    :links: SRS_BSW_00334
    
    All software modules shall provide a module ID both in the header file and in the module XML 
    description file.

    The value shall be taken from the Basic Software Module List.

    Naming convention: <MODULENAME>_MODULE_ID

    The module ID shall be represented in uint16 (16 bit).

    **Rationale:** Required for error reporting to Default Error Tracer (Det).

    **Use Case:** In file Eep.h:

    .. code-block:: c

        #define EEP_MODULE_ID 90


.. req:: All software modules shall provide version and identification information
    :id: SRS_BSW_00003
    :status: open
    :tags: bsw
    :links: SRS_BSW_00004, SRS_BSW_00318 
    
    All software modules shall provide a readable software version number in allimport header files.

    Version number macros can be used for checking (Inter Module Checks) and reading out the software 
    version of a software module during compile time and runtime.
    
    It is preferred to derive this information from the version management system automatically

    **Rationale:** Compatibility checking, configuration supervision


.. req:: The version numbers of AUTOSAR Basic Software Modules shall be enumerated according specific 
         rules
    :id: SRS_BSW_00321
    :status: open
    :tags: bsw
    :links: SRS_BSW_00318 
    
    The version numbers of AUTOSAR Basic Software Modules shall be enumerated according to the 
    following rules:

    - Increasing a more significant digit of a version number resets all less significant digits
    - The PATCH_VERSION is incremented if the module is still upwards and downwards compatible 
      (e.g. bug fixed)
    - The MINOR_VERSION is incremented if the module is still downwards compatible (e.g. 
      validfunctionality added)
    - The MAJOR_VERSION is incremented if the module is not compatible any more (e.g. existing API 
      valid)

    **Rationale:** Provide unambiguous version identification for each module, provide version
    cross check as well as basic version retrieval facilities.

    Compatibility is always visible!

    **Use Cases:** Example: ADC module with version 1.14.2

    - Versions 1.14.2 and 1.14.9 are exchangeable. 1.14.2 may contain bugs
    - Version 1.14.2 can be used instead of 1.12.0, but not vice versa
    - Version 1.14.2 cannot be used instead of 1.15.4 or 2.0.0


.. req:: Module documentation shall contains all needed informations
    :id: SRS_BSW_00341
    :status: open
    :tags: bsw
    
    All needed informations by user of a module shall be stated in the documentation of the module.

    **Rationale:** Opportunity to identify uniquely the specific microprocessor, including known
    bugs in the silicon so that its compatibility with the software can be established

    **Use Cases:** Different mask revisions of e.g. TriCore

.. req:: Each AUTOSAR Basic Software Module file shall provide version numbers in the header file
    :id: SRS_BSW_00318
    :status: open
    :tags: bsw
    :links: SRS_BSW_00321, SRS_BSW_00374, SRS_BSW_00402
    
    Each AUTOSAR Basic Software Module file shall provide version numbers in the header file as 
    defined below:

    Naming convention:

    - <MODULENAME>_SW_MAJOR_VERSION
    - <MODULENAME>_SW_MINOR_VERSION
    - <MODULENAME>_SW_PATCH_VERSION
    - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
    - <MODULENAME>_AR_RELEASE_MINOR_VERSION
    - <MODULENAME>_AR_RELEASE_REVISION_VERSION

    AR: Major/Minor/Revision Release Version number of AUTOSAR specification which the appropriate 
    implementation is based on.

    SW: Major/minor/patch version number of the vendor specific implementation of the module. The 
    numbering shall be vendor specific

    Each number shall be represent able as uint8 (8 bit).

    **Rationale:** Allow version identification and version checking in between software modules.

    **Use Case:** Example: Adc vendor module version 1.14.9; implemented according to the AUTOSAR 
    Release 4.0, Revision 1

    .. code-block:: c

        #define ADC_SW_MAJOR_VERSION            1
        #define ADC_SW_MINOR_VERSION            14
        #define ADC_SW_PATCH_VERSION            9
        #define ADC_AR_RELEASE_MAJOR_VERSION    4
        #define ADC_AR_RELEASE_MINOR_VERSION    0
        #define ADC_AR_RELEASE_REVISION_VERSION 1


.. req:: All Basic Software Modules shall provide an XML file that contains the meta data
    :id: SRS_BSW_00334
    :status: open
    :tags: bsw
    
    All Basic Software Modules shall provide an XML file that contains the meta data which is required 
    for the SW integration process

    **Rationale:** 
    
    - Being able to have several drivers of the same type (e.g. 2 different external flash drivers) 
      on the same ECU without name clash
    - Ensure system consistency and correctness

    **use Case:** 
    
    .. code-block:: xml

        <function_provided>
        <name>Eep_Write</name>
        <prototype>Eep_ST16RF42_Write</prototype>
        </function_provided>
    
    ST16RF42 is the type of the external EEPROM


.. req:: Encapsulation of compiler specific methods to map objects
    :id: SRS_BSW_00351
    :status: open
    :tags: bsw
    
    AUTOSAR shall define header files which encapsulate compiler and platform specific differences 
    in memory mapping such that BSW modules and SWC can be implemented of compiler and platform

    **Rationale:** AUTOSAR focuses on embedded systems with only restricted memory resources. 
    Therefore a precise mapping of objects (data,code) is needed

    **use Case:** Storage of different objects in memory with fast access times
