#include "ScopeCircle.h"

bool ScopeCircle::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	auto scopeCircle_1 = Sprite::create("png/circleIcon.png");
	auto scopeCircle_2 = Sprite::create("png/circleIcon.png");
	auto scopeCircle_3 = Sprite::create("png/circleIcon.png");
	auto scopeCircle_4 = Sprite::create("png/circleIcon.png");
	scopeCircle_1->setAnchorPoint(Point(1, 0));

	scopeCircle_1->setScaleX(1.1f);
	scopeCircle_2->setScaleX(1.1f);
	scopeCircle_3->setScaleX(1.1f);
	scopeCircle_4->setScaleX(1.1f);//显得略微扁平一点

	scopeCircle_2->setFlippedX(true);
	scopeCircle_2->setAnchorPoint(Point(0, 0));
	scopeCircle_3->setFlippedX(true);
	scopeCircle_3->setFlippedY(true);
	scopeCircle_3->setAnchorPoint(Point(0, 1));
	scopeCircle_4->setFlippedY(true);
	scopeCircle_4->setAnchorPoint(Point(1, 1));
	addChild(scopeCircle_1);
	addChild(scopeCircle_2);
	addChild(scopeCircle_3);
	addChild(scopeCircle_4);
	return true;
}