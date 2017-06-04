#include "Monkey.h"



Monkey* Monkey::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Monkey();
	if (monster&&monster->init()) {
		monster->pointsVector = temPointsVector;
		monster->setPosition(temPointsVector[0]);
		monster->setzoredr();
		monster->move();
		monster->schedule(schedule_selector(BaseMonster::stateUpdate), 0.5f);
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}



Monkey::Monkey() :BaseMonster()
{

}


Monkey::~Monkey()
{
}

bool Monkey::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 26,49,1,25,50,72,127,160 };
	name = "Gorilla";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist", "enemies_jungle-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.2f));
	pointcnt = 0;
	setMaxHp(600);
	setCurHp(600);
	setHpBar();
	setArmor(20);
	setSpeed(30);
	setMoney(50);
	this->addChild(baseSprite);

	return true;
}

