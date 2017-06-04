#ifndef __PRIEST_H__
#define __PRIEST_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Priest :
	public BaseMonster
{
public:
	static Priest* createMonster(std::vector<Point> temPointsVector);
	Priest();
	~Priest();
	CREATE_FUNC(Priest);
	virtual bool init();
};


#endif
