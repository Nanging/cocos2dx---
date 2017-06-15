#ifndef __STAGE_TWO_H__
#define __STAGE_TWO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseStage.h"

using namespace cocos2d;
using namespace ui;
class StageTwo 
	: public BaseStage
{

private:
	std::vector<Point>  tempointsVector1 = { Point(834,880),Point(829,688),Point(684,595),Point(623,589),Point(504,682),Point(369,694),Point(320,621),Point(357,546),Point(311,484),Point(219,399),Point(193,387)
		,Point(-30,429) };  //第二关路径1
	std::vector<Point>  tempointsVector2 = { Point(1300,170),Point(1048,205),Point(820,120),Point(775,107),Point(465,214),Point(419,198),Point(297,135),Point(248,138),Point(179,222),
		Point(244,348),Point(222,398),Point(-30,427) };//第二关路径2
public:
	StageTwo();
	~StageTwo();
	virtual bool init();
	CREATE_FUNC(StageTwo);
	void initUnbuild();
	void initMonster();
	void addNextWave();
	void addMonster(float dt);
};

#endif // !__STAGE_TWO_H__