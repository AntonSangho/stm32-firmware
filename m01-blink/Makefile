BINARY   = blink
OPENCM3_DIR = ../libopencm3

CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy

CFLAGS   = -Os -g \
		   -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
		   -DSTM32F4 \
		   -I$(OPENCM3_DIR)/include

LDFLAGS  = -Tstm32f446re.ld \
		   -L$(OPENCM3_DIR)/lib \
		   -nostartfiles \
		   --specs=nano.specs \
		   -Wl,-Map=$(BINARY).map \
		   -Wl,-L$(OPENCM3_DIR)/lib

LDLIBS   = -lopencm3_stm32f4

all: $(BINARY).elf $(BINARY).bin

$(BINARY).elf: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(BINARY).bin: $(BINARY).elf
	$(OBJCOPY) -O binary $< $@

flash: $(BINARY).bin
	st-flash --reset write $(BINARY).bin 0x8000000

clean:
	rm -f $(BINARY).elf $(BINARY).bin
