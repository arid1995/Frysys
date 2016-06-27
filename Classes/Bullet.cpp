/*
 * Author - Farid
*/

#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(cocos2d::Layer* _layer, float x, float y, int _direction, float speed) : damage(1) {
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
        ObjectList::getInstance()->deleteObject(this);
        delete this;
        return;
    }

    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }
}

int Bullet::getDamage() {
    layer->removeChild(this);
    int _damage = damage;
    ObjectList::getInstance()->deleteObject(this);
    delete this;
    return _damage;
}