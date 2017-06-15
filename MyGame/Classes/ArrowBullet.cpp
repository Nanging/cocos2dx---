#include"ArrowBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool ArrowBullet::init(){
	if (!Sprite::init()){
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/arrowCrit.png");
	spriteBullet = Sprite::create("png/arrowNormal.png");//普通子弹
	hitBullet = TextureCache::getInstance()->addImage("png/arrowHit.png");//击中子弹
	addChild(spriteBullet);
	setBulletType(single);//单体伤害
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_ArrowHit2.wav");
	return true;
}