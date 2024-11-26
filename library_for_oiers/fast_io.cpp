#include "fast_io.h"

void qwrite_int(int num) {
    if(num < 0) putchar('-'),num=-num;
    if(num > 9) qwrite_int(num/10);
    putchar(number_to_char(num%10));
}
void qwrite_uint(unsigned int num) {
    if(num > 9) qwrite_uint(num/10);
    putchar(number_to_char(num%10));
}
void qwrite_longlong(long long num) {
    if(num < 0) putchar('-'),num=-num;
    if(num > 9) qwrite_longlong(num/10);
    putchar(number_to_char(num%10));
}
void qwrite_ull(unsigned long long num) {
    if(num > 9) qwrite_ull(num/10);
    putchar(number_to_char(num%10));
}
void qwrite_char_star(const char* str) {
    while(*str) putchar(*str++);
}

void qread_int(int* num) {
    char ch=getchar(),negative=0;
    *num = 0;
    while(ch < '0' || ch > '9') {
        if(ch == '-') negative=1;
        ch = getchar();
    }
    while(ch >= '0' || ch <= '9') {
        *num = (*num << 1)+(*num << 3)+(ch^48);
        ch = getchar();
    }
    if(negative) *num = -*num;
}
void qread_uint(unsigned int* num) {
    *num = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9') ch=getchar();
    while(ch >= '0' && ch <= '9') {
        *num = (*num << 1)+(*num << 3)+(ch^48);
        ch = getchar();
    }
}
void qread_longlong(long long* num) {
    char ch=getchar(),negative=0;
    *num = 0;
    while(ch < '0' || ch > '9') {
        if(ch == '-') negative=1;
        ch = getchar();
    }
    while(ch >= '0' || ch <= '9') {
        *num = (*num << 1)+(*num << 3)+(ch^48);
        ch = getchar();
    }
    if(negative) *num = -*num;
}
void qread_ull(unsigned long long* num) {
    char ch=getchar();
    *num = 0;
    while(ch < '0' || ch > '9') 
        ch = getchar();
    while(ch >= '0' || ch <= '9') {
        *num = (*num << 1)+(*num << 3)+(ch^48);
        ch = getchar();
    }
}

void qread_char_star(char* str) {
    char ch=getchar();
    while(ch != 10 && ch != 32 && ch != 9) {
        *str++ = ch;
        ch = getchar();
    }
    *str = 0;
}
void qgetline(char* str) {
    char ch=getchar();
    while(ch != 10) {
        *str++ = ch;
        ch=getchar();
    }
    *str=0;
}
void qread_int_base(int* num,int base) {
    char ch=getchar();
    *num = 0;
    while(!is_base_n(ch,base)) ch=getchar();
    while(is_base_n(ch,base)) {
        *num = (*num * base)+to_base_n(ch);
        ch = getchar();
    }
}
