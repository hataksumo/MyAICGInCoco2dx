#ifndef _GRIDSPRITE_H_
#define _GRIDSPRITE_H_

#include "../ShaderHelper/2dShaderNode.h"

namespace ZhiFa
{
	class GridSprite : public ShaderNode2D
	{
	public:
		GridSprite();
		virtual ~GridSprite();
		static GridSprite* create(cocos2d::Texture2D *v_tex);
        virtual void setContentSize(const cocos2d::Size& contentSize)override;
        virtual void setAnchorPoint(const cocos2d::Vec2& anchorPoint)override;
		void setGridLen(float v_gridLen);
	protected:
		bool init(cocos2d::Texture2D *v_tex);
		virtual void onDraw(cocos2d::GLProgram *v_glp)override;
		virtual void onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp)override;
        virtual void genAttributeLoc(cocos2d::GLProgram *v_glp)override;
		virtual void bindVertexLayout(cocos2d::GLProgram *v_glp)override;
		virtual void addUniformToManager()override;
		//初始化顶点
		virtual void initVertex();
		cocos2d::Texture2D *m_tex;
		int m_cols, m_rows;
		float m_gridLen;
		//顶点是否需要初始化
		bool m_needInitVertex;
		int m_vertexCount, m_indexCount;
		std::vector<GLushort> m_indexes;
		std::vector<Position2TexCoord2> m_vertexes;
		GLint m_positionLoc, m_texCoordLoc;
	};
};




#endif