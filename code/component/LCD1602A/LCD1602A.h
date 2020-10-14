#ifndef _NARUKARA_LCD1602A_H_
#define _NARUKARA_LCD1602A_H_
#include <REG51.H>
#include <type.h>

#define DISPLAY_MODE_SET 0x38
#define DISPLAY_OFF 0x08
#define DISPLAY_ON_WITH_CURSOR 0x0f
#define DISPLAY_ON_WITHOUT_CURSOR 0x0c
#define CURSOR_FORWARD 0x06
#define CURSOR_BACKWARD 0x04
#define SCREEN_FORWARD 0x07
#define SCREEN_BACKWARD 0x05
#define SET_POINTER 0x80
#define CLEAN_SCREEN 0x01
#define CARRIAGE_RETURN 0x02

void LCD1602A_init();
u8 LCD1602A_read_status();
void LCD1602A_write_command(u8 command);
u8 LCD1602A_read_data();
void LCD1602A_write_data(u8 wdata);

/**** EXAMPLE **********
#include <REG51.H>

#include "LCD1602A.h"
#include "time.h"
#include "type.h"
#include "uart.h"

void main() {
    set_UART_mode(0, 1, 0, 0);
    set_UART_19200();
    LCD1602A_init();
    delay_100ms();
    UART_send('a');
    UART_send(LCD1602A_read_status());
    LCD1602A_write_command(DISPLAY_ON_WITH_CURSOR);
    delay_1s();
    UART_send(LCD1602A_read_status());
    LCD1602A_write_command(SET_POINTER | 0x4c);
    LCD1602A_write_data(0x30);
    while (1) {
        ;
    }
}
 */

#endif