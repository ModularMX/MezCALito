#include <stdint.h>

/*external reference varibales form linker scripts*/
extern uint8_t __stack_init;    /*stack init address*/
extern uint8_t __bss_start;     /*bss section start address*/
extern uint8_t __bss_end;       /*bss section end address*/
extern uint8_t __data_init;     /*data section start address in FLASH*/
extern uint8_t __data_start;    /*data section start address in RAM*/        
extern uint8_t __data_end;      /*data section end address in RAM*/

/*since we reference symbol main before the function declaration
we need to declare its prototype before array vectors*/
/* clang-format off */
extern int main(void);
void Reset_Handler( void );
void NMI_Handler( void )                                    __attribute__((weak, alias("Common_Handler")));
void HardFault_Handler( void )                              __attribute__((weak, alias("Common_Handler")));
void SVC_Handler( void )                                    __attribute__((weak, alias("Common_Handler")));
void PendSV_Handler( void )                                 __attribute__((weak, alias("Common_Handler")));
void SysTick_Handler( void )                                __attribute__((weak, alias("Common_Handler")));
void WWDG_IRQHandler( void )                                __attribute__((weak, alias("Common_Handler")));
void PVD_VDDIO2_IRQHandler( void )                          __attribute__((weak, alias("Common_Handler")));             
void RTC_TAMP_IRQHandler( void )                            __attribute__((weak, alias("Common_Handler")));               
void FLASH_IRQHandler( void )                               __attribute__((weak, alias("Common_Handler")));                  
void RCC_CRS_IRQHandler( void )                             __attribute__((weak, alias("Common_Handler")));                
void EXTI0_1_IRQHandler( void )                             __attribute__((weak, alias("Common_Handler")));                
void EXTI2_3_IRQHandler( void )                             __attribute__((weak, alias("Common_Handler")));                
void EXTI4_15_IRQHandler( void )                            __attribute__((weak, alias("Common_Handler")));               
void USB_UCPD1_2_IRQHandler( void )                         __attribute__((weak, alias("Common_Handler")));            
void DMA1_Channel1_IRQHandler( void )                       __attribute__((weak, alias("Common_Handler")));          
void DMA1_Channel2_3_IRQHandler( void )                     __attribute__((weak, alias("Common_Handler")));        
void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler( void )   __attribute__((weak, alias("Common_Handler"))); 
void ADC1_COMP_IRQHandler( void )                           __attribute__((weak, alias("Common_Handler")));              
void TIM1_BRK_UP_TRG_COM_IRQHandler( void )                 __attribute__((weak, alias("Common_Handler")));  
void TIM1_CC_IRQHandler( void )                             __attribute__((weak, alias("Common_Handler")));                
void TIM2_IRQHandler( void )                                __attribute__((weak, alias("Common_Handler")));
void TIM3_TIM4_IRQHandler( void )                           __attribute__((weak, alias("Common_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler( void )                     __attribute__((weak, alias("Common_Handler")));
void TIM7_LPTIM2_IRQHandler( void )                         __attribute__((weak, alias("Common_Handler")));
void TIM14_IRQHandler( void )                               __attribute__((weak, alias("Common_Handler")));
void TIM15_IRQHandler( void )                               __attribute__((weak, alias("Common_Handler")));
void TIM16_FDCAN_IT0_IRQHandler( void )                     __attribute__((weak, alias("Common_Handler")));
void TIM17_FDCAN_IT1_IRQHandler( void )                     __attribute__((weak, alias("Common_Handler")));
void I2C1_IRQHandler( void )                                __attribute__((weak, alias("Common_Handler")));
void I2C2_3_IRQHandler( void )                              __attribute__((weak, alias("Common_Handler")));
void SPI1_IRQHandler( void )                                __attribute__((weak, alias("Common_Handler")));
void SPI2_3_IRQHandler( void )                              __attribute__((weak, alias("Common_Handler")));
void USART1_IRQHandler( void )                              __attribute__((weak, alias("Common_Handler")));
void USART2_LPUART2_IRQHandler( void )                      __attribute__((weak, alias("Common_Handler")));
void USART3_4_5_6_LPUART1_IRQHandler( void )                __attribute__((weak, alias("Common_Handler")));
void CEC_IRQHandler( void )                                 __attribute__((weak, alias("Common_Handler")));
/* clang-format on */

/*The following array should be place at the first FLASH memory adress and it holds
the stack pointer plus the 48 interrupts vector addresses*/
__attribute__((section(".isr_vectors"))) unsigned long vectors[] =
{
    (unsigned long)&__stack_init, /*Stack init address*/
    (unsigned long)Reset_Handler,  /*function main address*/
    (unsigned long)NMI_Handler,  /*NMI interrupt service routine address*/
    (unsigned long)HardFault_Handler,  /*Hard Fault interrupt service routine address*/
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)SVC_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)PendSV_Handler,
    (unsigned long)SysTick_Handler,
    (unsigned long)WWDG_IRQHandler,                   /* Window WatchDog              */
    (unsigned long)PVD_VDDIO2_IRQHandler,             /* PVD through EXTI Line detect */
    (unsigned long)RTC_TAMP_IRQHandler,               /* RTC through the EXTI line    */
    (unsigned long)FLASH_IRQHandler,                  /* FLASH                        */
    (unsigned long)RCC_CRS_IRQHandler,                /* RCC & CRS                    */
    (unsigned long)EXTI0_1_IRQHandler,                /* EXTI Line 0 and 1            */
    (unsigned long)EXTI2_3_IRQHandler,                /* EXTI Line 2 and 3            */
    (unsigned long)EXTI4_15_IRQHandler,               /* EXTI Line 4 to 15            */
    (unsigned long)USB_UCPD1_2_IRQHandler,            /* USB, UCPD1, UCPD2            */
    (unsigned long)DMA1_Channel1_IRQHandler,          /* DMA1 Channel 1               */
    (unsigned long)DMA1_Channel2_3_IRQHandler,        /* DMA1 Channel 2 and Channel 3 */
    (unsigned long)DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler, /* DMA1 Ch4 to Ch7, DMA2 Ch1 to Ch5, DMAMUX1 overrun */
    (unsigned long)ADC1_COMP_IRQHandler,              /* ADC1, COMP1 and COMP2         */
    (unsigned long)TIM1_BRK_UP_TRG_COM_IRQHandler,    /* TIM1 Break, Update, Trigger and Commutation */
    (unsigned long)TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
    (unsigned long)TIM2_IRQHandler,                   /* TIM2                         */
    (unsigned long)TIM3_TIM4_IRQHandler,              /* TIM3, TIM4                   */
    (unsigned long)TIM6_DAC_LPTIM1_IRQHandler,        /* TIM6, DAC and LPTIM1         */
    (unsigned long)TIM7_LPTIM2_IRQHandler,            /* TIM7 and LPTIM2              */
    (unsigned long)TIM14_IRQHandler,                  /* TIM14                        */
    (unsigned long)TIM15_IRQHandler,                  /* TIM15                        */
    (unsigned long)TIM16_FDCAN_IT0_IRQHandler,        /* TIM16 & FDCAN1_IT0 & FDCAN2_IT0 */
    (unsigned long)TIM17_FDCAN_IT1_IRQHandler,        /* TIM17 & FDCAN1_IT1 & FDCAN2_IT1 */
    (unsigned long)I2C1_IRQHandler,                   /* I2C1                         */
    (unsigned long)I2C2_3_IRQHandler,                 /* I2C2, I2C3                   */
    (unsigned long)SPI1_IRQHandler,                   /* SPI1                         */
    (unsigned long)SPI2_3_IRQHandler,                 /* SPI2, SPI3                   */
    (unsigned long)USART1_IRQHandler,                 /* USART1                       */
    (unsigned long)USART2_LPUART2_IRQHandler,         /* USART2 & LPUART2             */
    (unsigned long)USART3_4_5_6_LPUART1_IRQHandler,   /* USART3, USART4, USART5, USART6, LPUART1   */
    (unsigned long)CEC_IRQHandler
};

/**
 * @brief  **Common vector handler**
 * 
 * All interrupts that are not defined in the application are handled here.
*/
void Common_Handler(void) 
{

}

/**
 * @brief  **Reset vector handler**
 * 
 * This function is called on startup and it is responsible for initializing the .bss and .data sections
 * and then calling the main function.
 */
void Reset_Handler(void) 
{
    uint32_t size;
    uint8_t *location;
    uint8_t *source;

    /*init bss section goes here*/
    location = &__bss_start; /*init pointer to set a zero on each .bss location*/
    size = &__bss_end - &__bss_start; /* cppcheck-suppress misra-c2012-18.4 ; fuck you MISRA */
    for (uint32_t i = 0; i < size; i++) 
    {
        *location = 0u; /*fill it with zeros*/
        location++;
    }

    /*init data section goes here*/
    source = &__data_init;              /*get the LMA .data starting address*/
    location = &__data_start;           /*get the VMA .data starting address*/
    size = &__data_end - &__data_start; /* cppcheck-suppress misra-c2012-18.4 */
    for (uint32_t i = 0; i < size; i++) 
    {
        *location = *source; /*copy from flash to ram one bit at the time*/
        location++;
        source++;
    }

    (void)main();
}
