#pragma once
#include "cocos2d.h"
using namespace cocos2d;
static const int TotolScore = 150;
struct SaveSlot
{
	int scores;
	int stage;
};
class Player
	:public Node
{
private:
	static Player* _instance;
	SaveSlot data[3];
	CC_SYNTHESIZE(bool, Started, Started);	
public:
	bool SaveStatus[3];
	Player();
	~Player();
	int currentSave;
	static Player * getInstance();
	bool initPlayer();
	void startSaveSlot(int num);
	void initSaveSlot(int num);
	void setScore(int num, int score = 0);
	int getScore(int num = 0);
	void setStage(int num, int stage = 0);
	int getStage(int num = 0);
};

