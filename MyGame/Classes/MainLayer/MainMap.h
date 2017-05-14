#ifndef __MAIN_MAP_SCENE_H__
#define __MAIN_MAP_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StageFlag.h"
using namespace cocos2d;
using namespace ui;
class MainMap
	:public Layer
{
	//Sprite * touch;
	ScrollView * sv;
	StageFlag* flagOne;
	StageFlag* flagTwo;
	StageFlag* flagThree;
	Label * score;
public:
	MainMap();
	~MainMap();
	static Scene * createScene();
	virtual bool init();
	void MapScroll(Ref* r, ScrollView::EventType e);
	CREATE_FUNC(MainMap);
	//void StageOne(Ref * psender);
	//void StageTwo(Ref * psender);
	//void StageThree(Ref * psender);
	void initMap();
	void initFlag();
	void ToMainMenu(Ref * psender);
	void techScene(Ref * psender);
	void initBotton();
	void initLabel();
};
#endif // !__MAIN_MAP_SCENE_H__
