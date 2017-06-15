#include"CannonTowerLv4.h"
#include"CannonBullet.h"

USING_NS_CC;

bool CannonTowerLv3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(POWER);
	setTowerLevel(3);
	initTower(3);
	setListener();
	setAttackScope(210.0f);
	setUpdateMoney(350);
	setSellMoney(380);
	setCrit(30);
	setTips();
	schedule(schedule_selector(CannonTowerLv3::attack), 1/attackFrequency);

	isUpdateMenuShown = false;
	return true;
}
void CannonTowerLv3::towerUpdate()
{
	auto cannonTowerLv4 = CannonTowerLv4::create();
	cannonTowerLv4->setSpriteLocation(spriteLocation);
	cannonTowerLv4->setTag(spriteLocation->getTag());
	cannonTowerLv4->setPosition(Point(0, 0));
	spriteLocation->addChild(cannonTowerLv4);
	this->towerRemove();
}