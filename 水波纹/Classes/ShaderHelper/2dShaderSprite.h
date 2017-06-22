#ifndef _2DSHADERSPRITE_H_
#define _2DSHADERSPRITE_H_
#include "2dShaderNode.h"

namespace ZhiFa
{
	class ShaderSprite2d : public ShaderNode2D
	{
	public:
		virtual void onDraw(cocos2d::GLProgram *v_glp)override;
		virtual void setContentSize(const cocos2d::Size& v_size)override;
		virtual void loadTexture(cocos2d::Texture2D *v_tex);
	protected:
		ShaderSprite2d();
		virtual ~ShaderSprite2d();
		bool initWithFragmentShader(std::string v_fragShaderPath);
		virtual bool init(cocos2d::Texture2D *v_tex);
		virtual void onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp)override;
		virtual void genAttributeLoc(cocos2d::GLProgram *v_glp)override;
		virtual void bindVertexLayout(cocos2d::GLProgram *v_glp)override;
		virtual void addUniformToManager()=0;
		virtual void beginDraw();
		cocos2d::Texture2D *m_tex;
		bool m_firstInit,m_vertexNeedChange;
		GLint m_posLoc, m_colorLoc, m_texLoc;
		cocos2d::Vec4 m_vertColor[4];
	};
};

#endif