#ifndef __UTILL_TOOL_H__
#define __UTILL_TOOL_H__
#include "cocos2d.h"
#include "TransitionGame.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

static const int  TotalScore = 15;
static const int  MaxScore = 5;
static const int  StageNumber = 3;
static const int  InitialLifes = 20;
static const int  InitialMoney = 200;
static const int  TowerNumber = 3;
static const float scale = 1.1f;
static const int TotalWave = 10;

enum  NodeTag
{
	TAG_SCENE,//RunningScene
	TAG_START,//StartLayer
	TAG_MAP,//MapLayer
	TAG_GAME,//GameLayer
	TAG_TEC,//TechLayer
	TAG_STAGE,//CurrentStageLayer
	TAG_UP,
	TAG_HUD,
	TAG_RESULT,
};
enum Tower 
{
	/*kinds of Tower*/
	NORMAL = 1,
	POWER,
	SPEED,
	//MORE,
};
enum Tech
{
	NONE = -1,
	UpForce,
	UpSpeed,
	UpMaxLevel,
};
enum Flag
{
	TAG_FLAG_ONE,//Flag of StageOne
	TAG_FLAG_TWO,//Flag of StageTwo
	TAG_FLAG_THREE,//Flag of StageThree
};
class UtilTool
{
public:
	UtilTool();
	~UtilTool();
	static Size getSize();//get visiblesize?
	static Layer* getLayerByTag(NodeTag t);//get Layer from RunningScene
	static bool pauseLayerByTag(NodeTag t);
	static bool resumeLayerByTag(NodeTag t);
};

#endif // !__UTILL_TOOL_H__