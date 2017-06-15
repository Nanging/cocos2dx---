#ifndef __BOSS_MONSTER_H__
#define __BOSS_MONSTER_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class BossMonster :
	public BaseMonster
{
public:
	static BossMonster* createMonster(std::vector<Point> temPointsVector);
	BossMonster();
	~BossMonster();
	CREATE_FUNC(BossMonster);
	virtual bool init();
	void tick(float delta);
	void update(float delta);
	/*virtual void move();*/
};


#endif
