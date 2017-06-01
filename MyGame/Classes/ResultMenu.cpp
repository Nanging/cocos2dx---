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
	score = 4;
	status = true;
	auto player = Player::getInstance();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	log("-%d-%d-%d-", player->saveStatus[1], player->saveStatus[2], player->saveStatus[3]);
	//if (player->current.life <= 0)
	//{
	//	status = false;
	//}
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
		auto paper = Sprite::create("paper.png");
		paper->setPosition(Vec2(size.width * 2 / 3, size.height / 2));
		paper->setScale(0.5f,0.8f);
		this->addChild(paper, 1);
		restartButton = MenuItemImage::create("stage_restart.png", "stage_restart.png", CC_CALLBACK_1(ResultMenu::restart, this));
		restartButton->setScale(0.5f);
		exitButton = MenuItemImage::create("stage_next.png", "stage_next.png", CC_CALLBACK_1(ResultMenu::quit, this));
		exitButton->setScale(0.4f);
		background = Sprite::create("pass.png");
		
		auto star = Sprite::create("star.png");
		//star->setSpriteFrame("");
		auto money = Sprite::create("money.png");
		auto life = Sprite::create("life.png");
		this->addChild(star, 2);
		this->addChild(money, 2);
		this->addChild(life, 2);
		life->setPosition(Vec2(size.width * 3 / 5, size.height *2/ 3));
		money->setPosition(Vec2(size.width * 3 / 5, size.height * 2 / 3 - life->getContentSize().height));
		star->setScale(1.2f);
		star->setPosition(Vec2(size.width * 3 / 5, size.height * 2 / 3 - 2.7 * life->getContentSize().height));

		
		auto player = Player::getInstance();
		auto lifeNumber = Label::createWithBMFont("Number_1.fnt", __String::createWithFormat("%d", player->current.life)->getCString());
		this->addChild(lifeNumber, 2);
		lifeNumber->setPosition(Vec2(size.width * 3 / 4, size.height * 2 / 3));

		auto moneyNumber = Label::createWithBMFont("Number_1.fnt", __String::createWithFormat("%d", player->current.totalMoney)->getCString());
		this->addChild(moneyNumber, 2);
		moneyNumber->setPosition(Vec2(size.width * 3 / 4, size.height * 2 / 3 - life->getContentSize().height));

		auto scoreLabel = Label::createWithSystemFont(__String::createWithFormat(" Score   :   %5d ", player->current.score)->getCString(), "arial", 30);
		scoreLabel->setPosition(Vec2(size.width * 2 / 3, size.height * 3 / 7));
		this->addChild(scoreLabel, 2);
		scoreLabel->setTextColor(Color4B::ORANGE);

		if (score == FullScore)
		{
			result = Sprite::create("prefect_victory.png");
			result->setScale(0.9f);
		}
		else
		{
			result = Sprite::create("victory.png");
		}
		result->setPosition(Vec2(size.width/3,size.height/2));
		this->addChild(result, 1);
	}
	else
	{
		background = Sprite::create("fail.png");
		restartButton = MenuItemImage::create("stage_try_again.png", "stage_try_again.png", CC_CALLBACK_1(ResultMenu::restart, this));	
		restartButton->setScale(0.4f);
		exitButton = MenuItemImage::create("stage_quit.png", "stage_quit.png", CC_CALLBACK_1(ResultMenu::quit, this));
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
	log("restart");
	auto player = Player::getInstance();
	auto scene = Game::createScene(player->current.currentStage);
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}
void ResultMenu::quit(Ref * psender)
{
	log("quit");
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
		//player->updateXML();
	}
}
void ResultMenu::effect(float dt)
{
	if (status)
	{
		SimpleAudioEngine::getInstance()->playEffect("Sound_VictoryCheer.wav");
		//int i = 0;
		//while (i<score)
		//{
		//	SimpleAudioEngine::getInstance()->playEffect("Sound_WinStars.wav");
		//	i++;
		//}
		
	}
	
}

