#pragma once
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
using namespace NTL;

void uniqueForZZX(ZZX&x,ZZ &q,long n){
    long i;
    x.rep.SetLength(n);

    for (i = 0; i < n; i++)
        x[i] = RandomBnd(q);
    x.normalize();
}

//生成ZZX多项式的随机数
void randomForZZX(ZZX& x, long n)
{
    long i;
    x.rep.SetLength(n);

    for (i = 0; i < n; i++)
        x[i] = RandomBnd(3)-1;
    x.normalize();
//        x.rep[i]._ZZ_p__rep = RandomBnd(3)-1;
//        RandomBnd(x.rep[i]._ZZ_p__rep, to_ZZ(2));
//        RandomBnd(x._ZZ_p__rep, ZZ_p::modulus());
//        random(x.rep[i]);
}
//获得ZZ_pX的随机数
void randomForZZ_pX(ZZ_pX& x, long n)
{
    long i;
    x.rep.SetLength(n);
    for (i = 0; i < n; i++)
        x[i] = RandomBnd(3)-1;
    x.normalize();
}
//四舍五入
void round(const ZZ& a,const ZZ& b,ZZ &res){
    res = (a%b)* 2 >= b ? a/b+ 1 : a/b;
}

