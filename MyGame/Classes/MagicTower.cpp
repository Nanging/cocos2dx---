#include"MagicTower.h"
#include"Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
void MagicTower::initTower(int towerLevel) {
	SimpleAudioEngine::getInstance()->playEffect("wav/Mage_Ready.wav");
	tp[0][0] = 1.0;
	tp[0][1] = 1.1;
	tp[0][2] = 1.2;
	tp[0][3] = 1.3;
	tp[0][4] = 1.4;//power
	tp[1][0] = 1.0;
	tp[1][1] = 1.1;
	tp[1][2] = 1.2;
	tp[1][3] = 1.3;
	tp[1][4] = 1.4;//speed
	tp[2][0] = 1;
	tp[2][1] = 2;
	tp[2][2] = 3;
	tp[2][3] = 4;
	tp[2][4] = 0;//maxLevel
	setTowerType(MAGIC);
	spriteTower = Sprite::create(String::createWithFormat("png/magicTower_%d.png", towerLevel)->getCString());
	addChild(spriteTower);
	readyBullet = Sprite::create("png/magicNormal.png");
	addChild(readyBullet);
	readyBullet->setPosition(Point(2, 35));
	maxLevel = Player::getInstance()->getTechLevel(towerType, UpMaxLevel);
}

void MagicTower::setTips() {
		auto player = Player::getInstance();
		auto forceLevel = player->getTechLevel(towerType, UpForce);
		auto speedLevel = player->getTechLevel(towerType, UpSpeed);

		setAtkValue(200 *towerLevel*tp[0][forceLevel]);
		setAttackFrequency(0.8 *(towerLevel + 1)*tp[1][speedLevel] / 2);
}

BaseBullet* MagicTower::towerBullet() {
	auto bullet = MagicBullet::create();
	bullet->setRotation(0);
	bullet->setMaxForce(getAtkValue());
	this->getParent()->addChild(bullet,20);
	this->setPositionZ(60);
	return bullet;
}