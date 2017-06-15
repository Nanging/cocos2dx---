#ifndef _MAGIC_TOWER_LVL3_H_
#define _MAGIC_TOWER_LVL3_H_

#include"cocos2d.h"
#include"MagicTowerLv2.h"


class MagicTowerLv3 : public MagicTower {
public:
	bool init();
	CREATE_FUNC(MagicTowerLv3);
	void towerUpdate();
protected:
};
#endif