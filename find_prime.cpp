#include<iostream>
#include<stdio.h>
#include<time.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#include "field.h"
using namespace std;
__int128 random128(__int128 mod){
    __int128 ans=0;
    __int128 x;
    for(int i =0; i< 16; i++){
        x = std::abs(std::rand())%256;
        ans += x;
        ans *=256;
    }
    return std::abs(ans)%mod;
}




__int128 pow2(__int128_t  t){
    __int128_t  ans = 1;
    while(ans <= 2*t)ans *= 2;
    return ans;
}


bool MillerRabinOne(__int128 n, __int128 a){
    if(n==2)return true;
    if(n<2)return false;
    if(n%2==0)return false;
    if(a % n == 1) return true;
    if(a > n) return true;
    __int128 d = n -1;
    __int128 s = 0;
    field::setPsilly(n);
    while(d%2==0){
        d = d/(__int128)2;
        s ++;
    }
    field x(a);
    x ^= d;
    for(int i =0; i< s; i++){
            if(x == (n-1)) return true;
            if(x == 1)return false;
            x ^=2;
    }
    return false;
}

bool MillerRabin(__int128 n){
    __int128 limit = n-2;
    if(limit > 2*std::log(n)*std::log(n))limit = 2*std::log(n)*std::log(n);
    for(int i =2; i< ((int)limit)+1; i++){
        if(!MillerRabinOne(n,i))return false;
    }
    return true;
 }

__int128 find_prime(__int128  n, __int128  t){
    srand((unsigned int)time(NULL));
    __int128  twotok  = pow2(t);
    __int128  mod = (t+n)*(n+t)*(n+t);
    int iterator = 0;
    while (true){
        if(iterator % 10000 == 9999)mod*=2;
        iterator ++;
        __int128  candidate = random128(mod);
        if(candidate > t){
            candidate = candidate * twotok + 1;
            if(MillerRabin(candidate)){
                std::cout<<toString(candidate);
                return candidate;
            } 
        }
    }
    return 0;
}