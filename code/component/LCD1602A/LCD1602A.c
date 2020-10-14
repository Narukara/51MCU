#include "LCD1602A.h"

#include "time.h"

sbit RS = P1 ^ 0;  // data = 1, command = 0
sbit RW = P1 ^ 1;  // read = 1,write = 0
sbit E = P2 ^ 5;   // enable
#define DB P0      // data IO
sbit DB0 = P0 ^ 0;
sbit DB1 = P0 ^ 1;
sbit DB2 = P0 ^ 2;
sbit DB3 = P0 ^ 3;
sbit DB4 = P0 ^ 4;
sbit DB5 = P0 ^ 5;
sbit DB6 = P0 ^ 6;
sbit DB7 = P0 ^ 7;

u8 LCD1602A_read_status() {
    u8 temp;
    RS = 0;
    RW = 1;
    E = 1;
    temp = DB;
    E = 0;
    return temp;
}

u8 LCD1602A_is_busy() {
    u8 status = LCD1602A_read_status();
    return status & 0x80;
}

void LCD1602A_wait() {
    while (LCD1602A_is_busy())
        ;
}

// write command without busy check
void LCD1602A_write_command_d(u8 command) {
    RS = 0;
    RW = 0;
    DB = command;
    E = 1;
    E = 0;
}

void LCD1602A_write_command(u8 command) {
    LCD1602A_wait();
    LCD1602A_write_command_d(command);
}

u8 LCD1602A_read_data() {
    u8 temp;
    RS = 1;
    RW = 1;
    E = 1;
    temp = DB;
    E = 0;
    return temp;
}

void LCD1602A_write_data(u8 wdata) {
    LCD1602A_wait();
    RS = 1;
    RW = 0;
    DB = wdata;
    E = 1;
    E = 0;
}

// call this function first
void LCD1602A_init() {
    u8 t = 15;
    E = 0;
    while (t-- > 0) delay_1ms();
    LCD1602A_write_command_d(DISPLAY_MODE_SET);
    for (t = 5; t > 0; t--) delay_1ms();
    LCD1602A_write_command_d(DISPLAY_MODE_SET);
    for (t = 5; t > 0; t--) delay_1ms();
    LCD1602A_write_command_d(DISPLAY_MODE_SET);
    LCD1602A_write_command(DISPLAY_MODE_SET);
    LCD1602A_write_command(DISPLAY_OFF);
    LCD1602A_write_command(CLEAN_SCREEN);
    LCD1602A_write_command(CURSOR_FORWARD);
    LCD1602A_write_command(DISPLAY_ON_WITHOUT_CURSOR);
}