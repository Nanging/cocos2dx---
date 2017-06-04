#ifndef __DESERT_EXECUTIONER_H__
#define __DESERT_EXECUTIONER_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class DesertExecutioner :
	public BaseMonster
{
public:
	static DesertExecutioner* createMonster(std::vector<Point> temPointsVector);
	DesertExecutioner();
	~DesertExecutioner();
	CREATE_FUNC(DesertExecutioner);
	virtual bool init();
};


#endif
