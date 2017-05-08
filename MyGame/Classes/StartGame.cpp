#include "StartGame.h"
#include "SlotMenu.h"
#include "Player.h"

StartGame::StartGame()
{
	log("---StartGame---");
}


StartGame::~StartGame()
{
	log("---StartGame_Delete---");
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
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("frame.plist");
	auto BackGround = Sprite::create("mainmenu_bg.png");
	BackGround->setScale(size.width / BackGround->getContentSize().width, size.height / BackGround->getContentSize().height);
	BackGround->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(BackGround, -1);
	//添加logo
	logo = Sprite::create("logo.png");
	logo->setPosition(Vec2(size.width / 2, size.height - logo->getContentSize().height/2));
	//logo->setScale(1.1f);
	this->addChild(logo,10);
	initStart();
	return true;
}
void StartGame::initStart()
{
	auto player = Player::getInstance();
	player-> setStarted(false);
	removeBotton(StartBottomOne);
	removeBotton(StartBottomTwo);

	//开始游戏键
	StartBottomOne = Sprite::create("start_botton_normal.png");
	StartBottomTwo = Sprite::create("start_botton_seleted.png");
	auto moveby = MoveBy::create(0.5, Vec2(0, -2 * StartBottomOne->getContentSize().height / 3));
	StartBottomOne->setPosition(Vec2(size.width / 2, size.height - logo->getContentSize().height / 2));
	this->addChild(StartBottomOne, 0);
	this->addChild(StartBottomTwo, 0);
	StartBottomOne->runAction(moveby);
	//开始游戏键的点击效果设置
	auto Startlistener = EventListenerTouchOneByOne::create();
	Startlistener->onTouchBegan = [=](Touch *t, Event *e) {
		Point p = t->getLocation();
		//Rect r = Rect(370, 190, 220, 100);
		//if (r.containsPoint(p)&&StartBottomOne->getNumberOfRunningActions()==0)
		//{
		//	StartBottomTwo->setPosition(StartBottomOne->getPosition());
		//	return true;
		//}
		if (StartBottomOne->getBoundingBox().containsPoint(p)&&StartBottomOne->getNumberOfRunningActions()==0)
		{
			StartBottomTwo->setPosition(StartBottomOne->getPosition());
			return true;
		}
		return false;
	};
	Startlistener->onTouchEnded = [=](Touch *t, Event *e)
	{
		
		auto Re_moveby = MoveBy::create(0.5, Vec2(0, 2 * StartBottomOne->getContentSize().height / 3));
		StartBottomOne->runAction(Re_moveby->clone());
		StartBottomTwo->runAction(Re_moveby->clone());
	//	StartBottomOne->setVisible(false);
	//	StartBottomTwo->setVisible(false);
		_eventDispatcher->removeEventListener(Startlistener);
		//this->removeChild(StartBottomOne);
		//this->removeChild(StartBottomTwo);
		setSaveMenuVisible();
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Startlistener, this);
}
Scene *StartGame::createScene()
{
	auto s = Scene::create();
	auto j = StartGame::create();
	s->setTag(TAG_SCENE);
	s->addChild(j,0,TAG_START);
	return s;
}
void StartGame::start(float dt)
{
	auto player = Player::getInstance();
	if (player->getStarted())
	{
		log("---Game-Start---");
		unschedule(schedule_selector(StartGame::start));
		//closeSaveMenu();
	}
}
void StartGame::setSaveMenuVisible()
{
	for (int i = 0; i <= 4; i++)
	{
		auto s = this->getChildByTag(i);
		if (s!=nullptr)
		{
			this->removeChildByTag(i);
		}
	}
	//设置菜单背景
	auto SaveMenu_bg = Sprite::create("mainmenu_saveslot_bg.png");
	SaveMenu_bg->setPosition(Vec2(size.width / 2, size.height / 2 - 0.95 * logo->getContentSize().height / 3 - 500));
	auto moveby = MoveBy::create(0.5,Vec2(0, 500));
	this->addChild(SaveMenu_bg,1,0);
	SaveMenu_bg->runAction(moveby);

	for (int i = 1;i<=3;i++)
	{
		auto saveslot = SlotMenu::createMenu(i);
		saveslot->setPosition(Vec2(size.width / 2 - SaveMenu_bg->getContentSize().width / 2 + 200 + (i-1)*280, size.height / 2 - logo->getContentSize().height / 3-500));
		saveslot->runAction(moveby->clone());
		this->addChild(saveslot, 6, i);
	}
	auto close_saveslot = MenuItemImage::create("close_saveslot.png", "close_saveslot.png", CC_CALLBACK_0(StartGame::closeSaveMenu, this));
	auto close_botton = Menu::createWithItem(close_saveslot);
	close_botton->setPosition(Vec2(size.width / 2, size.height / 2 - 1.7*SaveMenu_bg->getContentSize().height / 2  - 500));
	this->addChild(close_botton, 6, 4);
	close_botton->runAction(moveby->clone());
	schedule(schedule_selector(StartGame::start));
}
void StartGame::closeSaveMenu()
{
	auto removeby = MoveBy::create(0.5, Vec2(0, -500));
	for (int i = 0;i<=4;i++)
	{
		auto s = this->getChildByTag(i);
		s->runAction(removeby->clone());
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
	//if (botton->getNumberOfRunningActions()==0)
	//{
	//	this->removeChild(botton);
	//}
}