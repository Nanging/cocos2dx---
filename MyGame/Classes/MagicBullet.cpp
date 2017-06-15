#include"MagicBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool MagicBullet::init() {
	if (!Sprite::init()) {
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/magicCrit.png");
	spriteBullet = Sprite::create("png/magicNormal.png");//普通子弹
	hitBullet = TextureCache::getInstance()->addImage("png/magicHit.png");//击中子弹
	addChild(spriteBullet);
	setBulletType(single);//单体伤害
	SimpleAudioEngine::getInstance()->playEffect("wav/magic_attack.wav");
	return true;
}