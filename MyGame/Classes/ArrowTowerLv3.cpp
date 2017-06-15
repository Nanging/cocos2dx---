#include"ArrowTowerLv4.h"


USING_NS_CC;

bool ArrowTowerLv3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(SPEED);
	setTowerLevel(3);
	initTower(3);
	setListener();
	setAttackScope(240.0f);
	setCrit(80);
	setUpdateMoney(200);
	setSellMoney(220);
	setTips();
	schedule(schedule_selector(ArrowTowerLv3::attack), 1/attackFrequency);

	isUpdateMenuShown = false;
	return true;
}

void ArrowTowerLv3::towerUpdate()
{
	auto ArrowTowerLv4 = ArrowTowerLv4::create();
	ArrowTowerLv4->setSpriteLocation(spriteLocation);
	ArrowTowerLv4->setTag(spriteLocation->getTag());
	ArrowTowerLv4->setPosition(Point(0, 0));
	spriteLocation->addChild(ArrowTowerLv4);
	this->towerRemove();
}