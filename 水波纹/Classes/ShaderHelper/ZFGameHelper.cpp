//
//  ZFGameHelper.cpp
//  starblazer
//
//  Created by chuzy on 14-9-18.
//
//

#include "ZFGameHelper.h"
#include "GameMath.h"
#include <queue>
#include <stack>
using namespace ZhiFa;
using namespace cocos2d;

std::string GameHelper::IntegerToString(int v_integer)
{
    char strNum[20];
    std::stack<char> st;
    while(v_integer)
    {
        st.push(v_integer%10 + 48);
        v_integer /= 10;
    }
    int idx=0;
    if(v_integer<0)
    {
        strNum[idx++] = '-';
        v_integer = -v_integer;
    }
    while (!st.empty())
    {
        strNum[idx++] = st.top();
        st.pop();
    }
    strNum[idx] = '\0';
    return strNum;
}

std::string GameHelper::FloatToString(float value,int nPrecision)
{
    if(value==floorf(value)){
        return IntegerToString((int)value);
    }
    if(value==0)return std::string("0");
    //
    int sig;
    if(value==0){
        sig=0;
    }else if(value>0){
        sig=1;
    }else{
        sig=-1;
    }
    float abs=fabsf(value);
    int A=floor(abs);
    int B=floor((abs-A)*GameMathHelp::pown(10,nPrecision)) ;
    std::string Astr=IntegerToString(A);
    std::string Bstr=IntegerToString(B);
    std::string zerosStr;
    int makeUpZeroCount=nPrecision-(int)Bstr.size();
    assert(makeUpZeroCount>=0);
    for(int i=0;i<makeUpZeroCount;i++)zerosStr+="0";
    std::string valueStr;
    if(sig<0)valueStr+="-";
    valueStr+=Astr+"."+zerosStr+Bstr;
    return valueStr;
}