#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class Game
	:public Layer
{
private:
	Vector<MenuItemImage *> TowerPlace;
	
	Vector<Sprite*> Bullet;
	//ScrollView * sv;
	int stage;

public:
	Game();
	~Game();
	static Scene* createScene(int num);
	virtual bool initWithNum(int num);
	static Game * createWithNum(int num);
	void initUnbuild();
	void initBackGround();
	void pauseGame();
	void resumeGame();
	void Builded(Ref * psender);
};

