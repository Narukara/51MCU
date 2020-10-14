#include <REG51.H>
#include <intrins.h>

#include "type.h"

/*********************************
 * only for:
 *  STC89Cxx
 *  STC89LExx
 *  STC90Cxx
 *  STC90LExx
 *
 *  @11.0592MHz
 *********************************/

void delay_5us() {}

void delay_10us() {
    u8 i;
    i = 2;
    while (--i)
        ;
}

void delay_100us() {
    u8 i;
    _nop_();
    i = 43;
    while (--i)
        ;
}

void delay_1ms() {
    u8 i, j;
    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j)
            ;
    } while (--i);
}

void delay_10ms() {
    u8 i, j;
    i = 18;
    j = 235;
    do {
        while (--j)
            ;
    } while (--i);
}

void delay_100ms() {
    u8 i, j;
    i = 180;
    j = 73;
    do {
        while (--j)
            ;
    } while (--i);
}

void delay_1s() {
    u8 i, j, k;
    _nop_();
    i = 8;
    j = 1;
    k = 243;
    do {
        do {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

void delay_10s() {
    u8 i, j, k;
    _nop_();
    i = 71;
    j = 10;
    k = 171;
    do {
        do {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

void delay_100s() {
    u8 i, j, k;
    _nop_();
    i = 189;
    j = 97;
    k = 222;
    do {
        do {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

void set_timer(bit which, bit gate, bit ct, bit m1, bit m0) {
    u8 temp = gate;
    temp <<= 1;
    temp |= ct;
    temp <<= 1;
    temp |= m1;
    temp <<= 1;
    temp |= m0;
    if (which) {
        temp <<= 4;
        TMOD = (TMOD & 0x0f) | temp;
    } else {
        TMOD = (TMOD & 0xf0) | temp;
    }
}

void start_timer(bit which, bit start_or_end) {
    if (which) {
        TR1 = start_or_end;
    } else {
        TR0 = start_or_end;
    }
}