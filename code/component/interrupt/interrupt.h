#ifndef _NARUKARA_INTERRUPT_H_
#define _NARUKARA_INTERRUPT_H_

/****
 * INT0 : 0
 * T0 : 1
 * INT1 : 2
 * T1 : 3
 * UART : 4
 * T2 : 5
 * PCA : 6
 */

extern void set_all_interrupt(bit allow);
extern void set_INT_interrupt(bit which, bit allow, bit priority, bit way);
extern void set_UART_interrupt(bit allow, bit priority);
extern void set_timer_interrupt(bit which, bit allow, bit priority);

#endif