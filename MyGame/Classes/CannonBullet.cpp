#include"CannonBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool CannonBullet::init() {
	if (!Sprite::init()) {
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/cannonCrit.png");
	spriteBullet = Sprite::create("png/cannonNormal.png");//普通子弹
	hitBullet = TextureCache::getInstance()->addImage("png/cannonHit.png");//击中子弹
	addChild(spriteBullet);
	setBulletType(aoe);//单体伤害
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_Bomb1.wav");
	return true;
}