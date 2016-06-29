/*
 * Author - Farid
 * Not yet finished
*/
#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *_layer, std::string playerType) : AnimatedEntity(playerType)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer = _layer;
    layer->addChild(this);
    ObjectList::getInstance()->addObject(this);
    scheduleUpdate();
    resume();
}

void Player::shoot() {
    attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(shootFrames, ANIMATION_INTERVAL, false);
    Bullet* bullet = new Bullet(layer, getPosition().x + direction * (getContentSize().width / 2 + 25), getPosition().y, direction, 5);
}

void Player::collide(GameObject* object) {
    // TODO: write here what should player do on collision
}
void Player::inflictDamage(int damage) {
    // TODO: write here what should player inflict damage
}

int Player::getDamage () {
    return 0;
    // TODO: write here how should player recieve damage
}

void Player::dead() {
    startAnimation(deadFrames, ANIMATION_INTERVAL, false);
    // TODO: write other stuff that needs to happen when player dies
}

void Player::update(float delta) {
    std::list<GameObject*> collided = baseUpdate(delta);
}