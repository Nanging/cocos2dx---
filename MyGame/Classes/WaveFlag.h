#ifndef __WAVE_FLAG_H__
#define __WAVE_FLAG_H__
#include "cocos2d.h"
USING_NS_CC;

class WaveFlag :
	public Sprite
{
public:
	WaveFlag();
	virtual ~WaveFlag();
	CREATE_FUNC(WaveFlag);
	bool init();
	ProgressTimer* timer;       //计时器
	MenuItemImage* baseButton;  //触碰按钮
	Sprite* bubble;
	Label* des;
	Sprite * nextEmeny;
	bool isFirstWave;
	bool isRun;


	void startTimer(float dt);       //开始计时
	void reTimer();                 //重新开始计时
	void stopTimer();                //停止计时
	void waveTip(EventMouse* event);//悬停显示怪物数


};

#endif // !__WaveFlay_H__
