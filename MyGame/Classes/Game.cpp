#include "Game.h"
#include "Player.h"
#include "HudGameView.h"
#include "MainMap.h"
#include "StageOne.h"
#include "ResultMenu.h"
#include "WaveFlag.h"
#include "SimpleAudioEngine.h"
using namespace  CocosDenshion;
HudGameView* Hud = nullptr;
int count = 0;
Game::Game()
{
	log("---Game-Start---");
}

Game::~Game()
{
	log("---Game-Deleted---");
}
Scene * Game::createScene(int num)
{
	auto scene = Scene::create();
	scene->setTag(TAG_SCENE);
	if (num == 1)
	{
		auto maplayer = StageOne::create();
		scene->addChild(maplayer, -1, TAG_STAGE);
	}
	else if (num == 2)
	{

	}
	else if (num == 3)
	{

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
	//SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	auto player = Player::getInstance();
	log("-%d-%d-%d-", player->saveStatus[1], player->saveStatus[2], player->saveStatus[3]);
	player->start();
	player->current.currentStage = num;
	backConfirmed = false;
	stage = num;
	initUnbuild();
	result = Sprite::create("victory.png");
	Size size = UtilTool::getSize();
	result->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(result, 5);
	result->setVisible(false);
	auto atte = WaveFlag::create();
	atte->setPosition(Vec2(200, 300));
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
void Game::initUnbuild()
{
	Size size = UtilTool::getSize();
	auto unbuildPlaces = Menu::create();
	auto unbuildPlace = MenuItemImage::create("land_unbuild.png", "land_unbuild.png", CC_CALLBACK_1(Game::pauseGame, this));
	unbuildPlace->setPosition(Vec2(1.1 * size.width / 2, 1.2 * size.height / 2));

	unbuildPlaces->addChild(unbuildPlace,1);
	this->addChild(unbuildPlaces,1);
	unbuildPlaces->setPosition(Vec2(0,0));
	//}
}
void Game::pauseGame(Ref * psender)
{
	auto stage = dynamic_cast<StageOne*>(UtilTool::getLayerByTag(TAG_STAGE));
	count++;
	//if (count % 2)
	//{
	//	UtilTool::pauseLayerByTag(TAG_STAGE);
	//}
	//else
	//{
	//	UtilTool::resumeLayerByTag(TAG_STAGE);
	//}
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));

}
void Game::resumeGame(Ref * psender)
{
	this->resume();
}
void Game::Builded(Ref * psender)
{
	auto scene = dynamic_cast<StageOne*>(UtilTool::getLayerByTag(TAG_STAGE));
	scene->runAction(ScaleBy::create(1.0f, 0.8f));
}
void Game::tick(float dt)
{
	auto player = Player::getInstance();
	//log("-%d-%d-%d-%d-", player->saveStatus[1], player->saveStatus[2], player->saveStatus[3],player->currentSave);
	int life = player->current.life;
	
	if (life == 0&&!Director::getInstance()->isPaused())
	{
		unschedule(schedule_selector(Game::tick));
		//UtilTool::pauseLayerByTag(TAG_STAGE);
		gameOver();
	}
	if (backConfirmed)
	{
		backTo();
	}
}
void Game::backTo()
{
	//auto s = dynamic_cast<StageOne*>(UtilTool::getLayerByTag(TAG_STAGE));
	//s->setVisible(false);
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
}
void Game::gameOver()
{
	
	auto scene = ResultMenu::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
	//result->setVisible(true);
	//result = Sprite::create("prefect_victory.png");
	//auto GameMap = Sprite::create("map_1.png");

}