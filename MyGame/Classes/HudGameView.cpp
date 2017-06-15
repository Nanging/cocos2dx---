#include "HudGameView.h"
#include "Player.h"
#include "MainMap.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
int cnt = 0;
void HudGameView::voiceItem() {
	cnt++;
	auto sound = SimpleAudioEngine::getInstance();
	if (cnt % 2)
	{
		sound->pauseAllEffects(); sound->pauseBackgroundMusic();
	}
	else
	{
		sound->resumeAllEffects(); sound->resumeBackgroundMusic();
	}
}

void HudGameView::backToMenu() {//now the function is to EXIT ,and need modifying to BACK.
	UtilTool::resumeLayerByTag(TAG_STAGE);
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}

//Exit ask
void HudGameView::exitAsk() {
	this->removeChildByTag(2, 1);//menu_pause

								 //init 2 layer
	auto layerExitAsk = Layer::create();
	auto menuExitAsk = Menu::create();
	layerExitAsk->setPosition(Point::ZERO);
	menuExitAsk->setPosition(Point::ZERO);

	//init&set sprites
	auto spriteExitAsk = Sprite::create("png/AskFrame.png");
	spriteExitAsk->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2, (Director::getInstance()->getVisibleSize()).height / 2));
	spriteExitAsk->setScale(0.32f);
	layerExitAsk->addChild(spriteExitAsk);

	auto yesItem = MenuItemImage::create("png/yes_1.png", "png/yes_2.png", CC_CALLBACK_0(HudGameView::backToMenu, this));
	yesItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2 - 120, (Director::getInstance()->getVisibleSize()).height / 2 - 100));
	yesItem->setScale(0.8f);
	menuExitAsk->addChild(yesItem);

	auto noItem = MenuItemImage::create("png/no_1.png", "png/no_2.png", CC_CALLBACK_0(HudGameView::pause, this));//此处调用pause函数来返回游戏并清除这几个layer
	noItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2 + 120, (Director::getInstance()->getVisibleSize()).height / 2 - 100));
	noItem->setAnchorPoint(Point(0.5, 0.5));
	noItem->setScale(0.5f);
	menuExitAsk->addChild(noItem);

	//DO YOU CONFIRM BACK TO THE MENU ?
	auto labelAsk = Label::createWithTTF("DO YOU CONFIRM\n      BACK TO \n THE STAGE MAP?", "fonts/Comic_Book.ttf", 40);
	labelAsk->enableOutline(Color4B::BLACK, 1);
	labelAsk->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2, (Director::getInstance()->getVisibleSize()).height / 2 + 50));
	layerExitAsk->addChild(labelAsk);

	//添加时打标签并在pause函数中删除这两个层
	this->addChild(menuExitAsk, 2, 3);
	this->addChild(layerExitAsk, 1, 4);

}

//Pause
void HudGameView::pause() {
	auto menuPause = Menu::create();
	menuPause->setPosition(Point::ZERO);

	if (!(Director::getInstance()->isPaused())) {
		//Director::getInstance()->pause();
		UtilTool::pauseLayerByTag(TAG_STAGE);
		auto pausedItem = MenuItemImage::create("png/Pausing.png", "png/Pausing.png", CC_CALLBACK_0(HudGameView::pause, this));
		pausedItem->setScale(0.8f);
		pausedItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2, (Director::getInstance()->getVisibleSize()).height / 2));
		menuPause->addChild(pausedItem, 0);

		//Back item
		auto backItem = MenuItemImage::create("png/backItem_1.png", "png/backItem_2.png", CC_CALLBACK_0(HudGameView::exitAsk, this));
		backItem->setPosition(Point(Director::getInstance()->getVisibleSize().width - 70, Director::getInstance()->getVisibleSize().height - 70));
		backItem->setScale(0.55f);
		menuPause->addChild(backItem);

		//标记2以便删除
		this->addChild(menuPause, 0, 2);
	}
	else {
		//Director::getInstance()->resume();
		UtilTool::resumeLayerByTag(TAG_STAGE);
		this->removeChildByTag(2, 1);//menuPause
		this->removeChildByTag(3, 1);//menuExitAsk
		this->removeChildByTag(4, 1);//layerExitAsk
	}
}
bool HudGameView::init() {
	if (!Layer::init()) {
		return false;
	}
	//init the hp, modify it if necessary
	presentHealth = InitialLifes;//假设生命值为10（每关都一样的话就设成定值
	presentMoney = InitialMoney;
	presentWave = 0;
	//********此处需要一个函数获取关卡信息中的波数信息，前面的hp、金钱也可以通过这种方式初始化


					   //init 3 layer to deposit sprites
	auto layerBackground = Layer::create();
	auto layerHud = Layer::create();
	auto menuButton = Menu::create();

	layerBackground->setPosition(Point::ZERO);
	layerHud->setPosition(Point::ZERO);
	menuButton->setPosition(Point::ZERO);

	//init size
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//kuangkuang
	auto spriteBottomframe = Sprite::create("png/FrameBottom.png");
	spriteBottomframe->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + 30));
	spriteBottomframe->setScale(0.515f,0.42f);
	layerHud->addChild(spriteBottomframe, -1);

	//Health\Money\Wave value Frame
	auto spriteValueframe = Sprite::create("png/ValueFrame.png");
	spriteValueframe->setPosition(Point(origin.x + 150, origin.y + visibleSize.height - 80));
	spriteValueframe->setScale(0.6f);
	layerHud->addChild(spriteValueframe);


	//Health value label
	std::string strHealth = std::to_string(presentHealth);
	health = Label::createWithTTF(strHealth, "fonts/Comic_Book.ttf", 20);
	health->setPosition(Point(origin.x + 113, origin.y + visibleSize.height - 63));
	health->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(health);

	//Money value label
	std::string strMoney = std::to_string(presentMoney);
	labelMoney = Label::createWithTTF(strMoney, "fonts/Comic_Book.ttf", 20);
	labelMoney->setPosition(Point(origin.x + 220, origin.y + visibleSize.height - 63));
	labelMoney->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(labelMoney);

	//Wave value label
	std::string strWave = std::to_string(presentWave) + "/" + std::to_string(TotalWave);
	labelWave = Label::createWithTTF(strWave, "fonts/Comic_Book.ttf", 20);
	labelWave->setPosition(Point(origin.x + 175, origin.y + visibleSize.height - 105));
	labelWave->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(labelWave);


	//Pause
	auto pauseItem = MenuItemImage::create("png/pause_2.png", "png/pause_3.png", CC_CALLBACK_0(HudGameView::pause, this));
	pauseItem->setScale(0.7f);
	pauseItem->setPosition(Point(origin.x + visibleSize.width - 52, origin.y + 35));
	menuButton->addChild(pauseItem);

	//Voice
	auto voiceItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(HudGameView::voiceItem, this), MenuItemImage::create("png/VoiceOpen.png", "png/VoiceOpen.png"), MenuItemImage::create("png/VoiceClose.png", "png/VoiceClose.png"), NULL);
	voiceItem->setPosition(Point(origin.x + 45, origin.y + 35));
	voiceItem->setScale(0.6f);
	menuButton->addChild(voiceItem);


	this->addChild(menuButton, 1);
	this->addChild(layerHud, 0);
	this->addChild(layerBackground, -1);
	scheduleUpdate();
	//  注释掉测试
	return true;

}

void HudGameView::update(float delta)
{
	auto player = Player::getInstance();
	//healthMinus();
	presentWave = player->current.currentWave;
	presentHealth = player->current.life;
	presentMoney = player->current.money;
	//Health value label
	std::string strHealth = std::to_string(presentHealth);
	health->setString(strHealth.c_str());


	//Money value label
	std::string strMoney = std::to_string(presentMoney);
	labelMoney->setString(strMoney.c_str());


	//Wave value label
	std::string strWave = std::to_string(presentWave) + "/" + std::to_string(TotalWave);
	labelWave->setString(strWave.c_str());
}
