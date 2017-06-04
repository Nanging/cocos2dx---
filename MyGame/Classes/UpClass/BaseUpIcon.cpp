#include "BaseUpIcon.h"



BaseUpIcon::BaseUpIcon()
{
	forceLevel = 0;
	speedLevel = 0;
	MaxLevel = 0;
	des = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	des->setString("OK");
	briefDes = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	briefDes->setVisible(false);
	bubble = Sprite::create("pao.png");
	bubble->setScale(0.6f);
	bubble->setVisible(false);
	addChild(briefDes);
	addChild(bubble);
	forceIcon = MenuItemImage::create("unUpForce.png", "unUpForce.png");
	scopeIcon = MenuItemImage::create("unUpScope.png", "unUpScope.png");
	speedIcon = MenuItemImage::create("unUpSpeed.png", "unUpSpeed.png");
	forceIcon->setScale(0.8f);
	scopeIcon->setScale(0.8f);
	speedIcon->setScale(0.8f);
	forceIcon->setPosition(0, 100);
	scopeIcon->setPosition(-100, 100);
	speedIcon->setPosition(100, 100);
	auto menu = Menu::create(forceIcon, scopeIcon, speedIcon, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
	addChild(des, 1);
	des->setVisible(false);
}


BaseUpIcon::~BaseUpIcon()
{
}

bool BaseUpIcon::init() {
	if (!Sprite::init()) {
		return false;
	}
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

void BaseUpIcon::initIcon() {
	if (this->forceLevel != 0) {
		forceIcon->setNormalImage(Sprite::create("forceUp.png"));
		forceIcon->setSelectedImage(Sprite::create("forceUp.png"));
	}
	if (this->speedLevel != 0) {
		scopeIcon->setNormalImage(Sprite::create("scopeUp.png"));
		scopeIcon->setSelectedImage(Sprite::create("scopeUp.png"));
	}
	if (this->speedLevel != 0) {
		speedIcon->setNormalImage(Sprite::create("speedUp.png"));
		speedIcon->setSelectedImage(Sprite::create("speedUp.png"));
	}
}
