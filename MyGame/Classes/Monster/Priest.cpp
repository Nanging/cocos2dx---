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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist", "enemies_jungle-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(400);
	setCurHp(400);
	setHpBar();
	setArmor(0);
	setSpeed(80);
	setMoney(50);
	this->addChild(baseSprite);

	return true;
}

