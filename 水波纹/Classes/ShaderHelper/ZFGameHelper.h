//
//  ZFGameHelper.h
//  starblazer
//
//  Created by chuzy on 14-9-18.
//
//

#ifndef __starblazer__ZFGameHelper__
#define __starblazer__ZFGameHelper__

#include <iostream>

#include "cocos2d.h"

namespace ZhiFa
{
    class GameHelper
    {
    public:
        static std::string IntegerToString(int v_integer);
        static std::string FloatToString(float v_float,int v_persent);
    };
};

#endif /* defined(__starblazer__ZFGameHelper__) */
