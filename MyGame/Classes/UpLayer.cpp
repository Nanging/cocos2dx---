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
		//upButton->setEnabled(false);
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
	auto data = Sprite::create("introduce.png");                            //�ڸǲ�
	data->setPosition(winSize.width*0.77, winSize.height*0.55);
	data->setScale(0.5f,0.6f);
	auto starPicture = Sprite::create("star_count.png");             //ʣ��������ͼ��
	starPicture->setScale(0.8f);
	starPicture->setPosition(winSize.width*0.72,winSize.height*0.85);
	starCost = Sprite::create("star_count.png");                //�۸�ͼ��
	starCost->setScale(0.5f);
	starCost->setPosition(winSize.width*0.85, winSize.height*0.69);
	auto starBound = Sprite::create("star_count_bound.png");                     //װ��
	starBound->setPosition(winSize.width*0.77, winSize.height*0.85);
	starBound->setScale(0.7f);
	introduceBound = Sprite::create("notice.png");
	introduceBound->setPosition(winSize.width*0.28, winSize.height*0.90);
	introduceBound->setScale(0.5f,0.2f);
	slected = Sprite::create("slected.png");                     //ѡ��߿�
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
	des= Label::createWithTTF("XXX", "fonts/Marker Felt.ttf", 30);       //�ұ߿��ڵ���������
	des->setAnchorPoint(Point(0, 1));
	des->setDimensions(350,200);
	
	starNumDes = Label::createWithBMFont("fonts/Number_1.fnt", String::createWithFormat("%d", star)->getCString());
	starCostDes = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	introduce = Label::createWithTTF("click these icon to improve different kinds of towers' power ", "fonts/Marker Felt.ttf", 25);
	introduce->setDimensions(400, 200);

	des->setPosition(winSize.width*0.62, winSize.height*0.71);
	starNumDes->setPosition(winSize.width*0.82, winSize.height*0.85);
	starCostDes->setPosition(winSize.width*0.88, winSize.height*0.69);
	introduce->setPosition(winSize.width*0.30, winSize.height*0.77);

	this->addChild(starNumDes, 1);
	this->addChild(starCostDes, 3);
	this->addChild(introduce, 0);
	this->addChild(des, 1);
	//this->addChild(briefDes, 4);//�����ͣ����
	starCostDes->setTextColor(Color4B::BLACK);
	des->setTextColor(Color4B::BLACK);
	starCostDes->setVisible(false);
	//briefDes->setVisible(false);

	scheduleUpdate();
	return true;

}

bool UpLayer::initMenu() {
	Size winSize = Director::getInstance()->getVisibleSize();
	bgSprite = MenuItemImage::create("tech_layer_bg.png", "tech_layer_bg.png", CC_CALLBACK_0(UpLayer::swallow, this, 0));     //����ʧЧ
	bgSprite->setPosition(winSize.width*0.5,winSize.height*0.5);
    bgSprite->setScale(winSize.width/bgSprite->getContentSize().width,winSize.height/bgSprite->getContentSize().height); 
	auto menuTest = Menu::create(bgSprite, NULL);
	menuTest->setPosition(Vec2::ZERO);
	this->addChild(menuTest, -1);

	array = ArrayUpIcon::create();                                               //���������˵�
	array->setPosition(winSize.width*0.29,winSize.height*0.55);
	addChild(array,1);
	array->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 1));
	array->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 2));
	array->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 3));
	iconVector.push_back(array->forceIcon);  iconVector.push_back(array->speedIcon); iconVector.push_back(array->levelIcon);

	magic = MagicUpIcon::create();                                             //ħ���������˵�
	magic->setPosition(winSize.width*0.14, winSize.height*0.25);
	addChild(magic,3);
	magic->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 4));
	magic->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 5));
	magic->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 6));
	iconVector.push_back(magic->forceIcon);  iconVector.push_back(magic->speedIcon);  iconVector.push_back(magic->levelIcon);

	battery = BatteryUpIcon::create();                                       //���������˵�
	battery->setPosition(winSize.width*0.44, winSize.height*0.25);
	addChild(battery,2);
	battery->forceIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 7));
	battery->speedIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 8));
	battery->levelIcon->setCallback(CC_CALLBACK_0(UpLayer::showDes, this, 9));
	iconVector.push_back(battery->forceIcon);  iconVector.push_back(battery->speedIcon);  iconVector.push_back(battery->levelIcon);

	upButton = MenuItemImage::create("up_nor.png", "up_sel.png", "touch_false.png", CC_CALLBACK_1(UpLayer::up, this));
		//("69.png", "57.png", CC_CALLBACK_1(UpLayer::up, this));                                    //������ť
	resetButton = MenuItemImage::create("reset_nor.png", "reset_sel.png", "touch_false.png", CC_CALLBACK_1(UpLayer::reset, this));                              //���ð�ť
	quitButton = MenuItemImage::create("done_nor.png", "done_sel.png", CC_CALLBACK_1(UpLayer::quit, this));                              //�˳���ť
	
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
		star -= temprice;                          //�������������Ļ����Ǯ��������
		switch (choosestate)                       //����choostate������Ӧ������
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
		//upButton->setEnabled(false);
		showDes(10);       //Ǯ����
	}
	starNumDes->setString(String::createWithFormat("%d", star)->getCString());     //����ʣ�µ�������*/
	
}


void UpLayer::reset(Ref* pSender) {
	setStar(temstar);                         //����������
	des->setLocalZOrder(1);                  //�����ұ߿��ڵ���������
	slected->setVisible(false);              //����ѡ��ͼ��ʱ���ְ׿��Ч��
	choosestate = 0;                        
	starNumDes->setString(__String::createWithFormat("%d", temstar)->getCString());  
	starCostDes->setString("");
	starCost->setVisible(false);             //�۸���ʾ��ʧ
	upButton->setVisible(true);              //������ť�ɼ�
	//upDes->setVisible(true);
	array->reset();                          //ִ����Ӧ�˵�������Ч��
	magic->reset();
	battery->reset();

}


void UpLayer::showDes(int i) {
	getLevel();
	choosestate = i;
	//upButton->setEnabled(true);
	slected->setVisible(true);
	if (choosestate == 10) {
		des->setString("you can't afford it");   //Ǯ��������ʾ
		//upButton->setEnabled(false);
	}
	else{
	switch ((choosestate-1)/3)
	{
	case 0: {   //����Ǽ���
		auto temPoint = array->convertToWorldSpace(iconVector[i-1]->getPosition());   //��ȡͼ������
		slected->setPosition(temPoint);                                               //����ѡ��ʱ�׿�Ч��
		array->setDes(choosestate);                                                   //��������Ч������
		des->setString(array->des->getString());                                      //��ʾ����Ч������
	}break;


	case 1: {         //�����ħ����
		auto temPoint = magic->convertToWorldSpace(iconVector[i - 1]->getPosition());
		slected->setPosition(temPoint);
		magic->setDes(choosestate - 3);
		des->setString(magic->des->getString());
	}break;

	case 2: {           //���������
		auto temPoint = battery->convertToWorldSpace(iconVector[i - 1]->getPosition());
		slected->setPosition(temPoint);
		battery->setDes(choosestate - 6);
		des->setString(battery->des->getString());
	}break;
	}
	if (levelVector[choosestate-1]<=3) {   //δ��������ʾ������ť
		upButton->setVisible(true);
		//upDes->setVisible(true);
		starCost->setVisible(true);
		starCostDes->setString(String::createWithFormat("%d", price[i - 1][levelVector[i - 1]])->getCString());
		starCostDes->setVisible(true);
	}
	else {                       //�Ѿ��������ü۸��������ť��ʧ
		upButton->setVisible(false);
		//upDes->setVisible(false);
		starCost->setVisible(false);
		starCostDes->setVisible(false);
	}
}
	des->setLocalZOrder(3);

}

void UpLayer::swallow(int i) {     //��������Ļ�հײ��֣����ÿ���������ʧ��ѡ��ͼ��İ׿���ʧ
	choosestate = i;
	slected->setVisible(false);
	starCostDes->setVisible(false);
	starCost->setVisible(false);
	des->setLocalZOrder(1);
}


void UpLayer::quit(Ref* pSender) {
	//�鳤��д�ĺ���
	array->setLevel(SPEED);
	battery->setLevel(POWER);
	magic->setLevel(NORMAL);
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5f, scene));
	
}
void UpLayer::getLevel() {
	//��֪��ǰÿ���츳�ĵȼ�������һ�������ڷ������
	levelVector[0] = array->forceLevel;  levelVector[1] = array->speedLevel;  levelVector[2] = array->MaxLevel;
	levelVector[3] = magic->forceLevel; levelVector[4] = magic->speedLevel; levelVector[5] = magic->MaxLevel;
	levelVector[6] = battery->forceLevel; levelVector[7] = battery->speedLevel; levelVector[8] = battery->MaxLevel;
}
