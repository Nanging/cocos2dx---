#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class LoadScene
	:public Layer
{
public:
	LoadScene();
	~LoadScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);
	void loadSouce();
	void logic(float dt);
	int NumberOfLoadedResource;
};

