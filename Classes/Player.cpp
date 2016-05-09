/*
 * Author - Farid
 * Not yet finished
*/
#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer, std::string playerType) :
    AnimatedEntity(playerType)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer->addChild(this);
    this->scheduleUpdate();
    this->resume();
}

void Player::shoot() {
    if (isInTheAir()) return;
    this->attacked = true;
    this->attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(this->shootFrames, ANIMATION_INTERVAL, false);
}

void Player::collide() {
    // TODO: write here what should player do on collision
}
void Player::inflictDamage(int damage) {
    // TODO: write here what should player inflict damage
}

int Player::getDamage () {
    // TODO: write here how should player recieve damage
}

void Player::dead() {
    startAnimation(this->deadFrames, ANIMATION_INTERVAL, false);
    // TODO: write other stuff that needs to happen when player dies
}

void Player::update(float delta) {
    //FIXME: A big perfomance issue, has to be fixed
    if (this->attackDuration > 0) {
        this->attackDuration -= delta;
    } else
        if (attacked) {
            attacked = false;
            this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        }

    if (jumped && !jumpDuration){
        this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        jumped = false;
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        this->setFlippedX(true);
    } else {
        this->setFlippedX(false);
    }
    this->setSpeed(Vec2(getSpeedX(), getSpeedY()));
}