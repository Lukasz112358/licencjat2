#include "field.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<time.h>
#include<stack>


field enoughGoodRoot(__int128 k){
    field ans = field::getAlmostPrimitiveRoot();
    for(int i = k; i < field::getDegreeOfDegree(); i++){
        ans *= ans;
    }
    return ans;
}

std::string binary(__int128 x){
    std::string ans = "";
    for(int i = 0; i <64;i++){
        if(x%2 == 0)ans = "0" + ans;
        if((x%2)*(x%2) == 1)ans = "1" + ans;
        x = x>>1;
    }
    return ans;
}


long long reverseBits(long long x, long long k) {
    x = ((x & 0x5555555555555555) << 1)  | ((x & 0xAAAAAAAAAAAAAAAA) >> 1);  
    x = ((x & 0x3333333333333333) << 2)  | ((x & 0xCCCCCCCCCCCCCCCC) >> 2);
    x = ((x & 0x0F0F0F0F0F0F0F0F) << 4)  | ((x & 0xF0F0F0F0F0F0F0F0) >> 4);
    x = ((x & 0x00FF00FF00FF00FF) << 8)  | ((x & 0xFF00FF00FF00FF00) >> 8);
    x = ((x & 0x0000FFFF0000FFFF) << 16) | ((x & 0xFFFF0000FFFF0000) >> 16);
    x = ((x & 0x00000000FFFFFFFF) << 32) | ((x & 0xFFFFFFFF00000000) >> 32);
    x = ((unsigned long long)x)>>(64-k);
    return x;
}

void setToDo(std::vector<field>&coefficients, long long size){
    long long length = coefficients.size();
    long long log = 0;
    long long s = size;
    while(s > 1){
        s /= 2;
        log +=1;
    }
    for(__int128 i = 0; i < size - length; i++){
        coefficients.push_back(field(0));
    }
    for(long long i = 0; i < size; i++){
        long long j = reverseBits(i,log);
        if(j>i){
            field a = coefficients[i];
            coefficients[i] = coefficients[j];
            coefficients[j] = a;
        }
    }
}
__int128 log(__int128 x){
    __int128 ans = 0;
    while(x!=0){
        x /=2;
        ans ++;
    }
    return ans - 1;
}
std::vector<field> copy(std::vector<field> x){
    std::vector<field> ans(x.size());
    for(size_t i = 0; i<x.size(); i++){
        ans[i] = x[i];
    }
    return ans;
}
void inline DFT(std::vector<field>&coefficients, __int128 size, field omegaM){
    std::vector<field>useLater = copy(coefficients);
    setToDo(coefficients,size);
    field omegaMLater = omegaM;
    field useLaterM = omegaM;
    std::stack<field> omegasM;
    while(omegaM != 1){
        omegasM.push(omegaM);
        omegaM *= omegaM;
    }
    __int128 m = 1;
    while(!omegasM.empty()){   
        field currentOmegaM= omegasM.top();
        omegasM.pop();
        field omega = 1;
        m*=2;
        for(__int128 j = 0; j<m/2;j+=1){
            for(__int128 k = j; k<size; k+=m){
                field t = omega * coefficients[k+m/2];
                field u = coefficients[k];
                coefficients[k] = u+t;
                coefficients[k+m/2] =  u - t;
            }
            omega *= currentOmegaM;
        }
    }
}
std::vector<field>multiplication(std::vector<field> A, std::vector<field> B){
    __int128 size = 1;
    while(size < (__int128)((A.size() + B.size()) -1 )){
        size *= 2;
    }
    __int128 l = log(size);
    field omegaM = enoughGoodRoot(l);
    DFT(A,size,omegaM);
    DFT(B,size,omegaM);
    for(__int128 i=0;i<size;i++){
        A[i] = B[i] * A[i]; 
    }
    omegaM = field(1)/omegaM;
    DFT(A,size,omegaM);
    for(__int128 i=0;i<size;i++){
        A[i] /= field(size);
    }
    return A;
}
