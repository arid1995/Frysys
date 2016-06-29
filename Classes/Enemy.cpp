/*
 * Author - Farid
 * Not yet finished
 */
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(Layer *_layer, std::string enemyType) : //only "knight" is allowed yet
        AnimatedEntity(enemyType)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
    layer = _layer;
    layer->addChild(this);
    ObjectList::getInstance()->addObject(this);
    scheduleUpdate();
    resume();
}

void Enemy::inflictDamage(int damage) {
    // TODO: write here what should enemy inflict damage
}

int Enemy::getDamage () {
    // TODO: write here how should enemy recieve damage
}

void Enemy::update(float delta) {
    std::list<GameObject*> collided = baseUpdate(delta);

    if (collided.size() != 0) {
        for (std::list<GameObject*>::iterator i = collided.begin(); i != collided.end(); i++) {
            lives -= i.operator*()->getDamage();
        }
    }
    if (lives <= 0) {
        layer->removeChild(this);
        ObjectList::getInstance()->deleteObject(this);
        delete this;
        return;
    }
}