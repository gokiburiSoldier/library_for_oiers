/**
 * 如果你在同时使用`STL`和本文件时报错了: 
 * - 先include `STL`
 * 
 * 例如:
 * ```c++
 * #include "slong.h"
 * #include <iostream>
 * ```
 * 应该是:
 * ```c++
 * #include <iostream>
 * #include "slong.h"
 * ```
 */

#ifndef _SLONG_II_H
#define _SLONG_II_H 1 

#define STD_SIZE 48
#define byte     unsigned char
#define mod_256 &255
#define modwith_256 &=255

class superll {
    private:
        byte *record,*stack_top;
    public:
        superll(void);
        superll(unsigned long long);
        superll(int);
        superll(byte*,byte*);
        ~superll();
    public:
        void push(byte);
        byte& get(int) const;
        void show(void) const;
    public:
        void dev_ten(void);
        byte mod_ten(void);
        bool is_zero(void);
    public:
        superll ret_add(superll);
        superll ret_subtract(superll);
        superll ret_multiply(superll);
};

void rcstr_to_ll(char*,superll*);

#endif 
