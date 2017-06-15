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
	auto listener = EventListenerMouse::create();//��������¼�
	listener->onMouseUp = CC_CALLBACK_1(BuildBlock::mouseClick, this);
	listener->onMouseDown = [=](Event* event) {
		if (Targeted(event)) {
			buildBlock->setScale(0.95f);//���ʱ��������Ч��
		}
	};
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void BuildBlock::mouseClick(Event* event) {
	if(!isBuilted){
	buildBlock->setScale(1);//��������
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
	if (Targeted(event)) {//��������
		auto updateMenu = UpdateMenu::create();
		updateMenu->setPosition(this->getPosition());
		updateMenu->setTag(100);
		this->getParent()->addChild(updateMenu,100);//�ڵ�ͼ������Ӳ˵�
		updateMenu->setMyBlock(this);//���ò˵���myBlock
		updateMenu->UpdateMenu::inAnimation();//�˵��򿪶���

		isUpdateMenuShown = true;
	}
}

void BuildBlock::hideUpdateMenu() {
	this->getParent()->removeChildByTag(100);
	isUpdateMenuShown = false;
	buildBlock->setVisible(true);
}

bool BuildBlock::Targeted(Event* event) {//�����ж������λ���Ƿ�����ͼ��
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