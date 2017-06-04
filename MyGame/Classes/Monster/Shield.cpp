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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist", "enemies_jungle-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(400);
	setCurHp(400);
	setHpBar();
	setArmor(80);
	setSpeed(40);
	setMoney(50);
	this->addChild(baseSprite);

	return true;
}