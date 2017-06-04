#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#endif // !__GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class Game
	:public Layer
{
private:
	//Vector<MenuItemImage *> towerPlace;
	//
	//Vector<Sprite*> bullets;
	//ScrollView * sv;
	int stage;
	Sprite * result;
	
public:
	Game();
	~Game();
	bool backConfirmed;
	static Scene* createScene(int num);
	virtual bool initWithNum(int num);
	static Game * createWithNum(int num);
	void initUnbuild();
	void pauseGame(Ref * psender);
	void resumeGame(Ref * psender);
	void Builded(Ref * psender);
	void tick(float dt);
	void gameOver();
	void backTo();
};

