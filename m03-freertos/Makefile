BINARY      = freertos_blink
OPENCM3_DIR = ../libopencm3
FREERTOS_DIR = ../FreeRTOS

CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy

FREERTOS_SRC = \
    $(FREERTOS_DIR)/tasks.c \
    $(FREERTOS_DIR)/list.c \
    $(FREERTOS_DIR)/queue.c \
    $(FREERTOS_DIR)/timers.c \
    $(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c \
    $(FREERTOS_DIR)/portable/MemMang/heap_4.c

SRCS = main.c $(FREERTOS_SRC)
OBJS = $(SRCS:.c=.o)

CFLAGS  = -Os -g \
          -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
          -DSTM32F4 \
          -I$(OPENCM3_DIR)/include \
          -I$(FREERTOS_DIR)/include \
          -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F \
          -I.

LDFLAGS = -Tstm32f446re.ld \
          -L$(OPENCM3_DIR)/lib \
          -nostartfiles \
          --specs=nano.specs \
          -Wl,-Map=$(BINARY).map \
          -Wl,-L$(OPENCM3_DIR)/lib

LDLIBS  = -lopencm3_stm32f4

all: $(BINARY).elf $(BINARY).bin

$(BINARY).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINARY).bin: $(BINARY).elf
	$(OBJCOPY) -O binary $< $@

flash: $(BINARY).bin
	st-flash write $(BINARY).bin 0x8000000

clean:
	rm -f $(BINARY).elf $(BINARY).bin $(BINARY).map $(OBJS)
