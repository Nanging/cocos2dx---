#include"HudGameView.h"
//#include"关卡.h"
USING_NS_CC;

void HudGameView::voiceItem() {

}

void HudGameView::backToMenu() {//now the function is to EXIT ,and need modifying to BACK.
	Director::getInstance()->end();
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
	auto spriteExitAsk = Sprite::create("AskFrame.png");
	spriteExitAsk->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2, (Director::getInstance()->getVisibleSize()).height / 2));
	spriteExitAsk->setScale(0.32);
	layerExitAsk->addChild(spriteExitAsk);

	auto yesItem = MenuItemImage::create("yes_1.png", "yes_2.png", CC_CALLBACK_0(HudGameView::backToMenu, this));
	yesItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2 - 120, (Director::getInstance()->getVisibleSize()).height / 2 - 100));
	yesItem->setScale(0.8);
	menuExitAsk->addChild(yesItem);

	auto noItem = MenuItemImage::create("no_1.png", "no_2.png", CC_CALLBACK_0(HudGameView::pause, this));//此处调用pause函数来返回游戏并清除这几个layer
	noItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2 + 120, (Director::getInstance()->getVisibleSize()).height / 2 - 100));
	noItem->setAnchorPoint(Point(0.5, 0.5));
	noItem->setScale(0.5);
	menuExitAsk->addChild(noItem);

	//DO YOU CONFIRM BACK TO THE MENU ?
	auto labelAsk= Label::createWithTTF("DO YOU CONFIRM\nBACK TO THE MENU ?", "fonts/Comic_Book.ttf", 40);
	labelAsk->enableOutline(Color4B::BLACK, 1);
	labelAsk->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2 , (Director::getInstance()->getVisibleSize()).height / 2+50 ));
	layerExitAsk->addChild(labelAsk);

	//添加时打标签并在pause函数中删除这两个层
	this->addChild(menuExitAsk, 2, 3);
	this->addChild(layerExitAsk, 1, 4)；

}

//Pause
void HudGameView::pause() {
	auto menuPause = Menu::create();
	menuPause->setPosition(Point::ZERO);

	if (!(Director::getInstance()->isPaused())){
		Director::getInstance()->pause();
		auto pausedItem = MenuItemImage::create("Pausing.png", "Pausing.png", CC_CALLBACK_0(HudGameView::pause, this));
		pausedItem->setScale(0.8);
		pausedItem->setPosition(Point((Director::getInstance()->getVisibleSize()).width / 2, (Director::getInstance()->getVisibleSize()).height / 2));
		menuPause->addChild(pausedItem,0);

		//Back item
		auto backItem = MenuItemImage::create("backItem_1.png", "backItem_2.png", CC_CALLBACK_0(HudGameView::exitAsk, this));
		backItem->setPosition(Point(Director::getInstance()->getVisibleSize().width - backItem->getContentSize().width, Director::getInstance()->getVisibleSize().height - backItem->getContentSize().height));
		backItem->setScale(0.55);
		menuPause->addChild(backItem);

		//标记2以便删除
		this->addChild(menuPause, 0, 2);
}
	else {
		Director::getInstance()->resume();
		this->removeChildByTag(2,1);//menuPause
		this->removeChildByTag(3, 1);//menuExitAsk
		this->removeChildByTag(4, 1);//layerExitAsk
	}
}

//return present hp, to judge if be defeated
int HudGameView::getHealth() {
	return presentHealth;
}

//when an enemy pass
void HudGameView::healthMinus() {
	presentHealth--;
}

//return present money, to judge if an operation to buy a tower is permitted
int HudGameView::getMoney() {
	return presentMoney;
}

//when an enemy is killed or a tower is removed, Money+
void HudGameView::moneyPlus(int addMoney) {
	presentMoney += addMoney;
}

//when a tower begin to be built, Money-
void HudGameView::moneyMinus(int lessenMoney) {
	presentMoney -= lessenMoney;
}

//return present wave
int HudGameView::getWave() {
	return presentWave;
}

void HudGameView::wavePlus() {
	presentWave++;
}

bool HudGameView::init() {
	if (!Layer::init()) {
		return false;
	}
	//init the hp, modify it if necessary
	presentHealth = 10;//假设生命值为10（每关都一样的话就设成定值
	presentMoney = 1000;
	presentWave = 0;
	int totalWave = 14;//********此处需要一个函数获取关卡信息中的波数信息，前面的hp、金钱也可以通过这种方式初始化


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
	auto spriteBottomframe = Sprite::create("FrameBottom.png");
	spriteBottomframe->setPosition(Point(origin.x + visibleSize.width / 2, origin.y+30));
	spriteBottomframe->setScale(0.42);
	layerHud->addChild(spriteBottomframe, -1);

	//Health\Money\Wave value Frame
	auto spriteValueframe = Sprite::create("ValueFrame.png");
	spriteValueframe->setPosition(Point(origin.x + 150, origin.y + visibleSize.height - 80));
	spriteValueframe->setScale(0.6);
	layerHud->addChild(spriteValueframe);


	//Health value label
	std::string strHealth=std::to_string(presentHealth);
	auto health = Label::createWithTTF(strHealth, "fonts/Comic_Book.ttf", 20);
	health->setPosition(Point(origin.x + 113, origin.y + visibleSize.height - 63));
	health->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(health);

	//Money value label
	std::string strMoney = std::to_string(presentMoney);
	auto labelMoney = Label::createWithTTF(strMoney, "fonts/Comic_Book.ttf", 20);
	labelMoney->setPosition(Point(origin.x + 220, origin.y + visibleSize.height - 63));
	labelMoney->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(labelMoney);

	//Wave value label
	std::string strWave = std::to_string(presentWave)+"/"+std::to_string(totalWave);
	auto labelWave = Label::createWithTTF(strWave, "fonts/Comic_Book.ttf", 20);
	labelWave->setPosition(Point(origin.x + 175, origin.y + visibleSize.height - 105));
	labelWave->enableOutline(Color4B::BLACK, 1);
	layerHud->addChild(labelWave);


	//Pause
	auto pauseItem = MenuItemImage::create( "pause_2.png","pause_3.png", CC_CALLBACK_0(HudGameView::pause, this));
	pauseItem->setScale(0.7);
	pauseItem->setPosition(Point(origin.x + visibleSize.width -52, origin.y +35));
	menuButton->addChild(pauseItem);

	//Voice
	auto voiceItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(HudGameView::voiceItem, this), MenuItemImage::create("VoiceOpen.png", "VoiceOpen.png"), MenuItemImage::create("VoiceClose.png", "VoiceClose.png"), NULL);
	voiceItem->setPosition(Point(origin.x +45, origin.y+35));
	voiceItem->setScale(0.6);
	menuButton->addChild(voiceItem);


	this->addChild(menuButton, 1);
	this->addChild(layerHud, 0);
	this->addChild(layerBackground, -1);

	return true;

}
