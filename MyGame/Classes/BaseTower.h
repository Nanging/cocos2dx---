#ifndef _BASE_TOWER_
#define _BASE_TOWER_
//塔（tower）应该是作为建造地形单元（build block）的子节点，建造地形单元应该是地图上触摸层的子节点

#include "cocos2d.h"
#include"BaseBullet.h"//子弹类
#include"BuildBlock.h"//地图上的可建造区域
#include "BaseMonster.h"//敌人类
#include"utiltool.h"

/*
enum Tower {
	MAGE=1,//膜法塔
	CANNON,//炮塔
	ARCHER,//箭塔
};//三种类别的塔
*/

class BaseTower :public cocos2d::Sprite {
public:
	CC_SYNTHESIZE(int, sellMoney, SellMoney);//出售返还金钱
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, towerLevel, TowerLevel);//当前等级
	CC_SYNTHESIZE(float, attackScope, AttackScope);//攻击范围
	CC_SYNTHESIZE(float, nextAttackScope, NextAttackScope);//在确认升级之前显示下一级的攻击范围
	CC_SYNTHESIZE(float, attackFrequency, AttackFrequency);//攻击速度
	CC_SYNTHESIZE(int, atkValue, AtkValue);//攻击力(等于子弹的伤害值
	CC_SYNTHESIZE(Tower, towerType, TowerType);//类别
	CC_SYNTHESIZE(int, crit, Crit);//暴击率
	CC_SYNTHESIZE(BuildBlock*, spriteLocation, SpriteLocation);//塔所建造在的位置
	CC_SYNTHESIZE(int, maxLevel, MaxLevel);//塔的最高等级

	Sprite* readyBullet;//在塔上显示一个已准备好的子弹贴图
	bool init();//初始化一个塔类（应该在地图单元响应塔的建造时触发
	void towerUpdate();//升级函数
	void towerSell();//出售函数（此二由菜单按钮调用
	void towerRemove();//删除当前塔，一般用于升级和出售时
	void mouseClick(Event* event);
	virtual void showMenuTower(Event* event);//显示升级出售等操作，因显示的图标不同故作为虚函数在每个塔文件中单独定义
	void hideMenuTower();//
	virtual BaseBullet* towerBullet();//得到一个当前的子弹
	bool Targeted(Event* event);
	BaseMonster* attackTarget;//一个敌人作为攻击目标
	void findEnemy();//寻敌
	void attack(float dt);//产生攻击弹道
	double tp[3][5] = { 0 };

	void setListener();//添加监听，响应鼠标点击
	bool isUpdateMenuShown;//标记菜单状态

	
	Sprite* spriteTower;//塔类贴图
};
#endif
