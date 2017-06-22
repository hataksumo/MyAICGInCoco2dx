#include "BlurSpriteScene.h"
#include "BlurSprite.h"
#include "MySprite.h"
using namespace cocos2d;
using namespace ZhiFa;


BlurSpriteScene::BlurSpriteScene()
{

}
BlurSpriteScene::~BlurSpriteScene()
{

}
BlurSpriteScene* BlurSpriteScene::create()
{
	BlurSpriteScene *rtn = new BlurSpriteScene();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

Scene* BlurSpriteScene::createScene()
{
	Scene *pscene = Scene::create();
	BlurSpriteScene *pLayer = BlurSpriteScene::create();
	pscene->addChild(pLayer);
	return pscene;
}

bool BlurSpriteScene::init()
{
	Layer::init();
	Size winsize = Director::getInstance()->getWinSize();
	BlurSprite *bsp = BlurSprite::create("paojie.jpg");
	bsp->setPosition(Vec2(winsize.width * 0.65, winsize.height * 0.5));
	//addChild(bsp);
	bsp->setBlurSize(3);

	Sprite *sp = Sprite::create("paojie.jpg");
	sp->setPosition(Vec2(winsize.width * 0.35,winsize.height * 0.5));
	//addChild(sp);

	/*Texture2D *tex = Director::getInstance()->getTextureCache()->addImage("paojie.jpg");
	Size pictureSize = tex->getContentSize();
	BlurSpriteXY *bspx = BlurSpriteXY::create(tex, BlurSpriteEnum::XBlur);
	bspx->retain();
	bspx->setBlurSize(3);
	bspx->setPosition(pictureSize / 2.0f);



	m_rttx = RenderTexture::create(pictureSize.width, pictureSize.height);
	m_rttx->beginWithClear(0.0,0.0,0.0,1.0);
	m_rttx->getSprite()->getTexture()->setAntiAliasTexParameters();
	bspx->visit();
	m_rttx->end();
	m_rttx->retain();


	BlurSpriteXY *bspy = BlurSpriteXY::create(m_rttx->getSprite()->getTexture(), BlurSpriteEnum::YBlur);
	bspy->retain();
	bspy->setBlurSize(3);
	bspy->setPosition(pictureSize / 2.0f);

	m_rtty = RenderTexture::create(pictureSize.width, pictureSize.height);
	m_rtty->beginWithClear(0.0, 0.0, 0.0, 1.0);
	bspy->visit();
	m_rtty->end();
	m_rtty->retain();

	Sprite *blurSprite = Sprite::createWithTexture(m_rtty->getSprite()->getTexture());
	blurSprite->setPosition(Vec2(winsize.width * 0.5, winsize.height * 0.5));
	addChild(blurSprite);*/
	FileUtils *cfu = FileUtils::getInstance();
	auto fragmentFilePath = cfu->fullPathForFilename("shaders/filteBackColor.fsh");
	auto fragSource = cfu->getStringFromFile(fragmentFilePath);
	log(fragSource.data());
	GLProgram *glp = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	Sprite *spp = Sprite::create("dust.png");
	spp->setGLProgram(glp);
	spp->setPosition(winsize / 2.0f);
	addChild(spp);

	Sprite *bg = Sprite::create("frozen.png");
	bg->setPosition(winsize / 2.0f);
	addChild(bg, -1);

	//Renderer
	return true;
}
