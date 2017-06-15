#ifndef _ARROW_BULLET_
#define _ARROW_BULLET_

#include"BaseBullet.h"

class ArrowBullet :public BaseBullet {
public:
	virtual bool init();
	CREATE_FUNC(ArrowBullet);
};
#endif