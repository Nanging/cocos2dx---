#include"ArrowTowerLv2.h"
USING_NS_CC;

bool ArrowTowerLv1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(SPEED);
	initTower(1);
	setTowerLevel(1);
	setAttackScope(160.0f);
	setNextAttackScope(200.0f);
	setUpdateMoney(100);
	setSellMoney(50);
	setCrit(20);
	setTips();//根据天赋设置攻击力和攻击速度
	//设置塔的各项属性
	schedule(schedule_selector(ArrowTowerLv1::attack), 1/attackFrequency);//按攻击速度重复调用attack函数
	setListener();
	setSpriteLocation(static_cast<BuildBlock*>(this->getParent()));//
	isUpdateMenuShown = false;
	return true;
}

void ArrowTowerLv1::towerUpdate(){
	auto ArrowTowerLv2 = ArrowTowerLv2::create();
	ArrowTowerLv2->setSpriteLocation(spriteLocation);//使用同一个地形单元
	ArrowTowerLv2->setTag(spriteLocation->getTag());
	ArrowTowerLv2->setPosition(Point(0, 0));
	spriteLocation->addChild(ArrowTowerLv2);//添加新塔
	this->towerRemove();//删除旧塔
}


