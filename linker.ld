ENTRY( Reset_Handler )

MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512k
    SRAM (rw)  : ORIGIN = 0x20000000, LENGTH = 144k
}

__stack_init = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /*stack pointer, main function address and the rest of the code*/
    .text :
    {
        *(.isr_vectors)
        *(.text)
        /*To get an LMA .data address aligned also*/
        . = ALIGN(4);
        *(.rodata)
    } > FLASH
    
    /* get the load address for .data */
    __data_init = LOADADDR(.data);
    /*variables with init values, shall be store at FLASH and SRAM*/
    .data : 
    {
        /*align the starting address to 4 byte just in case*/
        . = ALIGN(4); 
        /*declare a symbol to represent .data starting address*/
        __data_start = .; 
        *(.data)
        /*align the last address to 4 byte just in case*/
        . = ALIGN(4);
        /*declare a symbol to represent .data ending address
        at this point the location counter incremented the size of .data*/ 
        __data_end = .;
    } > SRAM AT > FLASH
    
    /*for none initilize variables*/
    .bss : 
    {
        /*align the starting address to 4 byte just in case*/
        . = ALIGN(4); 
        /*declare a symbol to represent .bss starting address*/
        __bss_start = .; 
        *(.bss)
        /*align the last address to 4 byte just in case*/
        . = ALIGN(4);
        /*declare a symbol to represent .bss ending address
        at this point the location counter incremented the size of .bss*/ 
        __bss_end = .;
    } > SRAM AT > FLASH
}
