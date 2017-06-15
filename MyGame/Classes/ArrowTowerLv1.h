#ifndef _ARROW_TOWER_LVL1_H_
#define _ARROW_TOWER_LVL1_H_

#include"cocos2d.h"
#include"ArrowTower.h"
#include"UpdateMenuLayer.h"

class ArrowTowerLv1 : public ArrowTower {
public:
	bool init();
	CREATE_FUNC(ArrowTowerLv1);
	void towerUpdate();//升级函数
protected:
	//void buildingAnimation();
	//void buildingSmokeAnimation();//动画什么的以后再加

};
#endif