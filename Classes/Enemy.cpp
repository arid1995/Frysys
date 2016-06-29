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




