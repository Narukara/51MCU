#include <REG51.H>

#include "type.h"

sbit DIN = P2 ^ 7;
sbit CS = P2 ^ 6;
sbit CLK = P2 ^ 5;

void MAX7217_init() {
    CS = 1;
    CLK = 0;
}

void MAX7217_write(u16 rdata) {
    u8 i = 0;
    CS = 0;
    for (; i < 16; i++) {
        CLK = 0;
        DIN = rdata & 0x8000;
        rdata <<= 1;
        CLK = 1;
    }
    CS = 1;
    CLK = 0;
}