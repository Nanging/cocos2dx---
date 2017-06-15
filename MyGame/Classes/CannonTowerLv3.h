#ifndef _CANNON_TOWER_LVL3_H_
#define _CANNON_TOWER_LVL3_H_

#include"cocos2d.h"
#include"CannonTowerLv2.h"

class CannonTowerLv3 : public CannonTower {
public:
	bool init();
	CREATE_FUNC(CannonTowerLv3);
	void towerUpdate();
protected:
};
#endif