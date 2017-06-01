#ifndef __ARRAY_UP_ICON_H__
#define __ARRAY_UP_ICON_H__
#include "cocos2d.h"
#include "BaseUpIcon.h"
USING_NS_CC;

class ArrayUpIcon :
	public BaseUpIcon
{
public:
	CREATE_FUNC(ArrayUpIcon);
	bool init();
	ArrayUpIcon();
	virtual ~ArrayUpIcon();
	void upForce();
	void upScope();
	void upSpeed();
	void setDes(int i);
	void reset();
	void mouseTip(EventMouse* e);
	void initIcon();

};
#endif //!__ARRAY_UP_ICON_H__
