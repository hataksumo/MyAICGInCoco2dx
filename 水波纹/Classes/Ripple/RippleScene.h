#ifndef _RIPPLESCENE_H_
#define _RIPPLESCENE_H_

#include "cocos2d.h"
namespace ZhiFa
{
	class Ripple;
	class MyRipple;
	class GridSprite;
};

class RippleScene : public cocos2d::Layer
{
public:
	RippleScene();
	~RippleScene();
	static RippleScene* create();
	static cocos2d::Scene *createScene();
	void update(float v_dt)override;
	void onEnter()override;
protected:
	bool init();
	ZhiFa::MyRipple *m_ripple;
};

#endif