#include"MagicTowerLv4.h"
#include"MagicBullet.h"
USING_NS_CC;

bool MagicTowerLv3::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerLevel(3);
	initTower(3);
	setListener();
	setAttackScope(240.0f);
	setSellMoney(330);
	setUpdateMoney(320);
	setCrit(40);
	setTips();
	schedule(schedule_selector(MagicTowerLv3::attack), 1/attackFrequency);

	isUpdateMenuShown = false;
	return true;
}
void MagicTowerLv3::towerUpdate()
{
	auto magicTowerLv4 = MagicTowerLv4::create();
	magicTowerLv4->setSpriteLocation(spriteLocation);
	magicTowerLv4->setTag(spriteLocation->getTag());
	magicTowerLv4->setPosition(Point(-5, 0));
	spriteLocation->addChild(magicTowerLv4);
	this->towerRemove();
}