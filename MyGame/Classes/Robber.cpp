#include "Robber.h"



Robber* Robber::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Robber();
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



Robber::Robber() :BaseMonster()
{

}


Robber::~Robber()
{
}

bool Robber::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 23,44,1,22,45,66,89,106 };
	name = "desertRaider";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(2000);
	setCurHp(2000);
	setHpBar();
	setArmor(50);
	setSpeed(50);
	setMoney(20);
	this->addChild(baseSprite);

	return true;
}

