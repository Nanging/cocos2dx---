#include "Hunter.h"



Hunter* Hunter::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new Hunter();
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



Hunter::Hunter() :BaseMonster()
{

}


Hunter::~Hunter()
{
}

bool Hunter::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 23,44,1,22,45,66,106,138 };
	name = "CanibalHunter";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist", "enemies_jungle-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(1000);
	setCurHp(1000);
	setHpBar();
	setArmor(30);
	setSpeed(50);
	setMoney(100);
	this->addChild(baseSprite);

	return true;
}
