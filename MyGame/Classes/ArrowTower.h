#ifndef _BASE_ARROW_TOWER_
#define _BASE_ARROW_TOWER_
#include"BaseTower.h"
#include"cocos2d.h"
#include"ArrowBullet.h"

class ArrowTower :public BaseTower {
public:
protected:
	void initTower(int towerLevel);//������ͼ
	void setTips();//���ݵ�ǰ�츳���ù������͹����ٶ�
	BaseBullet* towerBullet();//�������Ĺ���������������ͬ���ӵ�
};
#endif