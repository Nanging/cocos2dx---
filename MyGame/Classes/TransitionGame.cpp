#include "TransitionGame.h"



TransitionGame::TransitionGame()
{
	log("---Transition-Start---");
}


TransitionGame::~TransitionGame()
{
	log("---Transition-Over---");
}
TransitionGame * TransitionGame::create(float t, Scene *scene)
{
	auto _Scene = new TransitionGame();
	if (_Scene && _Scene->initWithDuration(t, scene))
	{
		_Scene->autorelease();
		return _Scene;
	}
	CC_SAFE_DELETE(_Scene);
	return NULL;
}
void TransitionGame::onEnter()
{
	_inScene->setVisible(false);
	TransitionScene::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	//×ó±ßµÄ±³¾°
	auto leftdoor = Sprite::create("transition_left.png");
	leftdoor->setScale((size.width / 2) / leftdoor->getContentSize().width, size.height / leftdoor->getContentSize().height);
	leftdoor->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftdoor,1);
	leftdoor->setPosition(Vec2(0, size.height / 2));
	//×ó±ßlogo
	auto leftlogo = Sprite::create("logo_left.png");
	leftlogo->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftlogo, 3);
	leftlogo->setPosition(Vec2(0, size.height / 2 + leftlogo->getContentSize().height / 4));
	//×ó±ßµÄ¼ÓÔØÍ¼Æ¬
	auto leftload = Sprite::create("load_left.png");
	leftload->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftload, 5);
	leftload->setPosition(Vec2(0, size.height / 2 - leftlogo->getContentSize().height / 2));


	//×ó±ßÖ´ÐÐ¶¯×÷
	auto moveby = MoveBy::create(_duration / 3, Vec2(size.width / 2, 0));
	auto delay = DelayTime::create(_duration / 3);
	auto change = CallFuncN::create(CC_CALLBACK_0(TransitionGame::OnSencondActionFinish, this));
	auto over = CallFuncN::create(CC_CALLBACK_0(TransitionGame::LRFinish, this));
	auto leftAction = Sequence::create(moveby, change, delay, moveby->reverse(), over, NULL);
	leftlogo->runAction(leftAction->clone());
	leftload->runAction(leftAction->clone());
	leftdoor->runAction(leftAction);
	

	
	auto rightdoor = Sprite::create("transition_right.png");
	rightdoor->setScale((size.width / 2) / rightdoor->getContentSize().width, size.height / rightdoor->getContentSize().height);
	rightdoor->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightdoor, 1);
	rightdoor->setPosition(Vec2(size.width, size.height / 2));

	auto rightlogo = Sprite::create("logo_right.png");
	rightlogo->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightlogo, 3);
	rightlogo->setPosition(Vec2(size.width, size.height / 2 + rightlogo->getContentSize().height / 4));

	auto rightload = Sprite::create("load_right.png");
	rightload->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightload, 5);
	rightload->setPosition(Vec2(size.width, size.height / 2 - rightlogo->getContentSize().height / 2+2));

	auto rightAction = Sequence::create(moveby->clone()->reverse(), delay->clone(), moveby->clone(), NULL);
	rightlogo->runAction(rightAction->clone());
	rightload->runAction(rightAction->clone());
	rightdoor->runAction(rightAction);

}
void TransitionGame::LRFinish()
{
	TransitionScene::finish();
}
void TransitionGame::OnSencondActionFinish()
{
	_inScene->setVisible(true);
	_outScene->setVisible(false);
}