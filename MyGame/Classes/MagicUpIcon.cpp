#include "MagicUpIcon.h"



MagicUpIcon::MagicUpIcon():BaseUpIcon()
{
}


MagicUpIcon::~MagicUpIcon()
{
}

bool MagicUpIcon::init() {
	if (!BaseUpIcon::init()) {
		return false;
	}
	getLevel(MAGIC);
	initIcon();
	kindSprite = Sprite::create("png/kind2.png");
	kindSprite->setScale(0.9f);
	kindSprite->setPosition(0, 0);
	addChild(kindSprite);
	auto listener = EventListenerMouse::create();  //注册鼠标悬停
	listener->onMouseMove = CC_CALLBACK_1(MagicUpIcon::mouseTip, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, forceIcon);
	return true;
}

void MagicUpIcon::setDes(int i) {   //根据点击的图标设置文字描述

	int tem = 0;
	switch (i) {
	case 1:
		tem = forceLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("force enhance :\nnow effect :%d percent improve\nnext level effect: %d percent improve",
				effect[0][forceLevel], effect[0][forceLevel+1])->getCString());
		}
		else {
			des->setString("you have reached max level 100 percent improve in total");
		}break;
	case 2:
		tem = speedLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("speed enhance :\nnow effect :%d percent improve\nnext level effect: %d percent improve",
				effect[1][speedLevel],effect[1][speedLevel+1])->getCString());
		}
		else {
			des->setString("you have reached max level 100 percent improve in total");
		}break;
	case 3:
		tem = MaxLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("improve magic towers'\nmaxlevel by 1\nnow maxlevel: %d\nnext level effect:\nlet the maxlevel be %d",
				MaxLevel,MaxLevel+1)->getCString());
		}
		else {
			des->setString("now maxLevel:4");
		}break;

	}
}

void MagicUpIcon::upForce() {
	forceLevel++;
	setDes(1);
	forceIcon->setNormalImage(Sprite::create("png/forceUp.png"));
	forceIcon->setSelectedImage(Sprite::create("png/forceUp.png"));
}

void MagicUpIcon::upScope() {
	speedLevel++;
	setDes(2);
	speedIcon->setNormalImage(Sprite::create("png/scopeUp.png"));
	speedIcon->setSelectedImage(Sprite::create("png/scopeUp.png"));
}

void MagicUpIcon::upSpeed() {
	MaxLevel++;
	setDes(3);
	levelIcon->setNormalImage(Sprite::create("png/speedUp.png"));
	levelIcon->setSelectedImage(Sprite::create("png/speedUp.png"));
}

void MagicUpIcon::reset() {
	forceIcon->setNormalImage(Sprite::create("png/unUpForce.png"));        //重置图片
	forceIcon->setSelectedImage(Sprite::create("png/unUpForce.png"));
	speedIcon->setNormalImage(Sprite::create("png/unUpScope.png"));
	speedIcon->setSelectedImage(Sprite::create("png/unUpScope.png"));
	levelIcon->setNormalImage(Sprite::create("png/unUpSpeed.png"));
	levelIcon->setSelectedImage(Sprite::create("png/unUpSpeed.png"));
	forceLevel = 0;
	speedLevel = 0;
	MaxLevel = 1;
}


void MagicUpIcon::mouseTip(EventMouse* e) {

	briefDes->setVisible(true);
	bubble->setVisible(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point localNode = e->getLocation();
	localNode.y = visibleSize.height - localNode.y;
	auto reNode = this->convertToNodeSpace(localNode);
	if (forceIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' force");
		auto temPoint = forceIcon->getPosition() + forceIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else if (speedIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' speed");
		auto temPoint = speedIcon->getPosition() + speedIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else if (levelIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' maxlevel");
		auto temPoint = levelIcon->getPosition() + levelIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else {
		briefDes->setVisible(false);
		bubble->setVisible(false);
	}

}
void MagicUpIcon::initIcon() {
	if (this->forceLevel != 0) {
		forceIcon->setNormalImage(Sprite::create("png/forceUp.png"));
		forceIcon->setSelectedImage(Sprite::create("png/forceUp.png"));
	}
	if (this->speedLevel != 0) {
		speedIcon->setNormalImage(Sprite::create("png/scopeUp.png"));
		speedIcon->setSelectedImage(Sprite::create("png/scopeUp.png"));
	}
	if (this->MaxLevel != 1) {
		levelIcon->setNormalImage(Sprite::create("png/speedUp.png"));
		levelIcon->setSelectedImage(Sprite::create("png/speedUp.png"));
	}
}
