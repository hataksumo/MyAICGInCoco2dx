#include "MyRipple.h"
using namespace ZhiFa;
using namespace cocos2d;

MyRipple::MyRipple() :
m_backDpInx(0),
m_curDpIdx(1),
m_rippleStrength(8.0f),
m_time(0)
{

}
MyRipple::~MyRipple()
{

}
MyRipple* MyRipple::create(std::string v_path)
{
    Texture2D *tex = Director::getInstance()->getTextureCache()->addImage(v_path);
	return create(tex);
}

MyRipple* MyRipple::create(Texture2D *v_tex)
{
    MyRipple *rtn = new MyRipple();
    if (rtn&&rtn->init(v_tex))
    {
        rtn->autorelease();
        return rtn;
    }
    CC_SAFE_DELETE(rtn);
    return NULL;
}
MyRipple* MyRipple::create(SpriteFrame *v_spf)
{
    Texture2D *tex = v_spf->getTexture();
    return create(tex);
}

bool MyRipple::init(Texture2D *v_tex)
{
    if(!GridSprite::init(v_tex))
        return false;
    scheduleUpdate();
    return true;
}

//ÕÊº“¥•√˛ ±µƒ ¬º˛
void MyRipple::doTouch(const cocos2d::Vec2 &touchPoint, float depth, float r)
{
	Vec2 nodePos = convertToNodeSpace(touchPoint);
	Size contentSize = getContentSize();
	//检测是否超出范围
	if (nodePos.x < 0 || nodePos.x > contentSize.width ||
		nodePos.y <0 || nodePos.y > contentSize.height)
		return;

	float xmin = nodePos.x - r;
	float xmax = nodePos.x + r;
	float ymin = nodePos.y - r;
	float ymax = nodePos.y + r;

	int imin, imax, jmin, jmax;
	int nRow = m_rows + 2;
	int nCol = m_cols + 2;

	jmin = MAX(1, floorf(ymin / m_gridLen) + 1);
	jmax = MIN(nRow - 2, ceilf(ymax / m_gridLen) + 1);
	imin = MAX(1, floorf(xmin / m_gridLen) + 1);
	imax = MIN(nCol - 2, ceilf(xmax / m_gridLen) + 1);

	for (int j = jmin; j <= jmax; j++)
	{
		for (int i = imin; i <= imax; i++)
		{
			Vec2 &v = m_vertexes[(j-1) * m_cols + (i-1)].Pos;
			v.y = contentSize.height - v.y;
			float dis = v.distance(nodePos);
			if (dis <= r)
			{
				float curDepth = depth*(0.5 + 0.5*cosf(dis*M_PI / r));
				m_dp[m_backDpInx][i][j] -= curDepth;
			}
		}
	}
}

void MyRipple::updateOnce()
{
	float k = 0.5f - 0.5f / m_rippleStrength;
	float kTexCoord = 1.0f / 1048.0f;
	for (int j = 1; j <= m_rows; j++)
	{
		for (int i = 1; i <= m_cols; i++)
		{
			float Hup_src = m_dp[m_backDpInx][i][j+1];
			float Hdn_src = m_dp[m_backDpInx][i][j-1];
			float Hleft_src = m_dp[m_backDpInx][i-1][j];
			float Hright_src = m_dp[m_backDpInx][i+1][j];
			float Hcenter_dst = m_dp[m_curDpIdx][i][j];
			float H = (Hup_src + Hdn_src + Hleft_src + Hright_src - 2 * Hcenter_dst)*k;
			m_dp[m_curDpIdx][i][j] = H;
			float t_offset = (Hup_src - Hdn_src)*kTexCoord;
			float s_offset = (Hleft_src - Hright_src)*kTexCoord;

			int idx = (j - 1) * m_cols + (i - 1);
			Vec2 storeTexCoord = m_vertexes[idx].TexCoord;
			m_pertubedVertexes[idx].TexCoord.setPoint(storeTexCoord.x + s_offset, storeTexCoord.y + t_offset);
		}
	}
	int tmp = m_curDpIdx;
	m_curDpIdx = m_backDpInx;
	m_backDpInx = tmp;

	m_vertexChanged = true;
}
//÷ÿ‘ÿ≥ı ºªØ∂•µ„∫Ø ˝
void MyRipple::initVertex()
{
    GridSprite::initVertex();
	m_pertubedVertexes.resize(m_vertexes.size());
	for (int j = 0; j < m_rows; j++)
	{
		for (int i = 0; i < m_cols; i++)
		{
			int idx = j * m_cols + i;;
			m_pertubedVertexes[idx].Pos = m_vertexes[idx].Pos;
		}
	}
	m_dp[0].resize(m_cols + 2);
	m_dp[1].resize(m_cols + 2);
	for (int i = 0; i < m_cols + 2; i++)
	{
		m_dp[0][i].resize(m_rows + 2,0);
		m_dp[1][i].resize(m_rows + 2,0);
	}
	m_backDpInx = 0;
	m_curDpIdx = 1;
    updateOnce();
	m_needInitVertex = false;
}
//÷ÿ‘ÿÃ·Ωª∂•µ„∫Ø ˝
void MyRipple::onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp)
{
	if (m_needInitVertex)
	{
		initVertex();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* m_indexes.size(), m_indexes.data(), GL_STATIC_DRAW);
	}	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Position2TexCoord2)* m_pertubedVertexes.size(), m_pertubedVertexes.data(), GL_DYNAMIC_DRAW);
}

void MyRipple::update(float dt)
{
	GridSprite::update(dt);
	m_time += dt;
	if (m_time > 1 / 45.0f)
	{
		updateOnce();
		m_time = 0;
	}
}

void MyRipple::setRippleStrenth(float v_rippleStrenth)
{
    m_rippleStrength = v_rippleStrenth;
}

void MyRipple::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
{
    GridSprite::setAnchorPoint(anchorPoint);
    m_needInitVertex = true;
    m_vertexChanged = true;
}
void MyRipple::setContentSize(const cocos2d::Size& size)
{
    GridSprite::setContentSize(size);
    m_needInitVertex = true;
    m_vertexChanged = true;
}
