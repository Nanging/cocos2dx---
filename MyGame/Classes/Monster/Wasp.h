#ifndef __WASP_H__
#define __WASP_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Wasp :
	public BaseMonster
{
public:
	static Wasp* createMonster(std::vector<Point> temPointsVector);
	Wasp();
	~Wasp();
	CREATE_FUNC(Wasp);
	virtual bool init();
};


#endif

