#ifndef _BASE_TOWER_
#define _BASE_TOWER_
//����tower��Ӧ������Ϊ������ε�Ԫ��build block�����ӽڵ㣬������ε�ԪӦ���ǵ�ͼ�ϴ�������ӽڵ�

#include "cocos2d.h"
#include"BaseBullet.h"//�ӵ���
#include"BuildBlock.h"//��ͼ�ϵĿɽ�������
#include "BaseMonster.h"//������
#include"utiltool.h"

/*
enum Tower {
	MAGE=1,//Ĥ����
	CANNON,//����
	ARCHER,//����
};//����������
*/

class BaseTower :public cocos2d::Sprite {
public:
	CC_SYNTHESIZE(int, sellMoney, SellMoney);//���۷�����Ǯ
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, towerLevel, TowerLevel);//��ǰ�ȼ�
	CC_SYNTHESIZE(float, attackScope, AttackScope);//������Χ
	CC_SYNTHESIZE(float, nextAttackScope, NextAttackScope);//��ȷ������֮ǰ��ʾ��һ���Ĺ�����Χ
	CC_SYNTHESIZE(float, attackFrequency, AttackFrequency);//�����ٶ�
	CC_SYNTHESIZE(int, atkValue, AtkValue);//������(�����ӵ����˺�ֵ
	CC_SYNTHESIZE(Tower, towerType, TowerType);//���
	CC_SYNTHESIZE(int, crit, Crit);//������
	CC_SYNTHESIZE(BuildBlock*, spriteLocation, SpriteLocation);//���������ڵ�λ��
	CC_SYNTHESIZE(int, maxLevel, MaxLevel);//������ߵȼ�

	Sprite* readyBullet;//��������ʾһ����׼���õ��ӵ���ͼ
	bool init();//��ʼ��һ�����ࣨӦ���ڵ�ͼ��Ԫ��Ӧ���Ľ���ʱ����
	void towerUpdate();//��������
	void towerSell();//���ۺ������˶��ɲ˵���ť����
	void towerRemove();//ɾ����ǰ����һ�����������ͳ���ʱ
	void mouseClick(Event* event);
	virtual void showMenuTower(Event* event);//��ʾ�������۵Ȳ���������ʾ��ͼ�겻ͬ����Ϊ�麯����ÿ�����ļ��е�������
	void hideMenuTower();//
	virtual BaseBullet* towerBullet();//�õ�һ����ǰ���ӵ�
	bool Targeted(Event* event);
	BaseMonster* attackTarget;//һ��������Ϊ����Ŀ��
	void findEnemy();//Ѱ��
	void attack(float dt);//������������
	double tp[3][5] = { 0 };

	void setListener();//��Ӽ�������Ӧ�����
	bool isUpdateMenuShown;//��ǲ˵�״̬

	
	Sprite* spriteTower;//������ͼ
};
#endif
