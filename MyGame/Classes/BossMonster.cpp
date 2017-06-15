#include "BossMonster.h"   
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;



BossMonster* BossMonster::createMonster(std::vector<Point> temPointsVector) {

	auto monster = new BossMonster();
	if (monster&&monster->init()) {
		monster->pointsVector = temPointsVector;
		monster->setPosition(temPointsVector[0]);
		monster->setzoredr();
		monster->move();
		monster->schedule(schedule_selector(BaseMonster::stateUpdate), 0.5f);
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}



BossMonster::BossMonster() :BaseMonster()
{

}


BossMonster::~BossMonster()
{
	
}

bool BossMonster::init() {
	if (!Sprite::init()) {
		return false;
	}


	animationmark = { 1,31,1,31,33,62,251,292 };
	name = "CanibalBoos";
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.25f));
	pointcnt = 0;
	setMaxHp(5000);
	setCurHp(5000);
	setHpBar();
	setArmor(200);
	setSpeed(30);
	setMoney(100);
	this->addChild(baseSprite);
	hpbg->setScale(2.0f, 0.76f);
	hpBar->setScale(2.0f, 0.8f);
	hpbg->setPosition(0, baseSprite->getContentSize().height / 2 + 40);
	hpBar->setPosition(0, baseSprite->getContentSize().height / 2 + 40);
	schedule(schedule_selector(BossMonster::tick), 3.0f);
	return true;
}

void BossMonster::tick(float delta)
{
	if (getCurHp() > 200)
	{
		SimpleAudioEngine::getInstance()->playEffect("wav/boss_efreeti_evillaugh.wav");
	}

}
void BossMonster::update(float delta)
{
	if (getCurHp() == 0)
	{
		SimpleAudioEngine::getInstance()->playEffect("wav/boss_efreeti_death.wav");
		unscheduleUpdate();
	}
}
