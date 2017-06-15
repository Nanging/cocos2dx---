#include"CannonTowerLv4.h"
#include"CannonBullet.h"

USING_NS_CC;

bool CannonTowerLv4::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(POWER);
	setTowerLevel(4);
	initTower(4);
	setListener();
	setAttackScope(210.0f);
	setSellMoney(460);
	setCrit(40);
	setTips();
	schedule(schedule_selector(CannonTowerLv4::attack), 1 / attackFrequency);

	isUpdateMenuShown = false;
	return true;
}