#ifndef _LASET_H_
#define _LASET_H_
#include "../ShaderHelper/2dShaderSprite.h"
namespace ZhiFa
{
	class Laser : public ShaderSprite2d
	{
	public:
		Laser();
		~Laser();
	protected:
		bool init();
	};
};




#endif