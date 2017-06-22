#ifndef _MYSPRITETESTLAYER_h_
#define _MYSPRITETESTLAYER_h_
#include "cocos2d.h"
class MySpriteTestLayer : public cocos2d::Layer 
{
public:
	MySpriteTestLayer();
	~MySpriteTestLayer();
	static MySpriteTestLayer* create();
	static cocos2d::Scene* scene();
protected:
	bool init();
};

#endif