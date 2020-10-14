#include <REG51.H>

#include "type.h"

void set_UART_19200() {
    PCON = 0x80;                  // SMOD = 1
    TMOD = (TMOD & 0x0f) | 0x20;  // T1 mode 2, GATE = 0 , C/T = T
    TH1 = TL1 = 0xfd;             // init
    TR1 = 1;                      // T1 start
}

void set_UART_mode(bit sm0, bit sm1, bit sm2, bit ren) {
    SM0 = sm0;
    SM1 = sm1;
    SM2 = sm2;
    REN = ren;
    TI = 1;
}

void UART_send(char c) {
    while (!TI)
        ;
    TI = 0;
    SBUF = c;
}

// c must end with '\0'
void UART_send_string(char c[]) {
    u8 index = 0;
    char temp;
    while (1) {
        temp = c[index++];
        if (temp == '\0') {
            break;
        }
        UART_send(temp);
    }
}

void UART_receive(char* c) {
    while (!RI)
        ;
    *c = SBUF;
    RI = 0;
}