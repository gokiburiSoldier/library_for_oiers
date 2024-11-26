#ifndef _LONG_H
#define _LONG_H 1

#define byte char
#define BYTE_MAX 255 
#define STD_MALLOC_SIZE 512

#include <stddef.h>
#include <stdio.h>

class stdnum { /* 这玩意都可以单独写一个头文件了 */
    private:
        byte *array,*mtop,attr;
    public:
        stdnum(void);
        stdnum(byte*,byte*);
        stdnum(int*,int*);
        stdnum(int);
        const char* to_string(void) const;
        void printself(void);
        const byte get(int) const;
        byte& index(int);
    public: /* 运算符重载 */
        void to_negative(void);
        void push(byte num);
        byte* top(void) const;
        byte* bottom(void) const;
        bool operator< (const stdnum&) const;
        stdnum add(const stdnum&);
        stdnum subtract(const stdnum&);
        byte moveleft(byte);
        byte moveright(byte);
    public:
        bool and_1(void) const;
        bool isZero(void) const;
        stdnum ret_multiply(stdnum);
};

#endif
