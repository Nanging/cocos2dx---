#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "UtilTool.h"
using namespace cocos2d;
struct TowerTech
{
	int power;
	int speed;
	int level;
	TowerTech()
	{
		power = 0;
		speed = 0;
		level = 1;
	}
};
struct GameStatus
{
	int life;
	int score;
	int money;
	int totalMoney;

	GameStatus()
	{
		life = 0;
		score = 0;
		money = 0;
		totalMoney = 0;
	}
};
struct SaveSlot
{
	int score[StageNumber+1];
	int stage;
	TowerTech tech[TowerNumber + 1];
	SaveSlot()
	{
		for (int i = 0; i <= StageNumber; i++)
		{
			score[i] = 0;
		}
		stage = 0;
	}
};
class Player
	:public Ref
{
private:
	static Player* _instance;
	SaveSlot data[StageNumber+1];
	CC_SYNTHESIZE(bool, Started, Started);//status of game	
public:
	bool saveStatus[3];
	Player();
	~Player();
	GameStatus current;//current game status
	int currentSave;//current saveslot number
	static Player * getInstance();
	bool initPlayer();
	void startSaveSlot(int num);//start saveslot num
	void initSaveSlot(int num);//reset saveslot num
	void setScore(int num, int stage = 0, int score = 0);
	int getScore(int num = 0, int stage = 0);
	void setStage(int num, int stage = 0);
	int getStage(int num = 0);
	void resetGame();//reset all saveslot
	void start();//start game
	void upTechLevel(Tower n,Tech t);//update tech data of this saveslot
	void resetTech();//reset tech data of this saveslot
	void updateXML();
};
#endif // !__PLAYER_H__
