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
}//��������,�ڸ��ȼ���д

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
	static_cast<BuildBlock*>(this->getParent())->buildBlock->setVisible(true);//���ɽ���ĵ��ε�Ԫ��¶����
	Player::getInstance()->current.money += (getSellMoney());
	SimpleAudioEngine::getInstance()->playEffect("wav/Sound_TowerSell.wav");
	towerRemove();
}//���ۺ���

void BaseTower::showMenuTower(Event* event){
	if (Targeted(event)) {
		auto updateMenuLayer = UpdateMenu::create();
		updateMenuLayer->setTag(100);
		updateMenuLayer->setMyBlock(spriteLocation);
		updateMenuLayer->setTower(this);
		updateMenuLayer->setPosition(this->spriteLocation->getPosition());//����λ��
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

	auto monsterVector = stage->monsterVector;//��Ҫһ��������

	auto currMinDistant = this->attackScope*500/450;
	int size = monsterVector.size();
	BaseMonster* monsterTemp = NULL;//
	for (int i = 0; i < size; i++){//����monster vectorѰ�Ҿ��������
		auto monster = monsterVector.at(i);
		if (monster->getCurHp() > 0) {
			double distance = static_cast<BuildBlock*>(this->getParent())->getPosition().getDistance(monster->getPosition());//����������buildblock������ڵ�ͼ�ϵľ���
			if (distance < currMinDistant) {//�ҹ�����Χ�ھ�������ĵ���
				currMinDistant = distance;
				monsterTemp = monster;
			}
		}
	}
	attackTarget = monsterTemp;//�������Ϊ����Ŀ��
}//ÿ�ι���ʱ������

void BaseTower::setListener() {
	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(BaseTower::mouseClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}//��Ӽ�������Ӧ�����

void BaseTower::attack(float dt) {//��Ҫ��schedule�������Բ���dt
		findEnemy();//����Ѱ��
	if (attackTarget != NULL&&attackTarget->getCurHp()>0) {
		auto currBullet = towerBullet();//��ʼ��һ���ӵ�
		currBullet->setPosition(Point(0, 45));

		Point shootVector = attackTarget->getPosition() - this->getParent()->getPosition();//һ������ָ����˵����� 
		float startAngle = currBullet->getRotation();
		float endAngle = 0;
		auto pVectr = currBullet->getPosition() - shootVector;
		float angleRadians = atan(pVectr.y / pVectr.x);
		float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);

		if (shootVector.x - currBullet->getPosition().x <= 0) {//���󹥻�
			startAngle = startAngle + abs(angleDegrees);
			endAngle = -90;//�����Ƕ�
		}
		else {//����
			startAngle = startAngle - abs(angleDegrees);
			endAngle = 270;
		}
		//����
		ccBezierConfig bezier;
		//�������Ƶ�
		bezier.controlPoint_1 = Point(currBullet->getPosition().x, currBullet->getPosition().y + 200);
		bezier.controlPoint_2 = Point(shootVector.x, shootVector.y + 200);;
		bezier.endPosition = shootVector;
		auto action = Spawn::create(BezierTo::create(0.5f, bezier), RotateTo::create(0.5f, endAngle), NULL);
		//����һ�����������ߵĵ���

		currBullet->setIfCrit(false);//Ĭ��δ����
		srand((unsigned)time(NULL));//srand()��������һ���Ե�ǰʱ�俪ʼ��������ӣ��жϱ���
		int prob = rand() % 101;
		if (prob <= crit) {
			currBullet->setIfCrit(true);//����
		}

		currBullet->setBulletAction(action);//���������������ӵ�
		currBullet->setAttackTarget(attackTarget);
		currBullet->shoot();//�ӵ�ִ�й���
		currBullet = NULL;//�����ǰ�ӵ�
	}
}
//����Ĺ�����������ִ�У����������жϹ��������Լ�����һ�������ӵ�ִ�еĹ�������
BaseBullet* BaseTower::towerBullet() {
	return NULL;
}//���¼���д

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