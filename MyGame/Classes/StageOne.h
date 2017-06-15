#ifndef __STAHGE_ONE_H__
#define __STAHGE_ONE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseStage.h"

using namespace cocos2d;
using namespace ui;
class StageOne
	:public BaseStage
{
private:
	
	std::vector<Point> tempointsVector1 = { Point(1300,511),Point(877,514),Point(809,687),Point(646,686),Point(616,531),Point(500,510),Point(381,497),Point(325,431),Point(326,371)
		,Point(470,328),Point(659,361),Point(748,309),Point(744,229),Point(694,190),Point(548,159),Point(548,-30) };
public:
	StageOne();
	~StageOne();
	virtual bool init();
	CREATE_FUNC(StageOne);
	void initUnbuild();
	void initMonster();
	void addNextWave();
	void addMonster(float dt);
};

#endif // !__STAHGE_ONE_H__