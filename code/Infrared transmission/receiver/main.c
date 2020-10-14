#include "infared.h"
#include "interrupt.h"
#include "uart.h"

void main() {
    char c;
    set_all_interrupt(0);
    set_UART_mode(0, 1, 0, 0);
    set_UART_19200();
    infared_init(1);
    while (1) {
        infared_receive(&c);
        UART_send(c);
    }
}