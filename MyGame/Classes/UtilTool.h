#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#define  TotolScore 15
#define MaxScore 5
#define StageNumber 3
#define InitialLifes 20
#define InitialMoney 200
#define TowerNumber 3
enum  NodeTag
{
	TAG_SCENE,
	TAG_START,
	TAG_MAP,
	TAG_GAME,
	TAG_TEC,
	TAG_FLAG_ONE,
	TAG_FLAG_TWO,
	TAG_FLAG_THREE,
	TAG_MAP_ONE,
	TAG_MAP_TWO,
	TAG_MAP_THREE,
};
enum Tower
{
	NORMAL,
	POWER,
	SPEED,
	MORE,
};
enum Tech
{
	UpPower,
	UpSpeed,
	UpMaxLevel,
};
class UtilTool
{
public:
	UtilTool();
	~UtilTool();
	static Size getSize();
	static Layer* getLayerByTag(NodeTag t);
};

