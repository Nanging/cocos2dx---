#ifndef _MAGIC_TOWER_LVL2_H_
#define _MAGIC_TOWER_LVL2_H_

#include"cocos2d.h"
#include"MagicTowerLv1.h"

class MagicTowerLv2 : public MagicTower {
public:
	bool init();
	CREATE_FUNC(MagicTowerLv2);
	void towerUpdate();
protected:
};
#endif