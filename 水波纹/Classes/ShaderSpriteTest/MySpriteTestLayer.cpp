#include "MySpriteTestLayer.h"
#include "MySprite.h"
using namespace cocos2d;
using namespace ZhiFa;

MySpriteTestLayer::MySpriteTestLayer()
{

}
MySpriteTestLayer::~MySpriteTestLayer()
{

}
MySpriteTestLayer* MySpriteTestLayer::create()
{
	MySpriteTestLayer *rtn = new MySpriteTestLayer();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}
cocos2d::Scene* MySpriteTestLayer::scene()
{
	Scene *scene = Scene::create();
	MySpriteTestLayer* pLayer = MySpriteTestLayer::create();
	scene->addChild(pLayer);
	return scene;
}
bool MySpriteTestLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	MySprite *sp = MySprite::create("shuidi.png");
	sp->setPosition(winSize / 2.0f);
	sp->setEffectColor(Vec4(192, 255, 32,255) / 255.0f);
	sp->setTextColor(Vec4(1.0, 1.0, 1.0, 1.0));
	addChild(sp);
	return true;
}