#include "CustomRenderCommandTest.h"
using namespace cocos2d;


CustomRenderCommandTest::CustomRenderCommandTest()
{

}

CustomRenderCommandTest::~CustomRenderCommandTest()
{

}

CustomRenderCommandTest* CustomRenderCommandTest::create()
{
	CustomRenderCommandTest *rtn = new CustomRenderCommandTest();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

bool CustomRenderCommandTest::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void CustomRenderCommandTest::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	m_renderCommand.init(_globalZOrder);
	m_renderCommand.func = CC_CALLBACK_0(CustomRenderCommandTest::onDraw, this, transform, _globalZOrder);
	renderer->addCommand(&m_renderCommand);
}

void CustomRenderCommandTest::onDraw(const cocos2d::Mat4& transform, uint32_t flags)
{
	glClearColor(0.1f, 0.1f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}