#ifndef _2DSPRITENODE_H_
#define _2DSPRITENODE_H_
#include "cocos2d.h"
#include "ZFUniformManager.h"
#include "ZFPrimitive.h"


namespace ZhiFa
{

	class ShaderNode2D : public cocos2d::Node
	{
	public:
		virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
		virtual void drawTemplate(const cocos2d::Mat4& transform, uint32_t flags);
		virtual void onDraw(cocos2d::GLProgram *v_glp) = 0;
		virtual void beginDraw();
		void initGeometry();
	protected:
		ShaderNode2D();
		virtual ~ShaderNode2D();
		bool initShaderProgram(std::string v_vertPath, std::string v_fragPath);
		bool initShaderProgramByData(const char *v_vert, const char *v_frag);
		bool initShaderProgram(cocos2d::GLProgram *v_compiledGlp);
		virtual bool init();
		virtual void addUniformToManager() = 0;
		virtual void genBuffers();
		//virtual void genLocs()=0;
		virtual void onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp) = 0;
        virtual void genAttributeLoc(cocos2d::GLProgram *v_glp)=0;
		virtual void bindVertexLayout(cocos2d::GLProgram *v_glp) = 0;
		void subUpdateVertexBuffer(cocos2d::GLProgram *v_glp);
		GLuint m_VAO, m_VBO, m_EBO;
		bool m_vertexChanged;
		ShaderUniformManager *m_uniformManager;
		GLManageredUniformMat4 *m_mvpMatrix;
		cocos2d::CustomCommand m_renderCommand;
	};
};




#endif