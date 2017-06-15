#include"MagicTowerLv2.h"
#include"MagicBullet.h"
USING_NS_CC;

bool MagicTowerLv1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(MAGIC);
	setTowerLevel(1);
	initTower(1);
	setListener();
	setAttackScope(140.0f);
	setNextAttackScope(180.0f);
	setUpdateMoney(160);
	setSellMoney(70);
	setCrit(20);
	setTips();
	schedule(schedule_selector(MagicTowerLv1::attack), 1/attackFrequency);//¹¥»÷ËÙ¶È

	isUpdateMenuShown = false;
	return true;
}

void MagicTowerLv1::towerUpdate()
{
	auto magicTowerLv2 = MagicTowerLv2::create();
	magicTowerLv2->setSpriteLocation(spriteLocation);
	magicTowerLv2->setTag(spriteLocation->getTag());
	magicTowerLv2->setPosition(Point(0, 0));
	spriteLocation->addChild(magicTowerLv2);
	this->towerRemove();
}