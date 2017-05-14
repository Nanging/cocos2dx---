#ifndef __SLOT_MENU_H__
#define __SLOT_MENU_H__


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
	void initMenu();
	static SlotMenu* createMenu(int num);
protected:
	int slotNumber;
	Label* labelHint;
	Label* scoreLabel;
	MenuItemImage* buttonSavelotDelete;
	MenuItemImage* savelot;
	Sprite* star;
	Menu* confirmMenu;
};

#endif // !__SLOT_MENU_H__