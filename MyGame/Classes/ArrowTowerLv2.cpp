#include"ArrowTowerLv3.h"

USING_NS_CC;

bool ArrowTowerLv2::init()
{
	if (!Sprite::init())
	{
		return false;
	}	
	initTower(2);
	setTowerLevel(2);
	setAttackScope(200.0f);
	setNextAttackScope(240.0f);
	setUpdateMoney(150);
	setCrit(50);
	setSellMoney(120);
	setTips();
	//设置塔的属性
	setListener();
	schedule(schedule_selector(ArrowTowerLv2::attack), 1/attackFrequency);//按攻击速度重复调用attack函数

	isUpdateMenuShown = false;
	return true;
}

void ArrowTowerLv2::towerUpdate()
{
	auto ArrowTowerLv3 = ArrowTowerLv3::create();
	ArrowTowerLv3->setSpriteLocation(spriteLocation);
	ArrowTowerLv3->setTag(spriteLocation->getTag());
	ArrowTowerLv3->setPosition(Point(0,0));
	spriteLocation->addChild(ArrowTowerLv3);
	this->towerRemove();
}