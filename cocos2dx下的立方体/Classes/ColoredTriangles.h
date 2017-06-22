#ifndef _COLOREDTRIANGLES_H_
#define _COLOREDTRIANGLES_H_
#include "cocos2d.h"

namespace ColoredTrianglePrimative
{
	struct Vertex
	{
		cocos2d::Vec2 Position;
		cocos2d::Vec4 Color;
	};
};

class ColoredTrangle : public cocos2d::Node
{
public:
	ColoredTrangle();
	~ColoredTrangle();
	static ColoredTrangle* create();
	void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	void onDraw();
protected:
	bool init();
	void initShader();
	void generateBuffers();
	void iniUniforms();
	GLuint m_VAO, m_VBO, m_EBO;
	GLint m_positionLoc,m_colorLoc;
	GLint m_vmatrixLoc, m_cmatrixLoc;
	cocos2d::Mat4 m_vmatrix, m_cmatrix;
	cocos2d::CustomCommand m_customCommand;
};

#endif