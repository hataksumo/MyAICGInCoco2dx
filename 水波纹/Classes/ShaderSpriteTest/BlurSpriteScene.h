#ifndef _BLURSPRITESCENE_H_
#define _BLURSPRITESCENE_H_
#include "cocos2d.h"

class BlurSpriteScene : public cocos2d::Layer
{
public:
	BlurSpriteScene();
	~BlurSpriteScene();
	static BlurSpriteScene* create();
	static cocos2d::Scene* createScene();
protected:
	bool init();
	cocos2d::RenderTexture *m_rttx,*m_rtty;
	cocos2d::Sprite *m_sp;
};



#endif