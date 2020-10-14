#ifndef _NARUKARA_EXCEPTION_H_
#define _NARUKARA_EXCEPTION_H_
#include <setjmp.h>

/*******************************
 * Don't forget to define these three variables
 * Don't use formatter to this file
 *******************************/

extern char exception_code;
extern char exception_depth;
extern jmp_buf exception_jmpbuf[];

#define try if (!(exception_code = setjmp(exception_jmpbuf[exception_depth++])))
#define catch(x) else if (exception_code == x)
#define throw(x) longjmp(exception_jmpbuf[--exception_depth], x)

/*************** EXAMPLE *******************
 #include <stdio.h>

 #include "exception.h"

 char exception_code;
 char exception_depth;
 jmp_buf exception_jmpbuf[3];

 int fun1(){
     throw(1);
     printf("ok");
 }

 int fun2(){
     throw(2);
     printf("ok");
 }

 int main() {
     try {
         try {
             fun1();
         } catch (1) {
             printf("in\n");
         }
         fun1();
     } catch (1) {
         printf("e\n");
     }
     try {
         fun2();
     } catch (1) {
         printf("1\n");
     } catch (2) {
         printf("2\n");
     }
     return 0;
 }

 the output is:
 in
 e
 2

 ********************************************/

#endif
