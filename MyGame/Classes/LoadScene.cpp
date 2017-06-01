#include "LoadScene.h"
#include "StartGame.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

LoadScene::LoadScene()
{
	log("---Loading-Start---");
}


LoadScene::~LoadScene()
{
	log("---Loading-Over---");
}
Scene * LoadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
}
bool LoadScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	NumberOfLoadedResource = 0;
	Size size = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("loading.png");
	background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(background);
	schedule(schedule_selector(LoadScene::logic));
	return true;
}
void LoadScene::logic(float dt)
{
	if (NumberOfLoadedResource==0)
	{
		loadSouce();
	}
	if (NumberOfLoadedResource==2)
	{
		auto s = StartGame::createScene();
		Director::getInstance()->replaceScene(s);
	}
}
void LoadScene::loadSouce()
{
	//加载资源
	//加载音效资源
	auto sound = SimpleAudioEngine::getInstance();
	sound->preloadBackgroundMusic("savage_music_theme.wav");
	sound->preloadEffect("GUITransitionClose.wav");
	sound->preloadEffect("GUITransitionOpen.wav");
	sound->preloadBackgroundMusic("Map_Theme_1.wav");
	sound->preloadBackgroundMusic("savage_music_jungle_battle.wav");
	sound->preloadEffect("Sound_VictoryCheer.wav");
	sound->preloadEffect("Sound_WinStars.wav");
	
	NumberOfLoadedResource++;
	//加载图片资源
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
	NumberOfLoadedResource++;
}
