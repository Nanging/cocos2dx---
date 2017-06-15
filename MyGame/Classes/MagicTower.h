#ifndef _BASE_MAGIC_TOWER_
#define _BASE_MAGIC_TOWER_
#include"BaseTower.h"
#include"cocos2d.h"
#include"MagicBullet.h"

class MagicTower :public BaseTower {
public:
protected:
	void initTower(int towerLevel);
	void setTips();
	BaseBullet* towerBullet();
};
#endif