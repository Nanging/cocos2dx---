#include "WaveFlag.h"



WaveFlag::WaveFlag()
{
}


WaveFlag::~WaveFlag()
{
}

bool WaveFlag::init() {
	if (!Sprite::init()) {
		return false;
	}
	isRun = false;
	isFirstWave = true;
	baseButton = MenuItemImage::create("BOMB_PIG_FLY.png","BOMB_PIG_FLY.png",CC_CALLBACK_0(WaveFlag::stopTimer,this));
	baseButton->setScale(1.05f);
	auto menu = Menu::create(baseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	nextEmeny = Sprite::create("BOMB_PIG_FLY.png");
	bubble = Sprite::create("pao.png");
	bubble->setScale(0.7f);
	des = Label::createWithTTF("Next wave:       ", "fonts/Marker Felt.ttf", 28);
	bubble->setVisible(false);
	des->setVisible(false);
	nextEmeny->setVisible(false);
	this->addChild(bubble);
	this->addChild(des);
	this->addChild(nextEmeny);

	auto timerPicture = Sprite::create("waveflag_redcircle-ipadhd.png");
	timer = ProgressTimer::create(timerPicture);
	
	timer->setPosition(0, 0);
	timer->setType(ProgressTimer::Type::RADIAL);
	timer->setPercentage(0);
	this->addChild(timer);
	auto listener = EventListenerMouse::create();  //注册鼠标悬停
	listener->onMouseMove = CC_CALLBACK_1(WaveFlag::waveTip, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//schedule(schedule_selector(WaveFlag::startTimer));
	return true;
}

void WaveFlag::startTimer(float dt) {
	this->runAction(Sequence::create(ScaleTo::create(0.3f, 0.6f, 0.6f), ScaleTo::create(0.3f, 0.8f, 0.8f), NULL));//呼吸灯效果
	if (!isFirstWave)
	{
		auto percent = timer->getPercentage();
		percent += 2.5f;
		log("  %f ", percent);
		if (percent >= 99) {
			this->unschedule(schedule_selector(WaveFlag::startTimer));
			stopTimer();
		}
		else {
			timer->setPercentage(percent);
		}
	}


}


void WaveFlag::stopTimer() {
	timer->setPercentage(100);
	isRun = true;
	isFirstWave = false;
	this->setVisible(false);
	this->unschedule(schedule_selector(WaveFlag::startTimer));

}


void WaveFlag::reTimer() {
	isRun = false;
	if (isFirstWave)
	{
		timer->setPercentage(100);
	}
	else
	{
		timer->setPercentage(0);
	}
	this->setVisible(true);
	this->schedule(schedule_selector(WaveFlag::startTimer), 0.5f);
}


void WaveFlag::waveTip(EventMouse* event) {        //悬停提示
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto node = event->getLocation();
	node.y = visibleSize.height - node.y;    //转换至以左下为原点的坐标系
	auto localNode = this->convertToNodeSpace(node);   //转换至本地坐标
	if (baseButton->getBoundingBox().containsPoint(localNode)) {
		bubble->setPosition(120, 135);
		des->setPosition(95, 135);
		bubble->setVisible(true);
		des->setVisible(true);
		nextEmeny->setPosition(175, 135);
		nextEmeny->setVisible(true);
	}
	else {
		bubble->setVisible(false);
		des->setVisible(false);
		nextEmeny->setVisible(false);
	}
}

