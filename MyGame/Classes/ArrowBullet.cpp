#include"ArrowBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool ArrowBullet::init(){
	if (!Sprite::init()){
		return false;
	}
	critBullet = TextureCache::getInstance()->addImage("png/arrowCrit.png");
	spriteBullet = Sprite::create("png/arrowNormal.png");//��ͨ�ӵ�
	hitBullet = TextureCache::getInstance()->addImage("png/arrowHit.png");//�����ӵ�
	addChild(spriteBullet);
	setBulletType(single);//�����˺�
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_ArrowHit2.wav");
	return true;
}