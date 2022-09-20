#pragma once
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include "MyTools.hpp"

using namespace NTL;

struct Param{
    long n;
    ZZ p;
    ZZ q;
    ZZ_pXModulus fx;
};

//生成密钥
void generateSerretKey(long  n,ZZ& q,Vec<ZZX>& res){
    res.append(to_ZZX(1));
    ZZX s;
    randomForZZX(s, n);
    res.append(-s);
}

//生成公钥
void generatePublicKey(Param& param,Vec<ZZX> sk,Vec<ZZ_pX>& res){
    ZZ_p::init(param.q);
    ZZX a;
//    uniqueForZZX(a,param.q,param.n);
    randomForZZX(a,param.n);
    ZZX e1;randomForZZX(e1,param.n);
    ZZ_pX b = to_ZZ_pX(a*(-sk[1])+e1)%param.fx;//b = (a*s1+e1)mod fx
    res.append(b);
    res.append(to_ZZ_pX(a));
}
//加密
void Enc(Param param,Vec<ZZ_pX>& pk,ZZ_pX& m,Vec<ZZ_pX>& res){
    ZZ_pX e2,e3,e4;
    randomForZZ_pX(e2,param.n);
    randomForZZ_pX(e3,param.n);
    randomForZZ_pX(e4,param.n);
    res.append(m* (to_ZZ_pX(param.q/param.p)+pk[0]*e2+e3)%param.fx);//q/2*m+be2+e3
    res.append((pk[1]*e2+e4)%param.fx);//a*e2+e4
}

//解密
void Dec(Param& param, Vec<ZZX>&sk,Vec<ZZ_pX>&cipher,ZZ_pX& res){
    ZZ_p::init(param.p);
    auto temp = (sk[0]* to_ZZX(cipher[0])+sk[1]* to_ZZX(cipher[1]))*param.p;

    for (int i = 0; i < param.n; ++i) {
        round(temp[i],param.q,temp[i]);
    }
    res = to_ZZ_pX(temp);
    rem21(res, res, param.fx);//    res%=fx;
    res.SetLength(param.n);
}