#ifndef _BASE_BULLET_
#define _BASE_BULLET_
#include"cocos2d.h"
#include"BaseMonster.h"

USING_NS_CC;
enum BulletType {
	single,
	aoe
};
class BaseBullet :public Sprite{
public:
	BaseBullet::BaseBullet() :spriteBullet(NULL), maxForce(0), ifCrit(false){};
	virtual bool init();
	CREATE_FUNC(BaseBullet);
protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);//伤害数值
	CC_SYNTHESIZE(BulletType, bulletType, BulletType);//塔的子弹伤害范围（单体或aoe
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//接受一个攻击动作
	CC_SYNTHESIZE(bool, ifCrit, IfCrit);//是否暴击
	CC_SYNTHESIZE(BaseMonster*, attackTarget, AttackTarget);
	Sprite* spriteBullet;//子弹贴图
	Texture2D* critBullet;//暴击子弹贴图
	Texture2D* hitBullet;//子弹击中贴图
	virtual void shoot();//执行攻击动作
	virtual void removeBullet();//攻击结束调用清除当前子弹并结算伤害
};
#endif