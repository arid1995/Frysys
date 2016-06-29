/*
 * Author - Farid
 * Not yet finished
 */
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(Layer *_layer, std::string enemyType) : //only "knight" is allowed yet
        AnimatedEntity(enemyType, _layer)
{
    lives = PLAYER_LIVES_COUNT;
    damage = PLAYER_DAMAGE;
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
    
    GameObject* player = ObjectList::getInstance()->getFirstObject();
    Point enemyPosition = getPosition();
    Point playerPosition = player->getPosition();
    int dist = std::abs(enemyPosition.x - playerPosition.x);
    if (dist < 100 && dist > 70){
        if (!startRun){
            startRun = true;
            run(enemyPosition, playerPosition);
        }
    }
    else{
        startRun = false;
        if (dist > 40)
            stop();
    }
    if (dist < 40){
        if (!startFight){
            startFight = true;
            fight(enemyPosition, playerPosition);
        }

    }
    else{
        startFight = false;
    }
}

int Enemy::getLives(){
    return lives;
}

void Enemy::run(Point enemyPosition, Point playerPosition){
    if (enemyPosition.x - playerPosition.x < 0)
        runToTheRight();
    else
        runToTheLeft();
}

void Enemy::fight(Point enemyPosition, Point playerPosition){
    attack();
}




