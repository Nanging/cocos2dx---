#ifndef __WING_RIDER_H__
#define __WING_RIDER_H__
#include "BaseMonster.h"
#include"cocos2d.h"
USING_NS_CC;
class WingRider :
	public BaseMonster
{
public:
	static WingRider* createMonster(std::vector<Point> temPointsVector);
	WingRider();
	~WingRider();
	CREATE_FUNC(WingRider);
	virtual bool init();
};


#endif

