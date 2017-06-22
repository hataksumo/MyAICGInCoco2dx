#include "BlurSprite.h"
#include "../ShaderHelper/GameMath.h"
using namespace cocos2d;
using namespace ZhiFa;

BlurSpriteXY::BlurSpriteXY():
m_weightNeedInit(true)
{

}
BlurSpriteXY::~BlurSpriteXY()
{

}
BlurSpriteXY* BlurSpriteXY::create(Texture2D *v_tex, BlurSpriteEnum v_blurType)
{
	BlurSpriteXY *rtn = new BlurSpriteXY();
	if (rtn&&rtn->init(v_tex))
	{
		rtn->initShader(v_blurType);
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

bool BlurSpriteXY::initShader(BlurSpriteEnum v_blurType)
{
	switch (v_blurType)
	{
	case BlurSpriteEnum::XBlur:
		initWithFragmentShader("shaders/Blur_x.fsh");
		break;
	case BlurSpriteEnum::YBlur:
		initWithFragmentShader("shaders/Blur_y.fsh");
		break;
	default:
		break;
	}
	m_blurType = v_blurType;
	return true;
}
void BlurSpriteXY::setBlurSize(int v_size)
{
	m_blurSize = v_size;
	m_simga = v_size / 3.0f;
}
bool BlurSpriteXY::init(cocos2d::Texture2D *v_tex)
{
	ShaderSprite2d::init(v_tex);
	Size sizeInPixel = v_tex->getContentSizeInPixels();
	m_pixelSize.setPoint(1.0f / sizeInPixel.width, 1.0f / sizeInPixel.height);
	return true;
	
	return true;
}
void BlurSpriteXY::initWeights()
{
	m_uPixelSize->setData(m_pixelSize);
	m_uRadius->setData(m_blurSize);
	int end = m_blurSize * 2 + 1;
	m_weights.resize(end);
	const float pi = acosf(-1.0f);
	float sq2 = sqrt(2.0f * pi);
	float sqSigma2 = GameMathHelp::squre(m_simga);
	float sum = 0.0f;
	for (int i = 0; i < end; i++)
	{
		m_weights[i] = 1.0f / (m_simga * sq2) *
			exp(-GameMathHelp::squre(i - m_blurSize) / (2 * sqSigma2));
		sum += m_weights[i];
	}
	for (int i = 0; i < end; i++)
		m_weights[i] /= sum;
	GLProgram *glp = getGLProgram();
	GLint weightLoc = glp->getUniformLocation("u_weights");
	glUniform1fv(weightLoc, end, m_weights.data());
	m_weightNeedInit = false;
	//log("init weight, sum = %f, end = %d", sum, end);
}

void BlurSpriteXY::addUniformToManager()
{
	m_uPixelSize = m_uniformManager->addUniformVec2("u_pixelSize");
	m_uRadius = m_uniformManager->addUniformi("u_raduis");
	u_addFactor = m_uniformManager->addUniformVec4("u_addFactor");
	u_mulFactor = m_uniformManager->addUniformVec4("u_mulFactor");
	m_uRadius->setData(0);
	u_addFactor->setData(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
	u_mulFactor->setData(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void BlurSpriteXY::beginDraw()
{
	if (m_weightNeedInit)
		initWeights();
}

void BlurSpriteXY::setAddFactor(cocos2d::Vec4 v_addFactor)
{
	u_addFactor->setData(v_addFactor);
}
void BlurSpriteXY::setMulFactor(cocos2d::Vec4 v_mulFactor)
{
	u_mulFactor->setData(v_mulFactor);
}


BlurSprite::BlurSprite()
{

}
BlurSprite::~BlurSprite()
{
	m_xBlur->release();
	m_yBlur->release();
	m_rttX->release();
	m_rttY->release();
}

BlurSprite* BlurSprite::create(std::string v_fpath)
{
	BlurSprite *rtn = new BlurSprite();
	if (rtn&&rtn->init(v_fpath))
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

void BlurSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Size contentSize = getContentSize();

	m_xBlur->loadTexture(m_tex);
	m_xBlur->setPosition(contentSize / 2.0f);
	m_xBlur->setBlurSize(m_blurSize);
	m_rttX->beginWithClear(0.0f, 0.0f, 0.0f, 1.0f);
	m_xBlur->visit();
	m_rttX->end();	

	m_yBlur->loadTexture(m_rttX->getSprite()->getTexture());
	m_yBlur->setPosition(contentSize / 2.0f);
	m_yBlur->setBlurSize(m_blurSize);
	m_yBlur->setMulFactor(Vec4(1.1f, 1.1f, 1.1f, 1.0f));
	m_yBlur->setAddFactor(Vec4(0.1f, 0.1f, 0.1f, 0.0f));
	m_rttY->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	m_yBlur->visit();
	m_rttY->end();

	setTexture(m_rttY->getSprite()->getTexture());
	Sprite::draw(renderer, transform, flags);


}
bool BlurSprite::init(std::string v_fPath)
{
	m_tex = Director::getInstance()->getTextureCache()->addImage(v_fPath);
	initWithTexture(m_tex);
	m_xBlur = BlurSpriteXY::create(getTexture(), BlurSpriteEnum::XBlur);
	m_yBlur = BlurSpriteXY::create(getTexture(), BlurSpriteEnum::YBlur);
	m_xBlur->retain();
	m_yBlur->retain();
	m_rttX = RenderTexture::create(m_xBlur->getContentSize().width, m_xBlur->getContentSize().height);
	m_rttY = RenderTexture::create(m_yBlur->getContentSize().width, m_yBlur->getContentSize().height);
	m_rttX->retain();
	m_rttY->retain();
	return true;
}

void BlurSprite::setBlurSize(int v_blurSize)
{
	m_blurSize = v_blurSize;
}
