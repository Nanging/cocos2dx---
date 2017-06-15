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
	CC_SYNTHESIZE(BaseTower*, tower, Tower);//召唤菜单的塔
	CC_SYNTHESIZE(BuildBlock*, myBlock, MyBlock);//所处的地形单元
	virtual bool init();
	CREATE_FUNC(UpdateMenu);	
	void addIcons();//根据塔的不同生成不同按钮
	void addTower(int type);//建造
	void addTowerDemo(int type);//建造预览
	void updateDemo(int type, int lv);//升级预览
	void update(int type, int lv);//升级
	void inAnimation();//菜单打开动画
	void mouseClickBuild(EventMouse* e);//建造回调
	void mouseClickUpdate(EventMouse* e);//升级回调
	void mouseClickSell(EventMouse* e);//出售回调
	Sprite* planesprite;
	Sprite* scopeCircle;
	Sprite* nextScopeCircle;//攻击范围显示
	TowerIcon* sellIcon;
	TowerIcon* updateIcon;
	TowerIcon* arrowIcon;
	TowerIcon* magicIcon;
	TowerIcon* cannonIcon;
	Sprite* demoTower;//预览贴图
	bool isMenuShown;
};
#endif