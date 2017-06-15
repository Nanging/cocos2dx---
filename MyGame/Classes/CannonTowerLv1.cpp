#include"CannonTowerLv2.h"
USING_NS_CC;

bool CannonTowerLv1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initTower(1);
	setTowerType(POWER);
	setTowerLevel(1);	
	setListener();
	setAttackScope(150.0f);
	setNextAttackScope(180.0f);
	setUpdateMoney(200);
	setSellMoney(70);
	setCrit(10);
	setTips();
	schedule(schedule_selector(CannonTowerLv1::attack), 1/attackFrequency);//¹¥»÷ËÙ¶È

	isUpdateMenuShown = false;
	return true;
}

void CannonTowerLv1::towerUpdate()
{
	auto cannonTowerLv2 = CannonTowerLv2::create();
	cannonTowerLv2->setSpriteLocation(spriteLocation);
	cannonTowerLv2->setTag(spriteLocation->getTag());
	cannonTowerLv2->setPosition(Point(0, 0));
	spriteLocation->addChild(cannonTowerLv2);
	this->towerRemove();
}
