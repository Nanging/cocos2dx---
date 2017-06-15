#ifndef _CANNON_TOWER_LVL2_H_
#define _CANNON_TOWER_LVL2_H_

#include"cocos2d.h"
#include"CannonTowerLv1.h"

class CannonTowerLv2 : public CannonTower {
public:
	bool init();
	CREATE_FUNC(CannonTowerLv2);
	void towerUpdate();
protected:
};
#endif