#include "numbers.h"
#include "sbits.h"

char number = 0;

char check() {
    if (P3_4 == 0) {
        return 1;
    }
    if (P3_5 == 0) {
        return 2;
    }
    if (P3_6 == 0) {
        return 3;
    }
    return 0;
}

void main() {
    P3 = 0xff;
    select(0);
    while (1) {
        P3_0 = 0;
        number = 0 + check();
        if (number != 0) {
            show(number, 0);
        }
        P3_0 = 1;

        P3_1 = 0;
        number = 3 + check();
        if (number != 3) {
            show(number, 0);
        }
        P3_1 = 1;

        P3_2 = 0;
        number = 6 + check();
        if (number != 6) {
            show(number, 0);
        }
        P3_2 = 1;
    }
}