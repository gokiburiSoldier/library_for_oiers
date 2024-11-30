#include "slong.h"
#include <stddef.h>
#include <stdio.h>

superll::superll(void) {
    record = new byte[STD_SIZE]();
    stack_top = record;
}
superll::superll(unsigned long long number) {
    record = new byte[STD_SIZE]();
    stack_top = record;
    while(number) {
        *stack_top++ = number mod_256;
        number modwith_256;
    }
}
superll::superll(int number) {
    record = new byte[STD_SIZE]();
    stack_top = record;
    while(number) {
        *stack_top++ = number mod_256;
        number >>= 8;
    }
}
superll::superll(byte* begin,byte* end) {
    record = new byte[STD_SIZE]();
    stack_top = record;
    for(byte* i=begin;i < end;i++)
        *stack_top++ = *i;
}
superll::~superll() {
    stack_top = NULL;
    delete[] record; 
    record=NULL;
}

void superll::push(byte num) {
    *stack_top++ = num;
}
byte& superll::get(int index) const {
    return record[index];
}

/* 重中之重 */

void superll::show(void) const {
    superll tmp (record,stack_top);
    static char str[888]={}; /* 一个随意的数字 */
    int i=0;
    while(!tmp.is_zero()) {
        str[i++]=tmp.mod_ten() ^ 48;
        tmp.dev_ten();
    }
    for(int x=i-1;x >= 0;--x) putchar(str[x]);
}

bool superll::is_zero(void) {
    return stack_top == record && *stack_top == 0;
}
void superll::dev_ten(void) {
    short tmp=0,more=0;
    for(byte* i=stack_top-1;i >= record;--i) {
        tmp = (more + *i)/10;
        more = (more+*i)%10 << 8;
        *i = tmp;
    }
    while(!*stack_top && stack_top >= record) --stack_top;
    stack_top++;
}
byte superll::mod_ten(void) {
    short ret=0;
    int power=1;
    for(byte* i=record;i<stack_top;i++) {
        short val = (power* (*i))%10;
        ret += val;
        power = (power<<8)%10;
    }
    return ret%10;
}
