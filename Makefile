CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding -Wall -Wextra
LDFLAGS = -T linker.ld

SRC = boot.S main.c framebuffer.c mailbox.c uart.c
OBJ = boot.o main.o framebuffer.o mailbox.o uart.o
TARGET = kernel8.img

all: $(TARGET)

boot.o: boot.S
	$(CC) $(CFLAGS) -c $< -o $@
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@
framebuffer.o: framebuffer.c
	$(CC) $(CFLAGS) -c $< -o $@
mailbox.o: mailbox.c
	$(CC) $(CFLAGS) -c $< -o $@
uart.o: uart.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o kernel8.elf $(OBJ)
	$(OBJCOPY) -O binary kernel8.elf $@

clean:
	rm -f *.o *.elf $(TARGET)