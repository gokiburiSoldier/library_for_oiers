#ifndef _FAST_IO_H
#define _FAST_IO_H 1

#include <stdio.h>

#define is_base_n(x,n) (\
    (x) >= '0' && (x) <= '9' || \
    (x) >= 'A' && (x) <= 'A'+(n)\
)
#define to_base_n(x) ( \
    (x)>='0' && (x) <= '9' ? (x)^48 : (x)-'A'+10 \
)
#define number_to_char(x) ((x)^48)

void qwrite_int(int);
void qwrite_uint(unsigned int);
void qwrite_longlong(long long);
void qwrite_ull(unsigned long long);
void qwrite_char_star(const char*);

void qread_int(int*);
void qread_uint(unsigned int*);
void qread_longlong(long long*);
void qread_ull(unsigned long long*);
void qread_char_star(char*);
void qgetline(char*);
void qread_int_base(int*,int);

#endif
