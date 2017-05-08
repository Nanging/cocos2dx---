#include "Player.h"

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
	SaveStatus[1] = true;
	SaveStatus[3] = true;
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
	if (SaveStatus[num] == false)
	{
		SaveStatus[num] = true;
	}
	currentSave = num;
}
void Player::initSaveSlot(int num)
{
	SaveStatus[num] = false;
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
	setStarted(false);
	currentSave = 0;
	initSaveSlot(1);
	initSaveSlot(2);
	initSaveSlot(3);
	for (int i = 1; i <=StageNumber; i++)
	{
		SaveStatus[i] = false;
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