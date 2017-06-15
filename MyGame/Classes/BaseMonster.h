#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__
#include"cocos2d.h"
USING_NS_CC;
typedef enum {
	noState = 0,
	walkLeft=1,
	walkRight = 2,
	walkUp=3,
	walkDown = 4,
	hurt=5,
	death = 6
}MonsterState;

class BaseMonster :
	public Sprite
{
public:
	BaseMonster();
	virtual~BaseMonster();
	virtual bool init();
	CREATE_FUNC(BaseMonster);
	const char* name;        //名字

	CC_SYNTHESIZE(MonsterState, state, State);
	CC_SYNTHESIZE(int, curHp, CurHp);
	CC_SYNTHESIZE(int, maxHp, MaxHp);
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, armor, Armor);

	Sprite* baseSprite;
	ProgressTimer* hpBar;
	Sprite* hpbg;                  //血条底色
	unsigned int pointcnt;                                 
	std::vector<Point> pointsVector;                        //保存路径,pointsVector[pointcnt]即当前所在位置
	void isdead(float dt);
	bool isMoving;
	Point curPoint();
	Point nextPoint();
	virtual void move();                                           //寻路函数
	bool alive;
	void stateUpdate(float dt);
	Animation* createMonsterAnimation(const char* str1,int start,int end);  
	void stopMonsterAction();
	void getHurt(int damage);                               //传入伤害
	void dead();
	void disappear();
	void setHpBar();
	void setzoredr();                                     //再上面的怪物盖住下面的怪物

	std::vector<int> animationmark = { 0 };   //记录动画开始于结束帧 a[0]到a[7]分别是往上，往右，往下,死亡动画的开始帧和结束帧在plist文件中序号
	bool Arr;

};

#endif

