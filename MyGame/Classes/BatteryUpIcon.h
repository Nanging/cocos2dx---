#ifndef __BATTERY_UP_ICON_H__
#define __BATTERY_UP_ICON_H__
#include "cocos2d.h"
#include "BaseUpIcon.h"
USING_NS_CC;

class BatteryUpIcon :
	public BaseUpIcon
{
public:
	CREATE_FUNC(BatteryUpIcon);
	bool init();
	BatteryUpIcon();
	virtual ~BatteryUpIcon();
	void upForce();
	void upScope();
	void upSpeed();
	void setDes(int i);
	void reset();
	void mouseTip(EventMouse* e);
	void initIcon();
};
#endif //!__BATTERY_UP_ICON_H__
