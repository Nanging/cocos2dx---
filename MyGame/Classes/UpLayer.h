#ifndef __UP_LAYER_H__
#define __UP_LAYER_H__
#include"cocos2d.h"
USING_NS_CC;
class ArrayUpIcon;
class MagicUpIcon;
class BatteryUpIcon;



class UpLayer :
	public Layer
{
public:
	UpLayer();
	~UpLayer();
	CREATE_FUNC(UpLayer);
	bool init();
	bool initSprite();
	bool initLabel();
	bool initMenu();
	static Scene* createScene();
	void update(float delta);
	CC_SYNTHESIZE(int, star, Star);
	CC_SYNTHESIZE(int, choosestate, Choosestate);     //用来判断你选了哪个图标
	int temstar;                                      //记录星星初始个数


	void up(Ref* pSender);                         //执行升级
	void reset(Ref* pSender);                      //重置
	void quit(Ref* pSender);                     //待写
	void showDes(int i);                           //显示当前天赋效果
	void swallow(int i);                           
	void getLevel();

	ArrayUpIcon* array;                   //箭塔升级图
	MagicUpIcon* magic;                   //魔法塔升级图
	BatteryUpIcon* battery;               //炮塔升级图
	MenuItemImage* upButton;                  //升级按钮
	MenuItemImage* resetButton;               //重置按钮
	MenuItemImage* quitButton;
	MenuItemImage* bgSprite;                  //背景

	std::vector<MenuItemImage*> iconVector;               //将所有升级图标放在一个vector内便于管理
	int levelVector[9] = {0};                        //储存每种天赋当前的等级
	//const char* upKind[3] = { "force","scope","speed" };
	int price[9][4] = { {1,1,2,3},{ 1,1,2,3},{0,2,3,4}
					,{ 1,1,2,3 },{ 1,1,2,3 },{0,2,3,4}
					,{ 1,1,2,3 },{ 1,1,2,3 },{0,2,3,4} };
	//九种天赋每次升级所需的星星数，a[i][n]对应天赋i从第n级升到第n+1级所需的星星数，
	//例如a[i][0]=1：天赋i从第0级升到1级需要1颗星星 

	Label* des;                               //升级效果文字描述
	//Label* upDes;                             //升级按钮表面的文字
	//Label* resetDes;                          //重置按钮表面的文字
	//Label* quitDes;                          //退出按钮表面的文字
	Label* starNumDes;                       //剩余星星
	Label* starCostDes;                      //价格
	Label* introduce;                        //界面简单介绍
	//Label* briefDes;                        //鼠标悬停介绍

	//Sprite* data;                              //遮盖层
	//Sprite* starPicture;                      //显示星星剩余
	//Sprite* starBound;                        //包装星星的框
	//Sprite* towerKind1;                       //箭塔图标
	//Sprite* towerKind2;                       //魔法塔图标
	//Sprite* towerKind3;                       //炮塔图标
	Sprite* slected;                          //选中边框
	Sprite* starCost;                         //升级需要星星数
	Sprite* introduceBound;                   //装饰品
	//Sprite* bubble;                            //气泡

};

#endif // !__UP_LAYER_H__


