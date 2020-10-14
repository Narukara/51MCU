#include <REG51.H>

#include "time.h"
#include "type.h"

sbit Receive = P1 ^ 0;
sbit Send = P1 ^ 1;

static u16 code unit_length = 2;
static u16 code extra = 1;
static u16 code duration = 1;

static u8 mode;

void infared_init(u8 mode_) {
    /*
    0 : send only
    1 : receive only
    2 : send and wait for reply
    3 : receive and reply
    4 : send with Check Digit and wait for reply
    5 : receive and check, then reply
    */
    mode = mode_;
    Send = 0;
    Receive = 1;
}

void infared_send(u8 c) {
    u8 i = 0;
    Send = 1;
    for (; i < 8; i++) {
        delay_ms(unit_length);
        Send = 0x80 & c;
        c <<= 1;
    }
    if (mode == 0) {
        delay_ms(unit_length);
        Send = 0;
        delay_ms(duration);
        return;
    } else if (mode == 2) {
        // todo:
    } else if (mode == 4) {
        // todo:
    }
}

// Blocking method
u8 infared_receive() {
    u8 i = 0, c = 0;
    while (Receive)
        ;
    delay_ms(unit_length + extra);
    for (; i < 8; i++) {
        c <<= 1;
        c |= (Receive & 0x01);
        delay_ms(unit_length);
    }
    if (mode == 1) {
        return ~c;
    } else if (mode == 3) {
        // todo
    } else if (mode == 5) {
        // todo
    }
}