#include "BatteryUpIcon.h"



BatteryUpIcon::BatteryUpIcon():BaseUpIcon()
{
}


BatteryUpIcon::~BatteryUpIcon()
{
}

bool BatteryUpIcon::init() {//����ѡ�е�ͼ��������������
	if (!BaseUpIcon::init()) {
		return false;
	}
	getLevel(POWER);
	kindSprite = Sprite::create("kind3.png");
	kindSprite->setScale(0.9f);
	kindSprite->setPosition(0, 0);
	addChild(kindSprite);
	auto listener = EventListenerMouse::create();  //ע�������ͣ
	listener->onMouseMove = CC_CALLBACK_1(BatteryUpIcon::mouseTip, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, forceIcon);
	return true;
}

void BatteryUpIcon::setDes(int i) {

	int tem = 0;
	switch (i) {
	case 1:
		tem = forceLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("force enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		else {
			des->setString("you have reached max level 100 cent improve in total");
		}break;
	case 2:
		tem = speedLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("scope enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		else {
			des->setString("you have reached max level 100 cent improve in total");
		}break;
	case 3:
		tem = MaxLevel;
		if (tem <= 3) {
			des->setString(__String::createWithFormat("speed enhance :\n\nnow effect :%d cent improve\n\nnext level effect %d cent improve",
				tem*(tem + 1) * 5, (tem + 1)*(tem + 2) * 5)->getCString());
		}
		else {
			des->setString("you have reached max level 100 cent improve in total");
		}break;

	}
}

void BatteryUpIcon::upForce() {
	forceLevel++;
	setDes(1);
	forceIcon->setNormalImage(Sprite::create("forceUp.png"));
	forceIcon->setSelectedImage(Sprite::create("forceUp.png"));
}

void BatteryUpIcon::upScope() {
	speedLevel++;
	setDes(2);
	scopeIcon->setNormalImage(Sprite::create("scopeUp.png"));
	scopeIcon->setSelectedImage(Sprite::create("scopeUp.png"));
}

void BatteryUpIcon::upSpeed() {
	MaxLevel++;
	setDes(3);
	speedIcon->setNormalImage(Sprite::create("speedUp.png"));
	speedIcon->setSelectedImage(Sprite::create("speedUp.png"));
}

void BatteryUpIcon::reset() {
	forceIcon->setNormalImage(Sprite::create("unUpForce.png"));        //����ͼƬ
	forceIcon->setSelectedImage(Sprite::create("unUpForce.png"));
	scopeIcon->setNormalImage(Sprite::create("unUpScope.png"));
	scopeIcon->setSelectedImage(Sprite::create("unUpScope.png"));
	speedIcon->setNormalImage(Sprite::create("unUpSpeed.png"));
	speedIcon->setSelectedImage(Sprite::create("unUpSpeed.png"));
	forceLevel = 0;
	speedLevel = 0;
	MaxLevel = 0;
}

void BatteryUpIcon::mouseTip(EventMouse* e) {
	briefDes->setVisible(true);
	bubble->setVisible(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point localNode = e->getLocation();
	localNode.y = visibleSize.height - localNode.y;
	auto reNode = this->convertToNodeSpace(localNode);
	if (forceIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve battery\ntowers' force");
		auto temPoint = forceIcon->getPosition() + forceIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else if (scopeIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve battery\ntowers' scope");
		auto temPoint = scopeIcon->getPosition() + scopeIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else if (speedIcon->getBoundingBox().containsPoint(reNode)) {
		briefDes->setString("improve battery\ntowers' speed");
		auto temPoint = speedIcon->getPosition() + speedIcon->getContentSize();
		briefDes->setPosition(temPoint);
		bubble->setPosition(temPoint);
	}
	else {
		briefDes->setVisible(false);
		bubble->setVisible(false);
	}

}