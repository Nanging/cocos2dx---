#include "StageOne.h"
//#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace  CocosDenshion;

StageOne::StageOne()
{
	
}


StageOne::~StageOne()
{
	//auto sound = SimpleAudioEngine::getInstance();
	//if (sound->isBackgroundMusicPlaying())
	//{
	//	sound->stopBackgroundMusic(true);
	//}
}

bool StageOne::init()
{
	if (!BaseStage::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("savage_music_jungle_battle.wav", true);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Size size = UtilTool::getSize();
	sv = ScrollView::create();
	sv->setDirection(ScrollView::Direction::BOTH);
	sv->setAnchorPoint(Vec2(0.5, 0.5));
	sv->setScrollBarEnabled(false);
	sv->setInnerContainerSize(size*scale);
	sv->setContentSize(size);
	sv->setPosition(Vec2(size.width / 2, size.height / 2));
	sv->setInnerContainerPosition(Vec2(0, 0));
	this->addChild(sv, -1);



	auto GameMap = ImageView::create("map_1.png");
	GameMap->setPosition(Vec2(scale* size.width / 2, scale*size.height / 2));
	sv->addChild(GameMap, 0);
	GameMap->setScale(scale * size.width / GameMap->getContentSize().width, scale * size.height / GameMap->getContentSize().height);
	
	
	initUnbuild();
	schedule(schedule_selector(StageOne::tick),0.5f);
	return true;
}
void StageOne::initUnbuild()
{
	Size size = UtilTool::getSize();
	auto unbuildPlaces = Menu::create();
	auto unbuildPlace = MenuItemImage::create("land_unbuild.png", "land_unbuild.png", CC_CALLBACK_1(StageOne::pauseStage, this));
	unbuildPlace->setPosition(Vec2(1.1 * size.width / 2, 1.2 * size.height / 2));

	unbuildPlaces->addChild(unbuildPlace, 99);
	sv->addChild(unbuildPlaces, 99);
	unbuildPlaces->setPosition(Vec2(0, 0));
}
void StageOne::runCurrentWave()
{
	auto result = Sprite::create("victory.png");
	Size size = UtilTool::getSize();
	result->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(result, 5);
}
void StageOne::tick(float dt)
{
	Point p = sv->getInnerContainerPosition();
	/*log("x = %f,y = %f", p.x, p.y);*/
	auto player = Player::getInstance();
	totaltime += dt;
	log("life = %d", player->current.life);
	if (totaltime >= 1 && player->current.life > 0)
	{
		player->current.life--;
	}
}
void StageOne::pauseStage(Ref * psender)
{

	log("here");
}