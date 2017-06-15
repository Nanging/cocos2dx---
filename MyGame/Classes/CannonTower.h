#ifndef _BASE_CANNON_TOWER_
#define _BASE_CANNON_TOWER_
#include"BaseTower.h"
#include"cocos2d.h"
#include"CannonBullet.h"

class CannonTower :public BaseTower {
public:
protected:
	void initTower(int towerLevel);
	void setTips();
	BaseBullet* towerBullet();
};
#endif