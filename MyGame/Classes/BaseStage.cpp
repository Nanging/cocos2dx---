#include "BaseStage.h"



BaseStage::BaseStage()
{

}


BaseStage::~BaseStage()
{
}
bool BaseStage::init()
{
	if (!Layer::init())
	{
		return false;
	}
	isEmpty = false;
	ScaleX = 0.0;
	ScaleY = 0.0;
	groupMonster.resize(5);
	wavetime = 0.0f;
	scheduleUpdate();
	return true;
}
void BaseStage::update(float delta)
{
	if (monsterVector.empty())
	{
		return;
	}
	int num = 0;
	int size = monsterVector.size();
	for (int i = 0; i < size; i++)
	{
		auto monster = monsterVector.at(i);
		if (monster == nullptr)
		{
			num++;
		}
		else if (monster->isMoving == false)
		{
			num++;
		}
	}
	if (num == size)
	{
		isEmpty = true;
	}
	else
	{
		isEmpty = false;
	}
}