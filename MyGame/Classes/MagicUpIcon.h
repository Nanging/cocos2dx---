#ifndef __MAGIC_UP_ICON_H__
#define __MAGIC_UP_ICON_H__
#include "cocos2d.h"
#include "BaseUpIcon.h"
USING_NS_CC;

class MagicUpIcon :
	public BaseUpIcon
{
public:
	CREATE_FUNC(MagicUpIcon);
	bool init();
	MagicUpIcon();
	virtual ~MagicUpIcon();
	void upForce();
	void upScope();
	void upSpeed();
	void setDes(int i);             //������������
	void reset();
	void mouseTip(EventMouse* e);
	void initIcon();
	int effect[2][5]={                             //a[0][i]��ʾ�����츳��i��ʱ��Ч����a[1][i]��ʾ�ٶ��츳��i��ʱ��Ч�� 
	             {0,10,30,60,100}
	             ,{0,10,30,60,100}
				 };
};
#endif //!__MAGIC_UP_ICON_H__

