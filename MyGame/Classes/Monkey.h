#ifndef __MONKEY_H__
#define __MONKEY_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Monkey :
	public BaseMonster
{
public:
	static Monkey* createMonster(std::vector<Point> temPointsVector);
	Monkey();
	~Monkey();
	CREATE_FUNC(Monkey);
	virtual bool init();
};


#endif

