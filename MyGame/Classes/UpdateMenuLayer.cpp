#include "UpdateMenuLayer.h"
#include"Player.h"


bool UpdateMenu::init() {
	if (!Sprite::init()) {
		return false;
	}
	setMyBlock(NULL);
	setTower(NULL);
	isMenuShown = false;
	planesprite = Sprite::create("png/menuPanle.png");
	planesprite->setPosition(Point(0, 30));
	planesprite->setScale(0.2f);
	addChild(planesprite);
	return true;
}

void UpdateMenu::inAnimation() {
	planesprite->runAction(Sequence::create(ScaleTo::create(0.05f, 0.5, 0.5),
		CallFuncN::create(CC_CALLBACK_0(UpdateMenu::addIcons, this)),
		NULL));//菜单打开动画
}

void UpdateMenu::addIcons() {
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	if (getTower() != NULL) {//如果不是空地，生成升级菜单
		scopeCircle = ScopeCircle::create();
		nextScopeCircle = ScopeCircle::create();
		scopeCircle->setScale(tower->getAttackScope() / 360);
		addChild(scopeCircle, -1);
		scopeCircle->setVisible(true);
		nextScopeCircle->setScale(tower->getNextAttackScope() / 360);
		addChild(nextScopeCircle, -1);
		nextScopeCircle->setVisible(false);
		//生成攻击范围，并先隐藏
		int nextLevel = tower->getTowerLevel() + 1;
		int maxLevel = tower->getMaxLevel();//获得当前天赋下的满级
		if (maxLevel > 4)
			maxLevel = 4;
		if ((nextLevel <= maxLevel)) {//未到达顶级可继续升级
			int money = tower->getUpdateMoney();
			updateIcon = TowerIcon::createIcon(3, money);
			updateIcon->setScale(0.5);
			updateIcon->setPosition(Point(0, planesprite->getContentSize().height / 4 + 20));
			updateIcon->setMoney(money);
			addChild(updateIcon);

			auto mouseListener_1 = EventListenerMouse::create();
			mouseListener_1->onMouseUp = CC_CALLBACK_1(UpdateMenu::mouseClickUpdate, this);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_1, updateIcon);
			//升级按钮
		}
		else {
			auto lockedIcon = Sprite::create("png/lockedIcon.png");
			lockedIcon->setScale(0.5);
			lockedIcon->setPosition(Point(0, planesprite->getContentSize().height / 4 + 20));
			addChild(lockedIcon);
			//无法继续升级，显示上锁
		}
		int moneyBack = tower->getSellMoney();
		sellIcon = TowerIcon::createIcon(4, moneyBack);
		sellIcon->setScale(0.5);
		sellIcon->setPosition(Point(0, -(planesprite->getContentSize().height / 4) + 20));
		sellIcon->setMoney(moneyBack);
		addChild(sellIcon);

		auto mouseListener_2 = EventListenerMouse::create();
		mouseListener_2->onMouseUp = CC_CALLBACK_1(UpdateMenu::mouseClickSell, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_2, sellIcon);
		//出售按钮
	}
	else {//如果是空地，生成建造菜单
		arrowIcon = TowerIcon::createIcon(0, 70);
		arrowIcon->setScale(0.5);
		arrowIcon->setPosition(Point(-(planesprite->getContentSize().width / 4), 0 + 20));
		arrowIcon->setMoney(70);
		addChild(arrowIcon);

		cannonIcon = TowerIcon::createIcon(1, 100);
		cannonIcon->setScale(0.5);
		cannonIcon->setPosition(Point(0, planesprite->getContentSize().height / 4 + 20));
		cannonIcon->setMoney(100);
		addChild(cannonIcon);

		magicIcon = TowerIcon::createIcon(2, 100);
		magicIcon->setScale(0.5);
		magicIcon->setPosition(Point(planesprite->getContentSize().width / 4, 0 + 20));
		magicIcon->setMoney(100);
		addChild(magicIcon);

		auto mouseListener = EventListenerMouse::create();
		mouseListener->onMouseUp = CC_CALLBACK_1(UpdateMenu::mouseClickBuild, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, arrowIcon);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), cannonIcon);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), magicIcon);
		//三个建造按钮
	}

}

void UpdateMenu::mouseClickBuild(EventMouse* e) {
	auto target = static_cast<TowerIcon*>(e->getCurrentTarget());
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	Point position = Point(cursorX, cursorY);
	Point locationInNode = target->convertToNodeSpace(position);
	auto rect = target->towerIcon->getBoundingBox();
	if (rect.containsPoint(locationInNode)) {//判断鼠标点击位置
		e->stopPropagation();//吞没事件	
		auto myType = target->getType();
		if (!target->getIsSelected()) {//第一次点击
			addTowerDemo(myType);//生成预览
			arrowIcon->setNotSelected();
			cannonIcon->setNotSelected();
			magicIcon->setNotSelected();//重置其他按钮状态
			target->setSelected();
		}
		else {//第二次确认
			if (target->getIsAble()) {
				addTower(myType);
				myBlock->isBuilted = true;
				getParent()->removeChild(this, true);
			}
		}
	}
}

void UpdateMenu::addTowerDemo(int type) {//图标显示ok   显示塔的贴图   显示scope
	if (demoTower != NULL) {
		removeChild(demoTower, true);
	}
	if (scopeCircle != NULL) {
		removeChild(scopeCircle, true);
	}

	int scope = 0;
	this->myBlock->buildBlock->setVisible(false);
	switch (type) {
	case 0:demoTower = Sprite::create("png/arrowTower_1.png");
		demoTower->setPosition(Point(0, 0));
		scope = 160;
		break;
	case 1:demoTower = Sprite::create("png/cannonTower_1.png");
		demoTower->setPosition(Point(0, 0));
		scope = 150;
		break;
	case 2:demoTower = Sprite::create("png/magicTower_1.png");
		demoTower->setPosition(Point(0, 0));
		scope = 140;
		break;
	default:
		break;
	}
	addChild(demoTower);
	scopeCircle = ScopeCircle::create();
	scopeCircle->setVisible(true);
	scopeCircle->setScale(scope / 360.0f);
	scopeCircle->setPosition(Point(myBlock->getContentSize().width, myBlock->getContentSize().height));
	addChild(scopeCircle, -1);//预览时显示攻击范围
}

void UpdateMenu::addTower(int type) {
	removeChild(demoTower, true);
	if (scopeCircle != NULL) {
		myBlock->removeChild(scopeCircle, true);
	}
	switch (type) {
	case 0:
	{auto arrowTower = ArrowTowerLv1::create();
	arrowTower->setPosition(Point(0, 0));
	arrowTower->setSpriteLocation(myBlock);
	myBlock->addChild(arrowTower);
	Player::getInstance()->current.money -= 70;
	break; }
	case 1:
	{auto cannonTower = CannonTowerLv1::create();
	cannonTower->setPosition(Point(0, 0));
	cannonTower->setSpriteLocation(myBlock);
	myBlock->addChild(cannonTower);
	Player::getInstance()->current.money -= 100;
	break; }
	case 2:
	{auto magicTower = MagicTowerLv1::create();
	magicTower->setPosition(Point(0, 0));
	magicTower->setSpriteLocation(myBlock);
	myBlock->addChild(magicTower);
	Player::getInstance()->current.money -= 100;
	break; }
	default:break;
	}//建造并扣除金钱
}

void UpdateMenu::mouseClickUpdate(EventMouse* e) {
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	Point position = Point(cursorX, cursorY);
	Point locationInNode = updateIcon->convertToNodeSpace(position);
	auto rect = updateIcon->towerIcon->getBoundingBox();
	int lv = tower->getTowerLevel();
	int towerType = tower->getTowerType();
	if (rect.containsPoint(locationInNode)) {//判断鼠标点击位置

		e->stopPropagation();
		if (!updateIcon->getIsSelected()) {//第一次点击
			updateDemo(towerType, lv + 1);
			sellIcon->setNotSelected();//重置其他按钮状态
			updateIcon->setSelected();
		}
		else {//第二次确认
			if (updateIcon->getIsAble()) {
				update(towerType, lv);
				getParent()->removeChild(this, true);
			}
		}
	}
}

void UpdateMenu::updateDemo(int type, int Lv) {
	scopeCircle->setVisible(true);
	nextScopeCircle->setVisible(true);
	tower->setVisible(false);
	switch (type) {
	case 3:demoTower = Sprite::create(String::createWithFormat("png/arrowTower_%d.png", Lv)->getCString());
		demoTower->setPosition(Point(0, 0));
		break;
	case 2:demoTower = Sprite::create(String::createWithFormat("png/cannonTower_%d.png", Lv)->getCString());
		demoTower->setPosition(Point(0, 0));
		break;
	case 1:demoTower = Sprite::create(String::createWithFormat("png/magicTower_%d.png", Lv)->getCString());
		demoTower->setPosition(Point(0, 0));
		break;
	default:
		break;
	}
	addChild(demoTower);//预览并显示攻击范围变化
}

void UpdateMenu::update(int type, int Lv) {
	Player::getInstance()->current.money -= (tower->getUpdateMoney());//减去相应金钱
	switch (type) {
	case 3: {
		switch (Lv) {
		case 1: {static_cast<ArrowTowerLv1*>(tower)->towerUpdate(); break; }
		case 2: {static_cast<ArrowTowerLv2*>(tower)->towerUpdate(); break; }
		case 3: {static_cast<ArrowTowerLv3*>(tower)->towerUpdate(); break; }
		default:
			break;
		}
		break;
	}
	case 2: {
		switch (Lv) {
		case 1: {static_cast<CannonTowerLv1*>(tower)->towerUpdate(); break; }
		case 2: {static_cast<CannonTowerLv2*>(tower)->towerUpdate(); break; }
		case 3: {static_cast<CannonTowerLv3*>(tower)->towerUpdate(); break; }
		default:
			break;
		}
		break;
	}
	case 1: {
		switch (Lv) {
		case 1: {static_cast<MagicTowerLv1*>(tower)->towerUpdate(); break; }
		case 2: {static_cast<MagicTowerLv2*>(tower)->towerUpdate(); break; }
		case 3: {static_cast<MagicTowerLv3*>(tower)->towerUpdate(); break; }
		default:
			break;
		}
	default:
		break;
	}
			break;
	}//升级并减去金钱
}

void UpdateMenu::mouseClickSell(EventMouse* e) {
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	Point position = Point(cursorX, cursorY);
	Point locationInNode = sellIcon->convertToNodeSpace(position);
	auto rect = sellIcon->towerIcon->getBoundingBox();
	if (rect.containsPoint(locationInNode)) {//判断鼠标点击位置
		e->stopPropagation();
		auto myType = sellIcon->getType();
		if (!sellIcon->getIsSelected()) {//第一次
			if (updateIcon != NULL)
				updateIcon->setNotSelected();//重置其他按钮状态
			scopeCircle->setVisible(false);
			nextScopeCircle->setVisible(false);
			if (demoTower != NULL)
				demoTower->setVisible(false);
			tower->setVisible(true);
			sellIcon->setSelected();
		}
		else {//第二次确认
			myBlock->isBuilted = false;
			tower->towerSell();		
			getParent()->removeChild(this, true);			
		}//移除当前塔并返还金钱
	}
}