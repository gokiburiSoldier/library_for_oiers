#ifndef _SLONG_II_H
#define _SLONG_II_H 1 

#define STD_SIZE 32
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
};

#endif 
