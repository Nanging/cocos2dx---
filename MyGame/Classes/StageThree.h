#ifndef __STAGE_THREE_H__
#define __STAGE_THREE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseStage.h"

using namespace cocos2d;
using namespace ui;
class StageThree
	:public BaseStage
{
private:
	std::vector<Point> tempointsVector1 = { Point(680,880),Point(603,612),Point(409,596),Point(288,422),Point(-30,423) };//第三关路径1
	std::vector<Point> tempointsVector2 = { Point(1300,429),Point(643,422),Point(620,385),Point(642,303),Point(493,192),Point(319,238),Point(194,231),Point(80,163),Point(-30,167) };//第三关路径2
	std::vector<Point> tempointsVector3 = { Point{ 1300,170 },Point(917,158),Point(812,188),Point(714,140),Point(602,139),Point(532,200),Point(356,216),Point(298,242),Point(195,235),Point(113,167),Point(-30,161) };
	//第三关路径3
public:
	StageThree();
	~StageThree();
	virtual bool init();
	CREATE_FUNC(StageThree);
	void initUnbuild();
	void initMonster();
	void addNextWave();
	void addMonster(float dt);
};
#endif // !__STAGE_THREE_H__
