#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__


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
#endif // !__LOAD_SCENE_H__
