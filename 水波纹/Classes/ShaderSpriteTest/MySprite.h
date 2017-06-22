#ifndef _MYSPRITE_H_
#define _MYSPRITE_H_
#include "..\ShaderHelper\2dShaderSprite.h"

namespace ZhiFa
{
	class MySprite : public ShaderSprite2d
	{
	public:
		MySprite();
		virtual ~MySprite();
		static MySprite* create(std::string v_fpath);
		virtual bool init(cocos2d::Texture2D *v_tex);
		void setTextColor(cocos2d::Vec4 v_color);
		void setEffectColor(cocos2d::Vec4 v_color);
	protected:
		virtual void addUniformToManager()override;
		GLManageredUniformVec4 *m_uTextColor;
		GLManageredUniformVec4 *m_uEffectColor;
	};
};



#endif