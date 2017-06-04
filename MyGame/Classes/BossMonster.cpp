#include "BossMonster.h"   //由于素材中没有BOSS向上走的动画，在正式的游戏中，BOSS的路径只会有左右下三个方向（需选取适当的地图）





void BossMonster::move() {

	auto temcurpoint = curPoint();
	auto temnextpoint = nextPoint();
	if (temcurpoint != temnextpoint)         //如果没到终点则前往下一个点
	{
		Point nowpoint = this->getPosition();          //设置方向
		if (temnextpoint.x > temcurpoint.x&&temnextpoint.x - temcurpoint.x > fabs(temnextpoint.y - temcurpoint.y)) {
			setState(walkRight);
		}
		else if (temnextpoint.x<temcurpoint.x&&temcurpoint.x - temnextpoint.x>fabs(temnextpoint.y - temcurpoint.y)) {
			setState(walkLeft);
		}
		else if (temnextpoint.y > temcurpoint.y&&temnextpoint.y - temcurpoint.y > fabs(temnextpoint.x - temcurpoint.x)) {
			if (temnextpoint.x > temcurpoint.x) {
				setState(walkRight);
			}

			else {
				setState(walkLeft);
			}
		}
		else if (temnextpoint.y < temcurpoint.y&&temcurpoint.y - temnextpoint.y>fabs(temcurpoint.x - temcurpoint.x)) {
			setState(walkDown);
		}
		pointcnt++;
		auto dt = temcurpoint.getDistance(temnextpoint) / speed;
		this->runAction(Sequence::create(MoveTo::create(dt, temnextpoint)              //递调用归，走到一个点则前往下一个点
			, CallFuncN::create(CC_CALLBACK_0(BaseMonster::move, this))
			, NULL));
	}

}


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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level10-hd.plist", "sprite_level10-hd.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_0001.png", name)->getCString());
	baseSprite = Sprite::createWithSpriteFrame(frame);
	baseSprite->setAnchorPoint(Point(0.5f, 0.25f));
	pointcnt = 0;
	setMaxHp(4000);
	setCurHp(4000);
	setHpBar();
	setArmor(50);
	setSpeed(70);
	setMoney(1500);
	this->addChild(baseSprite);
	hpbg->setScale(2.0f, 0.76f);
	hpBar->setScale(2.0f, 0.8f);
	hpbg->setPosition(0, baseSprite->getContentSize().height / 2 + 40);
	hpBar->setPosition(0, baseSprite->getContentSize().height / 2 + 40);

	return true;
}

