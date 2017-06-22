#include "MySprite.h"
using namespace cocos2d;
using namespace ZhiFa;

MySprite::MySprite()
{
	setAnchorPoint(Vec2(0.5, 0.5));
}

MySprite::~MySprite()
{

}

MySprite* MySprite::create(std::string v_fpath)
{
	MySprite *rtn = new MySprite();
	Texture2D *tex = Director::getInstance()->getTextureCache()->addImage(v_fpath);
	if (rtn&&tex&&rtn->init(tex))
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

bool MySprite::init(Texture2D *v_tex)
{
	ShaderSprite2d::init(v_tex);
	initWithFragmentShader("shaders/Glow.fsh");
	return true;
}

void MySprite::addUniformToManager()
{
	m_uTextColor = m_uniformManager->addUniformVec4("u_textColor");
	m_uEffectColor = m_uniformManager->addUniformVec4("u_effectColor");
}

void MySprite::setTextColor(cocos2d::Vec4 v_color)
{
	m_uTextColor->setData(v_color);
}
void MySprite::setEffectColor(cocos2d::Vec4 v_color)
{
	m_uEffectColor->setData(v_color);
}