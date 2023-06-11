Specification of Standard Types
===============================

This document specifies the AUTOSAR standard types header file. It contains all types that are used 
across several modules of the basic software and that are platform and compiler independent.

It is strongly recommended that those standard types files are unique within the AUTOSAR community to 
guarantee unique types and to avoid types changes when changing from supplier A to B.

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SWS_StandardTypes.pdf


5 Software Architecture
-----------------------

5.1 Dependencies to other modules
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

5.2 File structure
^^^^^^^^^^^^^^^^^^

The include structures differ between BSW modules which are part of the COM-stack and other modules. 
BSW modules which is considered part of the COM stack shall include the ComStackTypes.h other modules 
shall include StandardTypes.h

5.2.1 Communication related BSW modules
"""""""""""""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00030
    :status: open
    :tags: bsw

    The include file structure shall be as follows:

    - ComStackTypes.h shall include StandardTypes.h
    - Communication related basic software modules shall include ComStackTypes.h


7 Functional specification
--------------------------

7.1 General issues
^^^^^^^^^^^^^^^^^^

.. req:: None
    :id: SWS_Std_00004
    :status: open
    :tags: bsw
    :links: SRS_BSW_00161

    It is not allowed to add any project or supplier specific extension to this file. Any extension 
    invalidates the AUTOSAR conformity.


.. req:: None
    :id: SWS_Std_00014
    :status: open
    :tags: bsw

    The standard types header file shall be protected against multiple inclusion:

    .. code-block:: c

        #ifndef STD_TYPES_H
        #define STD_TYPES_H

         ..
        /*
         * Contents of file
         */
         ..

        #endif /* STD_TYPES_H */


8 API specification
-------------------

8.1 Type definitions
^^^^^^^^^^^^^^^^^^^^

8.1.1 Std_ReturnType
""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00005
    :status: open
    :tags: bsw
    :links: SRS_BSW_00357

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_ReturnType                                                              |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+--------------+------+-------------------------------------------------------+
    | **Range**         | E_OK         | 0    | see 8.2.1, SWS_Std_00006                              |
    |                   +--------------+------+-------------------------------------------------------+
    |                   | E_NOT_OK     | 1    | see 8.2.1, SWS_Std_00006                              |
    |                   +--------------+------+-------------------------------------------------------+
    |                   | 0x02-0x3F    | 2    | Available to user specific errors                     |
    +-------------------+--------------+------+-------------------------------------------------------+
    | **Description**   | This type can be used as standard API return type which is shared between   |
    |                   | the RTE and the BSW modules. It shall be defined as follows:                |
    |                   | typedef uint8 Std_ReturnType                                                |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Std_00011
    :status: open
    :tags: bsw
    :links: SRS_BSW_00357, SRS_BSW_00441

    The Std_ReturnType shall normally be used with value E_OK or E_NOT_OK. If those return values 
    are not sufficient user specific values can be defined by using the 6 least specific bits.

    For the naming of the user defined values the module prefix shall be used as requested in 
    SRS_BSW_00441

    Layout of the Std_ReturnType shall be as stated in the RTE specification. Bit 7 and Bit 8 are 
    reserved and defined by the RTE specification


.. req:: None
    :id: SWS_Std_00015
    :status: open
    :tags: bsw
    :links: SRS_BSW_00004

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_VersionInfoType                                                         |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Structure                                                                   |
    +-------------------+-----------------------------------------------------------------------------+
    | **Elements**      | vendorID                                                                    |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | uint16                                                       |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    |                   +--------------+--------------------------------------------------------------+
    |                   | moduleID                                                                    |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | uint16                                                       |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    |                   +--------------+--------------------------------------------------------------+
    |                   | sw_major_version                                                            |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | uint8                                                        |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    |                   +--------------+--------------------------------------------------------------+
    |                   | sw_minor_version                                                            |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | uint8                                                        |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    |                   +--------------+--------------------------------------------------------------+
    |                   | sw_patch_version                                                            |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | uint8                                                        |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    +-------------------+--------------+--------------------------------------------------------------+
    | **Description**   | This type shall be used to request the version of a BSW module using the    |
    |                   | <Module name>_Get VersionInfo() function.                                   |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.1.3 Std_TransformerError
""""""""""""""""""""""""""

The data type Std_TransformerError is a struct which contains the error code and the transformer 
class to which the error belongs.

The data type Std_TransformerError shall be defined as follows:


.. req:: None
    :id: SWS_Std_00021
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00004

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_TransformerError                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Structure                                                                   |
    +-------------------+-----------------------------------------------------------------------------+
    | **Elements**      | errorCode                                                                   |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | Std_TransformerErrorCode                                     |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  | The specific meaning of the values of                        |
    |                   |              | Std_TransformerErrorCode is to be seen for the specific      |
    |                   |              | transformer chain for which the data type represents the     |
    |                   |              | transformer error                                            |
    |                   +--------------+--------------------------------------------------------------+
    |                   | transformerClass                                                            |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Type**     | Std_TransformerClass                                         |
    |                   +--------------+--------------------------------------------------------------+
    |                   | **Comment**  |                                                              |
    +-------------------+--------------+--------------------------------------------------------------+
    | **Description**   | Std_TransformerError represents a transformer error in the context of a     |
    |                   | certain transformer chain                                                   |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+

    The values are specified for each transformer class in [26, ASWS Transformer General]


.. req:: None
    :id: SWS_Std_00022
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00004, SRS_Xfrm_00008

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_TransformerErrorCode                                                    |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Derived from**  | uint8                                                                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Range**         | The values are specified for each transformer class in                      |
    |                   | ASWS_TransformerGeneral                                                     |
    +-------------------+-----------------------------------------------------------------------------+
    | **Description**   | The type of the Std_TransformerError                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+

    The Std_TransformerClass represents the transformer class in which the error occurred.


.. req:: None
    :id: SWS_Std_00023
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00009, SRS_Xfrm_00008

    The underlying data type of the type Std_TransformerClass shall be uint8

    The type Std_TransformerClass shall be an enumeration with the following elements where each 
    element represents a transformer class:


.. req:: None
    :id: SWS_Std_00024
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00004, SRS_Xfrm_00010

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_TransformerClass                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Derived from**  | uint8                                                                       |
    +-------------------+------------------+------+---------------------------------------------------+
    | **Range**         | STD_TRANSFORMER  | 0x00 | Transformer of a unspecified transformer class    |
    |                   | UNSPECIFIED      |      |                                                   |
    |                   +------------------+------+---------------------------------------------------+
    |                   | STD_TRANSFORMER  | 0x01 | Transformer of a serializer class.                |
    |                   | SERIALIZER       |      |                                                   |
    |                   +------------------+------+---------------------------------------------------+
    |                   | STD_TRANSFORMER  | 0x02 | Transformer of a safety class.                    |
    |                   | SAFETY           |      |                                                   |
    |                   +------------------+------+---------------------------------------------------+
    |                   | STD_TRANSFORMER  | 0x03 | Transformer of a security class.                  |
    |                   | SECURITY         |      |                                                   |
    |                   +------------------+------+---------------------------------------------------+
    |                   | STD_TRANSFORMER  | 0xFF | Transformer of a custom class not standardized by |
    |                   | CUSTOM           |      | AUTOSAR                                           |
    +-------------------+------------------+------+---------------------------------------------------+
    | **Description**   | Std_TransformerClass is an enumeration where each element represents a      |
    |                   | transformer class                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Std_00025
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00004

    The transformer class STD_TRANSFORMER_UNSPECIFIED shall be used if no transformer error occured


.. req:: None
    :id: SWS_Std_00026
    :status: open
    :tags: bsw
    
    .. links: SRS_Xfrm_00011

    The mapping from transformerClass of TransformationTechnology to value of data type 
    Std_TransformerClass shall be:

    - transformerClass serializer - STD_TRANSFORMER_SERIALIZER
    - transformerClass safety - STD_TRANSFORMER_SAFETY
    - transformerClass security - STD_TRANSFORMER_SECURITY
    - transformerClass custom - STD_TRANSFORMER_CUSTOM


8.1.4 Std_TransformerForwardCode
""""""""""""""""""""""""""""""""

The data type Std_TransformerForwardCode represents a forwarded transformer code in the context of 
a certain transformer chain (see [5]).

The specific meaning of the values of Std_TransformerForwardCode is always to be seen for the specific 
transformer chain for which the data type represents the transformer status.

.. req:: None
    :id: SWS_Std_00028
    :status: draft
    :tags: bsw
    
    .. links: SRS_Xfrm_00002

    A safety transformer shall handle the forwarded status according to table 8.1

    +---------------------------------------+---------------------------------------------------------+
    | **Error Name**       | **Error Code** | **Description**                                         |
    +----------------------+----------------+---------------------------------------------------------+
    | E_OK                 | 0x00           | No specific error to be injected                        |
    +----------------------+----------------+---------------------------------------------------------+
    | E_SAFETY_INVALID_REP | 0x01           | Repeat the last used sequence number                    |
    +----------------------+----------------+---------------------------------------------------------+
    | E_SAFETY_INVALID_CRC | 0x03           | Generate a deliberately wrong CRC                       |
    +----------------------+----------------+---------------------------------------------------------+
    | E_SAFETY_INVALID_SEQ | 0x02           | Use a wrong sequence number                             |
    +----------------------+----------------+---------------------------------------------------------+

    The underlying data type of the type Std_TransformerForwardCode shall be uint8


.. req:: None
    :id: SWS_Std_00029
    :status: draft
    :tags: bsw
    
    .. links: SRS_Xfrm_00002

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_TransformerForwardCode                                                  |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Derived from**  | uint8                                                                       |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Range**         | E_OK                 | 0x00 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | E_SAFETY_INVALID_REP | 0x01 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | E_SAFETY_INVALID_SEQ | 0x02 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | E_SAFETY_INVALID_CRC | 0x03 |                                               |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Description**   |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.1.5 Std_MessageTypeType
"""""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_91001
    :status: open
    :tags: bsw
    :links: SRS_BSW_00305

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_MessageTypeType                                                         |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Derived from**  | uint8                                                                       |
    +-------------------+--------------------------+------+-------------------------------------------+
    | **Range**         | STD_MESSAGETYPE_REQUEST  | 0x00 | Message type for a request message        |
    |                   +--------------------------+------+-------------------------------------------+
    |                   | STD_MESSAGETYPE_RESPONSE | 0x01 | Message type for a response message       |
    |                   +--------------------------+------+-------------------------------------------+
    |                   | 0x02-0x3F                | 0x02 | Reserverd for future message type         |
    +-------------------+--------------------------+------+-------------------------------------------+
    | **Description**   | This type is used to encode the different type of messages. - Currently this| 
    |                   | encoding is limited to the distinction between requests and responses in    | 
    |                   | C/S communication                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Std_00017
    :status: open
    :tags: bsw
    :links: SRS_BSW_00305

    The Std_MessageTypeType shall be used ot encode the different types of messages exchanged in 
    AUTOSAR. - Currently this encoding is limited to the distinction between requests and responses 
    in C/S communication.c(SRS_BSW_00305)

    Note: In future AUTOSAR release, the literals for this type may be extended with additional message 
    types.


8.1.6 Std_MessageResultType
"""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_91002
    :status: open
    :tags: bsw
    :links: SRS_BSW_00305

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | Std_MessageResultType                                                       |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Type                                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Derived from**  | uint8                                                                       |
    +-------------------+-------------------------+------+--------------------------------------------+
    | **Range**         | STD_MESSAGERESULT_OK    | 0x00 | STD_MESSAGERESULT_OK                       |
    |                   +-------------------------+------+--------------------------------------------+
    |                   | STD_MESSAGERESULT_ERROR | 0x01 | Messageresult for an ERROR response        |
    |                   +-------------------------+------+--------------------------------------------+
    |                   | 0x02-0x3F               | 0x02 | Reserverd for future message results       |
    +-------------------+-------------------------+------+--------------------------------------------+
    | **Description**   | This type is used to encode different types of results for response messages| 
    |                   | - Currently this encoding is limited to the distinction between OK and ERROR| 
    |                   | responses                                                                   |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


.. req:: None
    :id: SWS_Std_00019
    :status: open
    :tags: bsw
    :links: SRS_BSW_00305

    The Std_MessageResultType shall be used ot encode the different types of results for response 
    messages. - Currently this encoding is limited to the distinction between OK and ERROR 
    responses (SRS_BSW_00305)

    Note: In future AUTOSAR release, the literals for this type may be extended with additional 
    result types


8.1.7 Std_ExtractProtocolHeaderFieldsType
"""""""""""""""""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_91003
    :status: open
    :tags: bsw
    :links: SRS_BSW_00004

    +---------------------+---------------------------------------------------------------------------+
    | **Name**            | Std_ExtractProtocolHeaderFieldsType                                       |
    +---------------------+---------------------------------------------------------------------------+
    | **Kind**            | Function Pointer                                                          |
    +---------------------+---------------------------------------------------------------------------+
    | **Syntax**          | .. code-block:: c                                                         |
    |                     |                                                                           |
    |                     |     Std_ReturnType (*Std_ExtractProtocolHeaderFieldsType) (               |
    |                     |       const uint8* buffer,                                                |
    |                     |       uint32 bufferLength,                                                |
    |                     |       Std_MessageTypeType* messageType,                                   |
    |                     |       Std_MessageResultType* messageResult                                |
    |                     |       )                                                                   |
    |                     |                                                                           |
    +---------------------+----------------+----------------------------------------------------------+
    | **Parameters(in)**  | buffer         | Buffer allocated by the RTE, where the transformed data  |
    |                     |                | has to                                                   |
    |                     +----------------+----------------------------------------------------------+
    |                     | bufferLength   | Length of the buffer                                     |
    +---------------------+----------------+----------------------------------------------------------+
    | **Parameters(i/o)** | None                                                                      |
    +---------------------+----------------+----------------------------------------------------------+
    | **Parameters(out)** | messageType    | Canonical representation of the message type (extracted  |
    |                     |                | from the transformers protocol header)                   |
    |                     +----------------+----------------------------------------------------------+
    |                     | messageResult  | Canonical representation of the message result type      |
    |                     |                | (extracted from the transformers protocol header).       |
    +---------------------+----------------+----------------------------------------------------------+
    | **Return value**    | Std_ReturnType |                                                          |
    +---------------------+----------------+----------------------------------------------------------+
    | **Description**     | Type for the function pointer to extract the relevant protocol header     | 
    |                     | fields of the message and the type of the message result of a transformer | 
    |                     | - At the time being, this is limited to the types used for C/S            | 
    |                     | communication (i.e., REQUEST and RESPONSE and OK and ERROR)               |
    +---------------------+---------------------------------------------------------------------------+
    | **Available via**   | Std_Types.h                                                               |
    +---------------------+---------------------------------------------------------------------------+


8.2 Symbol definitions
^^^^^^^^^^^^^^^^^^^^^^

8.2.1 E_OK, E_NOT_OK
""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00006
    :status: open
    :tags: bsw
    :links: SRS_BSW_00357

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | E_OK, E_NOT_OK                                                              |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Range**         | E_OK                 | 0x00 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | E_NOT_OK             | 0x01 |                                               |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Description**   | Because E_OK is already defined within OSEK, the symbol E_OK has to be      |
    |                   | shared. To avoid name clashes and redefinition problems, the symbols have to| 
    |                   | be defined in the following way (approved within implementation):           |
    |                   |                                                                             |
    |                   | .. code-block:: c                                                           |
    |                   |                                                                             |
    |                   |     #ifndef STATUSTYPEDEFINED                                               |
    |                   |     #define STATUSTYPEDEFINED                                               |
    |                   |     #define E_OK 0x00u                                                      |
    |                   |     typedef unsigned char StatusType; /* OSEK compliance */                 |
    |                   |     #endif                                                                  |
    |                   |     #define E_NOT_OK 0x01u                                                  |
    |                   |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.2.2 STD_HIGH, STD_LOW
"""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00007
    :status: open
    :tags: bsw
    :links: SRS_BSW_00348

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | STD_HIGH, STD_LOW                                                           |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Range**         | STD_LOW              | 0x00 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | STD_HIGH             | 0x01 |                                               |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Description**   | The symbols STD_HIGH and STD_LOW shall be defined as follows                |
    |                   |                                                                             |
    |                   | .. code-block:: c                                                           |
    |                   |                                                                             |
    |                   |     #define STD_HIGH 0x01u /* Physical state 5V or 3.3V */                  |
    |                   |     #define STD_LOW 0x00u /* Physical state 0V */                           |
    |                   |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.2.3 STD_ACTIVE, STD_IDLE
""""""""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00013
    :status: open
    :tags: bsw
    :links: SRS_BSW_00348

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | STD_ACTIVE, STD_IDLE                                                        |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Range**         | STD_IDLE             | 0x00 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | STD_ACTIVE           | 0x01 |                                               |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Description**   | The symbols STD_ACTIVE and STD_IDLE shall be defined as follows:            |
    |                   |                                                                             |
    |                   | .. code-block:: c                                                           |
    |                   |                                                                             |
    |                   |     #define STD_ACTIVE 0x01u /* Logical state active */                     |
    |                   |     #define STD_IDLE 0x00u /* Logical state idle */                         |
    |                   |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.2.4 STD_ON, STD_OFF
"""""""""""""""""""""

.. req:: None
    :id: SWS_Std_00010
    :status: open
    :tags: bsw
    :links: SRS_BSW_00348

    +-------------------+-----------------------------------------------------------------------------+
    | **Name**          | STD_ON, STD_OFF                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Kind**          | Enumeration                                                                 |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Range**         | STD_OFF              | 0x00 |                                               |
    |                   +----------------------+------+-----------------------------------------------+
    |                   | STD_ON               | 0x01 |                                               |
    +-------------------+----------------------+------+-----------------------------------------------+
    | **Description**   | The symbols STD_ON and STD_OFF shall be defined as follows                  |
    |                   |                                                                             |
    |                   | .. code-block:: c                                                           |
    |                   |                                                                             |
    |                   |     #define STD_ON 0x01u                                                    |
    |                   |     #define STD_OFF 0x00u                                                   |
    |                   |                                                                             |
    +-------------------+-----------------------------------------------------------------------------+
    | **Available via** | Std_Types.h                                                                 |
    +-------------------+-----------------------------------------------------------------------------+


8.2.5 NULL_PTR
""""""""""""""

.. req:: None
    :id: SWS_Std_00031
    :status: open
    :tags: bsw
    :links: SRS_BSW_00480

    +-------------------+-----------------------------------------------------------------------------+
    | **Define**        | NULL_PTR                                                                    |
    +-------------------+----------------------+------------------------------------------------------+
    | **Range**         | void pointer         | (( void * )0)                                        |
    +-------------------+----------------------+------------------------------------------------------+
    | **Description**   | The implementation shall provide the NULL_PTR define with a void pointer to |
    |                   | zero definition                                                             |
    +-------------------+-----------------------------------------------------------------------------+
