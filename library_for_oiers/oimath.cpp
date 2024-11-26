#include "oimath.h"

ll power(ll a,ll b) {
    ll ret = 1LL;
    while(b) {
        if(b&1LL) ret *= a;
        a *= a;
        b >>= 1LL;
    }
    return ret;
}
ll power(ll a,ll b,ll p) {
    ll ret = 1LL;
    while (b) {
        if(b&1LL) ret = ((ret%p)*(a%p)) % p;
        a = ((a%p)*(a%p))%p;
        b >>= 1LL;
    }
    return ret;
}

void erato(bool* array,int max) {
    for(int i=2;i<=max;i++) 
        if(!array[i]) 
            for(int j=i<<1;j <= max;j += i) 
                array[i]=0;
}

void catalan(long long* array,int max) {
    array[0]=1;
    for(int i=1;i<=max;i++) array[i] = 
        array[i-1]* (4 * i - 2) / (i + 1);
}
