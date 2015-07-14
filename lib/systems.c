#include <stdint.h>
#include "systems.h"
#include <string.h>
#include <stm32f30x.h>
#include <stm32f30x_rcc.h>
#include <core_cm4.h>
#include <core_cmFunc.h>

extern RCC_ClocksTypeDef RCC_Clocks;

void send_openocd_command(int command, void *message)
{
   asm("mov r0, %[cmd];"
       "mov r1, %[msg];"
       "bkpt #0xAB"
         :
         : [cmd] "r" (command), [msg] "r" (message)
         : "r0", "r1", "memory");
}


void send_text( const char * text )
{
	uint32_t m[] = { 2, (uint32_t)text, strlen(text) };
	send_openocd_command(0x05, m);
}

int _write (int fd, const void *buf, size_t count)
{
	uint32_t m[] = { 2, (uint32_t)buf, count };
	send_openocd_command(0x05, m);
}

void * _sbrk(int incr) {
    extern char _ebss; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;


    if (heap_end == 0) {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

	char * stack = (char*) __get_MSP();
     if (heap_end + incr >  stack)
     {
		return  (void*)(-1);
     }

    heap_end += incr;

    return (void*) prev_heap_end;
}

void _delay_us(uint32_t us) {
	us *= RCC_Clocks.HCLK_Frequency/5000000;
	/* fudge for function call overhead */
	us--;
	asm volatile(" mov r0, %[us] \n\t"
	"1: subs r0, #1 \n\t"
	" bhi 1b \n\t"
	:
	: [us] "r" (us)
	: "r0");
}

