#ifndef __TRENSITION_SCENE_H__
#define __TRENSITION_SCENE_H__
#include "cocos2d.h"
using namespace cocos2d;
class TransitionGame
	:public TransitionScene
{
public:
	TransitionGame();
	~TransitionGame();
	void onEnter();
	static TransitionGame *create(float t, Scene *scene);
	//static TransitionGame *createWithRenderTexture(float t, Scene *scene, RenderTexture *sqr);
private:
	//void initRenderTexture(RenderTexture *sqr);
	void LRFinish();
	void OnSencondActionFinish();
};

#endif //!__TRENSITION_SCENE_H__