Specification of Bit Handling Routines
======================================

AUTOSAR Library routines are the part of system services in AUTOSAR architecture
and below figure shows position of AUTOSAR library in layered architecture.

Bfx routines specification specifies the functionality, API and the configuration of the
AUTOSAR library for BIT functionality dedicated to fixed-point arithmetic routines.
All bit functions are re-entrant and can handle several simultaneous requests from the
application.

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SWS_BFXLibrary.pdf


5 Dependencies to other modules
-------------------------------

5.1 File structure
^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00220
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00005

    The Bfx module shall provide the following files:

    - C files, Bfx_<name>.c used to implement the library. All C files shall be prefixed with **Bfx**.

    Header file Bfx.h provides all public function prototypes and types defined by the BFX library 
    specificationc(SRS_LIBS_00005)


.. req:: None
    :id: SWS_Bfx_00222
    :status: open
    :tags: bsw

    Implementation & grouping of routines with respect to C files shall be done according to one 
    of the options described below.c()

    Option 1 : <Name> can be function name providing one C file per function,
    eg.: Bfx_setbit.c etc.

    Option 2 : <Name> can have common name of group of functions:

    - 2.1 Group by object family: eg. `Bfx_set.c, Bfx_get.c`
    - 2.2 Group by routine family: eg. `Bfx_bit8.c,Bfx_bit16.c etc.`
    - 2.3 Group by other methods: (individual grouping allowed)
    
    Option 3 : <Name> can be removed so that single C file shall contain all Bfx functions,
    eg. `Bfx.c.``

    Using above options gives certain flexibility of choosing suitable granularity with reduced 
    number of C files. Depending on the tool-chain linking on demand can be possible or not.


7 Functional specification
--------------------------

7.1 Error Classification
^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00223
    :status: open
    :tags: bsw

    Section 7.1 "Error Handling" of the document "General Specification of Basic Software Modules" 
    describes the error handling of the Basic Software in detail. Above all, it constitutes a 
    classification scheme consisting of five error types which may occur in BSW modules

    Based on this foundation, the following section specifies particular errors arranged in
    the respective subsections below


7.2 Initialization and shutdown
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00200
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00002

    Bfx library shall not require initialization phase. A library function may be called at the 
    very first step of ECU initialization, e.g. even by the OS or EcuM, thus the library shall 
    be ready.


.. req:: None
    :id: SWS_Bfx_00201
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00003

    Bfx library shall not require a shutdown operation phase.c


7.3 Using Library API
^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00203
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00018

    Bfx API can be directly called from BSW modules or SWC. No port definition is required. It is a 
    pure function call


.. req:: None
    :id: SWS_Bfx_00205
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00007

    Using a library should be documented. if a BSW module or a SWC uses a Library, the developer should 
    add an Implementation-DependencyOnArtifact in the BSW/SWC template.

    minVersion and maxVersion parameters correspond to the supplier version. In case of AUTOSAR library, 
    these parameters may be left empty because a SWC or BSW module may rely on library behaviour, 
    not on a supplier implementation. However, the SWC or BSW modules shall be compatible with the 
    AUTOSAR platform where they are integrated


7.4 Library implementation
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00206
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00015

    The Bfx library shall be implemented in a way that the code can be shared among callers in 
    different memory partitions


.. req:: None
    :id: SWS_Bfx_00207
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00017

    Usage of macros must be avoided in the context of Library. The library function must be declared 
    as function or as inline function and Macro #define should not be used


.. req:: None
    :id: SWS_Bfx_00208
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00018

    A library function shall not call any BSW module functions, e.g. the DET. A library function 
    can call any other library functions since all library functions are re-entrant but not BSW 
    module functions, as they may not be re-entrantc


.. req:: None
    :id: SWS_Bfx_00209
    :status: open
    :tags: bsw
    :links: SRS_BSW_00007

    The library, written in C programming language, should confirm to the MISRA C Standard.
    Please refer to SWS_BSW_00115 for more details


.. req:: None
    :id: SWS_Bfx_00212
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304, SRS_BSW_00378

    All AUTOSAR library Modules should use the AUTOSAR data types (Integers, Boolean) instead of 
    native C data types, unless this library is clearly identified to be compliant only with a 
    platform


.. req:: None
    :id: SWS_Bfx_00213
    :status: open
    :tags: bsw
    :links: SRS_BSW_00348

    All AUTOSAR library Modules should avoid direct use of compiler and platform specific keyword, 
    unless this library clearly identified to be compliant only with a platform


.. req:: None
    :id: SWS_BfSWS_Bfx_00214x_00213
    :status: open
    :tags: bsw

    All Bit Library modules shall avoid handling user faults and values outside specified range


8 API specification
-------------------

8.1 Imported types
^^^^^^^^^^^^^^^^^^

In this chapter all types included from the following files are listed


.. req:: None
    :id: SWS_Bfx_91001
    :status: open
    :tags: bsw

    +--------------------+------------------------+---------------------------------------------------+
    | **Module**         | **Header File**        | **Imported Type**                                 |
    +--------------------+------------------------+---------------------------------------------------+
    | Std                | Std_Types.h            | Std_VersionInfoType                               |
    +--------------------+------------------------+---------------------------------------------------+

It is observed that since the sizes of the integer types provided by the C language are
implementation-defined, the range of values that may be represented within each of the integer 
types will vary between implementations.

Thus, in order to improve the portability of the software, these types are defined in 
Platform_Types.h [6]. The following mnemonic are used in the library routine names.

Note: The naming convention for the api’s with boolean return type/parameter type is given as 
_u8 which shall be interpreted as _b. (Boolean)

If there is no boolean data type present in the return type/parameter type then _u8 shall be 
interpreted as _u8 only.

+--------------------+------------------------+---------------------------------------------------+
| **Size**           | **Platform Type**      | **Mnemonic**                                      |
+--------------------+------------------------+---------------------------------------------------+
| unsigned 8-Bit     | boolean                | u8                                                |
+--------------------+------------------------+---------------------------------------------------+
| signed 8-Bit       | sint8                  | s8                                                |
+--------------------+------------------------+---------------------------------------------------+
| signed 16-Bit      | sint16                 | s16                                               |
+--------------------+------------------------+---------------------------------------------------+
| signed 32-Bit      | sint32                 | s32                                               |
+--------------------+------------------------+---------------------------------------------------+
| unsigned 8-Bit     | uint8                  | u8                                                |
+--------------------+------------------------+---------------------------------------------------+
| unsigned 16-Bit    | uint16                 | u16                                               |
+--------------------+------------------------+---------------------------------------------------+
| unsigned 32-Bit    | uint32                 | u32                                               |
+--------------------+------------------------+---------------------------------------------------+

As described in [6], the ranges for each of the base types are shown in Table 2

+------------------------+---------------------------------------------------+
| **Base Type**          | **Range**                                         |
+------------------------+---------------------------------------------------+
| boolean                | TRUE,FALSE                                        |
+------------------------+---------------------------------------------------+
| sint8                  |  -128, 127                                        |
+------------------------+---------------------------------------------------+
| sint16                 | -32768, 32767                                     |
+------------------------+---------------------------------------------------+
| sint32                 | -2147483648, 2147483647                           |
+------------------------+---------------------------------------------------+
| uint8                  |  0, 255                                           |
+------------------------+---------------------------------------------------+
| uint16                 | 0, 65535                                          |
+------------------------+---------------------------------------------------+
| uint32                 | 0, 4294967295                                     |
+------------------------+---------------------------------------------------+


As a convention in the rest of the document:

- Mnemonics will be used in the name of the routines (using <InTypeMn1> that means Type Mnemonic 
  for Input 1)
- The real type will be used in the description of the prototypes of the routines (using <InType> 
  or <OutType>).

The bit addressing for the document is

- The bit position of the lowest significant bit is defined as 0(zero)
- The bit field length is defined as the number of bits.


8.2 Type definitions
--------------------

None

8.3 Comment about functions optimized for target
------------------------------------------------

The functions described in this library may be realized as regular functions or as a, inline functions


8.4 Bit functions definitions
-----------------------------

8.4.1 Bfx_SetBit
^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00001
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_SetBit_<TypeMn>u8                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_SetBit_<TypeMn>u8 (                                        |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 BitPn                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x01 to 0x03                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitPn                 | Bit position                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall set the logical status of input data as **1** at the| 
    |                       | requested bit position.                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00002
    :status: open
    :tags: bsw

    Expected functionality: `*Data = *Data | (0x01 << BitPn)`
    
    For Example: `Data = 10001010b`

    `Bfx_SetBit_u8u8(&Data, 2)`

    The Data will be updated to **10001110b**


.. req:: None
    :id: SWS_Bfx_00008
    :status: open
    :tags: bsw

    List of implemented functions

    +----------------------+---------------------------------------------+----------------------------+
    | **Function ID[hex]** | **Function prototype**                      | **Maximum value of BitPn** |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x001**            | void Bfx_SetBit_u8u8(uint8*, uint8)         | 7                          |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x002**            | void Bfx_SetBit_u16u8(uint16*, uint8)       | 7                          |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x003**            | void Bfx_SetBit_u32u8(uint32*, uint8)       | 7                          |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x004**            | void Bfx_SetBit_u64u8(uint64*, uint8)       | 7                          |
    +----------------------+---------------------------------------------+----------------------------+


8.4.2 Bfx_ClrBit
^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00010
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ClrBit_<TypeMn>u8                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ClrBit_<TypeMn>u8 (                                        |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 BitPn                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x06 to 0x08                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitPn                 | Bit position                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall clear the logical status of the input data to **0** | 
    |                       |  at the requested bit position.                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00011
    :status: open
    :tags: bsw

    Expected functionality: 
    
    .. code-block:: c 
    
        *Data = (*Data & ~(0x01 << BitPn))
    
    For Example: 
    
    .. code-block:: c 
    
        Data = 10001010b
        Bfx_ClrBit_u8u8(&Data, 1)

    The Data will be updated to **10001000b**


.. req:: None
    :id: SWS_Bfx_00015
    :status: open
    :tags: bsw

    List of implemented functions

    +----------------------+---------------------------------------------+----------------------------+
    | **Function ID[hex]** | **Function prototype**                      | **Maximum value of BitPn** |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x006**            | void Bfx_ClrBit_u8u8(uint8*, uint8)         | 7                          |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x007**            | void Bfx_ClrBit_u16u8(uint16*, uint8)       | 15                         |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x008**            | void Bfx_ClrBit_u32u8(uint32*, uint8)       | 31                         |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x009**            | void Bfx_ClrBit_u64u8(uint64*, uint8)       | 63                         |
    +----------------------+---------------------------------------------+----------------------------+

   
8.4.3 Bfx_GetBit
^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00016
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_GetBit_<InTypeMn>u8_u8                                              |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     boolean Bfx_GetBit_<InTypeMn>u8_u8 (                                |
    |                       |          <InType> Data,                                                 |
    |                       |          uint8 BitPn                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x0a to 0x0c                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitPn                 | Bit position                                    |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | boolean               | Bit Status                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function shall return the logical status of the input data for the | 
    |                       | requested bit position.                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00017
    :status: open
    :tags: bsw

    .. code-block:: c 

        Result = TRUE, ((Data & (0x01 << BitPn)) != 0)
        Result = FALSE, else
    
    For Example:

    .. code-block:: c 

        Bfx_GetBit_u8u8(10001010b, 1)
        returns TRUE


.. req:: None
    :id: SWS_Bfx_00020
    :status: open
    :tags: bsw

    List of implemented functions

    +----------------------+---------------------------------------------+----------------------------+
    | **Function ID[hex]** | **Function prototype**                      | **Maximum value of BitPn** |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x00A**            | boolean Bfx_GetBit_u8u8_u8(uint8,uint8)     | 7                          |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x00B**            | boolean Bfx_GetBit_u16u8_u8(uint16,uint8)   | 15                         |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x00C**            | boolean Bfx_GetBit_u32u8_u8(uint32,uint8)   | 31                         |
    +----------------------+---------------------------------------------+----------------------------+
    | **0x00D**            | boolean Bfx_GetBit_u64u8_u8(uint64,uint8)   | 63                         |
    +----------------------+---------------------------------------------+----------------------------+


8.4.4 Bfx_SetBits
^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00021
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_SetBits_<TypeMn>u8u8u8                                              |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_SetBits_<TypeMn>u8u8u8 (                                   |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 BitStartPn,                                              |
    |                       |          uint8 BitLn,                                                   |
    |                       |          uint8 Status                                                   |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x20 to 0x22                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitStartPn            | Start bit position                              |
    |                       +-----------------------+-------------------------------------------------+
    |                       | BitLn                 | Bit field length                                |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Status                | Status value                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall set the input data as '1' or '0' as per 'Status'    |  
    |                       | value starting from 'BitStartPn' for the length 'BitLn'                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00022
    :status: open
    :tags: bsw

    For Example:

    .. code-block:: c 

        Data = 1110100000000111b
        Bfx_SetBits_u16u8u8u8(&Data, 5, 5, 1)

    The Data will be updated to **1110101111100111b**


.. req:: None
    :id: SWS_Bfx_00025
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **Function** | **Function prototype**                                | **Maximum**  | **Maximum**  | **Maximum**    |
    | **ID[hex]**  |                                                       | **value of** | **value of** | **value of**   |
    |              |                                                       | **BitLn**    | **StartPn**  | **BitStartPn** | 
    |              |                                                       |              |              | **+ BitLn**    |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x020**    | void Bfx_SetBits_u8u8u8u8(uint8*,uint8,uint8,uint8)   | 8            | 7            | 8              |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x021**    | void Bfx_SetBits_u16u8u8u8(uint16*,uint8,uint8,uint8) | 16           | 15           | 16             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x022**    | void Bfx_SetBits_u32u8u8u8(uint32*,uint8,uint8,uint8) | 32           | 31           | 32             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x023**    | void Bfx_SetBits_u64u8u8u8(uint64*,uint8,uint8,uint8) | 64           | 63           | 64             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+

   
8.4.5 Bfx_GetBits
^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00028
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_GetBits_<TypeMn>u8u8_<TypeMn>                                       |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     <Type> Bfx_GetBits_<TypeMn>u8u8_<TypeMn> (                          |
    |                       |          <Type> Data,                                                   |
    |                       |          uint8 BitStartPn,                                              |
    |                       |          uint8 BitLn                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x26 to 0x28                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitStartPn            | Start bit position                              |
    |                       +-----------------------+-------------------------------------------------+
    |                       | BitLn                 | Bit field length                                |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | <Type>                | Bit field sequence                              |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function shall return the Bits of the input data starting from     |  
    |                       | 'BitStartPn' for the length of 'BitLn'                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00029
    :status: open
    :tags: bsw

    For Example:

    .. code-block:: c 

        Bfx_GetBits_u16u8u8_u16(1110100000000111b, 9, 5)
        returns 0000000000010100b


.. req:: None
    :id: SWS_Bfx_00034
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **Function** | **Function prototype**                                | **Maximum**  | **Maximum**  | **Maximum**    |
    | **ID[hex]**  |                                                       | **value of** | **value of** | **value of**   |
    |              |                                                       | **BitLn**    | **StartPn**  | **BitStartPn** | 
    |              |                                                       |              |              | **+ BitLn**    |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x026**    | uint8 Bfx_GetBits_u8u8u8_u8(uint8,uint8,uint8)        | 8            | 7            | 8              |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x027**    | uint16 Bfx_GetBits_u16u8u8_u16(uint16,uint8,uint8)    | 16           | 15           | 16             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x028**    | uint32 Bfx_GetBits_u32u8u8_u32(uint32,uint8,uint8)    | 32           | 31           | 32             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+
    | **0x029**    | uint64 Bfx_GetBits_u64u8u8_u64(uint64,uint8,uint8)    | 64           | 63           | 64             |
    +--------------+-------------------------------------------------------+--------------+--------------+----------------+

   
8.4.6 Bfx_SetBitMask
^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00035
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_SetBitMask_<TypeMn><TypeMn>                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_SetBitMask_<TypeMn><TypeMn> (                              |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 Mask                                                     |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x2a to 0x2c                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Mask                  | Mask used to set bits                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall set the data to logical status '1' as per the       |  
    |                       | corresponding Mask bits when set to value 1 and remaining bits will     |
    |                       | retain their original values                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00036
    :status: open
    :tags: bsw

    Expected functionality:

    .. code-block:: c 

        *Data = *Data | Mask


.. req:: None
    :id: SWS_Bfx_00038
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x02A**    | void Bfx_SetBitMask_u8u8(uint8*, uint8)               |
    +--------------+-------------------------------------------------------+
    | **0x02B**    | void Bfx_SetBitMask_u16u8(uint16*, uint8)             |
    +--------------+-------------------------------------------------------+
    | **0x02C**    | void Bfx_SetBitMask_u32u8(uint32*, uint8)             |
    +--------------+-------------------------------------------------------+
    | **0x02D**    | void Bfx_SetBitMask_u64u8(uint64*, uint8)             |
    +--------------+-------------------------------------------------------+

   
8.4.7 Bfx_ClrBitMask
^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00039
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ClrBitMask_<TypeMn><TypeMn>                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ClrBitMask_<TypeMn><TypeMn> (                              |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 Mask                                                     |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x30 to 0x32                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Mask                  | Mask value                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall clear the logical status '0' for the input data for |  
    |                       | all the bit positions as per the mask                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00040
    :status: open
    :tags: bsw

    This function shall clear the data to logical status '0' as per the corresponding mask bits 
    value when set to 1. The remaining bits shall retain their original values.
    
    Expected functionality:

    .. code-block:: c 

        *Data = *Data & ~Mask


.. req:: None
    :id: SWS_Bfx_00045
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x030**    | void Bfx_ClrBitMask_u8u8(uint8*, uint8)               |
    +--------------+-------------------------------------------------------+
    | **0x031**    | void Bfx_ClrBitMask_u16u8(uint16*, uint8)             |
    +--------------+-------------------------------------------------------+
    | **0x032**    | void Bfx_ClrBitMask_u32u8(uint32*, uint8)             |
    +--------------+-------------------------------------------------------+
    | **0x033**    | void Bfx_ClrBitMask_u64u8(uint64*, uint8)             |
    +--------------+-------------------------------------------------------+

   
8.4.8 Bfx_TstBitMask
^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00046
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_TstBitMask_<InTypeMn><InTypeMn>_u8                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     boolean Bfx_TstBitMask_<InTypeMn><InTypeMn>_u8 (                    |
    |                       |          <InType> Data,                                                 |
    |                       |          <InType> Mask                                                  |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x36 to 0x38                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Mask                  | Mask value                                      |
    +                       +-----------------------+-------------------------------------------------+
    |                       | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | boolean               | value                                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function shall return TRUE, if all bits defined in Mask value are  |  
    |                       | set in the input Data value In all other cases this function shall      |
    |                       | return FALSE.                                                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00047
    :status: open
    :tags: bsw

    .. code-block:: c 

        Result = TRUE, ((Data & Mask) == Mask)
        Result = FALSE, //all other case

    For Example:

    .. code-block:: c 

        Bfx_TstBitMask_u8u8_u8(10010011b,10010000b) 
        //returns TRUE.


.. req:: None
    :id: SWS_Bfx_00050
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x036**    | boolean Bfx_TstBitMask_u8u8_u8(uint8,uint8)           |
    +--------------+-------------------------------------------------------+
    | **0x037**    | boolean Bfx_TstBitMask_u16u16_u8(uint16,uint16)       |
    +--------------+-------------------------------------------------------+
    | **0x038**    | boolean Bfx_TstBitMask_u32u32_u8(uint32,uint32)       |
    +--------------+-------------------------------------------------------+
    | **0x039**    | boolean Bfx_TstBitMask_u64u64_u8(uint64,uint64)       |
    +--------------+-------------------------------------------------------+


8.4.9 Bfx_TstBitLnMask
^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00051
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_TstBitLnMask_<InTypeMn><InTypeMn>_u8                                |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     boolean Bfx_TstBitLnMask_<InTypeMn><InTypeMn>_u8 (                  |
    |                       |          <InType> Data,                                                 |
    |                       |          <InType> Mask                                                  |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x3a to 0x3c                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Mask                  | Mask value                                      |
    +                       +-----------------------+-------------------------------------------------+
    |                       | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | boolean               | data                                            |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function makes a test on the input data and if at least one bit is |  
    |                       | set as per the mask, then the function shall return TRUE, otherwise it  |
    |                       | shall return FALSE.                                                     |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00055
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x03A**    | boolean Bfx_TstBitLnMask_u8u8_u8(uint8,uint8)         |
    +--------------+-------------------------------------------------------+
    | **0x03B**    | boolean Bfx_TstBitLnMask_u16u16_u8(uint16,uint16)     |
    +--------------+-------------------------------------------------------+
    | **0x03C**    | boolean Bfx_TstBitLnMask_u32u32_u8(uint32,uint32)     |
    +--------------+-------------------------------------------------------+
    | **0x03D**    | boolean Bfx_TstBitLnMask_u64u64_u8(uint64,uint64)     |
    +--------------+-------------------------------------------------------+


8.4.10 Bfx_TstParityEven
^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00056
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_TstParityEven_<InTypeMn>_u8                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     boolean Bfx_TstParityEven_<InTypeMn>_u8 (                           |
    |                       |          <InTypeMn> Data,                                               |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x40 to 0x42                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | boolean               | Status                                          |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function tests the number of bits set to 1. If this number is even |  
    |                       | it shall return TRUE, otherwise it returns FALSE.                       |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00060
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x040**    | boolean Bfx_TstParityEven_u8_u8(uint8)                |
    +--------------+-------------------------------------------------------+
    | **0x041**    | boolean Bfx_TstParityEven_u16_u8(uint16)              |
    +--------------+-------------------------------------------------------+
    | **0x042**    | boolean Bfx_TstParityEven_u32_u8(uint32)              |
    +--------------+-------------------------------------------------------+
    | **0x043**    | boolean Bfx_TstParityEven_u64_u8(uint64)              |
    +--------------+-------------------------------------------------------+


8.4.11 Bfx_ToggleBits
^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00061
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ToggleBits_<TypeMn>                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ToggleBits_<TypeMn> (                                      |
    |                       |          <Type>* Data,                                                  |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x46 to 0x48                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(in)**    | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | boolean               | Status                                          |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | This function toggles all the bits of data (1's Complement Data).       |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00065
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x046**    | void Bfx_ToggleBits_u8(uint8*)                        |
    +--------------+-------------------------------------------------------+
    | **0x047**    | void Bfx_ToggleBits_u16(uint16*)                      |
    +--------------+-------------------------------------------------------+
    | **0x048**    | void Bfx_ToggleBits_u32(uint32*)                      |
    +--------------+-------------------------------------------------------+
    | **0x049**    | void Bfx_ToggleBits_u64(uint64*)                      |
    +--------------+-------------------------------------------------------+


8.4.12 Bfx_ToggleBitMask
^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00066
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ToggleBitMask_<TypeMn><TypeMn>                                      |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ToggleBitMask_<TypeMn><TypeMn> (                           |
    |                       |          <Type>* Data,                                                  |
    |                       |          <Type> Mask                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x4a to 0x4c                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Mask                  | Mask                                            |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function toggles the bits of data when the corresponding bit of the|
    |                       | mask is enabled and set to 1                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00069
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+
    | **Function** | **Function prototype**                                |
    | **ID[hex]**  |                                                       |
    +--------------+-------------------------------------------------------+
    | **0x04A**    | void Bfx_ToggleBitMask_u8u8(uint8*, uint8)            |
    +--------------+-------------------------------------------------------+
    | **0x04B**    | void Bfx_ToggleBitMask_u16u16(uint16*, uint16)        |
    +--------------+-------------------------------------------------------+
    | **0x04C**    | void Bfx_ToggleBitMask_u32u32(uint32*, uint32)        |
    +--------------+-------------------------------------------------------+
    | **0x04D**    | void Bfx_ToggleBitMask_u32u32(uint32*, uint32)        |
    +--------------+-------------------------------------------------------+


8.4.13 Bfx_ShiftBitRt
^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00070
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ShiftBitRt_<TypeMn>u8                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ShiftBitRt_<TypeMn>u8 (                                    |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 ShiftCnt                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x50 to 0x52                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ShiftCnt              | Shift right count                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall shift data to the right by ShiftCnt. The most       |
    |                       | significant bit (left-most bit) is replaced by a '0' bit and the least  |
    |                       | significant bit (right-most bit) is discarded for every single bit shift| 
    |                       | cycle.                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00075
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                | **Maximum**  |
    | **ID[hex]**  |                                                       | **value of** |
    |              |                                                       | **ShiftCnt** |
    +--------------+-------------------------------------------------------+--------------+
    | **0x050**    | void Bfx_ShiftBitRt_u8u8(uint8*, uint8)               | 7            |
    +--------------+-------------------------------------------------------+--------------+
    | **0x051**    | void Bfx_ShiftBitRt_u16u8(uint16*, uint8)             | 15           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x052**    | void Bfx_ShiftBitRt_u32u8(uint32*, uint8)             | 31           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x053**    | void Bfx_ShiftBitRt_u64u8(uint64*, uint8)             | 63           |
    +--------------+-------------------------------------------------------+--------------+


8.4.14 Bfx_ShiftBitLt
^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00076
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ShiftBitLt_<TypeMn>u8                                               |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_ShiftBitLt_<TypeMn>u8 (                                    |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 ShiftCnt                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x56 to 0x58                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ShiftCnt              | Shift left count                                |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall shift data to the left by ShiftCnt. The most        |
    |                       | significant bit (right-most bit) is replaced by a '0' bit and the least |
    |                       | significant bit (left-most bit) is discarded for every single bit shift | 
    |                       | cycle.                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00080
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                | **Maximum**  |
    | **ID[hex]**  |                                                       | **value of** |
    |              |                                                       | **ShiftCnt** |
    +--------------+-------------------------------------------------------+--------------+
    | **0x056**    | void Bfx_ShiftBitLt_u8u8(uint8*, uint8)               | 7            |
    +--------------+-------------------------------------------------------+--------------+
    | **0x057**    | void Bfx_ShiftBitLt_u16u8(uint16*, uint8)             | 15           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x058**    | void Bfx_ShiftBitLt_u32u8(uint32*, uint8)             | 31           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x059**    | void Bfx_ShiftBitLt_u64u8(uint64*, uint8)             | 63           |
    +--------------+-------------------------------------------------------+--------------+


8.4.15 Bfx_RotBitRt
^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00086
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_RotBitRt_<TypeMn>u8                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_RotBitRt_<TypeMn>u8 (                                      |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 ShiftCnt                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x5a to 0x5c                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ShiftCnt              | Shift count                                     |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall rotate data to the right by ShiftCnt. The least     |
    |                       | significant bit is rotated to the most significant bit location for     |
    |                       | every single bit shift cycle.                                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        If ShiftCnt = 1 then,
            uint8 Data = 0001 0111 (before rotate right)
            Data = 1000 1011 (after rotate right)
        
        If ShiftCnt = 3 then,
            uint8 Data = 0001 0111 (before rotate right)
            Data = 1110 0010 (after rotate right)


.. req:: None
    :id: SWS_Bfx_00090
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                | **Maximum**  |
    | **ID[hex]**  |                                                       | **value of** |
    |              |                                                       | **ShiftCnt** |
    +--------------+-------------------------------------------------------+--------------+
    | **0x05A**    | void Bfx_RotBitRt_u8u8(uint8*, uint8)                 | 7            |
    +--------------+-------------------------------------------------------+--------------+
    | **0x05B**    | void Bfx_RotBitRt_u16u8(uint16*, uint8)               | 15           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x05C**    | void Bfx_RotBitRt_u32u8(uint32*, uint8)               | 31           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x05D**    | void Bfx_RotBitRt_u64u8(uint64*, uint8)               | 63           |
    +--------------+-------------------------------------------------------+--------------+


8.4.16 Bfx_RotBitLt
^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00095
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_RotBitLt_<TypeMn>u8                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_RotBitLt_<TypeMn>u8 (                                      |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 ShiftCnt                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x60 to 0x62                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ShiftCnt              | Shift count                                     |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall rotate data to the left by ShiftCnt. The least      |
    |                       | significant bit is rotated to the most significant bit location for     |
    |                       | every single bit shift cycle.                                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        If ShiftCnt = 1 then,
            uint8 Data = 1011 0111 (before rotate left)
            Data = 0110 1111 (after rotate left)
        
        If ShiftCnt = 3 then,
            uint8 Data = 1011 0111 (before rotate left)
            Data = 1011 1101 (after rotate left)


.. req:: None
    :id: SWS_Bfx_00098
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+-------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                | **Maximum**  |
    | **ID[hex]**  |                                                       | **value of** |
    |              |                                                       | **ShiftCnt** |
    +--------------+-------------------------------------------------------+--------------+
    | **0x060**    | void Bfx_RotBitLt_u8u8(uint8*, uint8)                 | 7            |
    +--------------+-------------------------------------------------------+--------------+
    | **0x061**    | void Bfx_RotBitLt_u16u8(uint16*, uint8)               | 15           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x062**    | void Bfx_RotBitLt_u32u8(uint32*, uint8)               | 31           |
    +--------------+-------------------------------------------------------+--------------+
    | **0x063**    | void Bfx_RotBitLt_u64u8(uint64*, uint8)               | 63           |
    +--------------+-------------------------------------------------------+--------------+


8.4.17 Bfx_CopyBit
^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00101
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_CopyBit_<TypeMn>u8<TypeMn>u8                                        |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_CopyBit_<TypeMn>u8<TypeMn>u8 (                             |
    |                       |          <Type>* DestinationData,                                       |
    |                       |          uint8 DestinationPosition,                                     |
    |                       |          <Type> SourceData,                                             |
    |                       |          uint8 SourcePosition                                           |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x66 to 0x68                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | DestinationPosition   | Destination Position                            |
    |                       +-----------------------+-------------------------------------------------+
    |                       | SourceData            | Source Data                                     |
    |                       +-----------------------+-------------------------------------------------+
    |                       | SourcePosition        | Source Position                                 |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | DestinationData       | Pointer to destination data                     |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall copy a bit from source data from bit position to    |
    |                       | destination data at bit position.                                       |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        DestinationData = 10100001b
        BFX_CopyBit_u8u8u8u8(&DestinationData, 6, 11011010, 1)

    The DestinationData will have 11100001b


.. req:: None
    :id: SWS_Bfx_00108
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+--------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                 | **Maximum**  |
    | **ID[hex]**  |                                                        | **value of** |
    |              |                                                        | **ShiftCnt** |
    +--------------+--------------------------------------------------------+--------------+
    | **0x066**    | void Bfx_CopyBit_u8u8u8u8(uint8*,uint8,uint8,uint8)    | 7            |
    +--------------+--------------------------------------------------------+--------------+
    | **0x067**    | void Bfx_CopyBit_u16u8u16u8(uint16*,uint8,uint16,uint8)| 15           |
    +--------------+--------------------------------------------------------+--------------+
    | **0x068**    | void Bfx_CopyBit_u32u8u32u8(uint32*,uint8,uint32,uint8)| 31           |
    +--------------+-------------------------------------------------------+---------------+
    | **0x069**    | void Bfx_CopyBit_u64u8u64u8(uint64*,uint8,uint64,uint8)| 63           |
    +--------------+-------------------------------------------------------+---------------+


8.4.18 Bfx_PutBits
^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00110
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_PutBits_<TypeMn>u8u8<TypeMn>                                        |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_PutBits_<TypeMn>u8u8<TypeMn> (                             |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 BitStartPn,                                              |
    |                       |          uint8 BitLn,                                                   |
    |                       |          <Type> Pattern                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x70 to 0x72                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitStartPn            | Start bit position                              |
    |                       +-----------------------+-------------------------------------------------+
    |                       | BitLn                 | Bit field length                                |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Pattern               | Pattern to be set                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall put a bits as mentioned in Pattern to the input Data|
    |                       | from the specified bit position                                         |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        Data = 11110000b
        Bfx_PutBits_u8u8u8u8(&Data, 1, 3, 00000011b)

    The Data will have 11110110b


.. req:: None
    :id: SWS_Bfx_00112
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+---------------------------------------------------------+--------------+--------------+----------------+
    | **Function** | **Function prototype**                                  | **Maximum**  | **Maximum**  | **Maximum**    |
    | **ID[hex]**  |                                                         | **value of** | **value of** | **value of**   |
    |              |                                                         | **BitLn**    | **StartPn**  | **BitStartPn** | 
    |              |                                                         |              |              | **+ BitLn**    |
    +--------------+---------------------------------------------------------+--------------+--------------+----------------+
    | **0x070**    | void Bfx_PutBits_u8u8u8u8(uint8*,uint8,uint8,uint8)     | 8            | 7            | 8              |
    +--------------+---------------------------------------------------------+--------------+--------------+----------------+
    | **0x071**    | void Bfx_PutBits_u16u8u8u16(uint16*,uint8,uint8,uint16) | 16           | 15           | 16             |
    +--------------+---------------------------------------------------------+--------------+--------------+----------------+
    | **0x072**    | void Bfx_PutBits_u32u8u8u32(uint32*,uint8,uint8,uint32) | 32           | 31           | 32             |
    +--------------+---------------------------------------------------------+--------------+--------------+----------------+
    | **0x073**    | void Bfx_PutBits_u64u8u8u64(uint64*,uint8,uint8,uint64) | 64           | 63           | 64             |
    +--------------+---------------------------------------------------------+--------------+--------------+----------------+


8.4.19 Bfx_PutBitsMask
^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00120
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_PutBitsMask_<TypeMn><TypeMn><TypeMn>                                |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_PutBitsMask_<TypeMn><TypeMn><TypeMn> (                     |
    |                       |          <Type>* Data,                                                  |
    |                       |          <Type> Pattern,                                                |
    |                       |          <Type> Mask                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x80 to 0x82                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Pattern               | Pattern to be set                               |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Mask                  | Mask value                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall put all bits defined in Pattern and for which the   |
    |                       | corresponding Mask bit is set to 1 in the input Data                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        Bfx_PutBitsMask_u8u8u8(11100000b, 11001101b, 00001111b)
        results in *Data = 11101101b


.. req:: None
    :id: SWS_Bfx_00124
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+---------------------------------------------------------+
    | **Function** | **Function prototype**                                  |
    | **ID[hex]**  |                                                         |
    +--------------+---------------------------------------------------------+
    | **0x080**    | void Bfx_PutBitsMask_u8u8u8(uint8*, uint8, uint8)       |
    +--------------+---------------------------------------------------------+
    | **0x081**    | void Bfx_PutBitsMask_u16u16u16(uint16*, uint16, uint16) |
    +--------------+---------------------------------------------------------+
    | **0x082**    | void Bfx_PutBitsMask_u32u32u32(uint32*, uint32, uint32) |
    +--------------+---------------------------------------------------------+
    | **0x083**    | void Bfx_PutBitsMask_u64u64u64(uint64*, uint64, uint64) |
    +--------------+---------------------------------------------------------+


8.4.20 Bfx_PutBit
^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_00130
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_PutBit_<TypeMn>u8u8                                                 |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     void Bfx_PutBit_<TypeMn>u8u8 (                                      |
    |                       |          <Type>* Data,                                                  |
    |                       |          uint8 BitPn,                                                   |
    |                       |          boolean Status                                                 |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x85 to 0x87                                                            |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | BitPn                 | Bit position                                    |
    |                       +-----------------------+-------------------------------------------------+
    |                       | Status                | Status value                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Pointer to input data                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Return value**      | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Description**       | This function shall update the bit specified by BitPn of input data as  |
    |                       | '1' or '0' as per 'Status' value.                                       |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+

    For Example:

    .. code-block:: c 

        uint8 InputData = 11100111b;
        Bfx_PutBit_u8u8u8(&InputData, 4, TRUE);
        results in InputData = 11110111b


.. req:: None
    :id: SWS_Bfx_00132
    :status: open
    :tags: bsw

    List of implemented functions

    +--------------+---------------------------------------------------------+--------------+
    | **Function** | **Function prototype**                                  | **Maximum**  |
    | **ID[hex]**  |                                                         | **value of** |
    |              |                                                         | **BitPn**    | 
    +--------------+---------------------------------------------------------+--------------+
    | **0x085**    | void Bfx_PutBit_u8u8u8(uint8*,uint8, boolean)           | 7            |
    +--------------+---------------------------------------------------------+--------------+
    | **0x086**    | void Bfx_PutBit_u16u8u8(uint16*,uint8, boolean)         | 15           |
    +--------------+---------------------------------------------------------+--------------+
    | **0x087**    | void Bfx_PutBit_u32u8u8(uint32*,uint8, boolean)         | 31           |
    +--------------+---------------------------------------------------------+--------------+
    | **0x088**    | void Bfx_PutBit_u64u8u8(uint64*,uint8, boolean)         | 63           |
    +--------------+---------------------------------------------------------+--------------+


8.4.21 Bfx_ShiftBitSat
^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_91002
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_ShiftBitSat_<TypeMn>s8                                              |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     <Type> Bfx_ShiftBitSat_<TypeMn>s8 (                                 |
    |                       |          sint8 ShiftCnt,                                                |
    |                       |          <Type> Data                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x100                                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Non Reentrant                                                           |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | ShiftCnt              | Shift count (-<MaxShiftRight> ... -1: right, 1  |
    |                       |                       | ... <MaxShiftLeft> left)                        |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | <Type>                | Shifted and saturated bit pattern               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | Arithmetic shift with saturation                                        |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00134
    :status: open
    :tags: bsw

    If the shift count is greater than or equal to zero, then shift the value in Data by the amount 
    specified by shift count to left.

    For signed data an arithmetic shift is performed. The vacated bits are filled with zeros and the 
    result is saturated if its sign bit differs from the sign bits that are shifted out.

    For unsigned data a logical shift is performed. In this case the result is saturated, if the leading 
    one bit is shifted out.

    If the shift count is less than zero, right-shift the value in Data by the absolute value of the 
    shift count. The vacated bits are filled with the sign-bit (the most significant bit) and bits 
    shifted out are discarded.

    Note that a shift right by the word width leaves all zeros or all ones in the result, depending 
    on the sign-bit.

    Example of 32 bit signed integer: The range for shift count is -32 to +31, allowing a shift left 
    up to 31 bit positions and a shift right up to 32 bit positions (a shift right by 32 bits leaves 
    all zeros or all ones in the result, depending on the sign bit).c()


.. req:: None
    :id: SWS_Bfx_00135
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00005, SRS_LIBS_00009, SRS_LIBS_00011

    List of implemented functions

    +--------------+-----------------------------------------------------+-----------+-----------+
    | **Function** | **Function prototype**                              | **Max**   | **Max**   | 
    | **ID[hex]**  |                                                     | **Shift** | **Shift** |
    |              |                                                     | **Left**  | **Right** | 
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F1**    | sint8 Bfx_ShiftBitSat_s8s8_s8(sint8, sint8)         | 8         | 8         |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F2**    | uint8 Bfx_ShiftBitSat_u8s8_u8(uint8, sint8)         | 8         | 8         |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F3**    | sint16 Bfx_ShiftBitSat_s16s8_s16(sint16, sint8)     | 16        | 16        |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F4**    | uint16 Bfx_ShiftBitSat_u16s8_u16(uint16, sint8)     | 16        | 16        |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F5**    | sint32 Bfx_ShiftBitSat_s32s8_s32(sint32, sint8)     | 31        | 32        |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F6**    | uint32 Bfx_ShiftBitSat_u32s8_u32(uint32, sint8)     | 31        | 32        |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F7**    | sint64 Bfx_ShiftBitSat_s64s8_s64(sint64, sint8)     | 63        | 64        |
    +--------------+-----------------------------------------------------+-----------+-----------+
    | **0x0F8**    | uint64 Bfx_ShiftBitSat_u64s8_u64(uint64, sint8)     | 63        | 64        |
    +--------------+-----------------------------------------------------+-----------+-----------+


8.4.22 Bfx_CountLeadingOnes
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_91003
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_CountLeadingOnes_<TypeMn>                                           |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     uint8 Bfx_CountLeadingOnes_<TypeMn> (                               |
    |                       |          <Type> Data                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x101                                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | uint8                 | Bit position                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | Count the number of consecutive ones in Data starting with the most     |
    |                       | significant bit and return the result.                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00137
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00005, SRS_LIBS_00009, SRS_LIBS_00011

    List of implemented functions

    +--------------+-----------------------------------------------------+------------+
    | **Function** | **Function prototype**                              | **Max**    | 
    | **ID[hex]**  |                                                     | **return** |
    |              |                                                     | **value**  | 
    +--------------+-----------------------------------------------------+------------+
    | **0x0F0**    | uint8 Bfx_CountLeadingOnes_u8(uint8)                | 8          |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F1**    | uint8 Bfx_CountLeadingOnes_u16(uint16)              | 16         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F2**    | uint8 Bfx_CountLeadingOnes_u32(uint32)              | 32         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F3**    | uint8 Bfx_CountLeadingOnes_u64(uint64)              | 64         |
    +--------------+-----------------------------------------------------+------------+
    

8.4.23 Bfx_CountLeadingSigns
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_91004
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_CountLeadingSigns_<TypeMn>                                          |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     uint8 Bfx_CountLeadingSigns_<TypeMn> (                              |
    |                       |          <Type> Data                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x102                                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | uint8                 | Bit position                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | Count the number of consecutive bits which have the same value as most  |
    |                       | significant bit in Data, starting with bit at position msb minus one.   |
    |                       | Put the result in Data. It is the number of leading sign bits minus one,| 
    |                       | giving the number of redundant sign bits in Data                        |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00139
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00005, SRS_LIBS_00009, SRS_LIBS_00011

    List of implemented functions

    +--------------+-----------------------------------------------------+------------+
    | **Function** | **Function prototype**                              | **Max**    | 
    | **ID[hex]**  |                                                     | **return** |
    |              |                                                     | **value**  | 
    +--------------+-----------------------------------------------------+------------+
    | **0x0F4**    | uint8 Bfx_CountLeadingSigns_s8(sint8)               | 8          |
    +-------------+------------------------------------------------------+------------+
    | **0x0F5**    | uint8 Bfx_CountLeadingSigns_s16(sint16)             | 16         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F6**    | uint8 Bfx_CountLeadingSigns_s32(sint32)             | 32         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F7**    | uint8 Bfx_CountLeadingSigns_s64(sint64)             | 64         |
    +--------------+-----------------------------------------------------+------------+


8.4.24 Bfx_CountLeadingZeros
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Bfx_91005
    :status: open
    :tags: bsw

    +-----------------------+-------------------------------------------------------------------------+
    | **Service Name**      | Bfx_CountLeadingZeros_<TypeMn>                                          |
    +-----------------------+-------------------------------------------------------------------------+
    | **Syntax**            | .. code-block:: c                                                       |
    |                       |                                                                         |
    |                       |     uint8 Bfx_CountLeadingZeros_<TypeMn> (                              |
    |                       |          <Type> Data                                                    |
    |                       |      )                                                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Service ID [hex]**  | 0x103                                                                   |
    +-----------------------+-------------------------------------------------------------------------+
    | **Sync/Async**        | Synchronous                                                             |
    +-----------------------+-------------------------------------------------------------------------+
    | **Reentrancy**        | Reentrant                                                               |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(in)**    | Data                  | Input data                                      |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Parameters(inout)** | None                                                                    |
    +-----------------------+-------------------------------------------------------------------------+
    | **Parameters(out)**   | None                                                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Return value**      | uint8                 | Bit position                                    |
    +-----------------------+-----------------------+-------------------------------------------------+
    | **Description**       | Count the number of consecutive zeros in Data starting with the most    |
    |                       | significant bit and return the result.                                  |
    +-----------------------+-------------------------------------------------------------------------+
    | **Available via**     | Bfx.h                                                                   |
    +-----------------------+-------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Bfx_00141
    :status: open
    :tags: bsw
    :links: SRS_LIBS_00005, SRS_LIBS_00009, SRS_LIBS_00011

    List of implemented functions

    +--------------+-----------------------------------------------------+------------+
    | **Function** | **Function prototype**                              | **Max**    | 
    | **ID[hex]**  |                                                     | **return** |
    |              |                                                     | **value**  | 
    +--------------+-----------------------------------------------------+------------+
    | **0x0F8**    | sint8 Bfx_CountLeadingZeros_u8(uint8)               | 8          |
    +--------------+-----------------------------------------------------+------------+
    | **0x0F9**    | sint8 Bfx_CountLeadingZeros_u16(uint16)             | 16         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0FA**    | sint8 Bfx_CountLeadingZeros_u32(uint32)             | 32         |
    +--------------+-----------------------------------------------------+------------+
    | **0x0FB**    | sint8 Bfx_CountLeadingZeros_u64(uint64)             | 64         |
    +--------------+-----------------------------------------------------+------------+

    