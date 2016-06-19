/*
 * Author - Farid
 * Base class for all movin' and actin' objects in the scene
 */

#pragma once

#include "GameObject.h"
#include "Constants.h"
class DynamicObject : public GameObject {
public:
    DynamicObject();
    DynamicObject(int width, int height, int x, int y, cocos2d::SpriteFrame *spriteFrame);
    DynamicObject(int width, int height, int x, int y, const std::string &spriteFrameName);
    virtual void jump() {};
    virtual void runToTheLeft() {};
    virtual void runToTheRight() {};
    virtual void attack() {};
    virtual void stop() {};
    void setSpeed(cocos2d::Vec2 velocity);
    void setSpeedY(float velocity);
    void setSpeedX(float velocity);
    float gravityA;
    float getSpeedY();
    float getSpeedX();
    short getDirection();
    ~DynamicObject() {};

private:
    float yVelocity;
    float xVelocity;
    int status;
protected:
    short direction;//-1 - left, 1 - right
};