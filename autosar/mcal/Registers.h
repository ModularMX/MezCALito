/**
 * @file Registers.h
 *
 * @brief This file contains the register definitions for the STM32G0xx microcontroller
 *
 * To be more specific only the part number stm32g0b1re is taken into account since the MCAL is only
 * designed intende for educational pourpose is not under the scope to make it geenric for the
 * entire stm32g0 familly
 *
 * @version 1.0
 */
#ifndef REGISTERS_H
#define REGISTERS_H

/** @addtogroup Peripheral_memory_map
 * @{ */
#define FLASH_BASE  ( 0x08000000UL ) /*!< FLASH base address */
#define SRAM_BASE   ( 0x20000000UL ) /*!< SRAM base address */
#define PERIPH_BASE ( 0x40000000UL ) /*!< Peripheral base address */
#define IOPORT_BASE ( 0x50000000UL ) /*!< IOPORT base address */

/**
 * @brief General Purpose I/O
 */
typedef struct
{
    volatile uint32 MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
    volatile uint32 OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
    volatile uint32 OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
    volatile uint32 PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    volatile uint32 IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
    volatile uint32 ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
    volatile uint32 BSRR;     /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
    volatile uint32 LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    volatile uint32 AFR[ 2 ]; /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    volatile uint32 BRR;      /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} Port_RegisterType;


/** @addtogroup Port_address Definitions of the Port base addresses
 * @{ */
#define PORTA_BASE ( IOPORT_BASE + 0x00000000UL ) /*!< Port A base address */
#define PORTB_BASE ( IOPORT_BASE + 0x00000400UL ) /*!< Port B base address */
#define PORTC_BASE ( IOPORT_BASE + 0x00000800UL ) /*!< Port C base address */
#define PORTD_BASE ( IOPORT_BASE + 0x00000C00UL ) /*!< Port D base address */
#define PORTE_BASE ( IOPORT_BASE + 0x00001000UL ) /*!< Port E base address */
#define PORTF_BASE ( IOPORT_BASE + 0x00001400UL ) /*!< Port F base address */
/** @} */

/** @addtogroup Port_registers Definitions of the Port registers
 * @{ */
#define PORTA      ( (Port_RegisterType *)PORTA_BASE ) /*!< Port A pointer access */
#define PORTB      ( (Port_RegisterType *)PORTB_BASE ) /*!< Port B pointer access */
#define PORTC      ( (Port_RegisterType *)PORTC_BASE ) /*!< Port C pointer access */
#define PORTD      ( (Port_RegisterType *)PORTD_BASE ) /*!< Port D pointer access */
#define PORTE      ( (Port_RegisterType *)PORTE_BASE ) /*!< Port E pointer access */
#define PORTF      ( (Port_RegisterType *)PORTF_BASE ) /*!< Port F pointer access */
/** @} */

#endif /* REGISTERS_H */
