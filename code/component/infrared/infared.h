#ifndef _NARUKARA_INFARED_H_
#define _NARUKARA_INFARED_H_
#include "type.h"

/*******************************
 * Don't forget to check Send, Receive
 *******************************/

void infared_init(u8 mode_);
void infared_send(u8 c);
void infared_receive(u8 *c);

#endif