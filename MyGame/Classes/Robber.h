#ifndef __ROBBER_H__
#define __ROBBER_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Robber :
	public BaseMonster
{
public:
	static Robber* createMonster(std::vector<Point> temPointsVector);
	Robber();
	~Robber();
	CREATE_FUNC(Robber);
	virtual bool init();
};


#endif

