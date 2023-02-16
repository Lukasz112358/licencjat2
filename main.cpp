#include<complex>
#include<cmath>
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<iostream>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<cassert>
#include<fstream>
#include"field.h"
#include"fourier.cpp"
#include"find_prime.cpp"



int Q;
std::vector<field>& compute(__int128 l, __int128 r, std::vector<field>& g, std::vector<field>& f){
    if(r-l>200)std::cout<<toString(l)<<' '<<toString(r)<<" "<<Q<<std::endl;
    if(l < r ){
        __int128 m = (l+r)/2;
        compute(l,m,g,f);
        std::vector<field>F(r-l+1,field(0));
        std::vector<field>G(m-l+1,field(0));
        for(int i = 0; i < r-l+1; i++){
            F[i] = i*f[i];
        }
        for(int i = 0; i < m-l+1; i++){
            G[i] = g[i+l];
        }
        __int128 size = 1;
        while(size < (__int128)((G.size() + F.size()) -1 )){
            size *= 2;
        }
        std::vector<field>H(size,field(0));
        H= multiplication(F,G);
        for(int i=(int)(m+1);i<r+1;i++){
            g[i]+=(H[i-l]/field(i));
        }
        compute(m+1,r,g,f);
    }
    //std::cout<<"returned";
    return g;
}

std::vector<field> mainCompute(std::vector<field>& f){
    std::vector<field> g(f.size(),0);
    g[0] = 1;
    compute(0,f.size()-1,g,f);
    return g;
}



std::vector<field> B(std::vector<field> s, __int128 t){
    std::vector<field> a(t+1,field(0));
    std::vector<field> ans(t+1,field(0));
    int K;
    for(int i =0; i<s.size(); i++){
        if(s[i].getValue()<=t)a[s[i].getValue()] ++;
    }
    for(__int128 k = 1; k <= t; k++){
        if(k%1000==0)std::cout<<"k="<<toString(k)<<" B"<<" "<<Q<<" JW"<<std::endl;
        for(__int128 j = 1; j <= t/k ; j++){
            if(j % 1000 == 0) std::cout<<"j="<<toString(j)<<" B"<<std::endl;
            field x(1);
            if((j-1)%2==1) x *=(-1);
            ans[k*j] = ans[k*j] + a[k]*x/field(j);
        }
    }
    return ans;
}

std::vector<bool> JinWu(std::vector<field>& s, __int128 t){
    __int128 p  = find_prime(s.size(), t);
    std::cout <<"x"<< toString(p)<<"x"<<std::endl;
    field::setP(p);
    std::vector<field> Bans(t+1,field(0));
    Bans= B(s,t) ;
    std::vector<field> computeAns(t+1,field(0));
    computeAns = mainCompute(Bans);
    std::vector<bool>ans(t+1,false);
    for(int i =0; i< t+1; i++){
        if(computeAns[i].getValue() != 0)ans[i]=true;
    }
    return ans;

}



std::vector<bool> brutalSum(std::vector<field>  s,long long t){    
    std::bitset<1000001>DP = std::bitset<1000001>();
    DP.set(0,1);
    for(int i = 0; i < s.size(); i++){
        if(i%1000==0)std::cout<<"i="<<i<<" "<<Q<<" BS"<<std::endl;
        DP=DP|(DP<<((long long)s[i].getValue()));
    }
    
    std::vector<bool> answer(t+1,0);
    for(int i =0; i< t+1;i++){
        answer[i] = (DP.test(i) == 1);
    }
    return answer;
}
int main() {
    int start = std::time(NULL);
    std::cout<<"podaj liczbe testow"<<std::endl;
    int tests;
    std::cin>>tests;
    std::ofstream wynik;
    wynik.open("wynik");
    for(int q = 0 ; q < tests; q++){
        Q = q;
        __int128 n,t;
        std::string sn,st;
        std::cout<<"podaj n i t"<<std::endl;
        std::cin>>sn>>st;
        n = fromString(sn);
        t = fromString(st);
        __int128 p  = find_prime(n, t);
        field::setP(p);
        std::cout<<"podaj S"<<std::endl;
        vector<field>S(n,0);
        std::string s;
        for(int i = 0; i < n; i++){
            std::cin>>s;
            S[i] = field(fromString(s));
        }
        std::vector<bool>ans(t+1,false);
        wynik<<"n="<<toString(n)<<" t="<<toString(t)<<std::endl;
        
        auto start = std::chrono::steady_clock::now();
        ans =  JinWu(S,t);
        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;
        wynik << "Jin Wu time: " <<std::chrono::duration<double, std::milli> (diff).count()<<"ms"<<std::endl;
        std::vector<bool>ans2(t+1,false);
        start = std::chrono::steady_clock::now();
        ans2 = brutalSum(S,t);
        end = std::chrono::steady_clock::now();
        diff = end - start;
        wynik << "Brutal time: "<< std::chrono::duration<double, std::milli> (diff).count()<<"ms"<<std::endl;
        std::cout<<endl;
        for(int i = 0; i< t+1; i++){
            if(i%200==199)std::cout<<endl;
            std::cout<<ans[i];
        }
        std::cout<<std::endl<<std::endl;
        std::cout<<std::endl<<std::endl;
        int poprawne = 0;
        for(int i = 0; i< t+1; i++){
            poprawne+=(ans[i]==ans2[i]);
        }
        wynik<<"poprawne "<<poprawne<<"/"<<toString(t+1)<<std::endl;
        wynik<<"____________________________________________________________________________________________________"<<std::endl;

    }
    return  0;
}
