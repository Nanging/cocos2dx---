#ifndef __ARROW_UP_ICON_H__
#define __ARROW_UP_ICON_H__
#include "cocos2d.h"
#include "BaseUpIcon.h"
USING_NS_CC;

class ArrowUpIcon :
	public BaseUpIcon
{
public:
	CREATE_FUNC(ArrowUpIcon);
	bool init();
	ArrowUpIcon();
	virtual ~ArrowUpIcon();
	void upForce();
	void upScope();
	void upSpeed();
	void setDes(int i);
	void reset();
	void mouseTip(EventMouse* e);
	void initIcon();
	int effect[2][5]={                             //a[0][i]表示力量天赋在i级时的效果，a[1][i]表示速度天赋在i级时的效果 
	             {0,10,30,60,100}
	             ,{0,10,30,60,100}
				 };

};
#endif //!__ARROW_UP_ICON_H__
