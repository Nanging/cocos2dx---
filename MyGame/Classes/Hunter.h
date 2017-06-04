#ifndef __HUNTER_H__
#define __HUNTER_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class Hunter :
	public BaseMonster
{
public:
	static Hunter* createMonster(std::vector<Point> temPointsVector);
	Hunter();
	~Hunter();
	CREATE_FUNC(Hunter);
	virtual bool init();
};


#endif

