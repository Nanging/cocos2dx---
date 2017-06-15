#ifndef __CANNON_UP_ICON_H__
#define __CANNON_UP_ICON_H__
#include "cocos2d.h"
#include "BaseUpIcon.h"
USING_NS_CC;

class CannonUpIcon :
	public BaseUpIcon
{
public:
	CREATE_FUNC(CannonUpIcon);
	bool init();
	CannonUpIcon();
	virtual ~CannonUpIcon();
	void upForce();
	void upScope();
	void upSpeed();
	void setDes(int i);
	void reset();
	void mouseTip(EventMouse* e);
	void initIcon();
	int effect[2][5]={                             //a[0][i]��ʾ�����츳��i��ʱ��Ч����a[1][i]��ʾ�ٶ��츳��i��ʱ��Ч�� 
	             {0,10,30,60,100}
	             ,{0,10,30,60,100}
				 };
};
#endif //!__CANNON_UP_ICON_H__
