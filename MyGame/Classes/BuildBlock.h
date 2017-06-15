#ifndef _BUILD_BLOCK_H_
#define _BUILD_BLOCK_H_

#include "cocos2d.h"

USING_NS_CC;

class BuildBlock : public Sprite {
public:
	void showUpdateMenu(Event* event);//添加菜单
	void hideUpdateMenu();
	void mouseClick(Event* event);
	bool Targeted(Event* event);//判断是否点击到
	bool isUpdateMenuShown;//标记菜单状态
	Sprite* buildBlock;//贴图精灵
	CREATE_FUNC(BuildBlock);
	bool isBuilted;
	virtual bool init();

};

#endif