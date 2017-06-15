#ifndef _UPDATE_MENU_LAYER_H_
#define _UPDATE_MENU_LAYER_H_

#include "cocos2d.h"
#include"BaseTower.h"
#include"ScopeCircle.h"
#include"BuildBlock.h"
#include"Tower.h"
USING_NS_CC;

class UpdateMenu : public Sprite {
public:
	CC_SYNTHESIZE(BaseTower*, tower, Tower);//�ٻ��˵�����
	CC_SYNTHESIZE(BuildBlock*, myBlock, MyBlock);//�����ĵ��ε�Ԫ
	virtual bool init();
	CREATE_FUNC(UpdateMenu);	
	void addIcons();//�������Ĳ�ͬ���ɲ�ͬ��ť
	void addTower(int type);//����
	void addTowerDemo(int type);//����Ԥ��
	void updateDemo(int type, int lv);//����Ԥ��
	void update(int type, int lv);//����
	void inAnimation();//�˵��򿪶���
	void mouseClickBuild(EventMouse* e);//����ص�
	void mouseClickUpdate(EventMouse* e);//�����ص�
	void mouseClickSell(EventMouse* e);//���ۻص�
	Sprite* planesprite;
	Sprite* scopeCircle;
	Sprite* nextScopeCircle;//������Χ��ʾ
	TowerIcon* sellIcon;
	TowerIcon* updateIcon;
	TowerIcon* arrowIcon;
	TowerIcon* magicIcon;
	TowerIcon* cannonIcon;
	Sprite* demoTower;//Ԥ����ͼ
	bool isMenuShown;
};
#endif