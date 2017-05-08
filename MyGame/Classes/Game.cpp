#include "Game.h"
#include "Player.h"
//#include "proj.win32/PowerBullet.h"
//#include "proj.win32/StageOne.h"
static Layer* GameMap = nullptr;
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
	auto s = Scene::create();
	s->setTag(TAG_SCENE);
	if (num == 1)
	{
		//auto k = StageOne::create();
		//s->addChild(k, -1, TAG_MAP_ONE);
	} 
	else if(num == 2)
	{
	}
	else if(num == 3)
	{

	}
	auto j = Game::createWithNum(num);
	s->addChild(j,0,TAG_GAME);
	
	return s;
}
bool Game::initWithNum(int num)
{
	if (!Layer::init())
	{
		return false;
	}
	stage = num;
	GameMap = UtilTool::getLayerByTag(TAG_MAP_ONE);
	if (GameMap == nullptr)
	{
		log("sss-------");
	}
	auto s = Director::getInstance()->getRunningScene();
	if (s->getTag() == TAG_SCENE)
	{
		log("------------------");
	}
	auto i = s->getChildrenCount();
	log("----------%d--------",i);
	//if (i == nullptr)
	//{
	//	log("s-5---------");
	//}
	//GameMap->setVisible(false);
	initBackGround();
	initUnbuild();
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
	//if (stage == 1)
	//{
	auto unBuildPlaces = Menu::create();
	auto unBuildPlace_1 = MenuItemImage::create("land_unbuild.png", "land_unbuild.png", CC_CALLBACK_1(Game::Builded, this));
	unBuildPlace_1->setPosition(Vec2(1.1 * size.width / 2, 1.2 * size.height / 2));

	unBuildPlaces->addChild(unBuildPlace_1,99);
	this->addChild(unBuildPlaces,99);
	unBuildPlaces->setPosition(Vec2(0,0));
	//}
}
void Game::initBackGround()
{

}
void Game::pauseGame()
{
	this->pause();
	//sv->pause();
}
void Game::resumeGame()
{
	//sv->resume();
	this->resume();
}
void Game::Builded(Ref * psender)
{

}