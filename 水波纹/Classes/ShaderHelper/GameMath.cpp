#include "GameMath.h"
#include <algorithm>
#include <stack>

using namespace ZhiFa;
using namespace ZhiFa::GameMath;
using namespace cocos2d;
using namespace std;

Segment::Segment()
{

}
Segment::Segment(Vec2 v_start, Vec2 v_end)
{
	m_start = v_start;
	m_end = v_end;
}
bool Segment::interset(Segment &v_seg)
{
	if (v_seg.Left() <= Right() && v_seg.Right() >= Left() &&
		v_seg.Top() >= Bottom() && v_seg.Bottom() <= Top())//øÏÀŸ≈≈≥‚ µ—È
	{
		Vec2 selfDir = ToDir();
		Vec2 otherDir = v_seg.ToDir();
		if ((v_seg.m_start - m_start).cross(selfDir) * selfDir.cross(v_seg.m_end - m_start) > 0 &&
			(m_start-v_seg.m_start).cross(otherDir) * otherDir.cross(m_end-v_seg.m_start) > 0)//øÁ¡¢ µ—È
		{
			return true;
		}
	}
	return false;
		
		
}
bool Segment::onSegment(cocos2d::Vec2 v_point)
{
	return ((v_point.x - m_start.x)*(m_end.y - m_start.y) == (m_end.x - m_start.x)*(v_point.y - m_start.y) &&//快速排斥实验
		Right() >= v_point.x&&v_point.x >= Left() && Top() >= v_point.y&&v_point.y >= Bottom());//跨立实验
}

float Segment::Top()
{
	return max(m_start.y, m_end.y);
}
float Segment::Bottom()
{
	return min(m_start.y, m_end.y);
}
float Segment::Left()
{
	return min(m_start.x, m_end.x);
}
float Segment::Right()
{
	return max(m_start.x, m_end.x);
}

Vec2 Segment::ToDir()
{
	return m_end - m_start;
}


Line::Line()
{
    
}
Line::Line(Vec2 v_dir,float v_b)
{
    this->dir = v_dir;
    this->b = v_b;
}
Line::~Line()
{
    
}
float Line::calPoint(cocos2d::Vec2 v_point)
{
    return v_point.x * dir.y - v_point.y * dir.x + b * dir.x;
}

float GameMathHelp::squre(float a)
{
    return a*a;
}

float GameMathHelp::pown(float q,int n)
{
    float res = 1;
    std::stack<bool> st;
    while(n)
    {
        if(n&1)
            st.push(true);
        else
            st.push(false);
        n>>=1;
    }
    while(!st.empty())
    {
        bool b = st.top();
        st.pop();
        if(b)
        {
            res = squre(res) * q;
        }
        else
        {
            res = squre(res);
        }
    }
    return res;
}
float GameMathHelp::GeometricSequencesSum(float a1,float q,int n)
{
    return a1 * (1 - pown(q, n)) / (1 - q);
}

float GameMathHelp::angleToRad(float v_angle)
{
    return MATH_DEG_TO_RAD(v_angle);
}
float GameMathHelp::radToAngle(float v_rad)
{
    return MATH_RAD_TO_DEG(v_rad);
}
float GameMathHelp::getFloatPart(float v_float, int v_idx)
{
    float floatPart = v_float - (int)v_float;
    if(v_idx<=0)
        return floatPart;
    else
    {
        return (int)(floatPart * pown(10, v_idx)) % 10;
    }
}
