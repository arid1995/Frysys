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
    void setSpeedY(int velocity);
    void setSpeedX(int velocity);
    float gravityA;
    int getSpeedY();
    int getSpeedX();
    bool isFalling();
    short getDirection();
    ~DynamicObject() {};

private:
    int yVelocity;
    int xVelocity;
    int status;
protected:
    short direction;//-1 - left, 1 - right
};