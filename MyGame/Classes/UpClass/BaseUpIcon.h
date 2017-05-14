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

	Label* des;           //文字描述
	MenuItemImage* forceIcon;    //升级图标
	MenuItemImage* scopeIcon;
	MenuItemImage* speedIcon;
	Sprite* kindSprite;         //塔的种类的图片 
	Label* briefDes;
	Sprite* bubble;

	int forceLevel;    //相应天赋等级
	int scopeLevel;
	int speedLevel;
	int price;

};
#endif

