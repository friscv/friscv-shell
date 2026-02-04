#include "uart.h"
#include "commands.h"

static int str_cmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(uint8_t *)s1 - *(uint8_t *)s2;
}

/*
TODO:
peek <addr>
poke <addr> <val>
led <n> <on|off|toggle>
leds <0-15>
dump <addr> <len>
rand
rand <max>
eval <expr>
reboot
*/

void cmd_help() {
    uart_puts((uint8_t *)"Commands:\r\n");
    uart_puts((uint8_t *)"  help        - Show this help\r\n");
    uart_puts((uint8_t *)"  clear       - Clear screen\r\n");
    uart_puts((uint8_t *)"  echo <text> - Echo input\r\n");
}

void cmd_clear() {
    uart_puts((uint8_t *)"\033[2J");
    uart_puts((uint8_t *)"\033[H");
}

void cmd_echo(char *args) {
    uart_puts((uint8_t *)args);
    uart_puts((uint8_t *)"\r\n");
}

void execute_cmd(char *cmd) {
    // Skip leading spaces
    while (*cmd == ' ') cmd++;

    // Empty command
    if (*cmd == '\0') return;

    // Find end of command name
    char *args = cmd;
    while (*args && *args != ' ') args++;
    if (*args) {
        *args = '\0';
        args++;
        while (*args == ' ') args++;
    }

    if (str_cmp(cmd, "help") == 0) {
        cmd_help();
    } else if (str_cmp(cmd, "clear") == 0) {
        cmd_clear();
    } else if (str_cmp(cmd, "echo") == 0) {
        cmd_echo(args);
    } else if (*cmd !='\n') {
        uart_puts((uint8_t *)"Unknown command: ");
        uart_puts((uint8_t *)cmd);
        uart_puts((uint8_t *)"\r\n");
    }
}
