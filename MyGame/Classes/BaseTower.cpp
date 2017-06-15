#include "BaseTower.h"
#include "Player.h"
#include "BaseMonster.h"
#include"UpdateMenuLayer.h"
#include "BaseStage.h"
#include"ScopeCircle.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

void BaseTower::towerUpdate() 
{
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_TowerUpgrade.wav");
}//升级函数,在各等级重写

bool BaseTower::init() {
	if (!Sprite::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_TowerBuilding.wav");
	isUpdateMenuShown = false;
	return true;
}

void BaseTower::towerSell() {
	static_cast<BuildBlock*>(this->getParent())->buildBlock->setVisible(true);//将可建造的地形单元裸露出来
	Player::getInstance()->current.money += (getSellMoney());
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_TowerSell.wav");
	towerRemove();
}//出售函数

void BaseTower::showMenuTower(Event* event){
	if (Targeted(event)) {
		auto updateMenuLayer = UpdateMenu::create();
		updateMenuLayer->setTag(100);
		updateMenuLayer->setMyBlock(spriteLocation);
		updateMenuLayer->setTower(this);
		updateMenuLayer->setPosition(this->spriteLocation->getPosition());//建造位置
		(this->getParent()->getParent())->addChild(updateMenuLayer, 100, 100);
		updateMenuLayer->inAnimation();
		isUpdateMenuShown = true;
	}
}

void BaseTower::hideMenuTower() {
		this->getParent()->getParent()->removeChildByTag(100);//update menu
		isUpdateMenuShown = false;
		setVisible(true);
}

void BaseTower::towerRemove(){
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	this->removeFromParent();

}

void BaseTower::findEnemy() {
	auto stage = dynamic_cast<BaseStage*>(UtilTool::getLayerByTag(TAG_STAGE));
	if (stage == nullptr)
	{
		return;
	}

	auto monsterVector = stage->monsterVector;//需要一个敌人组

	auto currMinDistant = this->attackScope*500/450;
	int size = monsterVector.size();
	BaseMonster* monsterTemp = NULL;//
	for (int i = 0; i < size; i++){//遍历monster vector寻找距离最近的
		auto monster = monsterVector.at(i);
		if (monster->getCurHp() > 0) {
			double distance = static_cast<BuildBlock*>(this->getParent())->getPosition().getDistance(monster->getPosition());//计算所处的buildblock与敌人在地图上的距离
			if (distance < currMinDistant) {//找攻击范围内距离最近的敌人
				currMinDistant = distance;
				monsterTemp = monster;
			}
		}
	}
	attackTarget = monsterTemp;//最近敌人为攻击目标
}//每次攻击时都调用

void BaseTower::setListener() {
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(BaseTower::mouseClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}//添加监听，响应鼠标点击

void BaseTower::attack(float dt) {//需要被schedule调用所以参数dt
		findEnemy();//重新寻敌
	if (attackTarget != NULL&&attackTarget->getCurHp()>0) {
		auto currBullet = towerBullet();//初始化一个子弹
		currBullet->setPosition(Point(0, 45));

		Point shootVector = attackTarget->getPosition() - this->getParent()->getPosition();//一个从塔指向敌人的向量 
		float startAngle = currBullet->getRotation();
		float endAngle = 0;
		auto pVectr = currBullet->getPosition() - shootVector;
		float angleRadians = atan(pVectr.y / pVectr.x);
		float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);

		if (shootVector.x - currBullet->getPosition().x <= 0) {//向左攻击
			startAngle = startAngle + abs(angleDegrees);
			endAngle = -90;//结束角度
		}
		else {//向右
			startAngle = startAngle - abs(angleDegrees);
			endAngle = 270;
		}
		//弧线
		ccBezierConfig bezier;
		//两个控制点
		bezier.controlPoint_1 = Point(currBullet->getPosition().x, currBullet->getPosition().y + 200);
		bezier.controlPoint_2 = Point(shootVector.x, shootVector.y + 200);;
		bezier.endPosition = shootVector;
		auto action = Spawn::create(BezierTo::create(0.5f, bezier), RotateTo::create(0.5f, endAngle), NULL);
		//生成一个贝塞尔曲线的弹道

		currBullet->setIfCrit(false);//默认未暴击
		srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子，判断暴击
		int prob = rand() % 101;
		if (prob <= crit) {
			currBullet->setIfCrit(true);//暴击
		}

		currBullet->setBulletAction(action);//将攻击动作传给子弹
		currBullet->setAttackTarget(attackTarget);
		currBullet->shoot();//子弹执行攻击
		currBullet = NULL;//清除当前子弹
	}
}
//这里的攻击函数由塔执行，作用在于判断攻击对象以及生成一个交由子弹执行的攻击动画
BaseBullet* BaseTower::towerBullet() {
	return NULL;
}//最下级重写

bool BaseTower::Targeted(Event* event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	auto rect = spriteTower->getBoundingBox();
	EventMouse* e = (EventMouse*)event;
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	Point position = Point(cursorX, cursorY);
	Point locationInNode = target->convertToNodeSpace(position);
	if (rect.containsPoint(locationInNode))
		return true;
	else
		return false;
}

void BaseTower::mouseClick(Event* event) {
	if (isUpdateMenuShown) {
		hideMenuTower();
	}
	else
		showMenuTower(event);
}