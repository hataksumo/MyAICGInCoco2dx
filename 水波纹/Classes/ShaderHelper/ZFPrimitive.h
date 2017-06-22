#ifndef _ZFPRIMITIVE_H_
#define _ZFPRIMITIVE_H_
#include "cocos2d.h"
namespace ZhiFa
{
	struct Position2TexCoord2
	{
		cocos2d::Vec2 Pos;
		cocos2d::Vec2 TexCoord;
	};
#define VertexOffset(Type,off) ((void*)((Type*)0 + off))
};

#endif