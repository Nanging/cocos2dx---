#include "Wasp.h"                 //该怪物会有多条行进路线



Wasp* Wasp::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Wasp();
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



Wasp::Wasp() :BaseMonster()
{

}


Wasp::~Wasp()
{
}

bool Wasp::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 15,29,1,14,30,42,43,53 };
	name = "wasp_queen";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(2000);
	setCurHp(2000);
	setHpBar();
	setArmor(30);
	setSpeed(50);
	setMoney(25);
	this->addChild(baseSprite);

	return true;
}


