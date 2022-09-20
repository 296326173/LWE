#include "MyTools.hpp"
#include "CRT.hpp"
struct MyParam{
    long n;
    ZZ p;
    ZZ q;
    ZZ_pXModulus fx;
    ZZX f;
    Vec<ZZ> mods;
    Vec<ZZ> fi;
    ZZ F;
    ZZ be2_e3;
    ZZ ae2_e4;
};

void init(ZZ&q,ZZ&p,long n,MyParam& param,Vec<ZZ_pX>& pk){
    ZZ_pX f;
    f.SetLength(n+1);
    f[0] =1;f[n] = 1;
    ZZ_pXModulus fx;
    build(fx,f);
    param.f = to_ZZX(f);
    param.q = q;
    param.p = p;
    param.n = n;
    param.fx = fx;

    Vec<ZZ> mods;
    getMods(q,n,mods);

    param.mods = mods;
    param.F = getF(mods);
    param.fi = getFi(param.F,mods);

    ZZ_pX e2;
    randomForZZ_pX(e2,param.n);
    ZZ_pX e3;
    randomForZZ_pX(e3,param.n);
    ZZ_pX be = (e2*pk[0]+e3)%fx;
    Vec<ZZ> temp = to_ZZX(be).rep;
//    cout<<"\ntemp:"<<temp<<endl;
    param.be2_e3 = CRT1(temp,mods);

    ZZ_pX e4;
    randomForZZ_pX(e4,param.n);

    ZZ_pX bt = (e2*pk[1]+e4)%fx;
    Vec<ZZ> temp1 = to_ZZX(be).rep;
    param.ae2_e4 = CRT1(temp1,mods);
//    cout<<endl<<"CRT_res:"<<CRT_res<<endl;
//    Vec<ZZ> result;
//    InvCRT(CRT_res,mods,result);
//    cout<<endl<<"result:"<<result<<endl;

}

void Enc(MyParam& param,Vec<ZZ> &m,Vec<ZZ>& result){
    ZZ A(0);
    InnerProduct(A,m,param.fi);
    result.append(A+param.be2_e3);
    result.append( param.ae2_e4);
}

void Dec(MyParam & param,Vec<ZZX> &sk,Vec<ZZ>& cipher,ZZ_pX&res){
    Vec<ZZ> cipher0;
    InvCRT(cipher[0],param.mods,cipher0);
    Vec<ZZ> cipher1;
    InvCRT(cipher[1],param.mods,cipher1);
    ZZ_p::init(param.p);
//    cout<<param.p<<endl;
    auto temp =((sk[0]* to_ZZX(cipher0)+sk[1]* to_ZZX(cipher1))*param.p)%param.f;
    for (int i = 0; i < param.n; ++i) {
        round(temp[i],param.q,temp[i]);
    }
//    cout<<temp<<endl;
//    cout<<temp.rep.length()<<endl;
    res = to_ZZ_pX(temp);
//    cout<<res<<endl;
    rem21(res, res, param.fx);//    res%=fx;
//    cout<<res<<endl;
    res.SetLength(param.n);
}


