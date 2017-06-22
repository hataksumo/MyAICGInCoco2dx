#include "2dShaderSprite.h"

using namespace cocos2d;
using namespace ZhiFa;

ShaderSprite2d::ShaderSprite2d():
m_firstInit(true),
m_vertexNeedChange(true)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertColor[i].set(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	setAnchorPoint(Vec2(0.5, 0.5));
}
ShaderSprite2d::~ShaderSprite2d()
{

}

bool ShaderSprite2d::initWithFragmentShader(std::string v_fragShaderPath)
{
	auto fileUtiles = FileUtils::getInstance();
	auto fragmentFilePath = fileUtiles->fullPathForFilename(v_fragShaderPath);
	auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);
	return initShaderProgramByData(ccPositionTextureColor_vert, fragSource.c_str());
}
bool ShaderSprite2d::init(Texture2D *v_tex)
{
	Node::init();
	m_tex = v_tex;
	setContentSize(m_tex->getContentSize());
	return true;
}
void ShaderSprite2d::onDraw(GLProgram *v_glp)
{
	GL::bindTexture2D(m_tex->getName());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, VertexOffset(GLushort, 0));
	GL::bindTexture2D(0);
	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

struct Vertex
{
	Vec2 Pos;
	Vec4 Color;
	Vec2 TexCoord;
};

void ShaderSprite2d::onSubUpdateVertexBuffer(GLProgram *v_glp)
{
	if (m_firstInit)
	{
		GLushort index[] = { 0, 1, 2, 0, 2, 3 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* 6, index, GL_STATIC_DRAW);
		m_firstInit = false;
	}
	if (m_vertexChanged)
	{
		Size contentSize = getContentSize();
		Vertex vertexes[] = {
			{ Vec2(0, 0), m_vertColor[0],Vec2(0,1) },
			{ Vec2(contentSize.width, 0), m_vertColor[1], Vec2(1, 1) },
			{ Vec2(contentSize.width, contentSize.height), m_vertColor[2], Vec2(1, 0) },
			{ Vec2(0, contentSize.height), m_vertColor[3], Vec2(0, 0) }
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
		m_vertexChanged = false;
	}
}
void ShaderSprite2d::genAttributeLoc(GLProgram *v_glp)
{
	m_posLoc = v_glp->getAttribLocation("a_position");
	m_colorLoc = v_glp->getAttribLocation("a_color");
	m_texLoc = v_glp->getAttribLocation("a_texCoord");
}
void ShaderSprite2d::bindVertexLayout(cocos2d::GLProgram *v_glp)
{
	glEnableVertexAttribArray(m_posLoc);
	glVertexAttribPointer(m_posLoc, 2, GL_FLOAT, true, sizeof(Vertex), VertexOffset(GLfloat, 0));
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, true, sizeof(Vertex), VertexOffset(GLfloat, 2));
	glEnableVertexAttribArray(m_texLoc);
	glVertexAttribPointer(m_texLoc, 2, GL_FLOAT, true, sizeof(Vertex), VertexOffset(GLfloat, 6));
}

void ShaderSprite2d::setContentSize(const Size& v_size)
{
	Node::setContentSize(v_size);
	m_vertexChanged = true;
}

void ShaderSprite2d::loadTexture(cocos2d::Texture2D *v_tex)
{
	m_tex = v_tex;
	setContentSize(m_tex->getContentSize());
}

void ShaderSprite2d::beginDraw()
{
	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}