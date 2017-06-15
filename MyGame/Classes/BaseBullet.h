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
	CC_SYNTHESIZE(int, maxForce, MaxForce);//�˺���ֵ
	CC_SYNTHESIZE(BulletType, bulletType, BulletType);//�����ӵ��˺���Χ�������aoe
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//����һ����������
	CC_SYNTHESIZE(bool, ifCrit, IfCrit);//�Ƿ񱩻�
	CC_SYNTHESIZE(BaseMonster*, attackTarget, AttackTarget);
	Sprite* spriteBullet;//�ӵ���ͼ
	Texture2D* critBullet;//�����ӵ���ͼ
	Texture2D* hitBullet;//�ӵ�������ͼ
	virtual void shoot();//ִ�й�������
	virtual void removeBullet();//�����������������ǰ�ӵ��������˺�
};
#endif