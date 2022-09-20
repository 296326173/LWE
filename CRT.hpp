#pragma once
#include <iostream>
#include <NTL/ZZX.h>

using namespace std;
using namespace NTL;
// (a,b) === 1,result =  inv(a) mod b 等价于 a的逆元
ZZ getInv(const ZZ & a,const ZZ & b){
    ZZ d,s,t;
    XGCD(d,s,t,a,b);
    return s%b;
}
ZZ getF(Vec<ZZ>& mods){
    ZZ result(1);
    for(auto & mod  : mods){
        result*=mod;
    }
    return result;
}
Vec<ZZ> getFi(ZZ &f, Vec<ZZ>&mods){
    Vec<ZZ> fi;
    for(auto& mod:mods){
        ZZ inv = getInv(f/mod,mod);
        fi.append(f * inv/mod);
    }
    return fi;
}

//我自己的CRT方案
ZZ CRT1(Vec<ZZ>& numbers,Vec<ZZ>& mods){
//    if(numbers.length()!=mods.length()){
//        cout<<numbers.length()<<"modlength:"<<mods.length()<<endl;
//    }
    ZZ f = getF(mods);
    Vec<ZZ> fi = getFi(f,mods);
    ZZ A(0);
//    for(int i=0;i<numbers.length();++i){
//        A+=numbers[i]*fi[i];
//    }
    InnerProduct(A,numbers,fi);
    return A;
}
void InvCRT(ZZ& number,Vec<ZZ>& mods,Vec<ZZ>& result){
    for(auto& i:mods){
        result.append(number%i);
    }
}
void getMods(ZZ & q,long n,Vec<ZZ>& mods){
    auto t = q;
    for(int i=0;i<n;++i){
        ZZ res;
        NextPrime(res,t+1);
        mods.append(res);
        t = res;
    }
}
/*
int main1() {
    Vec<ZZ> mods;
    mods.append(to_ZZ(2));
    mods.append(to_ZZ(5));
    mods.append(to_ZZ(7));
    mods.append(to_ZZ(11));
    ZZ f = getF(mods);
    Vec<ZZ> fi = getFi(f,mods);
    for(auto i:fi){
        cout<<i<<" ,";
    }
    Vec<ZZ> m;
    m.append(to_ZZ(1));
    m.append(to_ZZ(3));
    m.append(to_ZZ(6));
    m.append(to_ZZ(8));
//    ZZ A(0);
//    for(int i=0;i<m.length();++i){
//        A+=m[i]*fi[i];
//    }
    ZZ A = CRT1(m,mods);
    cout<<endl<<"A:"<<A<<endl;

    for(int i=0;i<m.length();++i){
        cout<<A%mods[i]<<" ,";
    }
}
*/
//ZZ d;
//ZZ a(14);
//ZZ b(11);
//ZZ s,t;
//XGCD(d,s,t,a,b);
//cout<<"求a%b后a的逆元:"<<s%b<<endl;
//cout<<"d:"<<d<<endl;