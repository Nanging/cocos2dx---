#include "StageOne.h"
#include "SimpleAudioEngine.h"
using namespace  CocosDenshion;

StageOne::StageOne()
{
	
}


StageOne::~StageOne()
{
}

bool StageOne::init()
{
	if (!BaseStage::init())
	{
		return false;
	}
	num = 0;
	SimpleAudioEngine::getInstance()->playBackgroundMusic("wav/savage_music_jungle_battle.wav", true);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Size size = UtilTool::getSize();
	sv = ScrollView::create();
	sv->setDirection(ScrollView::Direction::BOTH);
	sv->setAnchorPoint(Vec2(0.5, 0.5));
	sv->setScrollBarEnabled(false);
	sv->setInnerContainerSize(Size(scale * size ));
	sv->setContentSize(size);
	sv->setPosition(Vec2(size.width / 2, size.height / 2));
	sv->setInnerContainerPosition(Vec2(0, 0));
	this->addChild(sv, -1);

	GameMap = ImageView::create("png/map_1.png");
	GameMap->setPosition(Vec2(scale* size.width / 2, scale*size.height / 2));
	sv->addChild(GameMap, 0);
	ScaleX = scale * size.width / GameMap->getContentSize().width;
	ScaleY = scale * size.height / GameMap->getContentSize().height;
	GameMap->setScale(scale * size.width / GameMap->getContentSize().width, scale * size.height / GameMap->getContentSize().height);
	int count = tempointsVector1.size();
	for (int i = 0; i < count; i++)
	{
		Point p = tempointsVector1.at(i);
		p.x = p.x * ScaleX;
		p.y = p.y * ScaleY + 65;
		tempointsVector1.at(i) = p;
	}
	initMonster();
	initUnbuild();
	schedule(schedule_selector(StageOne::tick),0.5f);
	return true;
}
void StageOne::initUnbuild()
{
	Size size = UtilTool::getSize();

	auto unbuildPlaceOne = BuildBlock::create();
	unbuildPlaceOne->setPosition(Vec2(0.9 * size.width / 2 - 40, 1.2 * size.height / 2+10));
	sv->addChild(unbuildPlaceOne, 5);

	auto unbuildPlaceTwo = BuildBlock::create();
	unbuildPlaceTwo->setPosition(Vec2(1.5 * size.width / 2 - 90, 1.6 * size.height / 2 + 25));
	sv->addChild(unbuildPlaceTwo, 5);

	auto unbuildPlaceThree = BuildBlock::create();
	unbuildPlaceThree->setPosition(Vec2(1.1 * size.width / 2 + 40, 1.2 * size.height / 2 + 30));
	sv->addChild(unbuildPlaceThree, 5);

	auto unbuildPlaceFour = BuildBlock::create();
	unbuildPlaceFour->setPosition(Vec2(1.1 * size.width / 2 + 40, 0.9 * size.height / 2 - 20));
	sv->addChild(unbuildPlaceFour, 5);

	auto unbuildPlaceFive = BuildBlock::create();
	unbuildPlaceFive->setPosition(Vec2(0.9 * size.width / 2 + 20, 0.8 * size.height / 2- 15));
	sv->addChild(unbuildPlaceFive, 5);

	auto unbuildPlaceSix = BuildBlock::create();
	unbuildPlaceSix->setPosition(Vec2(1.2 * size.width / 2, 0.4 * size.height / 2 + 10));
	sv->addChild(unbuildPlaceSix, 5);

	auto unbuildPlaceSeven = BuildBlock::create();
	unbuildPlaceSeven->setPosition(Vec2(0.4 * size.width / 2, 1.3 * size.height / 2));
	sv->addChild(unbuildPlaceSeven, 5);
}
void StageOne::initMonster()
{
	
	for (int i = 0; i < 5; i++)
	{	
		Vector< BaseMonster* > tem;
		for (int i = 0; i < 5; i++)
		{
			auto thug = Thug::createMonster(tempointsVector1);
			tem.pushBack(dynamic_cast<BaseMonster*>(thug));
		}
		groupMonster.at(i) = tem;
	}
	for (int j = 2; j < 5; j++)
	{
		for (int i = 3; i < 5; i++)
		{
			auto robber = Robber::createMonster(tempointsVector1);
			groupMonster.at(j).replace(i, dynamic_cast<BaseMonster*>(robber));
		}
	}		
	auto desertExecutioner = DesertExecutioner::createMonster(tempointsVector1);
	groupMonster.at(4).replace(4,dynamic_cast<BaseMonster*>(desertExecutioner));

}
void StageOne::addNextWave()
{
	auto player = Player::getInstance();
	auto wave = player->current.currentWave;
	if (wave < TotalWave)
	{
		wavetime = 0.0f; num = 0;
		schedule(schedule_selector(StageOne::addMonster), 0.5f);
		player->current.currentWave++;
	}

}
void StageOne::addMonster(float dt)
{
	wavetime += dt;
	if (wavetime > 2.0f&&num < 5)
	{
		Size size = UtilTool::getSize();
		auto player = Player::getInstance();
		auto wave = player->current.currentWave;
		if (wave <= 5)
		{
			auto h = groupMonster.at(wave -1).at(num);
			h->setPosition(tempointsVector1.at(0));
			sv->addChild(h, 2);
			monsterVector.pushBack(h);
			wavetime = 0.0f; num++;
		}
	}		
}