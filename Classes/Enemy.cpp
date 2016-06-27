/*
 * Author - Farid
 * Not yet finished
 */
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(Layer *layer, std::string enemyType) : //only "knight" is allowed yet
        AnimatedEntity(enemyType)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer->addChild(this);
    ObjectList::getInstance()->addObject(this);
    scheduleUpdate();
    resume();
}

void Enemy::collide() {
    // TODO: write here what should enemy do on collision
}
void Enemy::inflictDamage(int damage) {
    // TODO: write here what should enemy inflict damage
}

int Enemy::getDamage () {
    // TODO: write here how should enemy recieve damage
}

void Enemy::update(float delta) {
    //FIXME: A big perfomance issue, has to be fixed
    if (attackDuration > 0) {
        attackDuration -= delta;
    } else
    if (attacked) {
        attacked = false;
        startAnimation(idleFrames, ANIMATION_INTERVAL);
    }

    if (jumped && !jumpDuration) {
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