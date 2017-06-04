#ifndef __SHIELD_H__
#define __SHIELD_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Shield :
	public BaseMonster
{
public:
	static Shield* createMonster(std::vector<Point> temPointsVector);
	Shield();
	~Shield();
	CREATE_FUNC(Shield);
	virtual bool init();
};


#endif

