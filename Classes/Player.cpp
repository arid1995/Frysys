/*
 * Author - Farid
 * Not yet finished
*/
#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *_layer, std::string playerType) : AnimatedEntity(playerType, _layer)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer->addChild(this);
    ObjectList::getInstance()->addObject(this);
    scheduleUpdate();
    resume();
}

void Player::shoot() {
}

void Player::collide(GameObject* object) {
    // TODO: write here what should player do on collision
}
void Player::inflictDamage(int damage) {
    // TODO: write here what should player inflict damage
}

void Player::update(float delta) {
    if (!isAlive()) {
        return;
    }

    std::list<GameObject *> collided = baseUpdate(delta);
}

int Player::getVelocity(){
    return PLAYER_MAX_VELOCITY;
}