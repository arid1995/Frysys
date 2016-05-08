/*
 * Author - Farid
 * Not yet finished
 */
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(cocos2d::Layer *layer, std::string spriteSheetPath, std::string plistPath, int frameCount) :
        AnimatedEntity(spriteSheetPath, plistPath, frameCount)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer->addChild(this);
    this->scheduleUpdate();
    this->resume();
}

void Enemy::update(float delta) {
    //FIXME: A big perfomance issue, has to be fixed
    if (this->attackDuration > 0) {
        this->attackDuration -= delta;
    } else
    if (attacked) {
        attacked = false;
        this->startAnimation(idleFrames, ANIMATION_INTERVAL);
    }

    if (jumped && !jumpDuration) {
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