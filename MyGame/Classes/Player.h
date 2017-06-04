#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "UtilTool.h"
#include <string>
using namespace cocos2d;
struct TowerTech
{
	int force;
	int speed;
	int level;
	TowerTech()
	{
		force = 0;
		speed = 0;
		level = 1;
	}
	void init(std::string str)
	{
		if (str.size()==3)
		{
			this->force = str.at(0) - '0';
			this->speed = str.at(1) - '0';
			this->level = str.at(2) - '0';
		}

	}
	std::string update()
	{
		std::string str;
		str.resize(3);
		str.at(0) = this->force + '0';
		str.at(1) = this->speed + '0';
		str.at(2) = this->level + '0';
		return str;
	}
};
struct GameStatus
{
	int life;
	int score;
	int money;
	int totalMoney;
	int currentStage;
	int currentWave;
	GameStatus()
	{
		life = 0;
		score = 0;
		money = 0;
		totalMoney = 0;
		currentStage = 0;
		currentWave = 0;
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
	void initScore(std::string str)
	{
		if (str.size()==3)
		{
			for (int i = 1; i <= StageNumber; i++)
			{
				this->score[i] = str.at(i - 1) - '0';
			}
			log("%d--%d--%d", str.at(0), str.at(1), str.at(2));
		}

	}
	std::string updateScore()
	{
		std::string str;
		str.resize(StageNumber);
		for (int i = 1; i <= StageNumber; i++)
		{
			str.at(i - 1) = this->score[i] + '0';
		}
		return str;
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
	int currentSave;//current saveslot number
	GameStatus current;//current game status
	static Player * getInstance();
	bool initPlayer();
	void startSaveSlot(int num);//start saveslot num
	void resetSaveSlot(int num);//reset saveslot num
	void initSaveSlot();
	void setScore(int num, int stage = 0, int score = 0);
	int getScore(int num = 0, int stage = 0);
	void setStage(int num, int stage = 0);
	int getStage(int num = 0);
	void resetGame();//reset all saveslot
	void start();//start game
	void upTechLevel(Tower n, Tech t);//update tech data of this saveslot
	void resetTech();//reset tech data of this saveslot
	int getTechLevel(Tower n, Tech t);
	void setTechLevel(Tower n,std::string str);
	void updateXML();
};
#endif // !__PLAYER_H__
