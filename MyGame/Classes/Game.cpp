#include "Game.h"
#include "Player.h"
#include "HudGameView.h"
#include "MainMap.h"
#include "StageOne.h"
#include "ResultMenu.h"
#include "WaveFlag.h"
#include "SimpleAudioEngine.h"
#include "StageTwo.h"
#include "StageThree.h"
using namespace  CocosDenshion;
HudGameView* Hud = nullptr;
int count = 0;
Game::Game()
{
}

Game::~Game()
{
}
Scene * Game::createScene(int num)
{
	auto scene = Scene::create();
	scene->setTag(TAG_SCENE);
	auto player = Player::getInstance();
	if (num == 1)
	{
		auto maplayer = StageOne::create();
		scene->addChild(maplayer, -1, TAG_STAGE);
	}
	else if (num == 2)
	{
		auto maplayer = StageTwo::create();
		scene->addChild(maplayer, -1, TAG_STAGE);
	}
	else if (num == 3)
	{
		auto maplayer = StageThree::create();
		scene->addChild(maplayer, -1, TAG_STAGE);
	}
	auto layer = Game::createWithNum(num);
	scene->addChild(layer,-1,TAG_GAME);
	Hud = HudGameView::create();
	scene->addChild(Hud, 0, TAG_HUD);
	return scene;
}
bool Game::initWithNum(int num)
{
	if (!Layer::init())
	{
		return false;
	}
	totaltime = 0.0f;
	auto player = Player::getInstance();
	player->start();
	player->current.currentStage = num;
	player->current.money = InitialMoney * num;
	player->current.totalMoney = InitialMoney * num;
	backConfirmed = false;
	stage = num;
	atte = WaveFlag::create();
	atte->setPosition(Vec2(100, 150));
	this->addChild(atte,50);
	atte->reTimer();
	schedule(schedule_selector(Game::tick));
	
	return true;
}
Game * Game::createWithNum(int num)
{
	auto _game = new Game;
	if (_game && _game->initWithNum(num))
	{
		_game->autorelease();
		return _game;
	}
	CC_SAFE_DELETE(_game);
	_game = nullptr;
	return nullptr;
}
void Game::tick(float dt)
{	
	totaltime += dt;
	if (totaltime > 20&&!atte->isFirstWave)
	{
		atte->reTimer();
		totaltime = 0;
	}
	auto stage = dynamic_cast<BaseStage*>(UtilTool::getLayerByTag(TAG_STAGE));
	if (stage==nullptr)
	{
		return;
	}
	auto player = Player::getInstance();
	int life = player->current.life;
	int wave = player->current.currentWave;
	int size = stage->monsterVector.size();
	if (wave >= TotalWave)
	{
		atte->isOver = true;
	}
	if (life == 0&&!Director::getInstance()->isPaused())
	{
		unschedule(schedule_selector(Game::tick));
		gameOver();
	}
	if (life > 0&&wave == TotalWave&&stage->num == 5&&stage->isEmpty)
	{
		unschedule(schedule_selector(Game::tick));
		gameOver();
	}
	if (backConfirmed)
	{
		backTo();
	}
}
void Game::backTo()
{
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}
void Game::gameOver()
{
	auto scene = ResultMenu::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));

}