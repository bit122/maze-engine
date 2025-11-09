#include "uart.h"

int main(void) {
    uart_init();
    uart_puts("Hello from kernel!\n");
    while(1);
    return 0;
}