CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding -Wall -Wextra
LDFLAGS = -T linker.ld

SRC = boot.S main.c framebuffer.c
OBJ = $(SRC:.c=.o)
TARGET = kernel8.img

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o kernel8.elf $(OBJ)
	$(OBJCOPY) -O binary kernel8.elf $@

clean:
	rm -f *.o *.elf $(TARGET)

.PHONY: all clean