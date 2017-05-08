#include "StageFlag.h"
#include "Player.h"
#include "StartGame.h"
#include "TransitionGame.h"
#include "Game.h"
StageFlag::StageFlag()
{
	log("---Flag-Up---");
}


StageFlag::~StageFlag()
{
	log("---Flag-Down---");
}
StageFlag* StageFlag::create(int num)
{
	auto stageflag = new StageFlag();
	if (stageflag && stageflag->init(num))
	{
		stageflag->autorelease();
		return stageflag;
	}
	CC_SAFE_DELETE(stageflag);
	stageflag = nullptr;
	return nullptr;
}
bool StageFlag::init(int num)
{
	if (!Sprite::init())
	{
		return false;
	}
	stage = num;
	flag = MenuItemImage::create("flag.png", "flag_seleted.png",CC_CALLBACK_1(StageFlag::startStage,this));
	auto botton = Menu::createWithItem(flag);
	botton->setPosition(Vec2(0,0));
	//auto move = MoveBy::create(1,Vec2(200, 0));
	//auto re = RepeatForever::create(Sequence::create(move, move->reverse(), NULL));	flag->runAction(re);
	this->addChild(botton, 1);

	Size s = flag->getContentSize();
	for (int i = 0; i < MaxScore; i++)
	{
		auto star = Sprite::create("missed_star.png");
		star_size = star->getContentSize();
		this->addChild(star, 3, i + 1);
		int k = i - 2;
		if (i < 2)
		{
			k = 2 - i;
		}
		star->setPosition(Vec2( (i - 2)*star_size.width, 0.8 * s.height - 0.5 * k * star_size.height));
		stars.pushBack(star);
	}
	initStars();
	return true;
}
void StageFlag::initStars()
{
	auto player = Player::getInstance();
	int save = player->currentSave;
	int current = player->getStage();
	int score = player->getScore(save, stage);
	log("---Flag---%d---cur--%d--", score,current);
	if (score == MaxScore)
	{
		auto ac_nor = Sprite::create("pass_flag_normal.png");
		auto ac_sel = Sprite::create("pass_flag_selected.png");
		flag->setNormalImage(ac_nor);
		flag->setSelectedImage(ac_sel);
	}
	else if (score >= 0 && stage != current+1)
	{
		auto ac_nor = Sprite::create("fail_flag_normal.png");
		auto ac_sel = Sprite::create("fail_flag_seleted.png");
		flag->setNormalImage(ac_nor);
		flag->setSelectedImage(ac_sel);
	}
	Size s = flag->getContentSize();
	for (int i = 0; i < score; i++)
	{
		auto star_gain = Sprite::create("gained_star.png");
		star_gain->setScale(1.2f);
		this->removeChildByTag(i + 1);
		stars.replace(i, star_gain);
		this->addChild(star_gain, 3, i + 1);
		int k = i - 2;
		if (i < 2)
		{
			k = 2 - i;
		}
		star_gain->setPosition(Vec2((i - 2)*star_size.width, 0.8 * s.height - 0.5 * k * star_size.height));
	}
}
void StageFlag::startStage(Ref* psender)
{
	log("---stage-%d---",stage);
	//auto flag = dynamic_cast<Node*>(psender);
	//flag->setVisible(false);
	auto s = Game::createScene(stage);
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, s));
}