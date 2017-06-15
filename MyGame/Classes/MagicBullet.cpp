#include"MagicBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool MagicBullet::init() {
	if (!Sprite::init()) {
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/magicCrit.png");
	spriteBullet = Sprite::create("png/magicNormal.png");//��ͨ�ӵ�
	hitBullet = TextureCache::getInstance()->addImage("png/magicHit.png");//�����ӵ�
	addChild(spriteBullet);
	setBulletType(single);//�����˺�
	SimpleAudioEngine::getInstance()->playEffect("wav/magic_attack.wav");
	return true;
}