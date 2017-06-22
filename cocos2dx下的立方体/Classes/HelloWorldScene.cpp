#include "HelloWorldScene.h"
#include "Curb.h"
#include "Curb1.h"
#include "Curb2.h"
#include "CustomRenderCommandTest.h"
#include "triangles.h"
#include "ColoredTriangles.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static std::string fruits[] = { "fig", "grape", "mango", "pear", "pomegranate", "strawberry" };
static std::string fruitRoot = "fruits";
std::string getFruitPath(int i)
{
	return fruitRoot + "/" + fruits[i] + ".png";
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {

        return false;
    }
	Size winSize = Director::getInstance()->getWinSize();
	Curb2 *primative = Curb2::create();
	addChild(primative);
	primative->setShader("shaders/curb2.vsh", "shaders/curb2.fsh");
	primative->generateBufferObject();
	primative->bindVertexArray();
	primative->bindUniforms();
	primative->setTexture("HelloWorld.png");
	primative->iniLight();
	primative->setLocalZOrder(1);
	//primative->setTexture("Fire001.bmp");

	/*for (int i = 0; i < 10000; i++)
	{
		Sprite *fruit = Sprite::create(getFruitPath(i%2));
		addChild(fruit);
		fruit->setNormalizedPosition(Vec2(rand() % 10000 / 10000.0f, rand() % 10000 / 10000.0f));
	}*/
	/*for (int i = 0; i < 10000; i++)
	{
		Sprite *fruit = Sprite::create(getFruitPath(3));
		addChild(fruit);
		fruit->setNormalizedPosition(Vec2(rand() % 10000 / 10000.0f, rand() % 10000 / 10000.0f));
		fruit->setLocalZOrder(i % 2);
	}*/
	/*for (int i = 0; i < 5000; i++)
	{
		Sprite *fruit = Sprite::create(getFruitPath(2));
		addChild(fruit);
		fruit->setNormalizedPosition(Vec2(rand() % 10000 / 10000.0f, rand() % 10000 / 10000.0f));
		fruit->setZOrder(i % 2);
	}*/

	/*CustomRenderCommandTest *cct = CustomRenderCommandTest::create();
	addChild(cct);*/

	/*Curb *primative = Curb::create();
	primative->setShader("shaders/vertexShader.vsh","shaders/pixelShader.fsh");
	primative->generateBufferObject();
	addChild(primative);*/
	/*TwoTrangle *towTriangle = TwoTrangle::create();
	addChild(towTriangle);*/
	/*ColoredTrangle *ct = ColoredTrangle::create();
	addChild(ct);*/


	/*Curb1 *primative = Curb1::create();
	addChild(primative);
	primative->setShader("shaders/curb1.vsh", "shaders/curb1.fsh");
	primative->generateBufferObject();
	primative->bindVertexArray();
	primative->bindUniforms();
	primative->setTexture("HelloWorld.png");
	primative->setLocalZOrder(1);*/


	Sprite *sp = Sprite::create("HelloWorld.png");
	sp->setNormalizedPosition(Vec2(0.5, 0.5));
	sp->setScale(2.0f);
	sp->setScale(0.1f);
	addChild(sp, -1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
