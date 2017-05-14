#include "LoadScene.h"
#include "StartGame.h"


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
	//������Դ
	//������Ч��Դ
	NumberOfLoadedResource++;
	//����ͼƬ��Դ
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
	NumberOfLoadedResource++;
}
