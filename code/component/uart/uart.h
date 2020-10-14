#ifndef _NARUKARA_UART_H_
#define _NARUKARA_UART_H_

extern void set_UART_19200();
extern void set_UART_mode(bit sm0, bit sm1, bit sm2, bit ren);
extern void UART_send(char c);
extern void UART_send_string(char c[]);
extern void UART_receive(char* c);

#endif