#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "proj.win32/BaseStage.h"
using namespace cocos2d;
using namespace ui;
class StageOne
	:public BaseStage
{
private:
public:
	StageOne();
	~StageOne();
	virtual bool init();
	CREATE_FUNC(StageOne);
	void initUnbuild();
	void runCurrentWave();
	void tick(float dt);
	void pauseStage(Ref * psender);
	void resumeStage();
};

