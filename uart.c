#include <stdint.h>
#define UART0_BASE (0x3F201000)

void uart_init(void) {
    // Minimal: Set up the UART for output only, no interrupts, default 115200 baud.
    volatile uint32_t *uart_cr   = (uint32_t*)(UART0_BASE + 0x30);
    volatile uint32_t *uart_ibrd = (uint32_t*)(UART0_BASE + 0x24);
    volatile uint32_t *uart_fbrd = (uint32_t*)(UART0_BASE + 0x28);
    volatile uint32_t *uart_lcrh = (uint32_t*)(UART0_BASE + 0x2C);
    volatile uint32_t *uart_imsc = (uint32_t*)(UART0_BASE + 0x38);

    *uart_cr = 0; // Disable UART
    *uart_ibrd = 1;
    *uart_fbrd = 40;
    *uart_lcrh = (3 << 5); // 8n1 (8 bits, no parity, 1 stop)
    *uart_imsc = 0;
    *uart_cr = (1 << 9) | (1 << 8) | 1; // Enable TX, RX, UART
}

void uart_putc(char c) {
    volatile uint32_t *uart_fr = (uint32_t*)(UART0_BASE + 0x18);
    volatile uint32_t *uart_dr = (uint32_t*)(UART0_BASE + 0x00);
    while (*uart_fr & 0x20) {} // Wait for TXFF to clear
    *uart_dr = c;
}

void uart_puts(const char* s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}