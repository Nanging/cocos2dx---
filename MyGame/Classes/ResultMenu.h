#ifndef __RESULT_MENU_LAYER_H__
#define __RESULT_MENU_LAYER_H__
#include "cocos2d.h"
using namespace cocos2d;
class ResultMenu
	:public Layer
{
private:
	bool status;
	int score;
	Sprite* background;
	Sprite* result;
	MenuItemImage * restartButton;
	MenuItemImage * exitButton;
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(ResultMenu);
	ResultMenu();
	~ResultMenu();
	void initBack();
	void restart(Ref * psender);
	void quit(Ref * psender);
	void updateResult();
	void effect(float dt);
};

#endif //!__RESULT_MENU_LAYER_H__