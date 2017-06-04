#include "UpLayer.h"
#include "ArrayUpIcon.h"
#include "MagicUpIcon.h"
#include "BatteryUpIcon.h"
#include "MainMap.h"
#include "TransitionGame.h"
#include "Player.h"
UpLayer::UpLayer()
{
}

UpLayer::~UpLayer()
{
}

Scene* UpLayer::createScene()
{
	auto scene = Scene::create();
	scene->setTag(TAG_SCENE);
	auto layer = UpLayer::create();
	scene->addChild(layer,0,TAG_UP);
	return scene;
}
bool UpLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	auto player = Player::getInstance();
	choosestate = 0;
	star = player->getScore();
	temstar = star;

	return initSprite()&&initMenu()&&initLabel();
}
bool UpLayer::initSprite() {
	Size winSize = Director::getInstance()->getVisibleSize();
	auto data = Sprite::create("top1.png");                            //遮盖层
	data->setPosition(winSize.width*0.77, winSize.height*0.55);
	data->setScale(0.5f);
	auto starPicture = Sprite::create("30.png");             //剩余星星数图标
	starPicture->setScale(0.8f);
	starPicture->setPosition(winSize.width*0.87,winSize.height*0.9);
	starCost = Sprite::create("30.png");                //价格图标
	starCost->setScale(0.5f);
	starCost->setPosition(winSize.width*0.87, winSize.height*0.76);
	auto starBound = Sprite::create("57.png");                     //装饰
	starBound->setPosition(winSize.width*0.9, winSize.height*0.9);
	starBound->setScale(0.5f);
	introduceBound = Sprite::create("57.png");
	introduceBound->setPosition(winSize.width*0.28, winSize.height*0.85);
	introduceBound->setScale(1.1f);
	slected = Sprite::create("slected.png");                     //选择边框
	slected->setScale(0.85f);
	slected->setVisible(false);

	this->addChild(starPicture, 1);
	this->addChild(starCost, 3);
	this->addChild(starBound, 0);
	this->addChild(data, 2);
	this->addChild(slected, 1);
	this->addChild(introduceBound, 0);

	starCost->setVisible(false);
	return true;
}

bool UpLayer::initLabel() {
	des= Label::createWithTTF("XXX", "fonts/Marker Felt.ttf", 30);       //右边框内的文字描述
	des->setAnchorPoint(Point(0, 1));
	des->setDimensions(350,200);
	starNumDes = Label::createWithBMFont("fonts/Number_1.fnt", String::createWithFormat("%d", star)->getCString());
	starCostDes = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	introduce = Label::createWithTTF("click the under icon to improve different kinds of towers' power ", "fonts/Marker Felt.ttf", 25);
	introduce->setDimensions(180, 200);

	des->setPosition(winSize.width*0.60, winSize.height*0.73);
	starNumDes->setPosition(winSize.width*0.91, winSize.height*0.9);
	starCostDes->setPosition(winSize.width*0.89, winSize.height*0.76);
	introduce->setPosition(winSize.width*0.28, winSize.height*0.80);

	this->addChild(starNumDes, 1);
	this->addChild(starCostDes, 3);
	this->addChild(introduce, 0);
	this->addChild(des, 1);
	//this->addChild(briefDes, 4);//鼠标悬停文字
	
	starCostDes->setVisible(false);
	//briefDes->setVisible(false);
	return true;

}

bool UpLayer::initMenu() {
	bgSprite = MenuItemImage::create("bg7.png", "bg7.png", CC_CALLBACK_0(UpLayer::swallow, this, 0));     //触摸失效
	bgSprite->setPosition(winSize.width*0.5,winSize.height*0.5);
    bgSprite->setScale(1.1f); 
	auto menuTest = Menu::create(bgSprite, NULL);
	menuTest->setPosition(Vec2::ZERO);
	this->addChild(menuTest, -1);

	array = ArrayUpIcon::create();                                               //箭塔升级菜单
	array->setPosition(winSize.width*0.26,winSize.height*0.45);
	addChild(array,2);
	array->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 1));
	array->scopeIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 2));
	array->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 3));
	iconVector.push_back(array->forceIcon);  iconVector.push_back(array->scopeIcon); iconVector.push_back(array->speedIcon);

	magic = MagicUpIcon::create();                                             //魔法塔升级菜单
	magic->setPosition(winSize.width*0.13, winSize.height*0.15);
	addChild(magic,2);
	magic->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 4));
	magic->scopeIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 5));
	magic->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 6));
	iconVector.push_back(magic->forceIcon);  iconVector.push_back(magic->scopeIcon);  iconVector.push_back(magic->speedIcon);

	battery = BatteryUpIcon::create();                                       //炮塔升级菜单
	battery->setPosition(winSize.width*0.40, winSize.height*0.15);
	addChild(battery,2);
	battery->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 7));
	battery->scopeIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 8));
	battery->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 9));
	iconVector.push_back(battery->forceIcon);  iconVector.push_back(battery->scopeIcon);  iconVector.push_back(battery->speedIcon);

	upButton = MenuItemImage::create("69.png", "57.png", CC_CALLBACK_1(UpLayer::up, this));                                    //升级按钮
	resetButton = MenuItemImage::create("69.png", "57.png", CC_CALLBACK_1(UpLayer::reset, this));                              //重置按钮
	quitButton = MenuItemImage::create("69.png", "57.png", CC_CALLBACK_1(UpLayer::quit, this));                              //退出按钮
	upButton->setScale(0.5f);
	resetButton->setScale(0.5f);
	quitButton->setScale(0.5f);
	upButton->setPosition(winSize.width*0.68, winSize.height*0.23);
	resetButton->setPosition(winSize.width*0.88, winSize.height*0.23);
	quitButton->setPosition(winSize.width*0.78, winSize.height*0.10);

	auto menu = Menu::create(upButton, resetButton, quitButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	getLevel();
	for (int i = 0;i < 9;i++) {
		if (levelVector[i] > 0) {
			for (int j = 0;j <= levelVector[i] - 1;j++) {
				star -= price[i][j];
			}
		}
	}
	
	return true;
}

void UpLayer::up(Ref* pSender) {
	getLevel();
	if (choosestate == 0) {
		return;
	}
	int temprice = price[choosestate - 1][levelVector[choosestate - 1]];
	if (star - temprice >= 0&&levelVector[choosestate-1]<4) {
		star -= temprice;                          //若果星星数够的话则扣钱进行升级
		switch (choosestate)                       //根据choostate进行相应的升级
		{
		case 1: {
			array->upForce();
			showDes(1);
		}break;

		case 2: {
			array->upScope();
			showDes(2);
		}break;

		case 3: {
			array->upSpeed();
			showDes(3);
		}break;

		case 4: {
			magic->upForce();
			showDes(4);
		}break;

		case  5: {
			magic->upScope();
			showDes(5);
		}break;

		case  6: {
			magic->upSpeed();
			showDes(6);
		}break;

		case 7: {
			battery->upForce();
			showDes(7);
		}break;

		case 8: {
			battery->upScope();
			showDes(8);
		}break;

		case 9: {
			battery->upSpeed();
			showDes(9);
		}break;

		}
	}
	else {
		showDes(10);       //钱不够
	}
	starNumDes->setString(String::createWithFormat("%d", star)->getCString());     //计算剩下的星星数*/
	
}


void UpLayer::reset(Ref* pSender) {
	setStar(temstar);                         //重置星星数
	des->setLocalZOrder(1);                  //隐藏右边框内的文字描述
	slected->setVisible(false);              //隐藏选中图标时出现白框的效果
	choosestate = 0;                        
	starNumDes->setString(__String::createWithFormat("%d", temstar)->getCString());  
	starCostDes->setString("");
	starCost->setVisible(false);             //价格显示消失
	upButton->setVisible(true);              //升级按钮可见
	//upDes->setVisible(true);
	array->reset();                          //执行相应菜单的重置效果
	magic->reset();
	battery->reset();

}


void UpLayer::showDes(int i) {
	getLevel();
	choosestate = i;
	slected->setVisible(true);
	if (choosestate == 10) {
		des->setString("you can't afford it");   //钱不够的提示
	}
	else{
	switch ((choosestate-1)/3)
	{
	case 0: {   //如果是箭塔
		auto temPoint = array->convertToWorldSpace(iconVector[i-1]->getPosition());   //获取图标坐标
		slected->setPosition(temPoint);                                               //设置选中时白框效果
		array->setDes(choosestate);                                                   //设置升级效果描述
		des->setString(array->des->getString());                                      //显示升级效果描述
	}break;


	case 1: {         //如果是魔法塔
		auto temPoint = magic->convertToWorldSpace(iconVector[i - 1]->getPosition());
		slected->setPosition(temPoint);
		magic->setDes(choosestate - 3);
		des->setString(magic->des->getString());
	}break;

	case 2: {           //如果是炮塔
		auto temPoint = battery->convertToWorldSpace(iconVector[i - 1]->getPosition());
		slected->setPosition(temPoint);
		battery->setDes(choosestate - 6);
		des->setString(battery->des->getString());
	}break;
	}
	if (levelVector[choosestate-1]<=3) {   //未满级则显示升级按钮
		upButton->setVisible(true);
		//upDes->setVisible(true);
		starCost->setVisible(true);
		starCostDes->setString(String::createWithFormat("%d", price[i - 1][levelVector[i - 1]])->getCString());
		starCostDes->setVisible(true);
	}
	else {                       //已经满级则让价格和升级按钮消失
		upButton->setVisible(false);
		//upDes->setVisible(false);
		starCost->setVisible(false);
		starCostDes->setVisible(false);
	}
}
	des->setLocalZOrder(3);

}

void UpLayer::swallow(int i) {     //如果点击屏幕空白部分，则让框内文字消失，选择图标的白框消失
	choosestate = i;
	slected->setVisible(false);
	starCostDes->setVisible(false);
	starCost->setVisible(false);
	des->setLocalZOrder(1);
}


void UpLayer::quit(Ref* pSender) {
	//组长来写的函数
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
	
}
void UpLayer::getLevel() {
	//获知当前每种天赋的等级，放在一个数组内方便管理
	levelVector[0] = array->forceLevel;  levelVector[1] = array->speedLevel;  levelVector[2] = array->MaxLevel;
	levelVector[3] = magic->forceLevel; levelVector[4] = magic->speedLevel; levelVector[5] = magic->MaxLevel;
	levelVector[6] = battery->forceLevel; levelVector[7] = battery->speedLevel; levelVector[8] = battery->MaxLevel;
}
