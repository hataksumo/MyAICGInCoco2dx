#ifndef _CUSTOMRENDERCOMMANDTEST_H_
#define _CUSTOMRENDERCOMMANDTEST_H_

#include "cocos2d.h"


class CustomRenderCommandTest : public cocos2d::Node
{
public:
	CustomRenderCommandTest();
	~CustomRenderCommandTest();
	static CustomRenderCommandTest* create();
	void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
protected:
	virtual bool init()override;
	cocos2d::CustomCommand m_renderCommand;
};


#endif