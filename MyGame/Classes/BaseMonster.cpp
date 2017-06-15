#include "BaseMonster.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;



BaseMonster::BaseMonster()
{
	curHp = 0;
	maxHp = 0;
	speed = 0;
	baseSprite = NULL;
	state = noState;
	pointcnt = 0;              //Point计数，pointsVector[pointcnt]即当前所在位置
}


BaseMonster::~BaseMonster()
{
}


bool BaseMonster::init() {
	if (!Sprite::init()){
		return false;
	}
	alive = true;
	isMoving = true;
	return true;
}


void BaseMonster::move() {
	
	auto temcurpoint = curPoint();
	auto temnextpoint = nextPoint();
	if (temcurpoint != temnextpoint)         //如果没到终点则前往下一个点
	{
		Point nowpoint = this->getPosition();          //设置方向
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
		this->runAction(Sequence::create(MoveTo::create(dt, temnextpoint)              //递调用归，走到一个点则前往下一个点
			, CallFuncN::create(CC_CALLBACK_0(BaseMonster::move, this))
			,NULL));
	}
	
}


Point BaseMonster::curPoint() {
	return pointsVector[pointcnt];
}

Point BaseMonster::nextPoint() {
	int tem = pointcnt;
	if (pointcnt < pointsVector.size() - 1){            //没到终点
		return pointsVector[tem + 1];
	}
	else {                  
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

	auto runUpAnimation = this->createMonsterAnimation(name, animationmark[0], animationmark[1]);             //由于没有runleft的资源，用runright后setFlippedX代替
	auto runUpAction = Animate::create(runUpAnimation);
	runUpAction->setTag(3);
	
	auto runRightAnimation = this->createMonsterAnimation(name, animationmark[2], animationmark[3]);
	auto runRightAction = Animate::create(runRightAnimation);
	runRightAction->setTag(2);
	
	auto runDownAnimation = this->createMonsterAnimation(name, animationmark[4], animationmark[5]);
	auto runDownAction = Animate::create(runDownAnimation);
	runDownAction->setTag(4);


	if (curPoint() == nextPoint()) {    //走到终点前此时curPoint=nextPoint设置方向时需要特别处理
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
		if (nowPosition.getDistance(temnextpoint) < 5.0f) {          //死亡效果测试，正式加到游戏里后删去
			auto player = Player::getInstance();
			if (isMoving &&player->current.life > 0)
			{
				SimpleAudioEngine::getInstance()->playEffect("wav/Sound_LooseLife.wav");
				player->current.life--;
				isMoving = false;
			}
			disappear();
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
	}  break;
	case walkLeft: {
		stopMonsterAction();
		baseSprite->runAction(runRightAction);
		baseSprite->setFlippedX(true);
	}  break;
	case walkUp: {
		stopMonsterAction();
		baseSprite->runAction(runUpAction);
	}  break;
	case walkDown: {
		stopMonsterAction();
	    baseSprite->runAction(runDownAction);
	}  break;

	case death: {
		baseSprite->stopAllActions();
		dead();
	}  break;

	}

	

}
void BaseMonster::isdead(float dt)
{
	if (curHp <= 0)
	{
		alive = false;
	}
	if (alive == false)
	{
		setState(death);
		baseSprite->stopAllActions();
		dead();
	}

}

void BaseMonster::stopMonsterAction() {
	baseSprite->stopActionByTag(2);
	baseSprite->stopActionByTag(3);
	baseSprite->stopActionByTag(4);
}


void BaseMonster::getHurt(int damage) {
	 //收到攻击后通过计算将伤害传给damage
	if (damage < 0)
	{
		return;
	}
	curHp -= damage;
	float rate = float(float(curHp) / float(maxHp));
	float percent = rate*100.0f;
	hpBar->setPercentage(percent);
	if (curHp <= 0) {  //如果hp<0则执行死亡函数
		setCurHp(0);
		setState(death);
		baseSprite->stopAllActions();
		dead();
	}
}


void BaseMonster::dead() {
	Player::getInstance()->current.money += money;
	Player::getInstance()->current.totalMoney += money;
	SimpleAudioEngine::getInstance()->playEffect("wav/inapp_cash.wav");
	this->unschedule(schedule_selector(BaseMonster::stateUpdate));
	this->stopAllActions();             //防止滑步
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
	baseSprite->runAction(Sequence::create(deadAnimate,CallFuncN::create( CC_CALLBACK_0(BaseMonster::disappear, this)), NULL));  //先播放死亡动画，然后setvisible
	//可以在管理类中可以创建个monstervector，在怪物死亡后将该monster erase

}


void BaseMonster::disappear() {
	isMoving = false;
	this->removeFromParentAndCleanup(true);
	this->setVisible(false);
}

void BaseMonster::setHpBar() {
	hpbg = Sprite::create("png/hp_bg.png");
	hpbg->setScale(0.5f, 0.21f);
	hpbg->setPosition(0, baseSprite->getContentSize().height / 2 + 20);
	this->addChild(hpbg);
	auto hpPicture = Sprite::create("png/hpbar.png");
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