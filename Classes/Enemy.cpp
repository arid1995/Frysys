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
    
    float size = Director::getInstance()->getVisibleSize().width;
    
    if (dist < size/DIST1 && dist > size/DIST2){
        if (!startShoot){
            startShoot = true;
            shoot();
        }
    }
    else{
        startShoot = false;
    }

    if (dist < size/DIST2 && dist > size/DIST3){
        if (!startRun){
            startRun = true;
            run(enemyPosition, playerPosition);
        }
    }
    else{
        startRun = false;
        if (dist > size/DIST4)
            stop();
    }
    if (dist < size/DIST4){
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
    shoot();
}

void Enemy::fight(Point enemyPosition, Point playerPosition){
    attack();
}

int Enemy::getVelocity(){
    return ENEMY_MAX_VELOCITY;
}




