#include "BaseMonster.h"
#include"Monster1.h"
USING_NS_CC;



BaseMonster::BaseMonster()
{
	curHp = 0;
	maxHp = 0;
	speed = 0;
	baseSprite = NULL;
	state = noState;
	pointcnt = 0;              //Point������pointsVector[pointcnt]����ǰ����λ��
}


BaseMonster::~BaseMonster()
{
}


bool BaseMonster::init() {
	if (!Sprite::init()){
		return false;
	}
	
	return true;
}


void BaseMonster::move() {
	
	auto temcurpoint = curPoint();
	auto temnextpoint = nextPoint();
	if (temcurpoint != temnextpoint)         //���û���յ���ǰ����һ����
	{
		Point nowpoint = this->getPosition();          //���÷���
		if (temnextpoint.x > temcurpoint.x&&temnextpoint.x-temcurpoint.x>fabs(temnextpoint.y-temcurpoint.y)) {
			setState(walkRight);
		}
		else if(temnextpoint.x<temcurpoint.x&&temcurpoint.x-temnextpoint.x>fabs(temnextpoint.y-temcurpoint.y)){
			setState(walkLeft);
		}
		else if (temnextpoint.y > temcurpoint.y&&temnextpoint.y-temcurpoint.y>fabs(temnextpoint.x-temcurpoint.x)) {
			setState(walkUp);
		}
		else if(temnextpoint.y < temcurpoint.y&&temcurpoint.y-temnextpoint.y>fabs(temcurpoint.x-temcurpoint.x)) {
			setState(walkDown);
		}
		pointcnt++;
		auto dt = temcurpoint.getDistance(temnextpoint) / speed;
		this->runAction(Sequence::create(MoveTo::create(dt, temnextpoint)              //�ݵ��ù飬�ߵ�һ������ǰ����һ����
			, CallFuncN::create(CC_CALLBACK_0(BaseMonster::move, this))
			,NULL));
	}
	
}


Point BaseMonster::curPoint() {
	return pointsVector[pointcnt];
}

Point BaseMonster::nextPoint() {
	int tem = pointcnt;
	if (pointcnt < pointsVector.size() - 1){            //û���յ�
		return pointsVector[tem+ 1];
	}

	else {                                            //�ѵ��յ�
		return pointsVector[tem];
	}
}


Animation* BaseMonster::createMonsterAnimation(const char* str1,int start,int end) {                        
	
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	int i = start;
	for (i = start;i<=end;i++) {
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0%03d.png",str1, i)->getCString());
		if (frame != nullptr) {
			frameVec.pushBack(frame);
		}
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.04f);
	return animation;
}

void BaseMonster::stateUpdate(float dt) {

	getHurt(10);
	auto runUpAnimation = this->createMonsterAnimation(name, animationmark[0], animationmark[1]);             //����û��runleft����Դ����runright��setFlippedX����
	auto runUpAction = Animate::create(runUpAnimation);
	runUpAction->setTag(3);
	
	auto runRightAnimation = this->createMonsterAnimation(name, animationmark[2], animationmark[3]);
	auto runRightAction = Animate::create(runRightAnimation);
	runRightAction->setTag(2);
	
	auto runDownAnimation = this->createMonsterAnimation(name, animationmark[4], animationmark[5]);
	auto runDownAction = Animate::create(runDownAnimation);
	runDownAction->setTag(4);


	if (curPoint() == nextPoint()) {    //�ߵ��յ�ǰ��ʱcurPoint=nextPoint���÷���ʱ��Ҫ�ر���
		log("end");
		int tem = pointsVector.size();
		auto temcurpoint = pointsVector[tem-2];
		auto temnextpoint = pointsVector[tem-1];
		if (temnextpoint.x > temcurpoint.x&&temnextpoint.x - temcurpoint.x > fabs(temnextpoint.y - temcurpoint.y)) {
			setState(walkRight);
		}
		else if (temnextpoint.x<temcurpoint.x&&temcurpoint.x - temnextpoint.x>fabs(temnextpoint.y - temcurpoint.y)) {
			setState(walkLeft);
		}
		else if (temnextpoint.y > temcurpoint.y&&temnextpoint.y - temcurpoint.y > fabs(temnextpoint.x - temcurpoint.x)) {
			setState(walkUp);
		}
		else if (temnextpoint.y < temcurpoint.y&&temcurpoint.y - temnextpoint.y>fabs(temcurpoint.x - temcurpoint.x)) {
			setState(walkDown);
		}
		auto nowPosition = this->getPosition();             
		if (nowPosition.getDistance(temnextpoint) < 5.0f) {          //����Ч�����ԣ���ʽ�ӵ���Ϸ���ɾȥ
			getHurt(maxHp);
		}
	}


	baseSprite->setFlippedX(false);
	switch (state)
	{
	case noState:{
		break;
		}
	case walkRight: {
		stopMonsterAction();
		baseSprite->runAction(runRightAction);
		log("walkright");
	}  break;
	case walkLeft: {
		stopMonsterAction();
		baseSprite->runAction(runRightAction);
		baseSprite->setFlippedX(true);
		log("walkleft");
	}  break;
	case walkUp: {
		stopMonsterAction();
		baseSprite->runAction(runUpAction);
		log("walkup");
	}  break;
	case walkDown: {
		stopMonsterAction();
	    baseSprite->runAction(runDownAction);
		log("walkdown");
	}  break;

	case death: {
		baseSprite->stopAllActions();
		dead();
	}  break;

	}

	

}


void BaseMonster::stopMonsterAction() {
	baseSprite->stopActionByTag(2);
	baseSprite->stopActionByTag(3);
	baseSprite->stopActionByTag(4);
}


void BaseMonster::getHurt(int damage) {
	 //�յ�������ͨ�����㽫�˺�����damage
	curHp -= damage;
	float rate = float(float(curHp) / float(maxHp));
	float percent = rate*100.0f;
	hpBar->setPercentage(percent);
	if (curHp <= 0) {  //���hp<0��ִ����������
		setCurHp(0);
		setState(death);
	}
}


void BaseMonster::dead() {
	this->unschedule(schedule_selector(BaseMonster::stateUpdate));
	this->stopAllActions();             //��ֹ����
	auto temcurpoint = curPoint();
	auto temnextpoint = nextPoint();
	if (temnextpoint.x > temcurpoint.x) {
		baseSprite->setFlippedX(false);
	}
	else {
		baseSprite->setFlippedX(true);
	}
	float dt = 0.3f;
	auto deadAnimation = this->createMonsterAnimation(name, animationmark[6], animationmark[7]);
	deadAnimation->setLoops(1);
	deadAnimation->setDelayPerUnit(0.1f);
	auto deadAnimate = Animate::create(deadAnimation);
	baseSprite->runAction(Sequence::create(deadAnimate,CallFuncN::create( CC_CALLBACK_0(BaseMonster::disappear, this)), NULL));  //�Ȳ�������������Ȼ��setvisible
	//�����ڹ������п��Դ�����monstervector���ڹ��������󽫸�monster erase

}


void BaseMonster::disappear() {
	this->setVisible(false);
}

void BaseMonster::setHpBar() {
	hpbg = Sprite::create("hp_bg.png");
	hpbg->setScale(0.5f, 0.21f);
	hpbg->setPosition(0, baseSprite->getContentSize().height / 2 + 20);
	this->addChild(hpbg);
	auto hpPicture = Sprite::create("hpbar.png");
	hpBar = ProgressTimer::create(hpPicture);
	hpBar->setScale(0.5f, 0.25f);
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(100.0f);
	hpBar->setPosition(0, baseSprite->getContentSize().height/2+20);
	hpBar->setLocalZOrder(5);
	this->addChild(hpBar);
}

void BaseMonster::setzoredr() {
	auto point = pointsVector[0];
	baseSprite->setLocalZOrder((point.y / 10));
}