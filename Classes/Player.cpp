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
    isDamageInflicted = false;
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

int Player::getDamage () {
    if (attacked) {
        int dmg = damage;
        damage = 0;
        isDamageInflicted = true;
        return dmg;
    }
    return 0;
}

void Player::dead() {
    startAnimation(deadFrames, ANIMATION_INTERVAL, false);
    // TODO: write other stuff that needs to happen when player dies
}

void Player::update(float delta) {
    std::list<GameObject*> collided = baseUpdate(delta);

    //for melee attack
    if (attacked && !isDamageInflicted) {
        isDamageInflicted = true;
        damage = 1;
    }

    if (!attacked) {
        isDamageInflicted = false;
    }
}

int Player::getVelocity(){
    return PLAYER_MAX_VELOCITY;
}