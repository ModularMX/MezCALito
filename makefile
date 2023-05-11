all :
	arm-none-eabi-gcc -c -mcpu=cortex-m0plus -O0 -Wall -o main.o main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m0plus -O0 -Wall -o startup.o startup.c
	arm-none-eabi-gcc main.o startup.o -mcpu=cortex-m0plus -T linker.ld -nostdlib -o main.elf
	arm-none-eabi-objcopy -O ihex main.elf main.hex

make flash:
	openocd -f board/st_nucleo_g0.cfg -c "program main.hex verify reset" -c shutdown
