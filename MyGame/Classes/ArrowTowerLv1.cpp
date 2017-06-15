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
	setTips();//�����츳���ù������͹����ٶ�
	//�������ĸ�������
	schedule(schedule_selector(ArrowTowerLv1::attack), 1/attackFrequency);//�������ٶ��ظ�����attack����
	setListener();
	setSpriteLocation(static_cast<BuildBlock*>(this->getParent()));//
	isUpdateMenuShown = false;
	return true;
}

void ArrowTowerLv1::towerUpdate(){
	auto ArrowTowerLv2 = ArrowTowerLv2::create();
	ArrowTowerLv2->setSpriteLocation(spriteLocation);//ʹ��ͬһ�����ε�Ԫ
	ArrowTowerLv2->setTag(spriteLocation->getTag());
	ArrowTowerLv2->setPosition(Point(0, 0));
	spriteLocation->addChild(ArrowTowerLv2);//�������
	this->towerRemove();//ɾ������
}


