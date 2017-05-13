#ifndef __BaseUpIcon_H__
#define __BaseUpIcon_H__
#include "cocos2d.h"
USING_NS_CC;

class BaseUpIcon :
	public Sprite
{
public:
	CREATE_FUNC(BaseUpIcon);
	virtual bool init();
	BaseUpIcon();
	virtual ~BaseUpIcon();
	virtual void upForce(){}
	virtual void upScope(){}
	virtual void upSpeed(){}
	virtual void setDes(int i){}
	virtual void reset(){}

	Label* des;           //��������
	MenuItemImage* forceIcon;    //����ͼ��
	MenuItemImage* scopeIcon;
	MenuItemImage* speedIcon;
	Sprite* kindSprite;         //���������ͼƬ 
	Label* briefDes;
	Sprite* bubble;

	int forceLevel;    //��Ӧ�츳�ȼ�
	int scopeLevel;
	int speedLevel;
	int price;

};
#endif

