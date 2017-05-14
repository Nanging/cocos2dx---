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
	//������
	auto player = Player::getInstance();


	size = Director::getInstance()->getVisibleSize();
	//��ӱ���ͼƬ
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("frame.plist");
	auto background = Sprite::create("mainmenu_bg.png");
	background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(background, -1);
	//���logo
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
	removeBotton(startBottomOne);
	removeBotton(startBottomTwo);

	//��ʼ��Ϸ��
	startBottomOne = Sprite::create("start_botton_normal.png");
	startBottomTwo = Sprite::create("start_botton_seleted.png");
	auto moveby = MoveBy::create(0.5, Vec2(0, -2 * startBottomOne->getContentSize().height / 3));
	startBottomOne->setPosition(Vec2(size.width / 2, size.height - logo->getContentSize().height / 2));
	this->addChild(startBottomOne, 0);
	this->addChild(startBottomTwo, 0);
	startBottomOne->runAction(moveby);
	//��ʼ��Ϸ���ĵ��Ч������
	auto Startlistener = EventListenerTouchOneByOne::create();
	Startlistener->onTouchBegan = [=](Touch *t, Event *e) {
		Point p = t->getLocation();
		//Rect r = Rect(370, 190, 220, 100);
		//if (r.containsPoint(p)&&StartBottomOne->getNumberOfRunningActions()==0)
		//{
		//	StartBottomTwo->setPosition(StartBottomOne->getPosition());
		//	return true;
		//}
		if (startBottomOne->getBoundingBox().containsPoint(p)&& startBottomOne->getNumberOfRunningActions()==0)
		{
			startBottomTwo->setPosition(startBottomOne->getPosition());
			return true;
		}
		return false;
	};
	Startlistener->onTouchEnded = [=](Touch *t, Event *e)
	{
		
		auto removeby = MoveBy::create(0.5, Vec2(0, 2 * startBottomOne->getContentSize().height / 3));
		startBottomOne->runAction(removeby->clone());
		startBottomTwo->runAction(removeby->clone());
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
		log("---Game-Start---");
		unschedule(schedule_selector(StartGame::start));
		//closeSaveMenu();
	}
}
void StartGame::setSaveMenuVisible()
{
	for (int i = 0; i <= 4; i++)
	{
		auto child = this->getChildByTag(i);
		if (child !=nullptr)
		{
			this->removeChildByTag(i);
		}
	}
	//���ò˵�����
	auto saceMenuBg = Sprite::create("mainmenu_saveslot_bg.png");
	saceMenuBg->setPosition(Vec2(size.width / 2, size.height / 2 - 0.95 * logo->getContentSize().height / 3 - 500));
	auto moveby = MoveBy::create(0.5,Vec2(0, 500));
	this->addChild(saceMenuBg,1,0);
	saceMenuBg->runAction(moveby);

	for (int i = 1;i<=3;i++)
	{
		auto saveslot = SlotMenu::createMenu(i);
		saveslot->setPosition(Vec2(size.width * (6.4+4.1*i)/ 15 - saceMenuBg->getContentSize().width / 2 , size.height / 2 - logo->getContentSize().height / 3-500));
		saveslot->runAction(moveby->clone());
		this->addChild(saveslot, 6, i);
	}
	auto closeSaveslot = MenuItemImage::create("close_saveslot.png", "close_saveslot.png", CC_CALLBACK_0(StartGame::closeSaveMenu, this));
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
	//if (botton->getNumberOfRunningActions()==0)
	//{
	//	this->removeChild(botton);
	//}
}