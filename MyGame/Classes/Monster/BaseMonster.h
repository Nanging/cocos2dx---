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

	const char* name;        //����

	CC_SYNTHESIZE(MonsterState, state, State);
	CC_SYNTHESIZE(int, curHp, CurHp);
	CC_SYNTHESIZE(int, maxHp, MaxHp);
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, armor, Armor);

	Sprite* baseSprite;
	ProgressTimer* hpBar;
	Sprite* hpbg;                  //Ѫ����ɫ
	unsigned int pointcnt;                                 
	std::vector<Point> pointsVector;                        //����·��,pointsVector[pointcnt]����ǰ����λ��


	Point curPoint();
	Point nextPoint();
	virtual void move();                                           //Ѱ·����

	void stateUpdate(float dt);
	Animation* createMonsterAnimation(const char* str1,int start,int end);  
	void stopMonsterAction();
	void getHurt(int damage);                               //�����˺�
	void dead();
	void disappear();
	void setHpBar();
	void setzoredr();                                     //������Ĺ����ס����Ĺ���

	std::vector<int> animationmark = { 0 };   //��¼������ʼ�ڽ���֡ a[0]��a[7]�ֱ������ϣ����ң�����,���������Ŀ�ʼ֡�ͽ���֡��plist�ļ������


};

#endif

