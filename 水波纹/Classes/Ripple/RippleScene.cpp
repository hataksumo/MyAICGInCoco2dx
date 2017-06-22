#include "RippleScene.h"
#include "GridSprite.h"
#include "MyRipple.h"
using namespace cocos2d;
using namespace ZhiFa;

RippleScene::RippleScene()
{

}
RippleScene::~RippleScene()
{

}
RippleScene* RippleScene::create()
{
	RippleScene *rtn = new RippleScene();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}
Scene* RippleScene::createScene()
{
	Scene *pscene = Scene::create();
	RippleScene *layer = RippleScene::create();
	pscene->addChild(layer);
	return pscene;
}
bool RippleScene::init()
{
	if (!Node::init())
		return false;
	auto director = Director::getInstance();
	//Texture2D *tex = director->getTextureCache()->addImage("frozen.png");
	m_ripple = MyRipple::create("frozen.png");
	Size winSize = director->getVisibleSize();
	m_ripple->setPosition(winSize / 2.0f);
	m_ripple->setGridLen(8.0f);
	//m_ripple->initGeometry();
	m_ripple->setLocalZOrder(1);
	addChild(m_ripple);


    //适配
    Size contentSize = m_ripple->getContentSize();
    float heightRadio = winSize.width / contentSize.width;
    float widthRadio = winSize.height / contentSize.height;
    float scale = MIN(heightRadio,widthRadio);
    m_ripple->setScale(scale);


    
    
	auto listener = EventListenerTouchOneByOne::create();
	auto eventDispach = director->getEventDispatcher();
	
	listener->onTouchBegan = [=] (Touch* touch, Event* event)
	{
		m_ripple->doTouch(touch->getLocation(),512 ,12 );
		return true;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		m_ripple->doTouch(touch->getLocation(), 512, 12);
	};

	eventDispach->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void RippleScene::update(float v_dt)
{
	Layer::update(v_dt);
	//m_ripple->updateOnce();
}

void RippleScene::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}