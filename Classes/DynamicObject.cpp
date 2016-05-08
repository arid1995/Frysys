/*
 * Author - Farid
 * Base class for all movin' and actin' objects in the scene
*/

#include "DynamicObject.h"

USING_NS_CC;

DynamicObject::DynamicObject() : xVelocity(0), yVelocity(0), gravityA(0) {};

DynamicObject::DynamicObject(int width, int height, int x, int y, SpriteFrame *spriteFrame) :
        GameObject(width, height, x, y, spriteFrame), xVelocity(0), yVelocity(0), gravityA(0) {
}
DynamicObject::DynamicObject(int width, int height, int x, int y, const std::string &spriteFrameName) :
        GameObject(width, height, x, y, spriteFrameName), xVelocity(0), yVelocity(0), gravityA(0) {
}

void DynamicObject::setSpeedY(float velocity){
    this->yVelocity = velocity;
}

void DynamicObject::setSpeedX(float velocity){
    this->xVelocity = velocity;
}

void DynamicObject::setSpeed(Vec2 velocity){
    if (velocity.y == 0)
        this->gravityA=0;
    else
        this->gravityA+=0.25;
    Point pos = this->getPosition();
    this->setPosition(Point(pos.x + velocity.x, pos.y - velocity.y - gravityA));
}

float DynamicObject::getSpeedX(){
    return this->xVelocity;
}

float DynamicObject::getSpeedY(){
    return this->yVelocity;
}

short DynamicObject::getDirection(){
    return direction;
}