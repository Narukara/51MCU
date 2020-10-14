#ifndef _NARUKARA_TIME_H_
#define _NARUKARA_TIME_H_
#include "type.h"

/*******************************
 * only for:
 *  STC89Cxx
 *  STC89LExx
 *  STC90Cxx
 *  STC90LExx
 *
 *  @11.0592MHz
 *******************************/

extern void delay_5us();
extern void delay_10us();
extern void delay_100us();
extern void delay_1ms();
extern void delay_10ms();
extern void delay_100ms();
extern void delay_1s();
extern void delay_10s();
extern void delay_100s();
extern void set_timer(bit which, bit gate, bit ct, bit m1, bit m0);
extern void start_timer(bit which, bit start_or_end);

#endif