Specification of Platform Types
===============================

This document specifies the AUTOSAR platform types header file. It contains all platform dependent 
types and symbols. Those types must be abstracted in order to become platform and compiler independent.
It is required that all platform types files are unique within the AUTOSAR community to guarantee 
unique types per platform and to avoid type changes when moving a
software module from platform A to B

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SWS_PlatformTypes.pdf


7 Functional specification
--------------------------

7.1 General issues
^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Platform_00002
    :status: open
    :tags: bsw

    All platform specific abstracted AUTOSAR data types and symbols shall be defined in the 
    `Platform_Types.h`  header file. It is not allowed to add any extension to this file. Any extension 
    invalidates the AUTOSAR conformity.


7.2 CPU Type
^^^^^^^^^^^^

.. req:: None
    :id: SWS_Platform_00044
    :status: open
    :tags: bsw

    For each platform the register width of the CPU used shall be indicated by defining `CPU_TYPE`


.. req:: None
    :id: SWS_Platform_00045
    :status: open
    :tags: bsw

    According to the register width of the CPU used, `CPU_TYPE` shall be assigned to one of the symbols 
    `CPU_TYPE_8`, `CPU_TYPE_16`, `CPU_TYPE_32` or `CPU_TYPE_64`.


7.3 Endianess
^^^^^^^^^^^^^

The pattern for bit, byte and word ordering in native types, such as integers, is called endianess.

.. req:: None
    :id: SWS_Platform_00043
    :status: open
    :tags: bsw

    For each platform the appropriate bit order on register level shall be indicated in the platform 
    types header file using the symbol `CPU_BIT_ORDER`


.. req:: None
    :id: SWS_Platform_00046
    :status: open
    :tags: bsw

    For each platform the appropriate byte order on memory level shall be indicated in the platform 
    types header file using the symbol `CPU_BYTE_ORDER`


7.3.1 Bit Ordering (Register)
"""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Platform_00048
    :status: open
    :tags: bsw

    In case of Big Endian bit ordering `CPU_BIT_ORDER` shall be assigned to `MSB_FIRST` in the platform 
    types header file.


.. req:: None
    :id: SWS_Platform_00049
    :status: open
    :tags: bsw

    In case of Little Endian bit ordering `CPU_BIT_ORDER` shall be assigned to `LSB_FIRST` in the 
    platform types header file

    .. image:: img/specification-of-platform-types-fig7.1.png

    **Important Note:**

    The naming convention Bit0, Bit1, etc. and the bit's significance within a byte, word, etc.
    are different topics and shall not be mixed. The counting scheme of bits in Motorola[3]
    µC-architecture's (Big Endian Bit Order) starts with Bit0 indicating the Most Significant
    Bit, whereas all other µC using Little Endian Bit Order assign Bit0 to be the Least
    Significant Bit!

    The MSB in an accumulator is always stored as the left-most bit regardless of the CPU
    type. Hence, Big and Little Endianess bit orders imply different bit-naming conventions


7.3.2 Byte Ordering (Memory)
""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Platform_00050
    :status: open
    :tags: bsw

    In case of Big Endian byte ordering `CPU_BYTE_ORDER` shall be assigned to `HIGH_BYTE_FIRST` in the 
    platform types header file

    .. image:: img/specification-of-platform-types-fig7.2.png

    +----------------+----------------+------------------------+
    | **Address**    | **Data**       | **Order**              |
    +================+================+========================+
    |n               |Byte 1          | Most Significant Byte  |
    |                |                | `HIGH_BYTE_FIRST`      |
    +----------------+----------------+------------------------+
    |n+1             |Byte 0          | Least Significant Byte |
    +----------------+----------------+------------------------+
    

.. req:: None
    :id: SWS_Platform_00051
    :status: open
    :tags: bsw

    dIn case of Little Endian byte ordering `CPU_BYTE_ORDER` shall be assigned to `LOW_BYTE_FIRST` 
    in the platform types header file

    .. image:: img/specification-of-platform-types-fig7.3.png

    +----------------+----------------+------------------------+
    | **Address**    | **Data**       | **Order**              |
    +================+================+========================+
    |n               |Byte 1          | Least Significant Byte |
    |                |                | `HIGH_BYTE_FIRST`      |
    +----------------+----------------+------------------------+
    |n+1             |Byte 0          | Most Significant Byte  |
    +----------------+----------------+------------------------+

    **Naming convention for illustration:** The Most Significant Byte within a 16 bit wide
    data is named Byte1. The Least Significant Byte within a 16 bit wide data is named Byte0.

    **Important Note:** The naming convention Byte0 and Byte1 is not unique and may be
    different in the manufacturer's reference documentation for a particular µC.


7.4 Optimized integer data types
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For details refer to the chapter "AUTOSAR Integer Data Types" of the document "General Requirements 
on Basic Software Modules" [1].

Examples of usage:

- Loop counters (e.g. maximum loop count = 124 ⇒ use `uint8_least`
- Switch case arguments (e.g. maximum number of states = 17 ⇒ use `uint8_least`


7.5 Boolean data type
^^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Platform_00027
    :status: open
    :tags: bsw
    :links: SRS_BSW_00378

    The standard AUTOSAR type `boolean` shall be implemented using the C99 build-in type `_Bool`

    Note: According to [4], chapter 6.2.5 (page 33), line 2, an object declared as type `_Bool` is 
    large enough to store the values 0 and 1. Thus, the exact size of an object of type `boolean` is 
    NOT defined by AUTOSAR anymore.


.. req:: None
    :id: SWS_Platform_00034
    :status: open
    :tags: bsw
    :links: SRS_BSW_00378

    The standard AUTOSAR type `boolean` shall only be used in conjunction with the standard symbols 
    `TRUE` and `FALSE`. For value assignments of variables of type boolean no arithmetic or logical 
    operators (`+, ++, -, --, *, /, %, <<, >>, ~, &`) must be used. The only allowed forms of assignment 
    are:

    .. code-block:: c

        1 boolean var = TRUE;
        2 ...
        3 var = TRUE;
        4 var = FALSE;
        5 var = (a < b) /* same for ">", "<=", ">=" */
        6 var = (c && d) /* same for "!", "||" */
        7 var = (e != f) /* same for "==" */

    The only allowed forms of comparison are:

    .. code-block:: c

        1 boolean var = FALSE;
        2 ...
        3 if (var == TRUE) ...
        4 if (var == FALSE) ...
        5 if (var != TRUE) ...
        6 if (var != FALSE) ...
        7 if (var) ...
        8 if (!var) ...


7.6 Error classification
^^^^^^^^^^^^^^^^^^^^^^^^

Section 7.2 "Error Handling" of the document "General Specification of Basic Software Modules" 
describes the error handling of the Basic Software in detail. Above all, it constitutes a 
classification scheme consisting of five error types which may occur in BSW modules.
    
Based on this foundation, the following section specifies particular errors arranged in the respective 
subsections below.


7.6.1 Development Errors
""""""""""""""""""""""""

There are no development errors.

7.6.2 Runtime Errors
""""""""""""""""""""

There are no runtime errors.

7.6.3 Transient Faults
""""""""""""""""""""""

There are no transient faults.

7.6.4 Production Errors
"""""""""""""""""""""""

There are no production errors.

7.6.5 Extended Production Errors
""""""""""""""""""""""""""""""""

There are no extended production errors


8 API specification
-------------------

8.1 Imported types
^^^^^^^^^^^^^^^^^^

Not applicable.

8.2 Type definitions
^^^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Platform_00061
    :status: open
    :tags: bsw

    Concerning the signed integer types, AUTOSAR supports for compiler and target implementation 
    only 2 complement arithmetic. This directly impacts the chosen ranges for these types


8.2.1 boolean
"""""""""""""

.. req:: boolean
    :id: SWS_Platform_00026
    :status: open
    :tags: bsw
    :links: SRS_BSW_00378, SWS_Platform_00027

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + boolean                                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+--------------+--------------------------------------------------------------+
    | **Range**         | FALSE        | false                                                        |
    |                   +--------------+--------------------------------------------------------------+
    |                   | TRUE         | true                                                         |
    +-------------------+--------------+--------------------------------------------------------------+
    | **Description**   | This standard AUTOSAR type shall only be used together with the definitions | 
    |                   | TRUE and FALSE                                                              |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     | -                                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.1 uint8
"""""""""""

.. req:: uint8
    :id: SWS_Platform_00013
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint8                                                                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | UINT8_MIN        | 0                   | Minimum possible uint8 value       |
    |                   +------------------+---------------------+------------------------------------+
    |                   | UINT8_MAX        | 255                 | Maximum possible uint8 value       |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 8 bit unsigned                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     | -                                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.2 uint16
""""""""""""

.. req:: uint16
    :id: SWS_Platform_00014
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint16                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | UINT16_MIN       | 0                   | Minimum possible uint16 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | UINT16_MAX       | 65535               | Maximum possible uint16 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 16 bit unsigned                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     | -                                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.4 uint32
""""""""""""

.. req:: uint32
    :id: SWS_Platform_00015
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint32                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | UINT32_MIN       | 0                   | Minimum possible uint32 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | UINT32_MAX       | 4294967295          | Maximum possible uint32 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 32 bit unsigned                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     | -                                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.5 uint64
""""""""""""

.. req:: uint64
    :id: SWS_Platform_00066
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint64                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | UINT64_MIN       | 0                   | Minimum possible uint64 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | UINT64_MAX       | 18446744073709551615| Maximum possible uint64 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 64 bit unsigned                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     | -                                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.6 sint8
"""""""""""

.. req:: sint8
    :id: SWS_Platform_00016
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint8                                                                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | SINT8_MIN        | -128                | Minimum possible sint8 value       |
    |                   +------------------+---------------------+------------------------------------+
    |                   | SINT8_MAX        | 127                 | Maximum possible sint8 value       |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 8 bit signed                         |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.7 sint16
""""""""""""

.. req:: sint16
    :id: SWS_Platform_00017
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint16                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | SINT16_MIN       | -32768              | Minimum possible sint16 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | SINT16_MAX       | 32767               | Maximum possible sint16 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 16 bit signed                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.8 sint32
""""""""""""

.. req:: sint32
    :id: SWS_Platform_00018
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint32                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | SINT32_MIN       | -2147483648         | Minimum possible sint32 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | SINT32_MAX       | 2147483647          | Maximum possible sint32 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 32 bit signed                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.9 sint64
""""""""""""

.. req:: sint64
    :id: SWS_Platform_00067
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint64                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | SINT64_MIN       | -9223372036854775808| Minimum possible sint64 value      |
    |                   +------------------+---------------------+------------------------------------+
    |                   | SINT64_MAX       | 9223372036854775807 | Maximum possible sint64 value      |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be of 64 bit unsigned                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Variation**     |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.10 uint8_least
""""""""""""""""""

.. req:: uint8_least
    :id: SWS_Platform_00020
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint8_least                                                                 |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------+----------------------------------------------------------+
    | **Derived from**  | uint             |                                                          |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Range**         | At least 0..255  |                     | 0x00..0xff                         |
    +-------------------+------------------+---------------------+------------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 8 bit unsigned                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.11 uint16_least
"""""""""""""""""""

.. req:: uint16_least
    :id: SWS_Platform_00021
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint16_least                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+-------------------+---------------------------------------------------------+
    | **Derived from**  | uint              |                                                         |
    +-------------------+-------------------+--------------------+------------------------------------+
    | **Range**         | At least 0..65535 |                    | 0x0000..0xffff                     |
    +-------------------+-------------------+--------------------+------------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 16 bit unsigned               |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.12 uint32_least
"""""""""""""""""""

.. req:: uint32_least
    :id: SWS_Platform_00022
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + uint32_least                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------------+----------------------------------------------------+
    | **Derived from**  | uint                   |                                                    |
    +-------------------+------------------------+---------------+------------------------------------+
    | **Range**         | At least 0..4294967295 |               | 0x00000000..0xFFFFFFFF             |
    +-------------------+------------------------+---------------+------------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 32 bit unsigned               |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.13 sint8_least
""""""""""""""""""

.. req:: sint8_least
    :id: SWS_Platform_00023
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint8_least                                                                 |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+---------------------+-------------------------------------------------------+
    | **Derived from**  | sint                |                                                       |
    +-------------------+---------------------+------------------+------------------------------------+
    | **Range**         | At least -128..+127 |                  | 0x80..0x7F                         |
    +-------------------+---------------------+------------------+------------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 8 bit signed                  |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.14 sint16_least
"""""""""""""""""""

.. req:: sint16_least
    :id: SWS_Platform_00024
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint16_least                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+-------------------------+---------------------------------------------------+
    | **Derived from**  | sint                    |                                                   |
    +-------------------+-------------------------+--------------------+------------------------------+
    | **Range**         | At least -32768..+32767 |                    | 0x8000..0x7FFF               |
    +-------------------+-------------------------+--------------------+------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 16 bit signed                 |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.15 sint32_least
"""""""""""""""""""

.. req:: uint32_least
    :id: SWS_Platform_00025
    :status: open
    :tags: bsw
    :links: SRS_BSW_00304

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + sint32_least                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+------------------------------------+----------------------------------------+
    | **Derived from**  | sint                               |                                        |
    +-------------------+------------------------------------+----+-----------------------------------+
    | **Range**         | At least -2147483648..+21474836475 |    | 0x80000000..0x7FFFFFFF            |
    +-------------------+------------------------------------+----+-----------------------------------+
    | **Description**   | This optimized AUTOSAR type shall be at least 32 bit signed                 |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.16 float32
""""""""""""""

.. req:: float32
    :id: SWS_Platform_00041
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + float32                                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+----------------------+------------------+-----------------------------------+
    | **Range**         | FLOAT32_MIN          | 1.17549435e-38   | Smallest positive value of float32|
    +-------------------+----------------------+------------------+-----------------------------------+
    |                   | FLOAT32_MAX          | 3.40282347e+38   | Largest value of float32          |
    +-------------------+----------------------+------------------+-----------------------------------+
    |                   | FLOAT32_EPSILON      |1.19209290e-07    | Smallest increment between two    |
    |                   |                      |                  | values of float32                 |
    +-------------------+----------------------+------------------+-----------------------------------+
    | **Description**   | This standard AUTOSAR type shall follow the 32-bit binary interchange format|
    |                   | according to IEEE 754-2008 with encoding parameters specified in chapter 3.6| 
    |                   | table 3.5, column "binary32"                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.17 float64
""""""""""""""

.. req:: float64
    :id: SWS_Platform_00042
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + float64                                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Type                                                                        |
    +-------------------+----------------+------------------------+-----------------------------------+
    | **Range**         | FLOAT64_MIN    | 2.2250738585072014e-308| Smallest positive value of float64|
    +-------------------+----------------+------------------------+-----------------------------------+
    |                   | FLOAT64_MAX    |1.7976931348623157e+308 | Largest value of float64          |
    +-------------------+----------------+------------------------+-----------------------------------+
    |                   | FLOAT64_EPSILON|2.2204460492503131e-16  | Smallest increment between two    |
    |                   |                |                        | values of float64                 |
    +-------------------+----------------+------------------------+-----------------------------------+
    | **Description**   | This standard AUTOSAR type shall follow the 64-bit binary interchange format|
    |                   | according to IEEE 754-2008 with encoding parameters specified in chapter 3.6| 
    |                   | table 3.5, column "binary64"                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.18 VoidPtr
""""""""""""""

.. req:: VoidPtr
    :id: SWS_Platform_91001
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + VoidPtr                                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Pointer                                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Type**          + void*                                                                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be a void pointer                          |
    |                   |                                                                             |
    |                   | Note: This type shall be used for buffers that contain data returned to the |
    |                   | caller                                                                      |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.2.19 ConstVoidPtr
"""""""""""""""""""

.. req:: VoidPtr
    :id: SWS_Platform_91002
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + ConstVoidPtr                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Const Pointer                                                               |
    +-------------------+-----------------------------------------------------------------------------+
    | **Type**          + const void*                                                                 |
    +-------------------+-----------------------------------------------------------------------------+
    | **Description**   | This standard AUTOSAR type shall be a void pointer to const                 |
    |                   |                                                                             |
    |                   | Note: This type shall be used for buffers that passed to callee             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.3 Symbol definitions
^^^^^^^^^^^^^^^^^^^^^^

8.3.1 CPU_TYPE
""""""""""""""

.. req:: CPU_TYPE
    :id: SWS_Platform_00064
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          + CPU_TYPE                                                                    |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          + Enumeration                                                                 |
    +-------------------+----------------+------------------------+-----------------------------------+
    | **Range**         | CPU_TYPE_8     |                        | Indicating a 8 bit processor      |
    +-------------------+----------------+------------------------+-----------------------------------+
    |                   | CPU_TYPE_16    |                        | Indicating a 16 bit processor     |
    +-------------------+----------------+------------------------+-----------------------------------+
    |                   | CPU_TYPE_64    |                        | Indicating a 32 bit processor     |
    +-------------------+----------------+------------------------+-----------------------------------+
    |                   |                |                        | Indicating a 64 bit processor     |
    +-------------------+----------------+------------------------+-----------------------------------+
    | **Description**   | This symbol shall be defined as #define having one of the values CPU_TYPE_8 |
    |                   | CPU_TYPE_16, CPU_TYPE_32 or CPU_TYPE_64 according to the platform           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.3.2 CPU_BIT_ORDER
"""""""""""""""""""

.. req:: CPU_BIT_ORDER
    :id: SWS_Platform_00038
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | CPU_BYTE_ORDER                                                              |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+---------------+-+-----------------------------------------------------------+
    | **Range**         |HIGH_BYTE_FIRST| |Within uint16, the high byte is located before the low byte|
    +-------------------+---------------+-+-----------------------------------------------------------+
    |                   |LOW_BYTE_FIRST | |Within uint16, the low byte is located before the high byte|
    +-------------------+---------------+-+-----------------------------------------------------------+
    | **Description**   | This symbol shall be defined as #define having one of the values            |
    |                   | HIGH_BYTE_FIRST, or LOW_BYTE_FIRST according to the platform                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


8.3.4 TRUE, FALSE
"""""""""""""""""""

.. req:: TRUE, FALSE
    :id: SWS_Platform_00056
    :status: open
    :tags: bsw

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | TRUE_FALSE                                                                  |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+---------------+-------+-----------------------------------------------------+
    | **Range**         | FALSE         | false |                                                     |
    +-------------------+---------------+-------+-----------------------------------------------------+
    |                   | TRUE          | true  |                                                     |
    +-------------------+---------------+-------+-----------------------------------------------------+
    | **Description**   | The symbols TRUE and FALSE shall be defined as follows:                     |
    |                   |                                                                             |
    |                   |   .. code-block:: c                                                         |
    |                   |                                                                             |
    |                   |       #ifndef TRUE                                                          |
    |                   |       #define TRUE true                                                     |
    |                   |       #endif                                                                |
    |                   |                                                                             |
    |                   |       #ifndef FALSE                                                         |
    |                   |       #define FALSE false                                                   |
    |                   |       #endif                                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Platform_Types.h                                                            |
    +-------------------+-----------------------------------------------------------------------------+


.. req:: none
    :id: SWS_Platform_00054
    :status: open
    :tags: bsw

    In case of in-built compiler support of the symbols, redefinitions shall be avoided using a conditional 
    check


.. req:: none
    :id: SWS_Platform_00055
    :status: open
    :tags: bsw

    These symbols shall only be used in conjunction with the `boolean` type defined in `Platform_Types.h`


8.4 Function definitions
^^^^^^^^^^^^^^^^^^^^^^^^

Not applicable.

8.5 Call-back notifications
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Not applicable.

8.6 Scheduled functions
^^^^^^^^^^^^^^^^^^^^^^^

Not applicable.

8.7 Expected Interfaces
^^^^^^^^^^^^^^^^^^^^^^^

Not applicable
