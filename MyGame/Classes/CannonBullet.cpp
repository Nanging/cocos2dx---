#include"CannonBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool CannonBullet::init() {
	if (!Sprite::init()) {
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/cannonCrit.png");
	spriteBullet = Sprite::create("png/cannonNormal.png");//��ͨ�ӵ�
	hitBullet = TextureCache::getInstance()->addImage("png/cannonHit.png");//�����ӵ�
	addChild(spriteBullet);
	setBulletType(aoe);//�����˺�
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_Bomb1.wav");
	return true;
}