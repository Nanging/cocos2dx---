#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class StartGame
	:public Layer
{
private:
	Sprite * logo;
	Sprite * StartBottomOne;
	Sprite * StartBottomTwo;
public:
	Size size;
	StartGame();
	~StartGame();
	void initStart();
	static Scene *createScene();
	virtual bool init();
	void start(float dt);
	void setSaveMenuVisible();
	void closeSaveMenu();
	void removeBotton(Sprite * botton);
	CREATE_FUNC(StartGame);
};

