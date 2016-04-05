#pragma once

#include "cocos2d.h"
#include <cmath>
#define JUMP_VELOCITY 300
#define RUN_VELOCITY 300
#define DELTA_Y_VELOCITY 0.1
#define PLAYERS_MASS 1

class Player: public cocos2d::Layer
{
public:
    Player(cocos2d::Layer *layer);
    
    void jump();
    void runToTheLeft();
    void runToTheRight();
    void stop();
    bool isInTheAir();

private:
    cocos2d::Size size;
    cocos2d::Vec2 origin;
    cocos2d::Sprite *skin;
    cocos2d::PhysicsBody *skinBody;
};