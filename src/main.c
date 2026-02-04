#include "uart.h"

int main() {
    uart_init();

    uart_puts((uint8_t *)"Ready\r\n");

    while (1) {
        uint8_t c = uart_getc();
        uart_putc(c);
        
        if (c == '\r') {
            uart_putc('\n');
        }
    }

    return 1;
}
