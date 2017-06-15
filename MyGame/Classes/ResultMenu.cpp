#include "ResultMenu.h"
#include "Game.h"
#include "Player.h"
#include "MainMap.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
const int FullScore = 5;
ResultMenu::ResultMenu()
{
}


ResultMenu::~ResultMenu()
{

}
Scene *ResultMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = ResultMenu::create();
	scene->setTag(TAG_SCENE);
	scene->addChild(layer, 0, TAG_RESULT);
	return scene;
}
bool ResultMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	score = 0;
	status = true;
	auto player = Player::getInstance();
	int stage = player->current.currentStage;
	int totalmoney = player->current.totalMoney;
	int leftmoney = player->current.money;
	int life = player->current.life;
	player->current.score = totalmoney - InitialMoney * stage + leftmoney * 2;
	if (player->current.score > stage * 250)
	{
		score+=2;
	}
	if (life > 0)
	{
		score += 2;
		if (life > 9)
		{
			score++;
		}
	}
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	if (life <= 0)
	{
		status = false;
	}
	updateResult();
	initBack();
	scheduleOnce(schedule_selector(ResultMenu::effect),1.0f);
	return true;
}
void ResultMenu::initBack()
{
	Size size = UtilTool::getSize();
	if (status)
	{
		auto player = Player::getInstance();
		if (player->getScore() < score)
		{
			player->setScore(player->currentSave, player->current.currentStage, score);
		}
		if (player->getStage() + 1 == player->current.currentStage)
		{
			player->setStage(player->currentSave, player->current.currentStage);
		}

		player->updateXML();
		auto paper = Sprite::create("png/paper.png");
		paper->setPosition(Vec2(size.width * 2 / 3, size.height / 2));
		paper->setScale(0.5f,0.8f);
		this->addChild(paper, 1);
		restartButton = MenuItemImage::create("png/stage_restart.png", "png/stage_restart.png", CC_CALLBACK_1(ResultMenu::restart, this));
		restartButton->setScale(0.5f);
		exitButton = MenuItemImage::create("png/stage_next.png", "png/stage_next.png", CC_CALLBACK_1(ResultMenu::quit, this));
		exitButton->setScale(0.4f);
		background = Sprite::create("png/pass.png");
		
		auto star = Sprite::create("png/star.png");
		auto money = Sprite::create("png/money.png");
		auto life = Sprite::create("png/life.png");
		this->addChild(star, 2);
		this->addChild(money, 2);
		this->addChild(life, 2);
		life->setPosition(Vec2(size.width * 3 / 5, size.height *2/ 3));
		money->setPosition(Vec2(size.width * 3 / 5, size.height * 2 / 3 - life->getContentSize().height));
		star->setScale(1.2f);
		star->setPosition(Vec2(size.width * 3 / 5, size.height * 2 / 3 - 2.7 * life->getContentSize().height));

		auto lifeNumber = Label::createWithBMFont("fonts/Number_1.fnt", __String::createWithFormat("%d", player->current.life)->getCString());
		this->addChild(lifeNumber, 2);
		lifeNumber->setPosition(Vec2(size.width * 3 / 4, size.height * 2 / 3));

		auto moneyNumber = Label::createWithBMFont("fonts/Number_1.fnt", __String::createWithFormat("%d", player->current.money)->getCString());
		this->addChild(moneyNumber, 2);
		moneyNumber->setPosition(Vec2(size.width * 3 / 4, size.height * 2 / 3 - life->getContentSize().height));

		auto scoreLabel = Label::createWithSystemFont(__String::createWithFormat(" Score   :   %5d ", player->current.score)->getCString(), "arial", 30);
		scoreLabel->setPosition(Vec2(size.width * 2 / 3, size.height * 3 / 7));
		this->addChild(scoreLabel, 2);
		scoreLabel->setTextColor(Color4B::ORANGE);
		
		auto starLabel = Label::createWithBMFont("fonts/Number_1.fnt", __String::createWithFormat("%d", score)->getCString());
		starLabel->setPosition(Vec2(size.width * 3 / 4, size.height * 2 / 3 - 2.7 * life->getContentSize().height));
		this->addChild(starLabel,2);
		if (score == FullScore)
		{
			result = Sprite::create("png/prefect_victory.png");
			result->setScale(0.9f);
		}
		else
		{
			result = Sprite::create("png/victory.png");
		}
		result->setPosition(Vec2(size.width/3,size.height/2));
		this->addChild(result, 1);
	}
	else
	{
		background = Sprite::create("png/fail.png");
		restartButton = MenuItemImage::create("png/stage_try_again.png", "png/stage_try_again.png", CC_CALLBACK_1(ResultMenu::restart, this));	
		restartButton->setScale(0.4f);
		exitButton = MenuItemImage::create("png/stage_quit.png", "png/stage_quit.png", CC_CALLBACK_1(ResultMenu::quit, this));
		exitButton->setScale(0.5f);
	}
	restartButton->setPosition(Vec2(size.width / 3, size.height/17));
	exitButton->setPosition(Vec2(size.width * 2 / 3, size.height/17));
	auto menu = Menu::create(restartButton, exitButton, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu, 0);
	background->setScale(size.width / background->getContentSize().width, size.height / background->getContentSize().height);
	background->setPosition(size.width / 2, size.height / 2);
	this->addChild(background, -1);
}
void ResultMenu::restart(Ref * psender)
{
	auto player = Player::getInstance();
	auto scene = Game::createScene(player->current.currentStage);
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}
void ResultMenu::quit(Ref * psender)
{
	auto player = Player::getInstance();
	player->updateXML();
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}
void ResultMenu::updateResult()
{
	if (status)
	{
		auto player = Player::getInstance();
		int saveNumber = player->currentSave;
		auto initialScore = player->getScore(saveNumber, player->current.currentStage);
		if (score > initialScore)
		{
			player->setScore(saveNumber, player->current.currentStage, score);
		}
		player->updateXML();
	}
}
void ResultMenu::effect(float dt)
{
	if (status)
	{
		SimpleAudioEngine::getInstance()->playEffect("wav/Sound_VictoryCheer.wav");	
	}
	
}

