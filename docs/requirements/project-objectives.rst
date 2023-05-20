Project Objectives
==================

Each AUTOSAR Partner has committed to the top level project objectives (PO) of AUTOSAR.

The project objectives are the top level requirements of the AUTOSAR standard and get further 
refined in order to get broken down into the specific technical requirements. For this purpose, 
the AUTOSAR Project Objectives are established as a fundamental base to derive these specific 
requirements. 

The term AUTOSAR is used as a synonym of the development partnership and the technical product 
AUTomotive Open System ARchitecture

https://www.autosar.org/fileadmin/standards/R22-11/FO/AUTOSAR_RS_ProjectObjectives.pdf


.. req:: AUTOSAR shall support the portability of software
    :id: RS_PO_00001
    :status: open
    :tags: autosar
    :links: RS_PO_00003, RS_PO_00004, RS_PO_00007

    AUTOSAR shall enable OEMs and suppliers to deploy software across the vehicle network and to 
    reuse software.

    **Rationale:** Deployment and reuse of software across the vehicle network allows overall system 
    scaling and optimization. Redevelopment of software is expensive and error prone

    **Use Case:** Application software is reusable across different product lines and OEMs. Scaling 
    and optimizing of vehicle networks by transferring application software.

    Basic software is reusable across different ECUs and domains.


.. req:: AUTOSAR shall support the scalability to different architectures and hardware variants
    :id: RS_PO_00002
    :status: open
    :tags: autosar

    AUTOSAR shall provide mechanisms to develop systems, which can be adapted to different vehicles, 
    platforms and ECU hardware capabilities

    **Rationale:** Software functions can be used in ECUs with different hardware characteristics.

    **Use Case:** Integration of an application on a different or updated hardware platform Development 
    of an application which can be configured to be integrated on different vehicles.


.. req:: AUTOSAR shall be domain agnostic
    :id: RS_PO_00003
    :status: open
    :tags: autosar
    :links: RS_PO_00001

    AUTOSAR shall be functional domain agnostic

    **Rationale:** A common architecture across the functional domains allows the relocation of software 
    components across domains

    **Use Case:** Applying the same software systems to multiple areas

   
.. req:: AUTOSAR shall support data exchange with non AUTOSAR systems
    :id: RS_PO_00010
    :status: open
    :tags: autosar
    :links: RS_PO_00001

    AUTOSAR shall support data exchange with non AUTOSAR systems

    **Rationale:** It increases the degree of freedom at generating the E/E system.

    **Use Case:** Communication of AUTOSAR ECUs with infotainment ECUs


.. req:: AUTOSAR shall define an open architecture for automotive software
    :id: RS_PO_00004
    :status: open
    :tags: autosar
    :links: RS_PO_00001, RS_PO_00005

    AUTOSAR shall define an open architecture for automotive software which can be maintained, 
    adapted and extended.

    **Rationale:** Findings from the application of AUTOSAR require maintaining AUTOSAR. Future 
    requirements will increase the necessity to further evolve AUTOSAR. Only common functionality 
    will be standardized by AUTOSAR. Therefore the architecture shall be extendable without comprising 
    fundamental principles of the architecture.

    **Use Case:** Adaption to new technologies e.g. from silicon industry and software industry, 
    Integration of drivers for specific hardware


.. req:: AUTOSAR shall support the development of dependable systems
    :id: RS_PO_00005
    :status: open
    :tags: autosar
    :links: RS_PO_00004

    Dependable systems are characterized by the following attributes which shall be supported by AUTOSAR:

    - Availability: readiness for correct service
    - Reliability: continuity of correct service
    - Safety: absence of unreasonable risk
    - Integrity: mechanisms to inhibit improper system alteration
    - Maintainability: ability to undergo modifications and repairs
    - Security: protecting automotive software systems from unauthorized access, use, disclosure, disruption, modification, perusal, inspection, recording or destruction

    **Rationale:** Numerous functions in the automotive domain have requirements on functional safety 
    and/or availability. Automotive systems are characterized by long product life cycles and short 
    reaction times when the need for updates and upgrades comes up

    **Use Case:** Software updates and upgrades. Exchange of hardware platforms

    **Supporting Material:** ISO 26262, SOTIF ISO-PAS 21448, SAE J3061, ISO/SAE 21434, UN/ECE/TRANS/WP-29


.. req:: AUTOSAR shall enable the collaboration between partners
    :id: RS_PO_00007
    :status: open
    :tags: autosar
    :links: RS_PO_00001

    AUTOSAR shall enable the collaboration between partners by standardized data exchange formats and 
    support the integration of basic software and application software from various partners on a single ECU
    via a middleware and across the vehicle network

    **Rationale:** The automotive domain is characterized by collaborations between various partners.
    Coordination of e.g. interface and parameter definitions is an ongoing challenge in distributed development 
    projects. In many ECUs software from different suppliers has to be integrated

    **Use Case:** Collaborations between partners (e.g. OEMs, System, Software, Hardware and Tool Suppliers)


.. req:: AUTOSAR shall support applicable international automotive standards and state-of-the-art technologies
    :id: RS_PO_00009
    :status: open
    :tags: autosar

    AUTOSAR results shall be compliant to existing and applicable international automotive standards and 
    state-of-the-art technologies

    **Rationale:** Enable AUTOSAR to be used in todays and future systems. Support is required to ensure 
    interoperability with existing standards. AUTOSAR results should be compliant to relevant standards and
    applicable state-of-the-art-technologies.

    **Use Case:** Support of existing and future bus systems (CAN, FlexRay, etc.). Support of relevant 
    ISO/SAE/IEC Standards and UN-ECE

