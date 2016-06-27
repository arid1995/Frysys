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
    if (isInTheAir()) return;
    attacked = true;
    attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(shootFrames, ANIMATION_INTERVAL, false);
    Bullet* bullet = new Bullet(layer, 500, 100, 1, 4);
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
    startAnimation(deadFrames, ANIMATION_INTERVAL, false);
    // TODO: write other stuff that needs to happen when player dies
}

void Player::update(float delta) {
    //FIXME: A big perfomance issue, has to be fixed
    if (attackDuration > 0) {
        attackDuration -= delta;
    } else
        if (attacked) {
            attacked = false;
            startAnimation(idleFrames, ANIMATION_INTERVAL);
        }

    if (jumped && !jumpDuration){
        startAnimation(idleFrames, ANIMATION_INTERVAL);
        jumped = false;
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }
    setSpeed(Vec2(getSpeedX(), getSpeedY()));
}