#include "SlotMenu.h"
#include "TransitionGame.h"
#include "Player.h"
#include "StartGame.h"
#include "MainMap.h"
SlotMenu::SlotMenu()
{
}
SlotMenu::~SlotMenu()
{
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
	//获得玩家
	auto player = Player::getInstance();

	savelot = MenuItemImage::create("png/SaveSlot_normal.png", "png/SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::createNewGame, this));
	auto newGame = Menu::createWithItem(savelot);
	newGame->setPosition(Vec2(0, 0));
	this->addChild(newGame,0);

	initMenu();
	//初始化存档
	auto status = player->saveStatus[num];
	if (status)
	{
		star->setVisible(true);
		__String *str1 = __String::createWithFormat("SaveSlot %d", num);
		labelHint = Label::createWithSystemFont(str1->getCString(), "fonts/arial", 30); 
		labelHint->setPosition(Vec2(0, 30));
		__String *str2 = __String::createWithFormat("%02d/%d", player->getScore(num),TotalScore);
		scoreLabel = Label::createWithSystemFont(str2->getCString(), "fonts/arial", 30);
		scoreLabel->setPosition(Vec2(20, -30));
		this->addChild(scoreLabel,1);

		newGame->setEnabled(false);
		savelot = MenuItemImage::create("png/SaveSlot_normal.png", "png/SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::startGame, this, num));
		auto startGame = Menu::createWithItem(savelot);
		startGame->setPosition(Vec2(0, 0));
		this->addChild(startGame,0);
	} 
	else
	{
		labelHint = Label::createWithSystemFont("New Game", "fonts/arial", 40);
		labelHint->setPosition(Vec2(0, 0));
		buttonSavelotDelete->setVisible(false);

	}
	this->addChild(labelHint);

	return true;
}
void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
	//存档删除确认
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
	//确认删除
	auto player = Player::getInstance();
	player->resetSaveSlot(slotNumber);
	player->updateXML();
	confirmMenu->setVisible(false);
	initWithNum(slotNumber);
}
void SlotMenu::cancel_delete(Ref* pSender)
{
	//取消删除
	confirmMenu->setVisible(false);
	initWithNum(slotNumber);
	
}
void SlotMenu::createNewGame()
{
	auto player = Player::getInstance();
	player->startSaveSlot(slotNumber);
	player->updateXML();
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}
void SlotMenu::startGame(int num)
{
	auto player = Player::getInstance();
	player->startSaveSlot(num);
	player->updateXML();
	auto scene = MainMap::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(1.5, scene));
}
void SlotMenu::initMenu()
{
	buttonSavelotDelete = MenuItemImage::create("png/delete_botton_normal.png", "png/delete_botton_seleted.png", CC_CALLBACK_1(SlotMenu::button_Savelot_Delete_callback, this));
	auto menuDelete = Menu::createWithItem(buttonSavelotDelete);
	menuDelete->setPosition(Vec2(savelot->getContentSize().width / 2, savelot->getContentSize().height / 2));
	this->addChild(menuDelete, 1);

	star = Sprite::create("png/star_count.png");
	star->setPosition(Vec2(-60, -30));
	star->setVisible(false);
	this->addChild(star, 1);

	auto confirm_botton = MenuItemImage::create("png/button_confirm.png", "png/button_confirm.png", CC_CALLBACK_1(SlotMenu::confirm_delete, this));
	auto cancel_botton = MenuItemImage::create("png/button_cancel.png", "png/button_cancel.png", CC_CALLBACK_1(SlotMenu::cancel_delete, this));
	confirmMenu = Menu::create(confirm_botton, cancel_botton, NULL);
	confirmMenu->setPosition(Vec2(0, -30));
	confirmMenu->alignItemsHorizontallyWithPadding(50);
	this->addChild(confirmMenu, 3);

	confirmMenu->setVisible(false);
}