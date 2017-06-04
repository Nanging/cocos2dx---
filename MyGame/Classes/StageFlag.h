#ifndef __STAGE_FLAG_H__
#define __STAGE_FLAG_H__

#include "cocos2d.h"
using namespace cocos2d;

class StageFlag
	: public Sprite
{
private:
	int stage;
	Size starSize;

	Vector<Sprite*> stars;
public:
	StageFlag();
	~StageFlag();	
	MenuItemImage * flag;
	virtual bool init(int num);
	static StageFlag * create(int num);
	void initStars();
	void startStage(Ref* psender);
};
#endif // !__STAGE_FLAG_H__
