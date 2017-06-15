#ifndef _TOWER_ICON_H_
#define _TOWER_ICON_H_

#include "cocos2d.h"


USING_NS_CC;

class TowerIcon : public Sprite
{
public:
	virtual bool initIcon(int type, int money);
	static TowerIcon* createIcon(int type, int money);
	CREATE_FUNC(TowerIcon);
	void setSelected();
	virtual void setNotSelected();
	virtual void setNotEnoughMoney();
	virtual void setEnoughMoney();
	Sprite* towerIcon;
private:
	CC_SYNTHESIZE(bool, isAble, IsAble);
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(bool, isSelected, IsSelected);
	CC_SYNTHESIZE(int, money, Money);
	void update(float dt);//不断更新获取当前金钱数并改变按钮状态
	Sprite* okIcon;
	Sprite* priceIcon;
	Label* priceLabel;
};

#endif