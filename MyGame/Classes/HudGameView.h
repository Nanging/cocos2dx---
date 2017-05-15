#ifndef __HUDGAMEVIEW_SCENE_H__
#define __HUDGAMEVIEW_SCENE_H__

#include "cocos2d.h"

class HudGameView : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();//demo only

	virtual bool init();


	void backToMenu();
	void exitAsk();//back�Ļص�����������ѯ���Ƿ�ȷ���˳�������backToMenu
	void voiceItem();
	void pause();

	int getMoney();//return present money, to judge if an operation to buy a tower is permitted
	void moneyPlus(int addMoney);//when an enemy is killed or a tower is removed, Money+
	void moneyMinus(int lessenMoney);//when a tower begin to be built, Money-

	int getHealth();//return present hp, to judge if be defeated
	void healthMinus();//when an enemy pass
	int getWave();//return present wave
	void wavePlus();//


	int presentMoney;
	int presentWave;
	int presentHealth;

	CREATE_FUNC(HudGameView);
};
#endif