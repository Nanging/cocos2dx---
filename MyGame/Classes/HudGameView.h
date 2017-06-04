#ifndef __HUDGAMEVIEW_SCENE_H__
#define __HUDGAMEVIEW_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HudGameView : public Layer
{
public:
	virtual bool init();

	void backToMenu();
	void exitAsk();//back的回调函数，弹出询问是否确认退出，调用backToMenu
	void voiceItem();
	void pause();

	//int getMoney();//return present money, to judge if an operation to buy a tower is permitted
	//void moneyPlus(int addMoney);//when an enemy is killed or a tower is removed, Money+
	//bool moneyMinus(int lessenMoney);//when a tower begin to be built, Money-

	//int getHealth();//return present hp, to judge if be defeated
	//bool healthMinus();//when an enemy pass
	//int getWave();//return present wave
	//void wavePlus();//

	int presentMoney;
	int presentWave;
	int presentHealth;

	Label *health;
	Label *labelMoney;
	Label *labelWave;

	void update(float delta);
	CREATE_FUNC(HudGameView);
};
#endif
