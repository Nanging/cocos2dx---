#include "MainMap.h"
#include "Player.h"
#include "StartGame.h"
#include "TransitionGame.h"
#include "UpLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
MainMap::MainMap()
{
	
	log("---Map-In---");
}
MainMap::~MainMap()
{
	log("---Map-Out---");
	//auto sound = SimpleAudioEngine::getInstance();
	//if (sound->isBackgroundMusicPlaying())
	//{
	//	sound->stopBackgroundMusic(false);
	//}
}
Scene * MainMap::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMap::create();
	scene->setTag(TAG_SCENE);
	scene->addChild(layer,0,TAG_MAP);
	return scene;
}
bool MainMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initLabel();
	initBotton();
	initMap();
	initFlag();

	return true;
}
//void MainMap::MapScroll(Ref* r, ScrollView::EventType e)
//{
//	switch (e)
//	{
//	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_TOP:
//		break;
//	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
//		break;
//	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_LEFT:
//		break;
//	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_RIGHT:
//		break;
//	case cocos2d::ui::ScrollView::EventType::SCROLLING:
//		break;
//	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
//		break;
//	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
//		break;
//	case cocos2d::ui::ScrollView::EventType::BOUNCE_LEFT:
//		break;
//	case cocos2d::ui::ScrollView::EventType::BOUNCE_RIGHT:
//		break;
//	case cocos2d::ui::ScrollView::EventType::CONTAINER_MOVED:
//		break;
//	case cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED:
//		break;
//	default:
//		break;
//	}
//}
//void MainMap::StageOne(Ref * psender)
//{
//	log("---stage-one---");
//	auto flag = dynamic_cast<Node*>(psender);
//	flag->setVisible(false);
//	auto s = StartGame::createScene();
//	Director::getInstance()->replaceScene(TransitionGame::create(1.5, s));
//}
//void MainMap::StageTwo(Ref * psender)
//{
//	log("---stage-two---");
//	auto flag = dynamic_cast<Node*>(psender);
//	flag->setVisible(false);
//
//}
//void MainMap::StageThree(Ref * psender)
//{
//	log("---stage-three---");
//	auto flag = dynamic_cast<Node*>(psender);
//	flag->setVisible(false);
//}
void MainMap::initMap()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Map_Theme_1.wav", true);
	Size size = Director::getInstance()->getVisibleSize();
	sv = ScrollView::create();
	sv->setDirection(ScrollView::Direction::BOTH);
	//sv->addEventListener(CC_CALLBACK_2(MainMap::MapScroll, this));
	sv->setAnchorPoint(Vec2(0.5, 0.5));
	sv->setScrollBarEnabled(false);
	sv->setInnerContainerSize(size*scale);
	sv->setContentSize(size);
	sv->setPosition(Vec2(size.width / 2, size.height / 2));
	sv->setInnerContainerPosition(Vec2(0, 0));
	this->addChild(sv, -1);


	auto mainMap = ImageView::create("mainmap.png");
	sv->addChild(mainMap, -1);
	mainMap->setPosition(Vec2(scale*size.width / 2, scale*size.height / 2));
	mainMap->setScale(scale*size.width / mainMap->getContentSize().width, scale*size.height / mainMap->getContentSize().height);

	flagOne = StageFlag::create(1);
	flagOne->setScale(0.7f);
	sv->addChild(flagOne,3,TAG_FLAG_ONE);
	flagOne->setPosition(Vec2(1.2*size.width / 6, 1.2*size.height / 2));
	flagOne->setVisible(false);

	flagTwo = StageFlag::create(2);
	flagTwo->setScale(0.7f);
	sv->addChild(flagTwo,3,TAG_FLAG_TWO);
	flagTwo->setPosition(Vec2(1.6*size.width / 4, 1.8*size.height / 2));
	flagTwo->setVisible(false);

	flagThree = StageFlag::create(3);
	flagThree->setScale(0.7f);
	sv->addChild(flagThree,3,TAG_FLAG_THREE);
	flagThree->setPosition(Vec2(1.2*size.width / 2, 1.3*size.height / 2));
	flagThree->setVisible(false);

	//auto mapseleter = Menu::create(flagOne, flagTwo, flagThree, NULL);
	//mapseleter->setPosition(Vec2(0, 0));
	//sv->addChild(mapseleter, 3);
}
void MainMap::initFlag()
{
	auto player = Player::getInstance();
	log("-%d-%d-%d-", player->saveStatus[1], player->saveStatus[2], player->saveStatus[3]);
	auto num = player->currentSave;
	log("----%d-----", num);
	auto stage =  player->getStage(num);
	flagOne->setVisible(true);
	if (stage>=1)
	{
		flagTwo->setVisible(true);
	}
	if (stage>=2)
	{
		flagThree->setVisible(true);
	}
	if (stage>=3)
	{
		log("impossible----");
	}
}
void MainMap::ToMainMenu(Ref * psender)
{
	//auto player = Player::getInstance();
	//player->updateXML();
	log("---Back-To-MainMenu---");
	auto scene = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}
void MainMap::techScene(Ref * psender)
{
	log("---Go-Tech---");
	auto scene = UpLayer::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
	//auto l = dynamic_cast<MainMap *>(UtilTool::getLayerByTag(TAG_MAP));
	//l->pause();
	//l->sv->setTouchEnabled(false);
	//dynamic_cast<StageFlag*>(l->sv->getChildByTag(1))->flag->pause();
}
void MainMap::initBotton()
{
	Size size = Director::getInstance()->getVisibleSize();
	auto backToMenu = MenuItemImage::create("back_to_menu_normal.png", "back_to_menu_seleted.png", CC_CALLBACK_1(MainMap::ToMainMenu, this));
	backToMenu->setScale(0.5);
	backToMenu->setPosition(size.width - 0.5*backToMenu->getContentSize().width, size.height - 0.5*backToMenu->getContentSize().height);

	auto tech = MenuItemImage::create("t_normal.png", "t_seleted.png", CC_CALLBACK_1(MainMap::techScene, this));
	tech->setScale(0.5);
	tech->setPosition(size.width - 0.5 * tech->getContentSize().width, 0.5 * tech->getContentSize().height);


	auto hudBotton = Menu::create(backToMenu, tech, NULL);
	hudBotton->setPosition(Vec2(0, 0));
	this->addChild(hudBotton, 3);

}
void MainMap::initLabel()
{
	Size size = Director::getInstance()->getVisibleSize();
	auto player = Player::getInstance();
	__String *str = __String::createWithFormat("%d", player->getScore(0));
	score = Label::createWithBMFont("Number_1.fnt", str->getCString());
	score->setScale(2);
	auto scoreBG = Sprite::create("start_count.png");
	scoreBG->setScale(0.5);
	scoreBG->setPosition(Vec2(0.5 * scoreBG->getContentSize().width, size.height - 0.5 * scoreBG->getContentSize().height));
	this->addChild(scoreBG);
	scoreBG->addChild(score);
	score->setPosition(Vec2(scoreBG->getContentSize().width * 0.8, scoreBG->getContentSize().height / 2));
}