#include "TowerIcon.h"
#include "Player.h"

TowerIcon* TowerIcon::createIcon(int type, int money)
{
	auto towerIcon = new TowerIcon();

	if (towerIcon && towerIcon->initIcon(type, money)){
		towerIcon->autorelease();
		return towerIcon;
	}
	CC_SAFE_DELETE(towerIcon);
	return NULL;
}

bool TowerIcon::initIcon(int type, int money){
	if (!Sprite::init())
	{
		return false;
	}
	isSelected = false;
	towerIcon = Sprite::create(String::createWithFormat("png/towerIcons_%02d.png", type)->getCString());
	towerIcon->setScale(1);

	addChild(towerIcon);
	

	priceIcon = Sprite::create("png/price_tag.png");
	priceIcon->setPosition(Point(0, -towerIcon->getContentSize().height / 2));
	addChild(priceIcon);

	std::string strMoney = std::to_string(money);
	priceLabel = Label::createWithTTF(strMoney, "fonts/Comic_Book.ttf", 30);
	priceLabel->setColor(Color3B(255, 153, 0));
	priceLabel->setPosition(Point(priceIcon->getContentSize().width / 2, priceIcon->getContentSize().height / 2));
	priceIcon->addChild(priceLabel);
	


	okIcon = Sprite::create("png/okIcon.png");
	okIcon->setPosition(Point(towerIcon->getContentSize().width / 2, towerIcon->getContentSize().height / 2));
	okIcon->setScale(1);
	if (type == 4) {
		okIcon->setScale(0.7f);
	}
	towerIcon->addChild(okIcon);
	okIcon->setVisible(false);
	
	setMoney(money);
	setType(type);
	this->scheduleUpdate();

	return true;
}//���ɸ��ְ�ť��ͼ����ʾ��Ӧ��Ǯ

void TowerIcon::setNotEnoughMoney(){//��Ǯ����״̬��������ɫ�ı䣬ֻ�ܽ���Ԥ�����޷��ڶ��ε��
	isAble = false;
	priceLabel->setColor(Color3B(102, 102, 102));
	Texture2D* ok_disabled = TextureCache::sharedTextureCache()->addImage("png/okIcon_disabled.png");
	okIcon->setTexture(ok_disabled);
}

void TowerIcon::setEnoughMoney(){//������ť
	isAble = true;
	priceLabel->setColor(Color3B(255, 153, 0));
	Texture2D* ok_abled = TextureCache::sharedTextureCache()->addImage("png/okIcon.png");
	okIcon->setTexture(ok_abled);
}

void TowerIcon::setSelected(){//��ѡ��״̬
	isSelected = true;
	okIcon->setVisible(true);
}

void TowerIcon::setNotSelected(){//��ʼ״̬
	isSelected = false;
	okIcon->setVisible(false);
}

void TowerIcon::update(float dt)
{
	if (type != 4) {//�����ǰ��ť���ǳ��۰�ť
		if (getMoney() <= Player::getInstance()->current.money) {//��ȡ��ǰ��Ǯ
			setEnoughMoney();//�жϲ��ı䰴ť״̬
		}
		else {
			setNotEnoughMoney();
		}
	}
}