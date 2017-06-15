#ifndef _BASE_ARROW_TOWER_
#define _BASE_ARROW_TOWER_
#include"BaseTower.h"
#include"cocos2d.h"
#include"ArrowBullet.h"

class ArrowTower :public BaseTower {
public:
protected:
	void initTower(int towerLevel);//生成贴图
	void setTips();//根据当前天赋设置攻击力和攻击速度
	BaseBullet* towerBullet();//根据塔的攻击力生成威力不同的子弹
};
#endif