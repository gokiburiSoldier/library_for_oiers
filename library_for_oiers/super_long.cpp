#include "super_long.h"

stdnum::stdnum(void) {
    this->array = new byte[STD_MALLOC_SIZE]();
    mtop = this->array;
    attr = 0;
}

stdnum::stdnum(byte* begin,byte* end) {
    this->array = new byte[STD_MALLOC_SIZE]();
    mtop = this->array;
    attr = 0;
    for(byte* i=begin;i != end;i++) *mtop++ = *i;
}

stdnum::stdnum(int* begin,int* end) {
    this->array = new byte[STD_MALLOC_SIZE]();
    mtop = this->array;
    attr = 0;
    if(end > begin) for(int* i=end-1;i>=begin;--i) {
        int val = *i;
        if(val < 0) {
            attr |= 1;
            val = -val;
        }
        while(val) {
            *mtop++ = val % 100;
            val /= 100;
        }
    }
}

stdnum::stdnum(int right) {
    this->array = new byte[STD_MALLOC_SIZE]();
    mtop = this->array;
    attr = right<0;
    while(right) {
        *mtop++ = right%100;
        right /= 100;
    }
}

const char* stdnum::to_string(void) const {
    static char ret[(STD_MALLOC_SIZE << 1)+STD_MALLOC_SIZE+1] = {};
    int index = 0;
    if(attr & 1) ret[index++] = '-';
    for(byte* i = mtop-1;i >= array;--i) {
        ret[index++] = (*i)/10 ^ 48;
        ret[index++] = (*i)%10 ^ 48;
    }
    return ret;
}

byte& stdnum::index(int id) {
    if(array+id >= mtop) mtop=array+id;
    return array[id];
}

void stdnum::printself(void) {
    if(attr&1) putchar('-');
    if(*(mtop-1) == 0) mtop--;
    if(*(mtop-1)/10) {
        putchar(*(mtop-1)/10 ^ 48);
        putchar(*(mtop-1)%10 ^ 48);
    }else if(*(mtop-1) % 10) putchar(*(mtop-1)%10 ^ 48);
    for(byte* i=mtop-2;i >= array;--i) {
        putchar((*i)/10 ^ 48);
        putchar((*i)%10 ^ 48);
    }
}

const byte stdnum::get(int index) const {
    return array[index];
}

void stdnum::to_negative(void) {
    this->attr ^= 1;
}
void stdnum::push(byte num) {
    *mtop++ = num;
}
byte* stdnum::top(void) const {
    return mtop;
}
byte* stdnum::bottom(void) const {
    return array;
}
bool stdnum::operator<(const stdnum& right) const {
    if(mtop-array > right.top()-right.bottom()) return false;
    for(byte *i=mtop-1,*j=right.top()-1;i >= array;--i) {
        if(*i > *j) return false;
    }
    return false;
}

stdnum stdnum::add(const stdnum& other) {
    byte *new_top = array,tmp;
    int more=0,i=0;
    while(other.bottom()+i < other.top()) {
        tmp = other.get(i++);
        *new_top += (short)(tmp)+more;
        more=0;
        if(*new_top >= 100) {
            *new_top -= 100;
            more ++;
        }
        new_top++;
    }
    *new_top++ += more;
    if(new_top > mtop) mtop = new_top;
    new_top = NULL;
    return other;
}

stdnum stdnum::subtract(const stdnum& other) {
    byte *new_top = array,tmp;
    int less=0,i=0,zero=0;
    while(tmp = other.get(i++)) {
        *new_top -= (short)(tmp)+less;
        less = 0;
        if(*new_top < 0) {
            *new_top += 100;
            ++less;
        }
        if(*new_top) zero = 0;
        else         zero++;
        new_top ++;
    }
    *new_top++ -= less;
    if(! *new_top) zero++;
    mtop = new_top - zero;
    new_top = NULL;
    return other;
}

byte stdnum::moveleft(byte right) {
    /* 从低位开始 */
    byte *new_top=array; 
    short more=0;
    while(new_top < mtop) {
        short value = short(*new_top) << short(right);
        *new_top++ = (value+more)%100;
        more = (value+more)/100;
    }
    while(more) {
        *new_top++ = more%100;
        more /= 100;
    }
    mtop = new_top;
    return right;
}

byte stdnum::moveright(byte right) {
    byte* new_top=mtop-1;
    short more=0;
    while(new_top >= array) {
        short value = short(*new_top)+more >> right;
        more = (*new_top &1)*100;
        *new_top = value%100;
        new_top--;
    }
    while(!*mtop) mtop--;
    ++mtop;
    return right;
}

bool stdnum::and_1(void) const {
    return array[0] & 1;
}
bool stdnum::isZero(void) const {
    return mtop == array && *array == 0;
}

stdnum stdnum::ret_multiply(stdnum right) {
    int tmp[STD_MALLOC_SIZE<<1]={},len=mtop-array+right.top()-right.bottom();
    for(int i=0;i<mtop-array;++i)
        for(int j=0;j<right.top()-right.bottom();j++) 
            tmp[i+j] += array[i]*right.get(j);
    for(int i=0;i<len;i++) {
        tmp[i+1] += tmp[i]/100;
        tmp[i] %= 100;
    }
    int nlen=len;
    for(int i=len-1;i>=0;--i) if(tmp[i]) continue; else --nlen;
    len = nlen;
    for(int i=0;i<(len >> 1);i++) {
        tmp[i] ^= tmp[len-i-1];
        tmp[len-i-1] ^= tmp[i];
        tmp[i] ^= tmp[len-i-1];
    }
    return stdnum(tmp, tmp+len);
}
