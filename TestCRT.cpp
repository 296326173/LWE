#include "CRT.hpp"
#include "MyTools.hpp"
int main(){
    Vec<ZZ> numbers;
    numbers.SetLength(8);
    for (int i = 0; i < 8; ++i) {
        numbers[i] = i+2;
    }
    Vec<ZZ> mods;
    ZZ q(16);
    getMods(q,8,mods);
    for(auto i:mods){
        cout<<i<<endl;
    }
    auto sum = CRT1(numbers, mods);
    Vec<ZZ> result;
    InvCRT(sum, mods,result);
    for(auto&i:result){
        cout<<i<<endl;
    }
    return 0;
}
