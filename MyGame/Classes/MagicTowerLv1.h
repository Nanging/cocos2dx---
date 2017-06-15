#ifndef _MAGIC_TOWER_LVL1_H_
#define _MAGIC_TOWER_LVL1_H_

#include"cocos2d.h"
#include"MagicTower.h"

class MagicTowerLv1 : public MagicTower {
public:
	bool init();
	CREATE_FUNC(MagicTowerLv1);
	void towerUpdate();
};
#endif