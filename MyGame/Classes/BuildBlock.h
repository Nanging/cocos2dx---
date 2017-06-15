#ifndef _BUILD_BLOCK_H_
#define _BUILD_BLOCK_H_

#include "cocos2d.h"

USING_NS_CC;

class BuildBlock : public Sprite {
public:
	void showUpdateMenu(Event* event);//��Ӳ˵�
	void hideUpdateMenu();
	void mouseClick(Event* event);
	bool Targeted(Event* event);//�ж��Ƿ�����
	bool isUpdateMenuShown;//��ǲ˵�״̬
	Sprite* buildBlock;//��ͼ����
	CREATE_FUNC(BuildBlock);
	bool isBuilted;
	virtual bool init();

};

#endif