#include"CannonTowerLv3.h"
#include"CannonBullet.h"
USING_NS_CC;

bool CannonTowerLv2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(POWER);
	setTowerLevel(2);
	initTower(2);
	setListener();
	setAttackScope(180.0f);
	setNextAttackScope(210.0f);
	setUpdateMoney(250);
	setSellMoney(210);
	setCrit(20);
	setTips();
	schedule(schedule_selector(CannonTowerLv2::attack), 1/attackFrequency);

	isUpdateMenuShown = false;
	return true;
}

void CannonTowerLv2::towerUpdate()
{
	auto cannonTowerLv3 = CannonTowerLv3::create();
	cannonTowerLv3->setSpriteLocation(spriteLocation);
	cannonTowerLv3->setTag(spriteLocation->getTag());
	cannonTowerLv3->setPosition(Point(0, 0));
	spriteLocation->addChild(cannonTowerLv3);
	this->towerRemove();
}