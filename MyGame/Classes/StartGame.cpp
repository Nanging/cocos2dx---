#include "StartGame.h"
#include "SlotMenu.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
StartGame::StartGame()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("wav/savage_music_theme.wav", true);
}


StartGame::~StartGame()
{
}


bool StartGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//获得玩家
	auto player = Player::getInstance();
	size = Director::getInstance()->getVisibleSize();
	//添加背景图片
	auto background = Sprite::create("png/mainmenu_bg.png");
	background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(background, -1);
	//添加logo
	logo = Sprite::create("png/logo.png");
	logo->setPosition(Vec2(size.width / 2, size.height - logo->getContentSize().height/2));
	this->addChild(logo,10);
	initStart();
	return true;
}
void StartGame::initStart()
{
	auto player = Player::getInstance();
	player-> setStarted(false);
	removeBotton(startBottomOne);
	removeBotton(startBottomTwo);

	//开始游戏键
	startBottomOne = Sprite::create("png/start_botton_normal.png");
	startBottomTwo = Sprite::create("png/start_botton_seleted.png");
	auto moveby = MoveBy::create(0.5, Vec2(0, -2 * startBottomOne->getContentSize().height / 3));
	startBottomOne->setPosition(Vec2(size.width / 2, size.height - logo->getContentSize().height / 2));
	this->addChild(startBottomOne, 0);
	this->addChild(startBottomTwo, 0);
	startBottomOne->runAction(moveby);
	//开始游戏键的点击效果设置
	auto Startlistener = EventListenerTouchOneByOne::create();
	Startlistener->onTouchBegan = [=](Touch *t, Event *e) {
		Point p = t->getLocation();
		if (startBottomOne->getBoundingBox().containsPoint(p)&& startBottomOne->getNumberOfRunningActions()==0)
		{
			startBottomTwo->setPosition(startBottomOne->getPosition());
			return true;
		}
		return false;
	};
	Startlistener->onTouchEnded = [=](Touch *t, Event *e)
	{
		
		auto removeby = MoveBy::create(0.5, Vec2(0, 1.5 * startBottomOne->getContentSize().height / 3));
		startBottomOne->runAction(removeby->clone());
		startBottomTwo->runAction(removeby->clone());
		_eventDispatcher->removeEventListener(Startlistener);
		setSaveMenuVisible();
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Startlistener, this);
}
Scene *StartGame::createScene()
{
	auto scene = Scene::create();
	auto layer = StartGame::create();
	scene->setTag(TAG_SCENE);
	scene->addChild(layer,0,TAG_START);
	return scene;
}
void StartGame::start(float dt)
{
	auto player = Player::getInstance();
	if (player->getStarted())
	{
		unschedule(schedule_selector(StartGame::start));
	}
}
void StartGame::setSaveMenuVisible()
{
	auto player = Player::getInstance();
	for (int i = 0; i <= 4; i++)
	{
		auto child = this->getChildByTag(i);
		if (child !=nullptr)
		{
			this->removeChildByTag(i);
		}
	}
	//设置菜单背景
	auto saceMenuBg = Sprite::create("png/mainmenu_saveslot_bg.png");
	saceMenuBg->setPosition(Vec2(size.width / 2, size.height / 2 - 0.95 * logo->getContentSize().height / 3 - 500));
	auto moveby = MoveBy::create(0.5,Vec2(0, 500));
	this->addChild(saceMenuBg,1,0);
	saceMenuBg->runAction(moveby);

	for (int i = 1;i<=3;i++)
	{
		auto saveslot = SlotMenu::createMenu(i);
		saveslot->setPosition(Vec2(size.width * (6.4+4.1*i)/ 15 - saceMenuBg->getContentSize().width / 2 , size.height / 2 - logo->getContentSize().height / 3-500));
		saveslot->runAction(moveby->clone());
		this->addChild(saveslot, 10-i, i);
	}
	auto closeSaveslot = MenuItemImage::create("png/close_saveslot.png", "png/close_saveslot.png", CC_CALLBACK_0(StartGame::closeSaveMenu, this));
	auto closeBotton = Menu::createWithItem(closeSaveslot);
	closeBotton->setPosition(Vec2(size.width / 2, size.height / 2 - 1.7*saceMenuBg->getContentSize().height / 2  - 500));
	this->addChild(closeBotton, 6, 4);
	closeBotton->runAction(moveby->clone());
	schedule(schedule_selector(StartGame::start));
}
void StartGame::closeSaveMenu()
{
	auto removeby = MoveBy::create(0.5, Vec2(0, -500));
	for (int i = 0;i<=4;i++)
	{
		auto child = this->getChildByTag(i);
		child->runAction(removeby->clone());
	}
	initStart();
}
void StartGame::removeBotton(Sprite * botton)
{
	if (botton==nullptr)
	{
		return;
	}
	this->removeChild(botton);
}