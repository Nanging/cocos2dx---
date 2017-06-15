#ifndef _ARROW_TOWER_LVL2_H_
#define _ARROW_TOWER_LVL2_H_

#include"cocos2d.h"
#include"ArrowTowerLv1.h"
class ArrowTowerLv2 : public ArrowTower {
public:
	bool init();
	CREATE_FUNC(ArrowTowerLv2);
	void towerUpdate();
protected:
};
#endif