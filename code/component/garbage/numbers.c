#include <reg51.h>

static char display_cache[4], dot_cache;

// which:0~3
void select(char which) {
    switch (which) {
        case 0:
            P2 = 0x88;
            break;
        case 1:
            P2 = 0x48;
            break;
        case 2:
            P2 = 0x28;
            break;
        case 3:
            P2 = 0x18;
            break;
    }
}

void show(char num, bit dot) {
    switch (num) {
        case -2:
            P0 = 0x79;  // error
            break;
        case -1:
            P0 = 0x00;  // empty
            break;
        case 0:
            P0 = 0x3f;
            break;
        case 1:
            P0 = 0x06;
            break;
        case 2:
            P0 = 0x5b;
            break;
        case 3:
            P0 = 0x4f;
            break;
        case 4:
            P0 = 0x66;
            break;
        case 5:
            P0 = 0x6d;
            break;
        case 6:
            P0 = 0x7d;
            break;
        case 7:
            P0 = 0x07;
            break;
        case 8:
            P0 = 0x7f;
            break;
        case 9:
            P0 = 0x6f;
            break;
        case 10:
            P0 = 0x40;  // -
            break;
    }
    if (dot) {
        P0 += 0x80;
    }
}

void load_i(int num) {
    char w = 0;
    dot_cache = -1;
    display_cache[0] = display_cache[1] = display_cache[2] = display_cache[3] =
        -1;
    if (num < 0) {
        num = -num;
        while (num != 0) {
            if (w == 3) {
                goto overflow;
            }
            display_cache[w++] = num % 10;
            num /= 10;
        }
        display_cache[w] = 10;  // -
    } else if (num == 0) {
        display_cache[0] = 0;
    } else {
        while (num != 0) {
            if (w == 4) {
                goto overflow;
            }
            display_cache[w++] = num % 10;
            num /= 10;
        }
    }
    return;
overflow:
    display_cache[0] = -2;
}

void load_f(float num) {}

void display() {
    char w = 0;
    if (display_cache[0] == -2) {
        select(0);
        show(-2, 0);
    } else {
        while (1) {
            show(-1, 0);
            select(w);
            show(display_cache[w], (dot_cache == w) ? 1 : 0);
            w++;
            if (w == 4) {
                w = 0;
            }
        }
    }
}
