Requirements on Port Driver
===========================

This document specifies requirements on the module PORT Driver.

Constraints

First scope for specification of requirements on basic software modules is systems, which are not 
safety relevant. For this reason safety requirements are assigned to medium priority

https://www.autosar.org/fileadmin/standards/R22-11/CP/AUTOSAR_SRS_PortDriver.pdf


4 Requirement Specification
---------------------------

This chapter describes all requirements driving the work to define the Port Driver.

4.1 Functional Overview
^^^^^^^^^^^^^^^^^^^^^^^

This module initializes the whole port structure of the microcontroller. Many ports and port pins 
can be assigned to various functionalities like e.g.

- General purpose I/O
- ADC
- SPI
- SCI
- PWM

For this reason there has to be an overall configuration and initialization of this port structure. 
The configuration and usage of those port pins is microcontroller and ECU dependent.

The following expressions are used within the Port driver:

 - **Physical Level (Input):** Two states possible: LOW/HIGH
 - **Physical Level (Output):** three states possible: LOW/HIGH/High Impedance
 - **Logical Level:** This level is seen within the software: TRUE/FALS


4.2 Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^

4.2.1 Configuration
"""""""""""""""""""

.. req:: The Port driver shall allow the static configuration of the following options for each port
    :id: SRS_Port_12001
    :status: open
    :tags: bsw
    :links: SRS_Port_12405, SRS_Port_12406

    The Port driver shall allow the static configuration of the following options for each port. The 
    granularity of configuration (whole port or single port pin) is microcontroller dependent.

    Mandatory parameters:
    
    - pin usage (e.g. DIO, ADC, SPI, ...)
    - pin direction (input, output)
    - pin level init value
    - pin direction changeable during runtime (yes/no)

    Optional parameters (only if supported by hardware):

    - activation of internal pull-ups/pull-downs
    - slew rate control
    - input thresholds
    - pin driver mode (push-pull/open drain)
    - further microcontroller specific properties

    Level inversion features shall not be configurable, but be set to the default value (not inverted).
    
    Level inversion is task of the I/O Hardware Abstraction.

    **Rationale:** Basic configuration;

    Pin direction changeable during runtime: this is information necessary for port refreshing and 
    runtime direction change, see [SRS_Port_12405] Set port pin direction and [SRS_Port_12406] Refresh 
    port direction.


.. req:: The port driver shall allow the static configuration of the port pin names
    :id: SRS_Port_12302
    :status: open
    :tags: bsw
    :links: SRS_Port_12405, SRS_Port_12406

    The port driver shall allow the static configuration of the following symbolic names: port pin names

    **Rationale:** Provide human readable symbolic names for microcontroller ports and port pins.

    **Use Case:** Examples: **PORT_A_PIN_0**


4.2.2 Normal Operation
^^^^^^^^^^^^^^^^^^^^^^

.. req:: The Port driver shall provide a service for setting the direction of port pins during runtime
    :id: SRS_Port_12405
    :status: open
    :tags: bsw
    :links: SRS_Port_12001

    The Port driver shall provide a service for setting the direction of port pins during runtime.

    The Port driver shall only allow to change the direction of those port pins that are configured as 
    changeable.

    **Use Cases:** Single wire bidirectional communication with ASICs.


.. req:: The Port driver shall provide a service to refresh the direction of all configured ports
    :id: SRS_Port_12406
    :status: open
    :tags: bsw
    :links: SRS_Port_12001

    The Port driver shall provide a service to refresh the direction of all configured ports to the 
    configured direction.

    The Port driver shall exclude those port pins from refreshing that are configured as "pin direction 
    changeable during runtime".

    **Rationale:** Make system more robust against EMC and application software bugs (port data direction 
    register corruption).


4.3 Non-Functional Requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. req:: All re-entrant functions of the Port Driver shall perform port register access actions in 
         an atomic way
    :id: SRS_Port_12423
    :status: open
    :tags: bsw

    All re-entrant functions of the Port Driver shall perform port register access actions in an 
    atomic way.

    **Rationale:** Avoid data integrity problems within concurrent access of Port Driver API 
    functions.

    **Use Case:** A specific microcontroller (or a specific compiler) does not provide atomic access 
    to single port pins. For that reason, the implementation has to use read-modify-write operations 
    on the whole port. Concurrent access to pins of the same port will lead to data integrity problems 
    if concurrent access it not blocked.


4.3.1 Process Requirements
""""""""""""""""""""""""""

.. req:: Ports and port pins that are not used shall be set to a defined state
    :id: SRS_Port_12300
    :status: open
    :tags: bsw

    Ports and port pins that are not used (neither as general purpose I/O nor as special purpose I/O) 
    shall be set to a defined state by the Port module configuration

    **Rationale:** Ensure that all ports and port pins are in a defined state.