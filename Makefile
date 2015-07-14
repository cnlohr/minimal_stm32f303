TARGET=main
all: burn

PREFIX=arm-none-eabi

CC=$(PREFIX)-gcc
LD=$(PREFIX)-gcc
AS=$(PREFIX)-as
CP=$(PREFIX)-objcopy
OD=$(PREFIX)-objdump


OBJCOPYFLAGS = -O binary

BIN=$(CP) -O ihex 

DEFS =  -DSTM32F30X  -DHSE_VALUE=25000000
STARTUP = lib/startup_stm32f30x.s

MCU = cortex-m3
MCFLAGS = -mcpu=$(MCU) -mthumb -mlittle-endian -mthumb-interwork

STM32_INCLUDES = -Ilib -I. -ISTM32F30x_StdPeriph_Driver/inc


OPTIMIZE       = -Os

CFLAGS	= $(MCFLAGS)  $(OPTIMIZE)  $(DEFS) -I. -I./ $(STM32_INCLUDES)  -Wl,-T,lib/stm32f303.ld
AFLAGS	= $(MCFLAGS) 

SRC = main.c \
	stm32f30x_it.c \
	lib/system_stm32f30x.c \
	lib/systems.c \
	STM32F30x_StdPeriph_Driver/src/stm32f30x_rcc.c \
	STM32F30x_StdPeriph_Driver/src/stm32f30x_gpio.c


burn : $(TARGET).bin
	openocd -f flash.cfg #-d3
terminal :
	openocd -f terminal.cfg

$(TARGET).bin : $(TARGET).out
	$(CP) $(OBJCOPYFLAGS) $< $@

$(TARGET).hex: $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(TARGET).out : $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $^ -lm -lc -lnosys  -o $@

clean:
	rm -f $(TARGET).lst $(TARGET).out $(TARGET).hex $(TARGET).bin $(TARGET).map  $(EXECUTABLE)
