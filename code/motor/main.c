#include "sbits.h"
#include "time.h"
#include "type.h"

const u16 delay = 100;

void main() {
    P1 = 0xff;
    P1_0 = 0;
    while (1) {
        P1_3 = 1;
        P1_1 = 0;
        delay_ms(delay);
        P1_0 = 1;
        P1_2 = 0;
        delay_ms(delay);
        P1_1 = 1;
        P1_3 = 0;
        delay_ms(delay);
        P1_2 = 1;
        P1_0 = 0;
        delay_ms(delay);
    }
}