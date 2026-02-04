#include "uart.h"
#include "commands.h"
#include <stdint.h>

#define MAX_CMD_LEN 128
#define PROMPT "> "

int main() {
    uart_init();

    uart_puts((uint8_t *)"FRISC-V UART Shell\r\n");
    uart_puts((uint8_t *)"Type 'help' for commands\r\n");

    char cmd_buf[MAX_CMD_LEN];
    int cmd_idx = 0;

    while (1) {
        uart_puts((uint8_t *)PROMPT);
        cmd_idx = 0;

        while (1) {
            uint8_t c = uart_getc();
            
            if (c == '\r' || c == '\n') {  // Enter/Return
                uart_puts((uint8_t *)"\r\n");
                cmd_buf[cmd_idx] = '\0';
                execute_cmd(cmd_buf);
                break;
            } else if (c == 0x7F || c == 0x08) {  // Backspace/DEL
                if (cmd_idx > 0) {
                    cmd_idx--;
                    uart_puts((uint8_t *)"\b \b");
                }
            } else if (c >= 32 && c < 127 && cmd_idx < MAX_CMD_LEN - 1) {
                cmd_buf[cmd_idx++] = c;
                uart_putc(c);  // Echo
            }
        }
    }

    return 0;
}
