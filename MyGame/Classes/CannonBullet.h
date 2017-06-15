#ifndef _CANNON_BULLET_
#define _CANNON_BULLET_

#include"BaseBullet.h"

class CannonBullet :public BaseBullet {
public:
	virtual bool init();
	CREATE_FUNC(CannonBullet);
};
#endif