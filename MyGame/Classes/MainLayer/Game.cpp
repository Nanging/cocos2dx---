#include "Game.h"
//#include "Player.h"
//#include "proj.win32/PowerBullet.h"
#include "proj.win32/StageOne.h"
static Layer* GameMap = nullptr;
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
		auto mapLayer = StageOne::create();
		scene->addChild(mapLayer, -1, TAG_STAGE);
	} 
	else if(num == 2)
	{

	}
	else if(num == 3)
	{

	}
	auto layer = Game::createWithNum(num);
	scene->addChild(layer,0,TAG_GAME);
	
	return scene;
}
bool Game::initWithNum(int num)
{
	if (!Layer::init())
	{
		return false;
	}
	stage = num;
	//GameMap = UtilTool::getLayerByTag(TAG_MAP_ONE);
	//if (GameMap == nullptr)
	//{
	//	log("sss-------");
	//}
	//auto s = Director::getInstance()->getRunningScene();
	//if (s->getTag() == TAG_SCENE)
	//{
	//	log("------------------");
	//}
	//auto i = s->getChildrenCount();
	//log("----------%d--------",i);
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
	auto unbuildPlaces = Menu::create();
	auto unbuildPlace = MenuItemImage::create("land_unbuild.png", "land_unbuild.png", CC_CALLBACK_1(Game::pauseGame, this));
	unbuildPlace->setPosition(Vec2(1.1 * size.width / 2, 1.2 * size.height / 2));

	unbuildPlaces->addChild(unbuildPlace,99);
	this->addChild(unbuildPlaces,99);
	unbuildPlaces->setPosition(Vec2(0,0));
	//}
}
void Game::initBackGround()
{

}
void Game::pauseGame(Ref * psender)
{
	auto stage = dynamic_cast<StageOne*>(UtilTool::getLayerByTag(TAG_STAGE));
	
	count++;
	if (count % 2)
	{
		UtilTool::pauseLayerByTag(TAG_STAGE);
	}
	else
	{
		UtilTool::resumeLayerByTag(TAG_STAGE);
	}
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