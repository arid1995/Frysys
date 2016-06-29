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

void Enemy::update(float delta) {
    if (!isAlive()) {
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

    std::list<GameObject*> collided = baseUpdate(delta);
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




