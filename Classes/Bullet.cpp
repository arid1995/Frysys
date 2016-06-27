/*
 * Author - Farid
*/

#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(cocos2d::Layer* _layer, float x, float y, int _direction, float speed) {
    initWithSpriteFrameName("Kunai.png");
    setHitBox(getTextureRect());
    setSpeedX(speed);
    setPosition(x, y);
    direction = _direction;

    layer = _layer;
    layer->addChild(this);
    ObjectList::getInstance()->addObject(this);

    scheduleUpdate();
    resume();
}

void Bullet::update(float delta) {

    Rect hitbox = getHitBox();
    setPosition(getPosition().x + direction * getSpeedX(), getPosition().y);
    //FIXME::Hardcode!
    if ((hitbox.origin.x > 950 || hitbox.origin.y > 950) || (hitbox.origin.x < 50 || hitbox.origin.y < 50)) {
        layer->removeChild(this);
        delete this;
        return;
    }

    std::list<GameObject*> collided = getCollidedObjects(ObjectList::getInstance()->getList());

    if (collided.size() != 0) {
        layer->removeChild(this);
        delete this;
        return;
    }

    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }
}