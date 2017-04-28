#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class StartGame
	:public Layer
{
private:
	Sprite * logo;
public:
	Size size;
	StartGame();
	~StartGame();
	void initStart();
	static Scene *createScene();
	virtual bool init();
	void start();
	void setSaveMenuVisible();
	void closeSaveMenu();
	CREATE_FUNC(StartGame);
};

