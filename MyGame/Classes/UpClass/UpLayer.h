#ifndef __UpLayer_H__
#define __UpLayer_H__
#include"cocos2d.h"
USING_NS_CC;
class ArrayUpIcon;
class MagicUpIcon;
class BatteryUpIcon;



class UpLayer :
	public Layer
{
public:
	UpLayer();
	~UpLayer();
	CREATE_FUNC(UpLayer);
	bool init();
	bool initSprite();
	bool initLabel();
	bool initMenu();

	
	CC_SYNTHESIZE(int, star, Star);
	CC_SYNTHESIZE(int, choosestate, Choosestate);     //�����ж���ѡ���ĸ�ͼ��
	int temstar;                                      //��¼���ǳ�ʼ����


	void up(Ref* pSender);                         //ִ������
	void reset(Ref* pSender);                      //����
	void player(Ref* pSender);                     //��д
	void showDes(int i);                           //��ʾ��ǰ�츳Ч��
	void swallow(int i);                           
	void getLevel();

	ArrayUpIcon* array;                   //��������ͼ
	MagicUpIcon* magic;                   //ħ��������ͼ
	BatteryUpIcon* battery;               //��������ͼ
	MenuItemImage* upButton;                  //������ť
	MenuItemImage* resetButton;               //���ð�ť
	MenuItemImage* quitButton;
	MenuItemImage* bgSprite;                  //����

	std::vector<MenuItemImage*> iconVector;               //����������ͼ�����һ��vector�ڱ��ڹ���
	int levelVector[9] = {0};                           //����ÿ���츳��ǰ�ĵȼ�
	const char* upKind[3] = { "force","scope","speed" };

	Label* des;                               //����Ч����������
	Label* upDes;                             //������ť���������
	Label* resetDes;                          //���ð�ť���������
	Label* quitDes;                          //�˳���ť���������
	Label* starNumDes;                       //ʣ������
	Label* starCostDes;                      //�۸�
	Label* introduce;                        //����򵥽���
	Label* briefDes;                        //�����ͣ����

	Sprite* top;                              //�ڸǲ�
	Sprite* starPicture;                      //��ʾ����ʣ��
	Sprite* starBound;                        //��װ���ǵĿ�
	Sprite* towerKind1;                       //����ͼ��
	Sprite* towerKind2;                       //ħ����ͼ��
	Sprite* towerKind3;                       //����ͼ��
	Sprite* slected;                          //ѡ�б߿�
	Sprite* starCost;                         //������Ҫ������
	Sprite* introduceBound;                   //װ��Ʒ
	Sprite* bubble;                            //����

};

#endif // !__UpLayer_H__


