#include "BaseUpIcon.h"



BaseUpIcon::BaseUpIcon()
{

}


BaseUpIcon::~BaseUpIcon()
{
}

bool BaseUpIcon::init() {
	if (!Sprite::init()) {
		return false;
	}
	forceLevel = 0;
	speedLevel = 0;
	MaxLevel = 1;
	des = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	des->setString("OK");
	briefDes = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	briefDes->setVisible(false);
	bubble = Sprite::create("pao_brown.png");
	bubble->setScale(0.6f);
	bubble->setVisible(false);
	this->addChild(briefDes,9);
	this->addChild(bubble,5);
	auto circle = Sprite::create("circle.png");
	this->addChild(circle,0);
	circle->setPosition(Vec2(0, 0));
	circle->setScale(0.8f);

	forceIcon = MenuItemImage::create("unUpForce.png", "unUpForce.png");
	speedIcon = MenuItemImage::create("unUpScope.png", "unUpScope.png");
	levelIcon = MenuItemImage::create("unUpSpeed.png", "unUpSpeed.png");
	forceIcon->setScale(0.8f);
	speedIcon->setScale(0.8f);
	levelIcon->setScale(0.8f);
	forceIcon->setPosition(0, 110);
	speedIcon->setPosition(-110, 0);
	levelIcon->setPosition(110, 0);
	auto menu = Menu::create(forceIcon, speedIcon, levelIcon, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	this->addChild(des, 1);
	des->setVisible(false);
	return true;
}

void BaseUpIcon::setLevel(Tower n) 
{
	auto player = Player::getInstance();
	std::string str;
	str.resize(3);
	str.at(0) = forceLevel + '0';
	str.at(1) = speedLevel + '0';
	str.at(2) = MaxLevel + '0';
	player->setTechLevel(n, str);
}
void BaseUpIcon::getLevel(Tower n)
{
	auto player = Player::getInstance();
	forceLevel = player->getTechLevel(n, UpForce);
	speedLevel = player->getTechLevel(n, UpSpeed);
	MaxLevel = player->getTechLevel(n, UpMaxLevel);
}


