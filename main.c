#include "framebuffer.h"
#include "uart.h"

typedef unsigned long size_t;
size_t strlen(const char *s) {
    size_t len = 0;
    while (s[len]) ++len;
    return len;
}

void print_device(const char* name, int ok) {
    fb_set_color(COLOR_WHITE);
    fb_print(name);
    for (size_t i = 0; i < 16 - strlen(name); ++i) fb_print(" ");
    if (ok) {
        fb_set_color(COLOR_GREEN);
        fb_print("[ OK ]\n");
    } else {
        fb_set_color(COLOR_RED);
        fb_print("[FAIL]\n");
    }
}

void print_process(const char* name, int ok) {
    fb_set_color(COLOR_GRAY);
    fb_print("Starting ");
    fb_print(name);
    fb_print("... ");
    if (ok) {
        fb_set_color(COLOR_GREEN);
        fb_print("[ OK ]\n");
    } else {
        fb_set_color(COLOR_RED);
        fb_print("[FAIL]\n");
    }
}

int main(void) {
    uart_init();
    uart_puts("Hello, UART world!\n");

    fb_init();
    fb_set_pos(32, 32);

    fb_set_color(COLOR_CYAN);
    fb_println("=== Boot Device Table ===");

    print_device("SD Card", 1);
    print_device("UART", 1);
    print_device("Ethernet", 0);
    print_device("USB Keyboard", 1);

    fb_set_color(COLOR_CYAN);
    fb_println("\n=== Boot Process Log ===");
    print_process("Timer", 1);
    print_process("Keyboard driver", 1);
    print_process("Network stack", 0);

    while(1);
    return 0;
}