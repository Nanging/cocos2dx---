#include"BaseBullet.h"
#include"Player.h"
#include "BaseStage.h"
bool BaseBullet::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void BaseBullet::removeBullet() {
	if (attackTarget != NULL&&attackTarget->getCurHp() > 0) {
		attackTarget->getHurt(this->getMaxForce() - attackTarget->getArmor());
	}
	auto stage = dynamic_cast<BaseStage*>(UtilTool::getLayerByTag(TAG_STAGE));
	if (stage == nullptr) {
		return;
	}
	if (bulletType) {
		int size = stage->monsterVector.size();
		for (int j = 0; j < size; j++) {
			auto monster = stage->monsterVector.at(j);
			double distance = attackTarget->getPosition().getDistance(monster->getPosition());
			if (distance <= 70 && monster != NULL&&monster->getCurHp() > 0)
				monster->getHurt(this->getMaxForce() - attackTarget->getArmor());
		}
	}
	spriteBullet->setTexture(hitBullet);//����֡�ı���ͼ
	spriteBullet->runAction(Sequence::create(FadeOut::create(1.0f)//����Ч��
		, CallFuncN::create(CC_CALLBACK_0(BaseBullet::removeFromParent, this))//�Ƴ�
		, NULL));

}

void BaseBullet::shoot(){
	if (ifCrit) {
		setMaxForce(2 * this->getMaxForce());//���������˺�
		spriteBullet->setTexture(critBullet);
	}
	this->runAction(Sequence::create(bulletAction, CallFuncN::create(CC_CALLBACK_0(BaseBullet::removeBullet, this)), NULL));
}//��ִ���ӵ����������ٽ�������