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

superll superll::ret_add(superll right) {
    superll ret=0;
    short tmp,more=0;
    for(int i=0;i<STD_SIZE;i++) {
        tmp = more+right.get(i)+record[i];
        more = tmp >>8;
        ret.push(tmp mod_256);
    } 
    return ret;
}

superll superll::ret_subtract(superll right) {
    superll ret=0;
    short tmp,less=0;
    for(int i=0;i<STD_SIZE;i++) {
        tmp=record[i]-right.get(i)-less;
        less = tmp<0;
        if(less) tmp += 255;
        ret.push(tmp mod_256);
    }
    return ret;
}

superll superll::ret_multiply(superll right) {
    byte result[(STD_SIZE << 1)+1]={};
    int tmp;
    for(int i=0;i<STD_SIZE;i++) {
        for(int j=0;j<STD_SIZE;j++) {
            tmp = record[i]*right.get(j)+result[i+j];
            result[i+j] = tmp mod_256;
            result[i+j+1] += tmp >> 8;
        }
    }
    int len=(STD_SIZE << 1);
    while(len && !result[len]) --len;
    return superll(result, result+len+1);
}

void str_to_hp(char* str,superll* num) {
    int len=0;
    short tmp=0;
    for(;str[len];len++) {
        tmp = (tmp << 1)+(tmp << 3)+(str[len]^48);
        printf("tmp=%d\n",tmp);
        while(tmp >= 256) {
            num->push(tmp mod_256);
            tmp >>= 8;
        }
    }
    while(tmp) {
        num->push(tmp mod_256);
        tmp >>= 8;
    }
}
