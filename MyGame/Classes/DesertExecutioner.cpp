#include "DesertExecutioner.h"



DesertExecutioner* DesertExecutioner::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new DesertExecutioner();
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



DesertExecutioner::DesertExecutioner() :BaseMonster()
{

}


DesertExecutioner::~DesertExecutioner()
{
}

bool DesertExecutioner::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 49,72,1,24,25,48,99,118 };
	name = "desertExecutioner";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(3000);
	setCurHp(3000);
	setHpBar();
	setArmor(100);
	setSpeed(40);
	setMoney(40);
	this->addChild(baseSprite);

	return true;
}