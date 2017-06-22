#include "GridSprite.h"
using namespace ZhiFa;
using namespace cocos2d;

GridSprite::GridSprite():
m_rows(1),
m_cols(1),
m_needInitVertex(true),
m_positionLoc(-1),
m_texCoordLoc(-1)
{
    setAnchorPoint(Vec2(0.5,0.5));
}
GridSprite::~GridSprite()
{

}
GridSprite* GridSprite::create(Texture2D *v_tex)
{
	GridSprite *rtn = new GridSprite();
	if (rtn&&rtn->init(v_tex))
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return rtn;
}
bool GridSprite::init(cocos2d::Texture2D *v_tex)
{
	m_tex = v_tex;
	setContentSize(v_tex->getContentSize());
	initShaderProgram("shaders/Ripple.vsh", "shaders/Ripple.fsh");
	return true;
}
void GridSprite::onDraw(cocos2d::GLProgram *v_glp)
{
    GL::bindTexture2D(m_tex->getName());
	glDrawElements(GL_TRIANGLES, (int)m_indexes.size(), GL_UNSIGNED_SHORT, 0);
	GL::bindTexture2D(0);
}
void GridSprite::onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp)
{
	if (m_needInitVertex)
	{
		initVertex();
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(Position2TexCoord2)* m_vertexes.size(), m_vertexes.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* m_indexes.size(), m_indexes.data(), GL_STATIC_DRAW);
}

void GridSprite::genAttributeLoc(cocos2d::GLProgram *v_glp)
{
    m_texCoordLoc = v_glp->getAttribLocation("b_texCord");
    m_positionLoc = v_glp->getAttribLocation("b_position");
}

void GridSprite::bindVertexLayout(cocos2d::GLProgram *v_glp)
{
	glEnableVertexAttribArray(m_positionLoc);
    glEnableVertexAttribArray(m_texCoordLoc);
	glVertexAttribPointer(m_positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Position2TexCoord2), VertexOffset(float,0));
	glVertexAttribPointer(m_texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Position2TexCoord2), VertexOffset(float, 2));
}
void GridSprite::addUniformToManager()
{
    
}
//≥ı ºªØ∂•µ„
void GridSprite::initVertex()
{
	Size contentSize = getContentSize();
    Vec2 ancho = getAnchorPoint();
    Vec2 anchoOff{contentSize.width * ancho.x,contentSize.height * ancho.y};
	m_vertexCount = m_rows * m_cols;

	m_vertexes.resize(m_vertexCount);

	for (int j = 0; j < m_rows; j++)
	{
		for (int i = 0; i < m_cols; i++)
		{
			float x = m_gridLen * i;
			float y = m_gridLen * j;
			float s = x / contentSize.width;
			float t = 1 - y / contentSize.height;

			int idx = j * m_cols + i;
            m_vertexes[idx].Pos.setPoint(x, y);
			m_vertexes[idx].TexCoord.setPoint(s, t);
		}
	}
	m_indexCount = (m_rows - 1) * (m_cols - 1) * 6;
	m_indexes.clear();
	m_indexes.reserve(m_indexCount);
	for (int j = 1; j < m_rows; j++)
	{
		for (int i = 1; i < m_cols; i++)
		{
			GLushort quardIndex[] = { (GLushort)((j - 1) * m_cols + i - 1), (GLushort)((GLushort)(j - 1) * m_cols + i),
				 (GLushort)(j * m_cols + i), (GLushort)(j * m_cols + i - 1) };

			m_indexes.push_back(quardIndex[0]);
			m_indexes.push_back(quardIndex[1]);
			m_indexes.push_back(quardIndex[2]);
			m_indexes.push_back(quardIndex[0]);
			m_indexes.push_back(quardIndex[2]);
			m_indexes.push_back(quardIndex[3]);
		}
	}
	/*Size contentSize = getContentSize();
	m_vertexes.clear();
	m_vertexes.resize(4);
	m_vertexes[0].Pos = Vec2(0, 0);
	m_vertexes[1].Pos = Vec2(contentSize.width, 0);
	m_vertexes[2].Pos = Vec2(contentSize.width, contentSize.height);
	m_vertexes[3].Pos = Vec2(0, contentSize.height);
	m_vertexes[0].TexCoord = Vec2(0.0f, 1.0f);
	m_vertexes[1].TexCoord = Vec2(1.0f, 1.0f);
	m_vertexes[2].TexCoord = Vec2(1.0f, 0.0f);
	m_vertexes[3].TexCoord = Vec2(0.0f, 0.0f);
	m_indexes.clear();
	GLushort index[] = { 0, 1, 2, 0, 2, 3 };
	for (GLushort idx : index)
		m_indexes.push_back(idx);*/
}


void GridSprite::setGridLen(float v_gridLen)
{
	Size contentSize = getContentSize();
	m_gridLen = v_gridLen;
	int rows = floorf(contentSize.height / m_gridLen) + 1;
	int cols = floorf(contentSize.width / m_gridLen) + 1;
	if (rows != m_rows || cols != m_cols)
	{
		m_needInitVertex = true;
		m_vertexChanged = true;
		m_rows = rows;
		m_cols = cols;
	}
}

void GridSprite::setContentSize(const Size& contentSize)
{
    ShaderNode2D::setContentSize(contentSize);
    m_needInitVertex = true;
}

void GridSprite::setAnchorPoint(const Vec2& anchorPoint)
{
    ShaderNode2D::setAnchorPoint(anchorPoint);
    m_needInitVertex = true;
}