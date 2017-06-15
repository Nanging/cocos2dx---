#ifndef __BASE_STAGE_H_
#define __BASE_STAGE_H_


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Monster.h"
#include "Tower.h"
#include <vector>
using namespace cocos2d;
using namespace ui;
class BaseStage
	:public Layer
{

public:
	int num;
	ScrollView* sv;
	BaseStage();
	~BaseStage();
	virtual bool init();
	CREATE_FUNC(BaseStage);
	ImageView *GameMap;
	virtual void initUnbuild(){}
	virtual void initMonster(){}
	//virtual void runCurrentWave(){}
	virtual void tick(float dt){}
	virtual void addNextWave(){}
	Vector<BaseMonster*>monsterVector;
	void update(float delta);
	bool isEmpty;
protected:
	std::vector< Vector<BaseMonster*> >groupMonster;
	float wavetime;
	double ScaleX;
	double ScaleY;
	Vec2 RelatedPosition;
};

#endif // !__BASE_STAGE_H_