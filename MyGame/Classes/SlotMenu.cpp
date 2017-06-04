#include "SlotMenu.h"
#include "TransitionGame.h"
#include "Player.h"
#include "StartGame.h"
#include "MainMap.h"
SlotMenu::SlotMenu()
{
	log("---SlotMenu---");
}
SlotMenu::~SlotMenu()
{
	log("---SlotMenu-Deleted---");
}
SlotMenu* SlotMenu::createMenu(int num)
{
	auto slotMenu = new SlotMenu();

	if (slotMenu && slotMenu->initWithNum(num))
	{
		slotMenu->autorelease();
		return slotMenu;
	}
	CC_SAFE_DELETE(slotMenu);
	return NULL;
}
bool SlotMenu::initWithNum(int num)
{
	if (!Sprite::init())
	{
		return false;
	}
	slotNumber = num;
	//»ñµÃÍæ¼Ò
	auto player = Player::getInstance();

	savelot = MenuItemImage::create("SaveSlot_normal.png", "SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::createNewGame, this));
	auto newGame = Menu::createWithItem(savelot);
	newGame->setPosition(Vec2(0, 0));
	this->addChild(newGame,0);

	initMenu();

	auto status = player->saveStatus[num];
	log("-------%d----%d-------", num,status);
	if (status)
	{
		star->setVisible(true);
		__String *str1 = __String::createWithFormat("SaveSlot %d", num);
		labelHint = Label::createWithSystemFont(str1->getCString(), "arial", 30); 
		labelHint->setPosition(Vec2(0, 30));
		__String *str2 = __String::createWithFormat("%02d/%d", player->getScore(num),TotalScore);
		scoreLabel = Label::createWithSystemFont(str2->getCString(), "arial", 30);
		scoreLabel->setPosition(Vec2(20, -30));
		this->addChild(scoreLabel,1);

		newGame->setEnabled(false);
		savelot = MenuItemImage::create("SaveSlot_normal.png", "SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::startGame, this, num));
		auto startGame = Menu::createWithItem(savelot);
		startGame->setPosition(Vec2(0, 0));
		this->addChild(startGame,0);
	} 
	else
	{
		labelHint = Label::createWithSystemFont("New Game", "arial", 40);
		labelHint->setPosition(Vec2(0, 0));
		buttonSavelotDelete->setVisible(false);

	}
	this->addChild(labelHint);

	return true;
}
void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
	log("---Delete-SaveSlot---");
	__String *str = __String::create("Delete SaveSlot ?");
	labelHint->setString(str->getCString());

	confirmMenu->setVisible(true);

	buttonSavelotDelete->setVisible(false);
	star->setVisible(false);
	scoreLabel->setVisible(false);
	savelot->setEnabled(false);
}
void SlotMenu::confirm_delete(Ref* pSender)
{
	log("---Confirm-Delete-Save-%d---", slotNumber);
	auto player = Player::getInstance();
	player->resetSaveSlot(slotNumber);
	confirmMenu->setVisible(false);
	initWithNum(slotNumber);
}
void SlotMenu::cancel_delete(Ref* pSender)
{
	log("---Cancel-Delete-%d---", slotNumber);
	confirmMenu->setVisible(false);
	initWithNum(slotNumber);
	
}
void SlotMenu::createNewGame()
{
	log("---New-Game-%d--", slotNumber);
	auto player = Player::getInstance();
	player->startSaveSlot(slotNumber);
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}
void SlotMenu::startGame(int num)
{
	log("---Start-SaveSlot-%d---", num);
	auto player = Player::getInstance();
	player->startSaveSlot(num);
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}
void SlotMenu::initMenu()
{
	buttonSavelotDelete = MenuItemImage::create("delete_botton_normal.png", "delete_botton_seleted.png", CC_CALLBACK_1(SlotMenu::button_Savelot_Delete_callback, this));
	auto menuDelete = Menu::createWithItem(buttonSavelotDelete);
	menuDelete->setPosition(Vec2(savelot->getContentSize().width / 2, savelot->getContentSize().height / 2));
	this->addChild(menuDelete, 1);

	star = Sprite::create("star_count.png");
	star->setPosition(Vec2(-60, -30));
	star->setVisible(false);
	this->addChild(star, 1);

	auto confirm_botton = MenuItemImage::create("button_confirm.png", "button_confirm.png", CC_CALLBACK_1(SlotMenu::confirm_delete, this));
	auto cancel_botton = MenuItemImage::create("button_cancel.png", "button_cancel.png", CC_CALLBACK_1(SlotMenu::cancel_delete, this));
	confirmMenu = Menu::create(confirm_botton, cancel_botton, NULL);
	confirmMenu->setPosition(Vec2(0, -30));
	confirmMenu->alignItemsHorizontallyWithPadding(50);
	this->addChild(confirmMenu, 3);

	confirmMenu->setVisible(false);
}