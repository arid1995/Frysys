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
        if (getSpeedX() != 0)
            startAnimation(runFrames, ANIMATION_INTERVAL);
        else
            startAnimation(idleFrames, ANIMATION_INTERVAL);
    }

    std::list<GameObject*> collided = getCollidedObjects(ObjectList::getInstance()->getList());

    if (collided.size() != 0) {
        for (std::list<GameObject*>::iterator i = collided.begin(); i != collided.end(); i++) {
            lives -= i.operator*()->getDamage();
        }
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }
    setSpeed(Vec2(getSpeedX(), getSpeedY()));

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




