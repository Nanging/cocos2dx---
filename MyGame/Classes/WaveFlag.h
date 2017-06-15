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
	ProgressTimer* timer;       //��ʱ��
	MenuItemImage* baseButton;  //������ť
	Sprite* bubble;
	Label* des;
	//Sprite * nextEmeny;
	bool isOver;
	bool isFirstWave;
	bool isRun;


	void startTimer(float dt);       //��ʼ��ʱ
	void reTimer();                 //���¿�ʼ��ʱ
	void stopTimer();                //ֹͣ��ʱ
	void waveTip(EventMouse* event);//��ͣ��ʾ������


};

#endif // !__WaveFlay_H__
