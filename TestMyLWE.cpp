#pragma once
#include "CRT.hpp"
#include "MyLWE.hpp"
#include "LWE.hpp"
int main(){
    clock_t start,finish;
    ZZ q(2);
    q<<=256;
    long n = 16;
    ZZ_p::init(q);
    ZZ p(64);
    ZZ_p::init(q);
    ZZ_pX f;
    f.SetLength(n+1);
    f[0] =1;f[n] = 1;
    ZZ_pXModulus fx;
    build(fx,f);
    Param param_1;
    param_1.p = p;
    param_1.q = q;
    param_1.fx = fx;
    param_1.n = n;

    MyParam param;

    Vec<ZZX> sk;
    generateSerretKey(n,q,sk);
    Vec<ZZ_pX> pk;
    generatePublicKey(param_1,sk,pk);
    init(q,p,n,param,pk);
    Vec<ZZ> m;
    m.SetLength(n);
    for (int i = 0; i < n; ++i) {
        m[i] = i;
    }
    //test LWE
    Vec<ZZ_pX> cipher1;
    auto plain = to_ZZ_pX(to_ZZX(m));
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        Enc(param_1,pk, plain,cipher1);
    }
    finish = clock();
    cout<<"加密的时间(ms)："<<(finish-start);
    ZZ_pX res_1;
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        Dec(param_1,sk,cipher1,res_1);
    }
    finish = clock();
    cout<<"\n解密的时间(ms)："<<(finish-start)<<endl;
//    cout<<res_1<<endl;
    //test MyLWE
    Vec<ZZ> cipher;
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        Enc(param,m,cipher);
    }
    finish = clock();
    cout<<"加密的时间(ms)："<<(finish-start);
    ZZ_pX res_m;
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        Dec(param,sk,cipher,res_m);
    }
    finish = clock();
    cout<<"\n解密的时间(ms)："<<(finish-start)<<endl;
//    cout<<res_m<<endl;
    return 0;
}