#include "BaseUpIcon.h"



BaseUpIcon::BaseUpIcon()
{
	forceLevel = 0;
	scopeLevel = 0;
	speedLevel = 0;
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
	forceIcon->setPosition(0, 80);
	scopeIcon->setPosition(-80, 80);
	speedIcon->setPosition(80, 80);
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


