#include"ArrowTowerLv4.h"


USING_NS_CC;

bool ArrowTowerLv4::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(SPEED);
	setTowerLevel(4);
	initTower(4);
	setListener();
	setAttackScope(280.0f);
	setCrit(80);
	setSellMoney(360);
	setTips();
	schedule(schedule_selector(ArrowTowerLv4::attack), 1 / attackFrequency);

	isUpdateMenuShown = false;
	return true;
}