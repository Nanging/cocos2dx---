#include "StageThree.h"
#include "SimpleAudioEngine.h"
using namespace  CocosDenshion;

StageThree::StageThree()
{

}


StageThree::~StageThree()
{

}

bool StageThree::init()
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
	sv->setInnerContainerSize(Size(scale * size));
	sv->setContentSize(size);
	sv->setPosition(Vec2(size.width / 2, size.height / 2));
	sv->setInnerContainerPosition(Vec2(0, 0));
	this->addChild(sv, -1);



	GameMap = ImageView::create("png/map_3.png");
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
	count = tempointsVector2.size();
	for (int i = 0; i < count; i++)
	{
		Point p = tempointsVector2.at(i);
		p.x = p.x * ScaleX;
		p.y = p.y * ScaleY + 65;
		tempointsVector2.at(i) = p;
	}
	count = tempointsVector3.size();
	for (int i = 0; i < count; i++)
	{
		Point p = tempointsVector3.at(i);
		p.x = p.x * ScaleX;
		p.y = p.y * ScaleY + 65;
		tempointsVector3.at(i) = p;
	}
	initMonster();
	initUnbuild();
	schedule(schedule_selector(StageThree::tick), 0.5f);
	return true;
}
void StageThree::initUnbuild()
{
	Size size = UtilTool::getSize();

	auto unbuildPlaceOne = BuildBlock::create();
	unbuildPlaceOne->setPosition(Vec2(1.3 * size.width / 2, 1.4 * size.height / 2 + 25));
	sv->addChild(unbuildPlaceOne, 5);

	auto unbuildPlaceTwo = BuildBlock::create();
	unbuildPlaceTwo->setPosition(Vec2(1.4 * size.width / 2, 1.0 * size.height / 2));
	sv->addChild(unbuildPlaceTwo, 5);

	auto unbuildPlaceThree = BuildBlock::create();
	unbuildPlaceThree->setPosition(Vec2(1.3 * size.width / 2 - 20, 0.7 * size.height / 2));
	sv->addChild(unbuildPlaceThree, 5);

	auto unbuildPlaceFour = BuildBlock::create();
	unbuildPlaceFour->setPosition(Vec2(0.5 * size.width / 2, 0.5 * size.height / 2 + 30));
	sv->addChild(unbuildPlaceFour, 5);

	auto unbuildPlaceFive = BuildBlock::create();
	unbuildPlaceFive->setPosition(Vec2(0.9 * size.width / 2, 1.4 * size.height / 2 + 25));
	sv->addChild(unbuildPlaceFive, 5);

	auto unbuildPlaceSix = BuildBlock::create();
	unbuildPlaceSix->setPosition(Vec2(0.9 * size.width / 2 - 35, 0.9 * size.height / 2));
	sv->addChild(unbuildPlaceSix, 5);

	auto unbuildPlaceSeven = BuildBlock::create();
	unbuildPlaceSeven->setPosition(Vec2(0.9 * size.width / 2 - 15, 1.9 * size.height / 2 - 10));
	sv->addChild(unbuildPlaceSeven, 5);

	auto unbuildPlaceEight = BuildBlock::create();
	unbuildPlaceEight->setPosition(Vec2(0.4 * size.width / 2, 1.4 * size.height / 2 + 10));
	sv->addChild(unbuildPlaceEight, 5);

	auto unbuildPlaceNine = BuildBlock::create();
	unbuildPlaceNine->setPosition(Vec2(0.3 * size.width / 2, 1.0 * size.height / 2 - 20));
	sv->addChild(unbuildPlaceNine, 5);

	auto unbuildPlaceTen = BuildBlock::create();
	unbuildPlaceTen->setPosition(Vec2(1.5 * size.width / 2, 0.4 * size.height / 2));
	sv->addChild(unbuildPlaceTen, 5);
}
void StageThree::initMonster()
{
	for (int i = 0; i < 5; i++)
	{
		Vector< BaseMonster* > tem;
		for (int i = 0; i < 5; i++)
		{
			auto hunter = Hunter::createMonster(tempointsVector1);
			tem.pushBack(dynamic_cast<BaseMonster*>(hunter));
		}
		for (int i = 0; i < 5; i++)
		{
			auto hunter = Hunter::createMonster(tempointsVector2);
			tem.pushBack(dynamic_cast<BaseMonster*>(hunter));
		}
		for (int i = 0; i < 5; i++)
		{
			auto hunter = Hunter::createMonster(tempointsVector3);
			tem.pushBack(dynamic_cast<BaseMonster*>(hunter));
		}
		groupMonster.at(i) = tem;
	}
	for (int j = 2; j < 5; j++)
	{
		for (int i = 3; i < 5; i++)
		{
			auto priest = Priest::createMonster(tempointsVector1);
			groupMonster.at(j).replace(i, dynamic_cast<BaseMonster*>(priest));
		}
		auto monkey = Monkey::createMonster(tempointsVector1);
		groupMonster.at(j).replace(4, dynamic_cast<BaseMonster*>(monkey));
	}
	for (int j = 2; j < 5; j++)
	{
		for (int i = 3; i < 5; i++)
		{
			auto priest = Priest::createMonster(tempointsVector2);
			groupMonster.at(j).replace(i + 5, dynamic_cast<BaseMonster*>(priest));
		}
		auto desertExecutioner = DesertExecutioner::createMonster(tempointsVector2);
		groupMonster.at(j).replace(9, dynamic_cast<BaseMonster*>(desertExecutioner));
	}
	for (int j = 2; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			auto wasp = Wasp::createMonster(tempointsVector3);
			groupMonster.at(j).replace(i + 10, dynamic_cast<BaseMonster*>(wasp));
		}
		auto wingRider = WingRider::createMonster(tempointsVector3);
		groupMonster.at(j).replace(14, dynamic_cast<BaseMonster*>(wingRider));
	}
	auto boss = BossMonster::createMonster(tempointsVector2);
	groupMonster.at(4).replace(9, dynamic_cast<BaseMonster*>(boss));

}
void StageThree::addNextWave()
{
	auto player = Player::getInstance();
	auto wave = player->current.currentWave;
	if (wave < TotalWave)
	{
		wavetime = 0.0f; num = 0;
		schedule(schedule_selector(StageThree::addMonster), 0.5f);
		player->current.currentWave++;
	}

}
void StageThree::addMonster(float dt)
{
	wavetime += dt;
	if (wavetime > 2.0f&&num < 5)
	{
		Size size = UtilTool::getSize();
		auto player = Player::getInstance();
		auto wave = player->current.currentWave;
		if (wave <= 5)
		{
			auto h = groupMonster.at(wave - 1).at(num);
			h->setPosition(tempointsVector1.at(0));
			sv->addChild(h, 2);
			monsterVector.pushBack(h);
			if (wave >= 2)
			{
				auto k = groupMonster.at(wave - 1).at(num + 5);
				k->setPosition(tempointsVector2.at(0));
				
				if (num != 4)
				{
					sv->addChild(k, 2);
				}
				else
				{
					sv->addChild(k, 999);
				}
				monsterVector.pushBack(k);
			}
			if (wave >= 3)
			{
				auto p = groupMonster.at(wave - 1).at(num + 10);
				p->setPosition(tempointsVector3.at(0));
				sv->addChild(p, 999);
				
				monsterVector.pushBack(p);
			}
			wavetime = 0.0f;
			num++;
		}
	}
}
