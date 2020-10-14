#include <REG51.H>

void set_all_interrupt(bit allow) { EA = allow; }

void set_INT_interrupt(bit which, bit allow, bit priority, bit way) {
    if (which) {
        EX1 = allow;
        PX1 = priority;
        IT1 = way;
    } else {
        EX0 = allow;
        PX0 = priority;
        IT0 = way;
    }
}

void set_UART_interrupt(bit allow, bit priority) {
    ES = allow;
    PS = priority;
}

void set_timer_interrupt(bit which, bit allow, bit priority) {
    if (which) {
        ET1 = allow;
        PT1 = priority;
    } else {
        ET0 = allow;
        PT0 = priority;
    }
}