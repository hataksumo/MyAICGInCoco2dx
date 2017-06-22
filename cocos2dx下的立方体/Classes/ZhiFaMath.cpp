#include <cmath>
#include"ZhiFaMath.h"
using namespace ZhiFa;
const float Math::Infinity = FLT_MAX;
const float Math::Pi = 3.1415926535f;
float Math::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	// Quadrant I or IV
	if (x >= 0.0f)
	{
		// If x = 0, then atanf(y/x) = +pi/2 if y > 0
		//                atanf(y/x) = -pi/2 if y < 0
		theta = atanf(y / x); // in [-pi/2, +pi/2]

		if (theta < 0.0f)
			theta += 2.0f*Pi; // in [0, 2*pi).
	}

	// Quadrant II or III
	else
		theta = atanf(y / x) + Pi; // in [0, 2*pi).

	return theta;
}
float Math::RadToAngle(float rad)
{
	return rad / Pi * 180.0f;
}
float Math::AngleToRad(float angle)
{
	return angle / 180.0f * Pi;
}