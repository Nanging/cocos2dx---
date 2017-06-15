#include "Priest.h"



Priest* Priest::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Priest();
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



Priest::Priest() :BaseMonster()
{

}


Priest::~Priest()
{
}

bool Priest::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 23,44,1,22,45,66,160,176 };
	name = "CanibalShamanPriest";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(2000);
	setCurHp(2000);
	setHpBar();
	setArmor(100);
	setSpeed(40);
	setMoney(40);
	this->addChild(baseSprite);

	return true;
}

