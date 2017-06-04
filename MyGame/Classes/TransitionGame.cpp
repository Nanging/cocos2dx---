#include "TransitionGame.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


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
	auto _scene = new TransitionGame();
	if (_scene && _scene->initWithDuration(t, scene))
	{
		_scene->autorelease();
		return _scene;
	}
	CC_SAFE_DELETE(_scene);
	return NULL;
}
void TransitionGame::onEnter()
{
	SimpleAudioEngine::getInstance()->playEffect("GUITransitionOpen.wav");
	_inScene->setVisible(false);
	TransitionScene::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	//×ó±ßµÄ±³¾°
	auto leftDoor = Sprite::create("transition_left.png");
	leftDoor->setScale((size.width / 2) / leftDoor->getContentSize().width, size.height / leftDoor->getContentSize().height);
	leftDoor->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftDoor,1);
	leftDoor->setPosition(Vec2(0, size.height / 2));
	//×ó±ßlogo
	auto leftLogo = Sprite::create("logo_left.png");
	leftLogo->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftLogo, 3);
	leftLogo->setPosition(Vec2(0, size.height / 2 + leftLogo->getContentSize().height / 4));
	//×ó±ßµÄ¼ÓÔØÍ¼Æ¬
	auto leftLoad = Sprite::create("load_left.png");
	leftLoad->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(leftLoad, 5);
	leftLoad->setPosition(Vec2(0, size.height / 2 - leftLogo->getContentSize().height / 2));


	//×ó±ßÖ´ÐÐ¶¯×÷
	auto moveby = MoveBy::create(_duration / 3, Vec2(size.width / 2, 0));
	auto delay = DelayTime::create(_duration / 3);
	auto change = CallFuncN::create(CC_CALLBACK_0(TransitionGame::OnSencondActionFinish, this));
	auto over = CallFuncN::create(CC_CALLBACK_0(TransitionGame::LRFinish, this));
	auto leftAction = Sequence::create(moveby, change, delay, moveby->reverse(), over, NULL);
	leftLogo->runAction(leftAction->clone());
	leftLoad->runAction(leftAction->clone());
	leftDoor->runAction(leftAction);
	

	
	auto rightDoor = Sprite::create("transition_right.png");
	rightDoor->setScale((size.width / 2) / rightDoor->getContentSize().width, size.height / rightDoor->getContentSize().height);
	rightDoor->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightDoor, 1);
	rightDoor->setPosition(Vec2(size.width, size.height / 2));

	auto rightLogo = Sprite::create("logo_right.png");
	rightLogo->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightLogo, 3);
	rightLogo->setPosition(Vec2(size.width, size.height / 2 + rightLogo->getContentSize().height / 4));

	auto rightLoad = Sprite::create("load_right.png");
	rightLoad->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(rightLoad, 5);
	rightLoad->setPosition(Vec2(size.width, size.height / 2 - rightLogo->getContentSize().height / 2+2));

	auto rightAction = Sequence::create(moveby->clone()->reverse(), delay->clone(), moveby->clone(), NULL);
	rightLogo->runAction(rightAction->clone());
	rightLoad->runAction(rightAction->clone());
	rightDoor->runAction(rightAction);

}
void TransitionGame::LRFinish()
{
	SimpleAudioEngine::getInstance()->playEffect("GUITransitionClose.wav");
	auto sound = SimpleAudioEngine::getInstance();
	if (!sound->isBackgroundMusicPlaying())
	{
		sound->resumeBackgroundMusic();
	}
	TransitionScene::finish();
}
void TransitionGame::OnSencondActionFinish()
{
	auto sound = SimpleAudioEngine::getInstance();
	//if (sound->isBackgroundMusicPlaying())
	//{
	//	sound->pauseBackgroundMusic();
	//}
	_inScene->setVisible(true);
	if (sound->isBackgroundMusicPlaying())
	{
		sound->pauseBackgroundMusic();
	}
	//_outScene->removeAllChildren();
	_outScene->setVisible(false);
	//if (sound->isBackgroundMusicPlaying())
	//{
	//	sound->pauseBackgroundMusic();
	//}
	
}