#include "WingRider.h"                               //该怪物会有多条行进路线



WingRider* WingRider::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new WingRider();
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



WingRider::WingRider() :BaseMonster()
{

}


WingRider::~WingRider()
{
}

bool WingRider::init() {
	if (!Sprite::init()) {
		return false;
	}

	animationmark = { 15,28,1,14,29,42,57,67 };
	name = "CanibalWingRider";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist", "enemies_jungle-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.3f));
	pointcnt = 0;
	setMaxHp(200);
	setCurHp(200);
	setHpBar();
	setArmor(0);
	setSpeed(100);
	setMoney(50);
	this->addChild(baseSprite);

	return true;
}


