#include "Player.h"
#include <string>

//-----------------------------------------------------------------------------------

#define isFileExist "isUserDefaultXmpExist" //key - bool

#define  is_save_one "StatusOfSaveSlotOne" //key - bool
#define  star_save_one "TotalStarOfSaveSlotOne" //key - integer
#define  stage_save_one "CurrentStageOfSaveSlotOne" //key - integer
#define  first_tech_one "theFirstKindOfTowerTechOfSaveSlotOne" //key - str
#define  second_tech_one "theSecondKindOfTowerTechOfSaveSlotOne" //key - str
#define  third_tech_one "theThirdKindOfTowerTechOfSaveSlotOne" //key - str

#define  is_save_two "StatusOfSaveSlotTwo" //key - bool
#define  star_save_two "TotalStarOfSaveSlotTwo" //key - integer
#define  stage_save_two "CurrentStageOfSaveSlotTwo" //key - integer
#define  first_tech_two "theFirstKindOfTowerTechOfSaveSlotTwo" //key - str
#define  second_tech_two "theSecondKindOfTowerTechOfSaveSlotTwo" //key - str
#define  third_tech_two "theThirdKindOfTowerTechOfSaveSlotTwo" //key - str

#define  is_save_three "StatusOfSaveSlotThree" //key - bool
#define  star_save_three "TotalStarOfSaveSlotThree" //key - integer
#define  stage_save_three "CurrentStageOfSaveSlotThree" //key - integer
#define  first_tech_three "theFirstKindOfTowerTechOfSaveSlotThree" //key - str
#define  second_tech_three "theSecondKindOfTowerTechOfSaveSlotThree" //key - str
#define  third_tech_three "theThirdKindOfTowerTechOfSaveSlotThree" //key - str

//-----------------------------------------------------------------------------------

Player * Player::_instance = nullptr;
Player::Player()
{
	log("---Player-On---");
}
Player::~Player()
{
	log("---Player-Off---");
}
bool  Player::initPlayer()
{
	resetGame();
	setScore(1, 1, 4);
	setScore(3, 1, 5);
	setScore(3, 2, 3);
	setStage(1, 1);
	setStage(3, 2);
	saveStatus[1] = true;
	saveStatus[3] = true;
	return true;
}
Player *Player::getInstance()
{
	if (!_instance)
	{
		_instance = new Player;
		if (_instance&&_instance->initPlayer())
		{
			_instance->autorelease();
			_instance->retain();
			return _instance;
		}
		else
		{
			CC_SAFE_DELETE(_instance);
			_instance = nullptr;
			return nullptr;
		}
	}
	return _instance;
}
void Player::startSaveSlot(int num)
{
	setStarted(true);
	if (saveStatus[num] == false)
	{
		saveStatus[num] = true;
	}
	currentSave = num;
}
void Player::initSaveSlot(int num)
{
	saveStatus[num] = false;
	log("-%d-false---",num);
	setScore(num);
	setStage(num);
}
void Player::setScore(int num, int stage /* = 0 */, int score /* = 0 */)
{
	if (stage > StageNumber)
	{
		return;
	}
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return;
		}
		if (stage == 0)
		{
			for (int i = 1; i <= StageNumber; i++)
			{
				data[currentSave].score[i] = 0;
			}
		}
		else
		{
			if (score > MaxScore)
			{
				return;
			}
			data[currentSave].score[stage] = score;
		}
	}
	if (stage == 0)
	{
		for (int i = 1; i <= StageNumber; i++)
		{
			data[num].score[i] = 0;
		}
	}
	else
	{
		if (score > MaxScore)
		{
			return;
		}
		data[num].score[stage] = score;
	}
}
int Player::getScore(int num /* = 0 */, int stage /* = 0 */)
{
	if (stage > StageNumber)
	{
		return -1;
	}
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return -1;
		}
		if (stage == 0)
		{
			int sum = 0;
			for (int i = 1; i <= StageNumber; i++)
			{
				sum += data[currentSave].score[i];
			}
			return sum;
		}
		return data[currentSave].score[stage];
	}
	if (stage == 0)
	{
		int sum = 0;
		for (int i = 1; i <= StageNumber; i++)
		{
			sum += data[num].score[i];
		}
		return sum;
	}
	return data[num].score[stage];
}
void Player::setStage(int num, int stage /* = 0 */)
{
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return;
		}
		data[currentSave].stage = stage;
	}
	data[num].stage = stage;
}
int Player::getStage(int num /* = 0 */)
{

	if (num == 0)
	{
		if (currentSave == 0)
		{
			return -1;
		}
		return data[currentSave].stage;
	}
	return data[num].stage;
}
void Player::resetGame()
{
	auto isExist = UserDefault::getInstance()->isXMLFileExist();
	if (isExist)
	{
		auto s = UserDefault::getXMLFilePath();
		log("%s",s.c_str());
		//UserDefault::getInstance()->UserDefault::setDoubleForKey("sss", 1.1);
	}
	else
	{
		log("no");
	}
	setStarted(false);
	currentSave = 0;
	initSaveSlot(1);
	initSaveSlot(2);
	initSaveSlot(3);
	for (int i = 1; i <=StageNumber; i++)
	{
		saveStatus[i] = false;
		setScore(i);
		setStage(i);
	}
	current.life = InitialLifes;
	current.money = InitialMoney;
	current.score = 0;
	current.totalMoney = InitialMoney;
}
void Player::start()
{
	current.life = InitialLifes;
	current.money = InitialMoney;
	current.score = 0;
	current.totalMoney = InitialMoney;
}
void Player::upTechLevel(Tower n,Tech t)
{
	switch (t)
	{
	case UpPower:
		data[currentSave].tech[n].power++;
		break;
	case UpSpeed:
		data[currentSave].tech[n].speed++;
		break;
	case UpMaxLevel:
		data[currentSave].tech[n].level++;
		break;
	default:
		break;
	}
}
void Player::resetTech()
{
	for (int i = 0; i < TowerNumber; i++)
	{
		data[currentSave].tech[i].level = 1;
		data[currentSave].tech[i].power = 0;
		data[currentSave].tech[i].speed = 0;
	}
}
void Player::updateXML()
{
	log("-----");
}