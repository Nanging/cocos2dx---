#ifndef __MagicUpIcon_H__
#define __MagicUpIcon_H__
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
	void setDes(int i);             //…Ë÷√Œƒ◊÷√Ë ˆ
	void reset();
	void mouseTip(Event* event);

};
#endif

