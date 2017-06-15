#ifndef _CANNON_TOWER_LVL1_H_
#define _CANNON_TOWER_LVL1_H_

#include"cocos2d.h"
#include"CannonTower.h"
#include"UpdateMenuLayer.h"
//#include"BaseMap.h"
class CannonTowerLv1 : public CannonTower {
public:
	bool init();
	CREATE_FUNC(CannonTowerLv1);
	void towerUpdate();
protected:
};
#endif