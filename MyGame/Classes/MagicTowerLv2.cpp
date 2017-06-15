#include"MagicTowerLv3.h"
#include"MagicBullet.h"
USING_NS_CC;

bool MagicTowerLv2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(MAGIC);
	setTowerLevel(2);
	initTower(2);
	setListener();
	setAttackScope(180.0f);
	setNextAttackScope(240.0f);
	setUpdateMoney(220);
	setSellMoney(180);
	setCrit(30);
	setTips();
	schedule(schedule_selector(MagicTowerLv2::attack), 1/attackFrequency);

	isUpdateMenuShown = false;
	return true;
}

void MagicTowerLv2::towerUpdate()
{
	auto magicTowerLv3 = MagicTowerLv3::create();
	magicTowerLv3->setSpriteLocation(spriteLocation);
	magicTowerLv3->setTag(spriteLocation->getTag());
	magicTowerLv3->setPosition(Point(-5, 0));
	spriteLocation->addChild(magicTowerLv3);
	this->towerRemove();
}