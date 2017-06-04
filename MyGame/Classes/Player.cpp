#include "Player.h"


//-----------------------------------------------------------------------------------

#define isFileExist "isUserDefaultXmpExist" //key - bool

#define  is_save_one "StatusOfSaveSlotOne" //key - bool
#define  star_save_one "TotalStarOfSaveSlotOne" //key - str
#define  stage_save_one "CurrentStageOfSaveSlotOne" //key - integer
#define  first_tech_one "theFirstKindOfTowerTechOfSaveSlotOne" //key - str
#define  second_tech_one "theSecondKindOfTowerTechOfSaveSlotOne" //key - str
#define  third_tech_one "theThirdKindOfTowerTechOfSaveSlotOne" //key - str

#define  is_save_two "StatusOfSaveSlotTwo" //key - bool
#define  star_save_two "TotalStarOfSaveSlotTwo" //key - str
#define  stage_save_two "CurrentStageOfSaveSlotTwo" //key - integer
#define  first_tech_two "theFirstKindOfTowerTechOfSaveSlotTwo" //key - str
#define  second_tech_two "theSecondKindOfTowerTechOfSaveSlotTwo" //key - str
#define  third_tech_two "theThirdKindOfTowerTechOfSaveSlotTwo" //key - str

#define  is_save_three "StatusOfSaveSlotThree" //key - bool
#define  star_save_three "TotalStarOfSaveSlotThree" //key - str
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
	current.life = 0;
	currentSave = 0;
	setScore(1, 1, 4);
	setScore(3, 1, 5);
	setScore(3, 2, 3);
	setStage(1, 1);
	setStage(3, 2);
	saveStatus[1] = true;
	saveStatus[3] = true;
	updateXML();
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
void Player::resetSaveSlot(int num)
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
	
	if (!UserDefault::getInstance()->getBoolForKey(isFileExist))
	{
		auto ub = UserDefault::getInstance();
		ub->setBoolForKey(isFileExist, true);

		ub->setBoolForKey(is_save_one, false);
		ub->setStringForKey(star_save_one, "000");
		ub->setIntegerForKey(stage_save_one, 0);
		ub->setStringForKey(first_tech_one, "001");
		ub->setStringForKey(second_tech_one, "001");
		ub->setStringForKey(third_tech_one, "001");

		ub->setBoolForKey(is_save_two, false);
		ub->setStringForKey(star_save_two, "000");
		ub->setIntegerForKey(stage_save_two, 0);
		ub->setStringForKey(first_tech_two, "001");
		ub->setStringForKey(second_tech_two, "001");
		ub->setStringForKey(third_tech_two, "001");

		ub->setBoolForKey(is_save_three, false);
		ub->setStringForKey(star_save_three, "000");
		ub->setIntegerForKey(stage_save_three, 0);
		ub->setStringForKey(first_tech_three, "001");
		ub->setStringForKey(second_tech_three, "001");
		ub->setStringForKey(third_tech_three, "001");

		resetSaveSlot(1);
		resetSaveSlot(2);
		resetSaveSlot(3);
	}
	else
	{
		log("Exist");
	}
	initSaveSlot();
	setStarted(false);
	currentSave = 0;
	current.life = InitialLifes;
	current.money = InitialMoney;
	current.score = 0;
	current.totalMoney = InitialMoney;
	current.currentStage = 0;
	current.currentStage = 0;
}
void Player::initSaveSlot()
{
	auto ub = UserDefault::getInstance();

	saveStatus[1] = ub->getBoolForKey(is_save_one);
	data[1].initScore(ub->getStringForKey(star_save_one));
	data[1].stage = ub->getIntegerForKey(stage_save_one);
	data[1].tech[1].init(ub->getStringForKey(first_tech_one));
	data[1].tech[2].init(ub->getStringForKey(second_tech_one));
	data[1].tech[3].init(ub->getStringForKey(third_tech_one));

	saveStatus[2] = ub->getBoolForKey(is_save_two);
	data[2].initScore(ub->getStringForKey(star_save_two));
	data[2].stage = ub->getIntegerForKey(stage_save_two);
	data[2].tech[1].init(ub->getStringForKey(first_tech_two));
	data[2].tech[2].init(ub->getStringForKey(second_tech_two));
	data[2].tech[3].init(ub->getStringForKey(third_tech_two));

	saveStatus[3] = ub->getBoolForKey(is_save_three);
	data[3].initScore(ub->getStringForKey(star_save_three));
	data[3].stage = ub->getIntegerForKey(stage_save_three);
	data[3].tech[1].init(ub->getStringForKey(first_tech_three));
	data[3].tech[2].init(ub->getStringForKey(second_tech_three));
	data[3].tech[3].init(ub->getStringForKey(third_tech_three));

	log("%d--%d--%d",getScore(1),getScore(2),getScore(3));
}
void Player::start()
{
	current.life = InitialLifes;
	current.money = InitialMoney;
	current.score = 0;
	current.totalMoney = InitialMoney;
	current.currentStage = 0;
	current.currentStage = 0;
}
void Player::upTechLevel(Tower n,Tech t)
{
	switch (t)
	{
	case UpForce:
		data[currentSave].tech[n].force++;
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
		data[currentSave].tech[i].force = 0;
		data[currentSave].tech[i].speed = 0;
	}
}
int Player::getTechLevel(Tower n, Tech t)
{
	switch (t)
	{
	case UpForce:
		return data[currentSave].tech[n].force;
		break;
	case UpSpeed:
		return data[currentSave].tech[n].speed;
		break;
	case UpMaxLevel:
		return data[currentSave].tech[n].level;
		break;
	default:
		return -1;
		break;
	}
}
void Player::setTechLevel(Tower n, std::string str)
{
	data[currentSave].tech[n].init(str);
}
void Player::updateXML()
{
	auto ub = UserDefault::getInstance();
	ub->setBoolForKey(is_save_one, saveStatus[1]);
	ub->setStringForKey(star_save_one,data[1].updateScore());
	ub->setIntegerForKey(stage_save_one,data[1].stage);
	ub->setStringForKey(first_tech_one,data[1].tech[1].update());
	ub->setStringForKey(second_tech_one,data[1].tech[2].update());
	ub->setStringForKey(third_tech_one,data[1].tech[3].update());

	ub->setBoolForKey(is_save_two, saveStatus[2]);
	ub->setStringForKey(star_save_two,data[2].updateScore());
	ub->setIntegerForKey(stage_save_two,data[2].stage);
	ub->setStringForKey(first_tech_two,data[2].tech[1].update());
	ub->setStringForKey(second_tech_two,data[2].tech[2].update());
	ub->setStringForKey(third_tech_two,data[2].tech[3].update());

	ub->setBoolForKey(is_save_three,saveStatus[3]);
	ub->setStringForKey(star_save_three,data[3].updateScore());
	ub->setIntegerForKey(stage_save_three,data[3].stage);
	ub->setStringForKey(first_tech_three,data[3].tech[1].update());
	ub->setStringForKey(second_tech_three,data[3].tech[2].update());
	ub->setStringForKey(third_tech_three,data[3].tech[3].update());
	log("---Update-To-Local---");
}