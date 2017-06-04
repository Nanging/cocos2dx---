#ifndef __BASE_UP_ICON_H__
#define __BASE_UP_ICON_H__
#include "cocos2d.h"
#include "Player.h"
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
	void getLevel(Tower n);
	void setLevel(Tower n);
	virtual void initIcon(){}

	Label* des;           //��������
	MenuItemImage* forceIcon;    //����ͼ��
	MenuItemImage* speedIcon;
	MenuItemImage* levelIcon;
	Sprite* kindSprite;         //���������ͼƬ 
	Label* briefDes;
	Sprite* bubble;

	int forceLevel;    //��Ӧ�츳�ȼ�
	int speedLevel;
	int MaxLevel;


};
#endif //!__BASE_UP_ICON_H__

