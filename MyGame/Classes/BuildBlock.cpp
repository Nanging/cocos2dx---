#include "BuildBlock.h"
#include"UpdateMenuLayer.h"
bool BuildBlock::init(){
	if (!Sprite::init()){
		return false;
	}
	isUpdateMenuShown = false;
	buildBlock = Sprite::create("png/buildBlock.png");
	addChild(buildBlock);
	isBuilted = false;
	auto listener = EventListenerMouse::create();//监听鼠标事件
	listener->onMouseUp = CC_CALLBACK_1(BuildBlock::mouseClick, this);
	listener->onMouseDown = [=](Event* event) {
		if (Targeted(event)) {
			buildBlock->setScale(0.95f);//点击时产生缩放效果
		}
	};
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void BuildBlock::mouseClick(Event* event) {
	if(!isBuilted){
	buildBlock->setScale(1);//消除缩放
	if (isUpdateMenuShown) {
		hideUpdateMenu();
	}
	else {
		if(buildBlock->isVisible())
			showUpdateMenu(event);
	}
	}
}

void BuildBlock::showUpdateMenu(Event* event) {
	if (Targeted(event)) {//如果点击到
		auto updateMenu = UpdateMenu::create();
		updateMenu->setPosition(this->getPosition());
		updateMenu->setTag(100);
		this->getParent()->addChild(updateMenu,100);//在地图层中添加菜单
		updateMenu->setMyBlock(this);//设置菜单的myBlock
		updateMenu->UpdateMenu::inAnimation();//菜单打开动画

		isUpdateMenuShown = true;
	}
}

void BuildBlock::hideUpdateMenu() {
	this->getParent()->removeChildByTag(100);
	isUpdateMenuShown = false;
	buildBlock->setVisible(true);
}

bool BuildBlock::Targeted(Event* event) {//用于判断鼠标点击位置是否在贴图上
	auto rect = buildBlock->getBoundingBox();
	EventMouse* e = (EventMouse*)event;
	float cursorX = e->getCursorX();
	float cursorY = e->getCursorY();
	Point position = Point(cursorX, cursorY);
	Point locationInNode = this->convertToNodeSpace(position);
	if (rect.containsPoint(locationInNode)) {
		return true;
	}
	else
		return false;
}