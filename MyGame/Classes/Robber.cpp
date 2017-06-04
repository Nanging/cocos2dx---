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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert-hd.plist", "enemies_desert-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(700);
	setCurHp(700);
	setHpBar();
	setArmor(30);
	setSpeed(90);
	setMoney(80);
	this->addChild(baseSprite);

	return true;
}

