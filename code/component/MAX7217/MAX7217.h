#ifndef _NARUKARA_MAX7217_H_
#define _NARUKARA_MAX7217_H_
#include "type.h"

/*******************************
 * Don't forget to check DIN, CS, CLK
 *******************************/

#define DIG0 0x0100
#define DIG1 0x0200
#define DIG2 0x0300
#define DIG3 0x0400
#define DIG4 0x0500
#define DIG5 0x0600
#define DIG6 0x0700
#define DIG7 0x0800
#define Decode 0x0900     // 1:BCD decode, 0:no-decode
#define Intensity 0x0a00  // D0 ~ D3
#define ScanLimit 0x0b00  // D0 ~ D2
#define Shutdown 0x0c00   // D0 = 0 : shutdown, D0 = 1 : normal
#define Test 0x0f00       // D0 = 0 : normal, D0 = 1 : display test

extern void MAX7217_init();
extern void MAX7217_write(u16 rdata);

#endif

/********** EXAMPLE **********
#include "MAX7217.h"

void main() {
    MAX7217_init();
    MAX7217_write(Decode | 0x00);
    MAX7217_write(Intensity | 0x00);
    MAX7217_write(ScanLimit | 0x07);
    MAX7217_write(Shutdown | 0x01);
    MAX7217_write(Test | 0x00);
    MAX7217_write(DIG0 | 0xf0);
    MAX7217_write(DIG1 | 0x0f);
    MAX7217_write(DIG2 | 0xf0);
    MAX7217_write(DIG3 | 0x0f);
    MAX7217_write(DIG4 | 0xf0);
    MAX7217_write(DIG5 | 0x0f);
    MAX7217_write(DIG6 | 0xf0);
    MAX7217_write(DIG7 | 0x0f);
}
 *
 */