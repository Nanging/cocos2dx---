#ifndef __ArrayUpIcon_H__
#define __ArrayUpIcon_H__
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
	void mouseTip(Event* event);

};
#endif
