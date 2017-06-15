#ifndef _ARROW_TOWER_LVL3_H_
#define _ARROW_TOWER_LVL3_H_

#include"cocos2d.h"
#include"ArrowTowerLv2.h"

class ArrowTowerLv3 : public ArrowTower {
public:
	bool init();
	CREATE_FUNC(ArrowTowerLv3);
	void towerUpdate();
protected:
};
#endif