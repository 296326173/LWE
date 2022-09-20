#include "LWE.hpp"
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    clock_t start,finish;
    ZZ q(2);
    q<<=256;
    long n = 1024;
    ZZ p(64);
    ZZ_p::init(q);
    ZZ_pX f;
    f.SetLength(n+1);
    f[0] =1;f[n] = 1;
    ZZ_pXModulus fx;
    build(fx,f);
    Param param;
    param.p = p;
    param.q = q;
    param.fx = fx;
    param.n = n;
    cout<<"密文模数："<<q<<"\n明文模数："<<p<<"\n明文slot数："<<n<<endl;
    Vec<ZZX> sk;
    start = clock();
    generateSerretKey(n, q,sk);
    finish = clock();
    cout<<"生成密钥的时间："<<(finish-start);
    //cout<<"密钥："<<sk<<endl;
    Vec<ZZ_pX> pk;
    start = clock();
    generatePublicKey(param,sk,pk);
    finish = clock();
    cout<<"生成公钥的时间："<<(finish-start);
    //cout<<"公钥："<<pk<<endl;
    ZZ_pX m;
    m.SetLength(n);
    m[0] =1;
    m[1] = 2;
    m[2] = 3;
    m[3] = 4;
    m[4] = 5;
    m[5] = 29;
    m[6] = 22;
    m[7] = 23;
    m[1023] = 1;
    Vec<ZZ_pX> cipher;
    start = clock();
    Enc(param,pk,m,cipher);
    finish = clock();
    cout<<"加密的时间："<<(finish-start);
   //cout<<"密文："<<cipher<<endl;
    ZZ_pX M;
    start = clock();
    Dec(param,sk,cipher,M);
    finish = clock();
    cout<<"解密的时间："<<(finish-start);
    cout<<"明文："<<M<<endl;
    return 0;
}