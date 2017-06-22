#include "cocos2d.h"
#ifndef _ZHIFAMATH_H_ 
#define _ZHIFAMATH_H_ 


namespace ZhiFa
{
	class Math
	{
	public:
		static float RandF()
		{
			return (float)(rand()) / (float)RAND_MAX;
		}

		// Returns random float in [a, b).
		static float RandF(float a, float b)
		{
			return a + RandF()*(b - a);
		}

		template<typename T>
		static T Min(const T& a, const T& b)
		{
			return a < b ? a : b;
		}

		template<typename T>
		static T Max(const T& a, const T& b)
		{
			return a > b ? a : b;
		}

		template<typename T>
		static T Lerp(const T& a, const T& b, float t)
		{
			return a + (b - a)*t;
		}

		template<typename T>
		static T Clamp(const T& x, const T& low, const T& high)
		{
			return x < low ? low : (x > high ? high : x);
		}

			// Returns the polar angle of the point (x,y) in [0, 2*PI).
		static float AngleFromXY(float x, float y);
		static float RadToAngle(float rad);
		static float AngleToRad(float angle);

		static const float Infinity;
		static const float Pi;

#define XM_PI               3.141592654f
#define XM_2PI              6.283185307f
#define XM_1DIVPI           0.318309886f
#define XM_1DIV2PI          0.159154943f
#define XM_PIDIV2           1.570796327f
#define XM_PIDIV4           0.785398163f

#define XM_SELECT_0         0x00000000
#define XM_SELECT_1         0xFFFFFFFF

#define XM_PERMUTE_0X       0x00010203
#define XM_PERMUTE_0Y       0x04050607
#define XM_PERMUTE_0Z       0x08090A0B
#define XM_PERMUTE_0W       0x0C0D0E0F
#define XM_PERMUTE_1X       0x10111213
#define XM_PERMUTE_1Y       0x14151617
#define XM_PERMUTE_1Z       0x18191A1B
#define XM_PERMUTE_1W       0x1C1D1E1F

#define XM_CRMASK_CR6       0x000000F0
#define XM_CRMASK_CR6TRUE   0x00000080
#define XM_CRMASK_CR6FALSE  0x00000020
#define XM_CRMASK_CR6BOUNDS XM_CRMASK_CR6FALSE

#define XM_CACHE_LINE_SIZE  64

#define XMMin(a, b) (((a) < (b)) ? (a) : (b))
#define XMMax(a, b) (((a) > (b)) ? (a) : (b))


	};
};
#endif