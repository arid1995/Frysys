/*
 * Author - Farid
*/

#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(cocos2d::Layer *layer, float x, float y, float direction, float speed) {
    initWithSpriteFrameName("Kunai.png");
    setHitBox(getTextureRect());
    setSpeedX(speed);
    setPosition(x, y);
    layer->addChild(this);
    scheduleUpdate();
    resume();
}

void Bullet::update(float delta) {
    //FIXME::Hardcode!
    Rect hitbox = getHitBox();
    if ((hitbox.origin.x > 950 || hitbox.origin.y > 950) || (hitbox.origin.x < 50 || hitbox.origin.y < 50)) {
        delete this;
    }
}