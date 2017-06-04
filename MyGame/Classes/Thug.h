#ifndef __THUG_H__
#define __THUG_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Thug :
	public BaseMonster
{
public:
	static Thug* createMonster(std::vector<Point> temPointsVector);
	Thug();
	~Thug();
	CREATE_FUNC(Thug);
	virtual bool init();
};


#endif


