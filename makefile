# arm directory location (/opt at students)
HOME = /home/xps15/Studia/Sem5/PMK

CC = arm-eabi-gcc
OBJCOPY = arm-eabi-objcopy
FLAGS = -mthumb -mcpu=cortex-m4
CPPFLAGS = -DSTM32F411xE
CFLAGS = $(FLAGS) -Wall -g \
		 -O2 -ffunction-sections -fdata-sections \
		 -I$(HOME)/arm/stm32/inc \
		 -I$(HOME)/arm/stm32/CMSIS/Include \
		 -I$(HOME)/arm/stm32/CMSIS/Device/ST/STM32F4xx/Include
LDFLAGS = $(FLAGS) -Wl,--gc-sections -nostartfiles \
		  -L$(HOME)/arm/stm32/lds -Tstm32f411re.lds

vpath %.c $(HOME)/arm/stm32/src

ifeq ($(TARGET),)
        TARGET = wav_player
endif

HEADERS = pcm.h pcm_t.h buttons.h
OBJECTS = $(TARGET).o startup_stm32.o gpio.o delay.o pcm_data.o

.SECONDARY: $(TARGET).elf $(OBJECTS)

all: $(TARGET).bin

%.elf: $(OBJECTS) #$(HEADERS)
	$(CC) $(LDFLAGS) $^ -o $@
	
%.bin: %.elf
	$(OBJCOPY) $< $@ -O binary

pre:
	$(CC) -E $(CFLAGS) $(CPPFLAGS) $< $(TARGET).c -o $(TARGET).pre

clean:
	rm -f *.bin *.elf *.hex *.d *.o *.bak *~ *.pre

flash: all
	$(HOME)/arm/stm32/ocd/qfn4 $(TARGET).bin
