#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class SlotMenu
	:public Sprite
{
public:
	SlotMenu();
	~SlotMenu();
	virtual bool initWithNum(int num);
	//CREATE_FUNC(SlotMenu);
	void button_Savelot_Delete_callback(Ref* pSender);
	void confirm_delete(Ref* pSender);
	void cancel_delete(Ref* pSender);
	void createNewGame();
	void startGame(int num);
	static SlotMenu* createMenu(int num);
protected:
	int slotnumber;
	Label* label_hint;
	Label* score_label;
	MenuItemImage* button_Savelot_Delete;
	MenuItemImage* savelot;
	Sprite* star;
	Menu* confirm_menu;
};

