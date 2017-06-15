#include "LoadScene.h"
#include "StartGame.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
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
	auto background = Sprite::create("png/loading.png");
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
	sound->preloadBackgroundMusic("wav/savage_music_theme.wav");
	sound->preloadEffect("wav/GUITransitionClose.wav");
	sound->preloadEffect("wav/GUITransitionOpen.wav");
	sound->preloadBackgroundMusic("wav/Map_Theme_1.wav");
	sound->preloadBackgroundMusic("wav/savage_music_jungle_battle.wav");
	sound->preloadEffect("wav/Sound_VictoryCheer.wav");
	sound->preloadEffect("wav/Sound_WinStars.wav");
	sound->preloadEffect("wav/Sound_TowerSell.wav");
	sound->preloadEffect("wav/Sound_TowerBuilding.wav");
	sound->preloadEffect("wav/Sound_TowerUpgrade.wav");
	sound->preloadEffect("wav/Sound_ArrowHit2.wav");
	sound->preloadEffect("wav/Sound_Bomb1.wav");
	sound->preloadEffect("wav/magic_attack.wav");
	sound->preloadEffect("wav/Archer_Ready.wav");
	sound->preloadEffect("wav/ac_Ready.wav");
	sound->preloadEffect("wav/Mage_Ready.wav");
	sound->preloadEffect("wav/inapp_cash.wav");
	sound->preloadEffect("wav/Sound_LooseLife.wav");
	sound->preloadEffect("wav/Sound_NextWaveReady.wav");
	sound->preloadEffect("wav/Sound_WaveIncoming.wav");
	sound->preloadEffect("wav/boss_efreeti_evillaugh.wav");
	sound->preloadEffect("wav/boss_efreeti_death.wav");
	sound->preloadEffect("wav/inapp_star.wav");
	NumberOfLoadedResource++;
	//加载图片资源
	auto sprite = SpriteFrameCache::getInstance();
	sprite->addSpriteFramesWithFile("png/enemies_jungle-hd.plist", "png/enemies_jungle-hd.png");
	sprite->addSpriteFramesWithFile("png/enemies_desert_3-hd.plist", "png/enemies_desert_3-hd.png");
	sprite->addSpriteFramesWithFile("png/sprite_level10-hd.plist", "png/sprite_level10-hd.png");
	sprite->addSpriteFramesWithFile("png/enemies_desert-hd.plist", "png/enemies_desert-hd.png");
	auto player = Player::getInstance();
	NumberOfLoadedResource++;
}
