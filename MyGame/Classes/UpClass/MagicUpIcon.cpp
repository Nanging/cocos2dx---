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
	kindSprite = Sprite::create("kind2.png");
	kindSprite->setScale(0.9f);
	kindSprite->setPosition(0, 0);
	addChild(kindSprite);
	auto listener = EventListenerMouse::create();  //ע�������ͣ
	listener->onMouseMove = CC_CALLBACK_1(MagicUpIcon::mouseTip, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, forceIcon);
	return true;
}

void MagicUpIcon::setDes(int i) {   //���ݵ����ͼ��������������

	int tem = 0;
	switch (i) {
	case 1:
		tem = forceLevel;
		if (tem <= 3) {
			des->setString(String::createWithFormat("force enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		else {
			des->setString("you have reached max level 100 cent improve in total");
		}break;
	case 2:
		tem = scopeLevel;
		if (tem <= 3) {
			des->setString(String::createWithFormat("scope enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		if (tem == 4) {
			des->setString("you have reached max level 100 cent improve in total");
		}break;
	case 3:
		tem = speedLevel;
		if (tem <= 3) {
			des->setString(String::createWithFormat("speed enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		if (tem == 4) {
			des->setString("you have reached max level 100 cent improve in total");
		}break;

	}
}

void MagicUpIcon::upForce() {
	forceLevel++;
	setDes(1);
	forceIcon->setNormalImage(Sprite::create("forceUp.png"));
	forceIcon->setSelectedImage(Sprite::create("forceUp.png"));
}

void MagicUpIcon::upScope() {
	scopeLevel++;
	setDes(2);
	scopeIcon->setNormalImage(Sprite::create("scopeUp.png"));
	scopeIcon->setSelectedImage(Sprite::create("scopeUp.png"));
}

void MagicUpIcon::upSpeed() {
	speedLevel++;
	setDes(3);
	speedIcon->setNormalImage(Sprite::create("speedUp.png"));
	speedIcon->setSelectedImage(Sprite::create("speedUp.png"));
}

void MagicUpIcon::reset() {
	forceIcon->setNormalImage(Sprite::create("unUpForce.png"));        //����ͼƬ
	forceIcon->setSelectedImage(Sprite::create("unUpForce.png"));
	scopeIcon->setNormalImage(Sprite::create("unUpScope.png"));
	scopeIcon->setSelectedImage(Sprite::create("unUpScope.png"));
	speedIcon->setNormalImage(Sprite::create("unUpSpeed.png"));
	speedIcon->setSelectedImage(Sprite::create("unUpSpeed.png"));
	forceLevel = 0;
	scopeLevel = 0;
	speedLevel = 0;
}


void MagicUpIcon::mouseTip(Event* event) {
	int i = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	EventMouse* e = (EventMouse*)event;
	Point localNode = e->getLocation();
	localNode.y = visibleSize.height - localNode.y;
	auto reNode = this->convertToNodeSpace(localNode);
	if (forceIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' force");
		auto temPoint = forceIcon->getPosition();
		temPoint.x += 40; temPoint.y += 80;
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
		i = 1;
	}
	else if (scopeIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' scope");
		auto temPoint = scopeIcon->getPosition();
		temPoint.x += 40; temPoint.y += 80;
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
		i = 2;
	}
	else if (speedIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve magic\ntowers' speed");
		auto temPoint = speedIcon->getPosition();
		temPoint.x += 40; temPoint.y += 80;
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
		i = 3;
	}
	else {
		i = 4;
	}

	if (i != 4) {
		briefDes->setVisible(true);
		bubble->setVisible(true);
	}
	if (i == 4) {
		briefDes->setVisible(false);
		bubble->setVisible(false);
	}
}