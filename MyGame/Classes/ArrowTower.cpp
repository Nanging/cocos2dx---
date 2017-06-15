#include"ArrowTower.h"
#include"Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
void ArrowTower::initTower(int towerLevel){
	SimpleAudioEngine::getInstance()->playEffect("wav/Archer_Ready.wav");
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
	setTowerType(SPEED);
	spriteTower = Sprite::create(String::createWithFormat("png/arrowTower_%d.png", towerLevel)->getCString());//塔类贴图
	addChild(spriteTower);
	readyBullet = Sprite::create("png/arrowNormal.png");//在底座上创建一个子弹贴图
	addChild(readyBullet);
	readyBullet->setPosition(Point(0, 40));
	maxLevel = Player::getInstance()->getTechLevel(towerType, UpMaxLevel);//设置塔的最高等级
}

void ArrowTower::setTips() {//调用时需要已经设置当前等级
		auto player = Player::getInstance();
		auto forceLevel = player->getTechLevel(towerType, UpForce);
		auto speedLevel = player->getTechLevel(towerType, UpSpeed);

		setAtkValue(130*(towerLevel + 1) * tp[0][forceLevel] / 2);//根据天赋等级与塔的当前等级计算攻击力及攻击速度
		setAttackFrequency(1.2*(towerLevel + 1) * tp[1][speedLevel]/ 2);
}

BaseBullet* ArrowTower::towerBullet() {
	auto bullet = ArrowBullet::create();
	bullet->setRotation(0);//初始角度
	bullet->setMaxForce(getAtkValue());//根据塔的攻击力设置子弹伤害
	this->getParent()->addChild(bullet,20);//
	this->setPositionZ(60);
	return bullet;
}

