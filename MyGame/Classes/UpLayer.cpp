#include "UpLayer.h"
#include "ArrowUpIcon.h"
#include "MagicUpIcon.h"
#include "CannonUpIcon.h"
#include "MainMap.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	choosestate = 0;
	star = player->getScore();
	temstar = star;
	
	return initSprite()&&initMenu()&&initLabel();
}
void UpLayer::update(float delta)
{
	if (star == temstar)
	{
		resetButton->setEnabled(false);
	}
	else
	{
		resetButton->setEnabled(true);
	}
	upButton->setEnabled(true);
	if (choosestate == 0)
	{
		return;
	}
	int temprice = price[choosestate - 1][levelVector[choosestate - 1]];
	if (star < temprice)
	{
		showDes(10);
		upButton->setEnabled(false);
	}
}
bool UpLayer::initSprite() {
	Size winSize = Director::getInstance()->getVisibleSize();
	auto data = Sprite::create("png/introduce.png");                            //遮盖层
	data->setPosition(winSize.width*0.77, winSize.height*0.55);
	data->setScale(0.5f,0.6f);
	auto starPicture = Sprite::create("png/star_count.png");             //剩余星星数图标
	starPicture->setScale(0.8f);
	starPicture->setPosition(winSize.width*0.72,winSize.height*0.85);
	starCost = Sprite::create("png/star_count.png");                //价格图标
	starCost->setScale(0.5f);
	starCost->setPosition(winSize.width*0.85, winSize.height*0.69);
	auto starBound = Sprite::create("png/star_count_bound.png");                     //装饰
	starBound->setPosition(winSize.width*0.77, winSize.height*0.85);
	starBound->setScale(0.7f);
	introduceBound = Sprite::create("png/notice.png");
	introduceBound->setPosition(winSize.width*0.28, winSize.height*0.90);
	introduceBound->setScale(0.5f,0.2f);
	slected = Sprite::create("png/slected.png");                     //选择边框
	slected->setScale(0.75f);
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
	Size winSize = Director::getInstance()->getVisibleSize();
	des= Label::createWithTTF("XXX", "fonts/Marker Felt.ttf", 30);       //右边框内的文字描述
	des->setAnchorPoint(Point(0, 1));
	des->setDimensions(350,200);
	
	starNumDes = Label::createWithBMFont("fonts/Number_1.fnt", String::createWithFormat("%d", star)->getCString());
	starCostDes = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	introduce = Label::createWithTTF("click these icon to improve different kinds of towers' power ", "fonts/Marker Felt.ttf", 25);
	tips=Label::createWithTTF("", "fonts/Marker Felt.ttf", 30);
	introduce->setDimensions(400, 200);

	des->setPosition(winSize.width*0.62, winSize.height*0.68);
	starNumDes->setPosition(winSize.width*0.82, winSize.height*0.85);
	starCostDes->setPosition(winSize.width*0.88, winSize.height*0.69);
	introduce->setPosition(winSize.width*0.30, winSize.height*0.77);
	tips->setPosition(winSize.width*0.70, winSize.height*0.42);

	this->addChild(starNumDes, 1);
	this->addChild(starCostDes, 3);
	this->addChild(introduce, 0);
	this->addChild(des, 1);
	this->addChild(tips, 4);
	starCostDes->setTextColor(Color4B::BLACK);
	des->setTextColor(Color4B::BLACK);
	starCostDes->setVisible(false);

	scheduleUpdate();
	return true;

}

bool UpLayer::initMenu() {
	Size winSize = Director::getInstance()->getVisibleSize();
	bgSprite = MenuItemImage::create("png/tech_layer_bg.png", "png/tech_layer_bg.png", CC_CALLBACK_0(UpLayer::swallow, this, 0));     //触摸失效
	bgSprite->setPosition(winSize.width*0.5,winSize.height*0.5);
    bgSprite->setScale(winSize.width/bgSprite->getContentSize().width,winSize.height/bgSprite->getContentSize().height); 
	auto menuTest = Menu::create(bgSprite, NULL);
	menuTest->setPosition(Vec2::ZERO);
	this->addChild(menuTest, -1);

	array = ArrowUpIcon::create();                                               //箭塔升级菜单
	array->setPosition(winSize.width*0.29,winSize.height*0.55);
	addChild(array,1);
	array->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 1));
	array->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 2));
	array->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 3));
	iconVector.push_back(array->forceIcon);  iconVector.push_back(array->speedIcon); iconVector.push_back(array->levelIcon);

	magic = MagicUpIcon::create();                                             //魔法塔升级菜单
	magic->setPosition(winSize.width*0.14, winSize.height*0.25);
	addChild(magic,3);
	magic->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 4));
	magic->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 5));
	magic->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 6));
	iconVector.push_back(magic->forceIcon);  iconVector.push_back(magic->speedIcon);  iconVector.push_back(magic->levelIcon);

	battery = CannonUpIcon::create();                                       //炮塔升级菜单
	battery->setPosition(winSize.width*0.44, winSize.height*0.25);
	addChild(battery,2);
	battery->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 7));
	battery->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 8));
	battery->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 9));
	iconVector.push_back(battery->forceIcon);  iconVector.push_back(battery->speedIcon);  iconVector.push_back(battery->levelIcon);

	upButton = MenuItemImage::create("png/up_nor.png", "png/up_sel.png", "png/touch_false.png", CC_CALLBACK_1(UpLayer::up, this));                                 //升级按钮
	resetButton = MenuItemImage::create("png/reset_nor.png", "png/reset_sel.png", "png/touch_false.png", CC_CALLBACK_1(UpLayer::reset, this));                              //重置按钮
	quitButton = MenuItemImage::create("png/done_nor.png", "png/done_sel.png", CC_CALLBACK_1(UpLayer::quit, this));                              //退出按钮
	
	upButton->setScale(0.7f);
	resetButton->setScale(0.7f);
	quitButton->setScale(0.7f);
	upButton->setPosition(winSize.width*0.68, winSize.height*0.26);
	resetButton->setPosition(winSize.width*0.86, winSize.height*0.26);
	quitButton->setPosition(winSize.width*0.77, winSize.height*0.13);

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
		SimpleAudioEngine::getInstance()->playEffect("wav/Sound_TowerUpgrade.wav");
		star -= temprice;                          //若果星星数够的话则扣钱进行升级
		switch (choosestate)                       //根据choostate进行相应的升级
		{
		case 1: {
			array->upForce();
		}break;

		case 2: {
			array->upScope();
		}break;

		case 3: {
			array->upSpeed();
		}break;

		case 4: {
			magic->upForce();
		}break;

		case  5: {
			magic->upScope();
		}break;

		case  6: {
			magic->upSpeed();
		}break;

		case 7: {
			battery->upForce();
		}break;

		case 8: {
			battery->upScope();
		}break;

		case 9: {
			battery->upSpeed();
		}break;

		}
	}
	else {
		showDes(10);       //钱不够
	}
	showDes(choosestate);
	starNumDes->setString(String::createWithFormat("%d", star)->getCString());     //计算剩下的星星数*/
	
}


void UpLayer::reset(Ref* pSender) {
	SimpleAudioEngine::getInstance()->playEffect("wav/inapp_star.wav");
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
	//upButton->setEnabled(true);
	slected->setVisible(true);
	tips->setVisible(false);
	if (choosestate == 10) {
		tips->setString("you can't afford it");   //钱不够的提示
		tips->setVisible(true);
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
	tips->setVisible(false);
	des->setLocalZOrder(1);
}


void UpLayer::quit(Ref* pSender) {
	//组长来写的函数
	array->setLevel(SPEED);
	battery->setLevel(POWER);
	magic->setLevel(MAGIC);
	auto player = Player::getInstance();
	player->updateXML();
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
	
}
void UpLayer::getLevel() {
	//获知当前每种天赋的等级，放在一个数组内方便管理
	levelVector[0] = array->forceLevel;  levelVector[1] = array->speedLevel;  levelVector[2] = array->MaxLevel;
	levelVector[3] = magic->forceLevel; levelVector[4] = magic->speedLevel; levelVector[5] = magic->MaxLevel;
	levelVector[6] = battery->forceLevel; levelVector[7] = battery->speedLevel; levelVector[8] = battery->MaxLevel;
}
