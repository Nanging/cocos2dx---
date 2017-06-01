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
		starSize = star->getContentSize();
		this->addChild(star, 3, i + 1);
		int k = i - 2;
		if (i < 2)
		{
			k = 2 - i;
		}
		star->setPosition(Vec2( (i - 2)*starSize.width, 0.8 * s.height - 0.5 * k * starSize.height));
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
		auto acNor = Sprite::create("pass_flag_normal.png");
		auto acSel = Sprite::create("pass_flag_selected.png");
		flag->setNormalImage(acNor);
		flag->setSelectedImage(acSel);
	}
	else if (score >= 0 && stage != current+1)
	{
		auto acNor = Sprite::create("fail_flag_normal.png");
		auto acSel = Sprite::create("fail_flag_seleted.png");
		flag->setNormalImage(acNor);
		flag->setSelectedImage(acSel);
	}
	Size s = flag->getContentSize();
	for (int i = 0; i < score; i++)
	{
		auto starGain = Sprite::create("gained_star.png");
		starGain->setScale(1.2f);
		this->removeChildByTag(i + 1);
		stars.replace(i, starGain);
		this->addChild(starGain, 3, i + 1);
		int k = i - 2;
		if (i < 2)
		{
			k = 2 - i;
		}
		starGain->setPosition(Vec2((i - 2)*starSize.width, 0.8 * s.height - 0.5 * k * starSize.height));
	}
}
void StageFlag::startStage(Ref* psender)
{
	log("---stage-%d---",stage);
	//auto flag = dynamic_cast<Node*>(psender);
	//flag->setVisible(false);
	auto scene = Game::createScene(stage);
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}