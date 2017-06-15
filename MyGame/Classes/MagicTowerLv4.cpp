#include"MagicTowerLv4.h"
#include"MagicBullet.h"
USING_NS_CC;

bool MagicTowerLv4::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerLevel(4);
	initTower(4);
	setListener();
	setAttackScope(320.0f);
	setSellMoney(400);
	setCrit(60);
	setTips();
	schedule(schedule_selector(MagicTowerLv3::attack), 1 / attackFrequency);
	isUpdateMenuShown = false;
	return true;
}