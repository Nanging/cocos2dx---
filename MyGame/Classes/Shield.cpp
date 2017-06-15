#include "Shield.h"






Shield* Shield::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Shield();
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



Shield::Shield() :BaseMonster()
{

}


Shield::~Shield()
{
}

bool Shield::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 23,44,1,22,45,66,100,118 };
	name = "CanibalShamanShield";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(1500);
	setCurHp(1500);
	setHpBar();
	setArmor(50);
	setSpeed(50);
	setMoney(30);
	this->addChild(baseSprite);

	return true;
}