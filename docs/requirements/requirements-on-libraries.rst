Requirements on Libraries
=========================

This document specifies requirements on the AUTOSAR Libraries. It applies to all
the libraries specified by AUTOSAR:

- **Mfx** Library of Mathematical FiXed point calculations
- **Mfl** Library of Mathematical FLoating point point calculations
- **Ifx** Library of Interpolation functions of FiXed point
- **Ifl** Library of Interpolation functions of FLoating point
- **Bfx** Library of Bit handling
- **Efx** Library of Extended functions on Fixed point
- **Crc** Library of CRC routines
- **E2E** SW-C End-to-End Communication Protection Library

Each of these libraries has its own independent SWS but this SRS document applies to all libraries.

Conformance to all requirements is mandatory for all implementations. “Configurable” also means, 
the requirement must be met, but such functionality can be disabled, if not needed in an ECU 
(BSW or SW-C).

This document was initially dedicated to CRC routines. In order to keep traceability, the CRC 
requirements are still present but in a dedicated chapter

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SRS_Libraries.pdf


4 Functional Overview
---------------------

The AUTOSAR libraries provide other BSW modules and application SW-Cs with mathematical services.
The libraries offer C functions that can be called from source code, i.e. from BSW modules, from 
SW-C, from RTE or from Complex Drivers.


4.1 CRC library
^^^^^^^^^^^^^^^

The CRC Library provides functions for 8 bit, 16 bit, 32 bit and 64 bit CRC (cyclic redundancy 
check) calculations. The CRC library can be scaled in terms of

- Table based calculation (fast, but higher code size)
- Runtime calculation (slow, but smaller code size)
- Different standard CRC generator polynomials

Hardware supported CRC calculation is already supported by automotive microcontrollers.


4.2 SW-C End-to-End Communication Protection Library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The SW-C End-to-End Communication Protection Library (in short: E2E library) provides functions for 
detecting errors in (safety-related) communication between safety-related SW-Cs. The protection is 
done by means of protecting of safety-related data elements exchanged between SW-Cs, and the 
responsibility to protect/check the signal is given to the SW-Cs (application), which call directly 
the E2E library. The library is supposed to work over a priori any communication stack used for 
inter-SW-C communication, which are currently FlexRay, CAN and LIN. In future, when further
communication stacks are added, there might be a need to add further E2E profiles


6 Requirements Specification
----------------------------

6.1 Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^

6.1.1 Configuration
"""""""""""""""""""

.. req:: The functional behavior of each library functions shall not be configurable
    :id: SRS_LIBS_00001
    :status: open
    :tags: bsw

    The functional behavior of library functions shall not be configurable. For some given inputs 
    (c function parameters), a function shall return always the same outputs, as defined with the 
    function specification. However, the internal behavior can be configurable. For examples: choose 
    resource consumption strategy e.g. priority to CPU/RAM/ROM. But this is implementation specific 
    and not standardized by AUTOSAR

    **Rationale:** A SW-C that uses a library function expects a deterministic and standardized 
    behavior. It the SW integrator has the possibility to configure and change the behavior, the 
    SW-C may react unexpectedly

    **Use Case:** Division function. In case of division by zero, the function shall always return 
    the same value. If the SW integrator has the possibility to configure this return value, it may 
    be right for some SW-Cs but it may also be catastrophic for other SW-Cs


.. req:: It shall be possible to configure the microcontroller so that the library code is shared 
         between all callers
    :id: SRS_LIBS_00015
    :status: open
    :tags: bsw

    In case memory partitioning is enabled on a given microcontroller, then it shall be possible to 
    configure the microcontroller so that the library code is shared between all callers of the shared 
    library.

    **Rationale:** This enables to reduce the Flash memory consumption.

    **Use Case:** In a partitioned system, SW-Cs in different partitions access the same library.


6.1.2 Initialization
""""""""""""""""""""

.. req:: A library shall be operational before all BSW modules and application SW-Cs
    :id: SRS_LIBS_00002
    :status: open
    :tags: bsw

    **Rationale:** A Library function may be called at the very first step of ECU initialization, 
    e.g. even by the OS or EcuM, thus the library shall be ready.

    **Use Case:** AUTOSAR OS initialization may call bit handling function


6.1.3 Normal Operation
""""""""""""""""""""""

.. req:: Using libraries shall not pass through a port interface
    :id: SRS_LIBS_00004
    :status: open
    :tags: bsw

    SW-Cs shall directly invoke library functions, without passing through port RTE interface. To 
    access the library API, the SW-Cs shall directly include the library header file.

    **Rationale:** The SW developer should be free to use libraries without having to change the SW-C 
    interface description: reduce effort and inconsistencies The port+RTE mechanism is not required 
    for library calls: no consistency check, no queuing, no communication outside ECU, etc.
    
    - Using library functions is a software designer decision. It is related to implementation, not 
      to SW-C interface.
    - Calling a library function is an elemental operation. It is not like a client/server operation
    - because, they are often used, library function shall be called in an efficient way

    Thus, the function can be directly called from the source code, e.g. runnables, without using 
    RTE API.

    **Use Case:** Application includes floating point arithmetic library header, and calls floating
    point routines in control loop calculations, without crossing RTE.


.. req:: Each library shall provide one header file with its public interface
    :id: SRS_LIBS_00005
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00004

    Each library shall provide one header file with its public interface. This header shall declare 
    all the public function prototypes and types defined by the library specification The header file 
    shall be named like: <library short name>.h

    **Rationale:** Access to function prototypes and types Standardization of header file name

    **Use Case:** #include "AR_MFX.h


.. req:: All library functions shall be re-entrant
    :id: SRS_LIBS_00009
    :status: open
    :tags: bsw

    All library functions shall be re-entrant, which means that they shall be able to handle several 
    simultaneous, interleaved or/and concurrent requests. A function, in order to be re-entrant, 
    it (1) shall not call any non-re-entrant functions, (2) shall not write any global nor static 
    variables. If some kind of data shall be handled, the callers have to create (define) them and 
    pass them as function parameters.

    A library function only runs in the context of the caller, on the core where it is called, in the 
    same protection environment.

    A library function can only call library functions.

    A library function is synchronous, e.g. it does not have wait points.

    **Rationale:** Avoid consistency mechanisms which bring to weak efficiency

    **Use Case:** Multitasking environments. Every BSW modules and SW-C will use the same functions 
    in different tasks


.. req:: A library shall define its own specific types in the library header file if and only if 
         they are not yet defined by AUTOSAR
    :id: SRS_LIBS_00010
    :status: open
    :tags: bsw

    A library shall define (typedef) its own specific types in the library header file if and only 
    if they are not yet defined by AUTOSAR in std_types.h and platform_types.h. These types shall be 
    identified in the corresponding SWS by the name and the description, but not the actual implementation.

    No new implementation-specific types are allowed in the implementation of the public library interface, 
    i.e. other types that are not specified in the SWS shall not be present.

    The implementation (typedef) can be different, e.g. according the platform.

    The caller shall not rely on any implementation. Using C operators on these specific types is forbidden.

    **Rationale:** A library may handle some specific types not defined by AUTOSAR Only SWS specified type 
    are allowed in order to insure code portability independent from any specific AUTOSAR library 
    implementation

    **Use Case:** Types u64, S64 for the 64bits data math library


.. req:: All function names and type names shall start with "Library short name"
    :id: SRS_LIBS_00011
    :status: open
    :tags: bsw

    All function names and type names shall start with "Library short name"

    **Rationale:** Avoid collision with already existing library Quickly identified AUTOSAR library 
    calls in the code


.. req:: All function names and type names shall start with "Library short name"
    :id: SRS_LIBS_00012
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00008

    Function calls become simpler. If a set of fixed parameters is required. They can be defined 
    once in a structure and may be used several times.

    In some circumstances, it makes sense to group several function parameters into one of 
    few structures:

    - when there are many parameters,
    - when some parameters can be grouped by functionality

    **Use Case:**

    .. code-block:: c

        sint16 EFX_PGOV_WIN ( sint32 X,
                              sint32 Kp,
                              sint32 KpPos,
                              sint32 KpNeg,
                              sint32 WinPos,
                              sint32 WinNeg )

        sint16 EFX_PGOV_WIN( sint32 X, const PWin_Type * Struct )


    **Dependencies:** if a parameter is added to the structure, a new structure name and a new 
    function name shall be defined. So there is no risk that a new structure field would be forgotten 
    in case of library evolution.

    
6.1.4 Shutdown Operation
""""""""""""""""""""""""

.. req:: A library shall be operational until the shutdown
    :id: SRS_LIBS_00003
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00008

    A library shall be operational until the shutdown .A library should not require a shutdown 
    operation phase. If so, it shall occur after all AUTOSAR BSW modules shutdown operations

    **Rationale:** A Library function may be called at the very latest step of ECU shutdown,
    e.g. even by the OS, thus the library shall be ready until the end

    **Use Case:** AUTOSAR OS shutdown operation may call bit handling function


6.1.5 Fault Operation
"""""""""""""""""""""

.. req:: The error cases, resulting in the check at runtime of the value of input parameters, 
         shall be listed in SWS
    :id: SRS_LIBS_00013
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00001

    Function should check at runtime (both in production and development code) the value of input 
    parameters, especially cases where erroneous value can bring to fatal error or unpredictable 
    result, if they have the values allowed by the function specification.

    All the error cases shall be listed in SWS and the function should return a specified value 
    (in SWS) that is not configurable. This value is dependant of the function and the error case 
    so it is determined case by case.

    **Rationale:** Avoid fatal error, provide standardized behaviour

    **Use Case:** Division by zero, negative number of a square root, out of range, overflow,
    underflow, etc.


6.2.2 CRC library
"""""""""""""""""

.. req:: For a given function prototype name, the behavior and the parameters shall not evolve once 
         it is a part of an AUTOSAR final release
    :id: SRS_LIBS_00008
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00001

    For a given function prototype name, the behavior and the parameters shall not evolve once it 
    is a part of an AUTOSAR final release. For any reasons, if the specification of a behavior has 
    to be changed in AUTOSAR release N+1, e.g. the WP LIBRARIES decides of a new feature, or a 
    parameter/type has to be added/removed/modified from the specification, and if library 
    implementations might be already in production, then a new function prototype shall be created. 
    
    The previous one (AUTOSAR release N) shall be kept unchanged.

    In case of a type implementation is specified in SWS, then if this implementation changes, a 
    new type name and API name shall be created and the previous one shall be retained.

    In case of a type implementation is not defined in SWS, then the library developer is free to 
    change the implementation without creating new type name.

    **Rationale:** Avoid SW-C re-developing in case of library evolution. Avoid having to integrate 
    new library releases if SW-C do not require new function. 
    
    if an integrator has to add different SW-C which rely on different libraries(AUTOSAR specification) 
    versions, he can (has to) purchase the latest library version since the ascending compatibility 
    is insured.

    **Use Case:** On a project, the integrator uses a library compatible with AR4.0, and a SW-C that 
    use this library. On a next V cycle, a new library release compatible with AR4.1 is integrated. 
    With the ascending compatibility rule, it is ensured that the SW-C will react in the same way 
    even if new functions have been added.


.. req:: A SW-C may use a non-AUTOSAR library available on the market
    :id: SRS_LIBS_00016
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00011

    A SW-C may use a non-AUTOSAR library available on the market. In this case, the developer may not 
    deliver this library but just mention it in the SW-C template (DependencyOnLibrary). It is the 
    responsibility of the integrator to get this library to be able to integrate the SW-C.

    This non-AUTOSAR library should respect the requirements of this document.
    
    It is recommended that non-AUTOSAR functions start with a specific vendor prefix

    **Rationale:** Allows freedom of implementation. Avoid name collisions.

    **Use Case:** Supplier specific libraries.


.. req:: Using a library should be documented
    :id: SRS_LIBS_00007
    :status: open
    :tags: bsw

    If a BSW module or a SW-C uses a Library, the developer should add an Implementation-
    DependencyOnLibrary in the BSW/SW-C template. minVersion and maxVersion parameters correspond 
    to the supplier version.

    In case of AUTOSAR library, these parameters may be left empty because a SW-C or BSW module 
    may rely on a library behaviour, not on a supplier implementation. However, the SW-C or BSW 
    modules shall be compatible with the AUTOSAR platform where they are integrated.

    **Rationale:** SW integrator to checks the AUTOSAR platform compatibilities while integrating 
    a BSW module or a SW-C


.. req:: Usage of macros should be avoided
    :id: SRS_LIBS_00017
    :status: open
    :tags: bsw

    The function should be declared as function or inline function. Macro #define should not be used

    **Rationale:** Macros do not specify argument type and return type so there is more chance of 
    improper use


.. req:: A library function may only call library functions
    :id: SRS_LIBS_00018
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00009

    A library function shall not call any BSW modules functions, e.g. the DET A library function can 
    call other library functions

    Rationale: A library function shall be re-entrant. Other BSW modules functions may not be re-entrant.

    **Use Case:** Multi-core architecture, Memory protection scheme
