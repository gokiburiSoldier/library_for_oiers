#include "slong.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
    static char str[STD_SIZE<<2]={}; /* 一个随意的数字 */
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
        tmp = (more+*i)/10;
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

#if 0
void str_memset(char* str,int size) {
    for(int i=0;i<size && str[i];i++) str[i]=0;
}
void str_memcpy(char* str,int size,const char* src) {
    for(int i=0;i<size && src[i];++i) str[i]=src[i];
}
#endif

void rcstr_to_ll(const char* str,superll* num,int size) {
    if(size <= 0) return;
    --size;
    char n_str[size+1]={};
    int indexns=0;
    short tmp=0;
    #if 0
    for(;str[len];len++) {
        tmp = (tmp << 1)+(tmp << 3)+(str[len]^48);
        printf("tmp=%d\n",tmp);
        while(tmp >= 256) {
            num->push(tmp mod_256);
            tmp >>= 8;
        }
    }
    do {
        indexns = 0;
        for(len=0;len <= size;len++) {
            tmp = (tmp << 1)+(tmp << 3)+(str[len]^48);
            if(tmp >= 256) {
                if(indexns || (tmp>>8)) n_str[indexns++]=(tmp>>8)^48;
                tmp >>= 8;
            }
        }
        num->push(tmp);
        for(int i=0;i<indexns;i++) str[i] = n_str[i];
        memset(n_str,0,size);
    } while(*str);
    #endif
    for(int i=0;i<=size;++i) {
        tmp = (tmp << 1)+(tmp << 3)+(str[i]^48);
        if(tmp >= 256) {
            if(indexns || (tmp>>8)) n_str[indexns++]=(tmp>>8)^48;
            tmp modwith_256;
        }
    }
    num->push(tmp); /* 余数 */
    rcstr_to_ll(n_str,num,indexns);
}

void lpstr_to_ll(const char* cstr,superll* num,int size) {
    --size;
    char nstr[size+1]={},str[size+1]={};
    strcpy(str,cstr);
    int index=0;
    short tmp=0;
    while(1) {
        for(int i=0;i<=size;++i) {
            tmp = (tmp << 1)+(tmp << 3)+(str[i]^48);
            if(tmp >= 256) {
                if(index || (tmp>>8)) nstr[index++]=(tmp>>8)^48;
                tmp modwith_256;
            }
        }
        size = index-1;
        index = 0;
        strcpy(str, nstr);
        memset(nstr,0,sizeof nstr);
        // printf("tmp=%d,str=%s\n",tmp,str);
        num->push(tmp); /* 余数 */
        tmp = 0;
        if(size < 0) break;
    }
}
