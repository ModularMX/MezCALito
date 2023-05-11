int main( void )
{
    /*enable GPIOA clock*/
    *(volatile unsigned long*)0x40021034 |= 0x01;
    /*Set pin 5 from port A as output*/
    *(volatile unsigned long*)0x50000000 &= ~(2 << (5 << 1));
    
    for( ; ; ) /*infinite loop*/
    {
        /*toggle pin 5 where the led is conected*/
        *(volatile unsigned long*)0x50000014 ^= (1 << 5);
        /*Dirty delay*/
        for( unsigned long i=0 ; i<100000 ; i++ );
    }
    return 0;
}
