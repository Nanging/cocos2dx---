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
	spriteTower = Sprite::create(String::createWithFormat("png/arrowTower_%d.png", towerLevel)->getCString());//������ͼ
	addChild(spriteTower);
	readyBullet = Sprite::create("png/arrowNormal.png");//�ڵ����ϴ���һ���ӵ���ͼ
	addChild(readyBullet);
	readyBullet->setPosition(Point(0, 40));
	maxLevel = Player::getInstance()->getTechLevel(towerType, UpMaxLevel);//����������ߵȼ�
}

void ArrowTower::setTips() {//����ʱ��Ҫ�Ѿ����õ�ǰ�ȼ�
		auto player = Player::getInstance();
		auto forceLevel = player->getTechLevel(towerType, UpForce);
		auto speedLevel = player->getTechLevel(towerType, UpSpeed);

		setAtkValue(130*(towerLevel + 1) * tp[0][forceLevel] / 2);//�����츳�ȼ������ĵ�ǰ�ȼ����㹥�����������ٶ�
		setAttackFrequency(1.2*(towerLevel + 1) * tp[1][speedLevel]/ 2);
}

BaseBullet* ArrowTower::towerBullet() {
	auto bullet = ArrowBullet::create();
	bullet->setRotation(0);//��ʼ�Ƕ�
	bullet->setMaxForce(getAtkValue());//�������Ĺ����������ӵ��˺�
	this->getParent()->addChild(bullet,20);//
	this->setPositionZ(60);
	return bullet;
}

