#include "Std_Types.h"
#include "Port.h"

int main( void )
{
    /*enable GPIOA clock*/
    *(volatile uint32 *)0x40021034 |= 0x01;
    /*Init all ports*/
    Port_Init( &PortConfig );

    for( ;; ) /*infinite loop*/
    {
        /*toggle pin 5 where the led is conected*/
        *(volatile uint32 *)0x50000014 ^= ( 1 << 5 );
        /*Dirty delay*/
        for( uint32 i = 0; i < 100000; i++ )
            ;
    }
    return 0;
}
