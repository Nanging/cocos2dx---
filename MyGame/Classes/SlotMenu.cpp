#include "SlotMenu.h"
#include "TransitionGame.h"
#include "Player.h"
#include "StartGame.h"
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
	slotnumber = num;
	//»ñµÃÍæ¼Ò
	auto player = Player::getInstance();

	savelot = MenuItemImage::create("SaveSlot_normal.png", "SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::createNewGame, this));
	auto new_game = Menu::createWithItem(savelot);
	new_game->setPosition(Vec2(0, 0));
	this->addChild(new_game,0);


	button_Savelot_Delete = MenuItemImage::create("delete_botton_normal.png", "delete_botton_seleted.png", CC_CALLBACK_1(SlotMenu::button_Savelot_Delete_callback, this));
	auto menu_delete = Menu::createWithItem(button_Savelot_Delete);
	menu_delete->setPosition(Vec2(savelot->getContentSize().width / 2, savelot->getContentSize().height / 2));
	this->addChild(menu_delete,1);

	star = Sprite::create("star_count.png");
	star->setPosition(Vec2(-60, -30));
	star->setVisible(false);
	this->addChild(star,1);

	auto confirm_botton = MenuItemImage::create("button_confirm.png", "button_confirm.png", CC_CALLBACK_1(SlotMenu::confirm_delete, this));
	auto cancel_botton = MenuItemImage::create("button_cancel.png", "button_cancel.png", CC_CALLBACK_1(SlotMenu::cancel_delete, this));
	confirm_menu = Menu::create(confirm_botton, cancel_botton, NULL);
	confirm_menu->setPosition(Vec2(0, -30));
	confirm_menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(confirm_menu, 3);


	confirm_menu->setVisible(false);


	auto status = player->SaveStatus[num - 1];
	log("-------%d----%d-------", num,status);
	if (status)
	{
		star->setVisible(true);
		__String *str1 = __String::createWithFormat("SaveSlot %d", num);
		label_hint = Label::createWithSystemFont(str1->getCString(), "arial", 30); label_hint->setPosition(Vec2(0, 30));
		__String *str2 = __String::createWithFormat("%03d/%d", player->getScore(num),TotolScore);
		score_label = Label::createWithSystemFont(str2->getCString(), "arial", 30);
		score_label->setPosition(Vec2(20, -30));
		this->addChild(score_label,1);

		new_game->setEnabled(false);
		savelot = MenuItemImage::create("SaveSlot_normal.png", "SaveSlot_seleted.png", CC_CALLBACK_0(SlotMenu::startGame, this, num));
		auto start_game = Menu::createWithItem(savelot);
		start_game->setPosition(Vec2(0, 0));
		this->addChild(start_game,0);
	} 
	else
	{
		label_hint = Label::createWithSystemFont("New Game", "arial", 40);
		label_hint->setPosition(Vec2(0, 0));
		button_Savelot_Delete->setVisible(false);

	}
	this->addChild(label_hint);

	return true;
}
void SlotMenu::button_Savelot_Delete_callback(Ref* pSender)
{
	log("---Delete-SaveSlot---");
	__String *str = __String::create("Delete SaveSlot ?");
	label_hint->setString(str->getCString());

	confirm_menu->setVisible(true);

	button_Savelot_Delete->setVisible(false);
	star->setVisible(false);
	score_label->setVisible(false);
	savelot->setEnabled(false);
}
void SlotMenu::confirm_delete(Ref* pSender)
{
	log("---Confirm-Delete-Save-%d---", slotnumber);
	auto p = Player::getInstance();
	p->initSaveSlot(slotnumber);
	confirm_menu->setVisible(false);
	initWithNum(slotnumber);
}
void SlotMenu::cancel_delete(Ref* pSender)
{
	log("---Cancel-Delete-%d---", slotnumber);
	confirm_menu->setVisible(false);
	initWithNum(slotnumber);
	
}
void SlotMenu::createNewGame()
{
	log("---New-Game-%d--", slotnumber);
	auto player = Player::getInstance();
	player->setStarted(true);
	auto s = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(3, s));
}
void SlotMenu::startGame(int num)
{
	log("---Start-SaveSlot-%d---", num);
	auto player = Player::getInstance();
	player->setStarted(true);
	auto s = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionGame::create(3, s));
}
