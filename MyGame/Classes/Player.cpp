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
	if (!Node::init())
	{
		return false;
	}
	setStarted(false);
	currentSave = 0;
	initSaveSlot(1);
	initSaveSlot(2);
	initSaveSlot(3);
	setScore(1, 50);
	setScore(3, 4);
	SaveStatus[0] = true;
	SaveStatus[2] = true;
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
	if (SaveStatus[num - 1] == false)
	{
		SaveStatus[num - 1] = true;
	}
	currentSave = num;
}
void Player::initSaveSlot(int num)
{
	int t = num - 1;
	SaveStatus[t] = false;
	log("-%d-false---",num);
	data[t].scores = 0;
	data[t].stage = 0;
}
void Player::setScore(int num, int score /* = 0 */)
{
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return;
		}
		data[currentSave - 1].scores = score;
	}
	data[num - 1].scores = score;
}
int Player::getScore(int num /* = 0 */)
{
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return -1;
		}
		return data[currentSave - 1].scores;
	}
	return data[num - 1].scores;
}
void Player::setStage(int num, int stage /* = 0 */)
{
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return;
		}
		data[currentSave - 1].scores = stage;
	}
	data[num - 1].stage = stage;
}
int Player::getStage(int num /* = 0 */)
{
	if (num == 0)
	{
		if (currentSave == 0)
		{
			return -1;
		}
		return data[currentSave - 1].stage;
	}
	return data[num - 1].stage;
}