#ifndef _GAMEMAT_H_
#define _GAMEMAT_H_
#include "cocos2d.h"

namespace ZhiFa
{
	namespace GameMath
	{
		class Segment
		{
		public:
			Segment();
			Segment(cocos2d::Vec2 v_start, cocos2d::Vec2 v_end);
			bool interset(Segment &v_seg);
			bool onSegment(cocos2d::Vec2 v_point);
			float Top();
			float Bottom();
			float Left();
			float Right();
			cocos2d::Vec2 ToDir();
			cocos2d::Vec2 m_start, m_end;
		};
        class Line
        {
        public:
            Line();
            Line(cocos2d::Vec2 v_dir,float v_b);
            ~Line();
            float calPoint(cocos2d::Vec2 v_point);
            cocos2d::Vec2 dir;
            float b;
        };
	};
    class GameMathHelp
    {
    public:
        static float squre(float a);
        static float pown(float q,int n);
        static float GeometricSequencesSum(float a1,float q,int n);
        static float angleToRad(float v_angle);
        static float radToAngle(float v_rad);
        static float getFloatPart(float v_float,int v_idx);
    };
};


#endif