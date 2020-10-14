#include "REG51.H"
#include "uart.h"

void main() {
    P2 = 0x01;
    while (1) {
        delay_1s();
        P2 <<= 1;
    }
}