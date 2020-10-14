#include "infared.h"
#include "interrupt.h"
#include "uart.h"

void main() {
    char c;
    set_all_interrupt(0);
    set_UART_mode(0, 1, 0, 1);
    set_UART_19200();
    infared_init(0);
    while (1) {
        UART_receive(&c);
        UART_send(c);
        infared_send(c);
    }
}