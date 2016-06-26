/*
 * Author - Farid
 * Base class for all "alive" objects
*/
#pragma once

#include "cocos2d.h"
#include "DynamicObject.h"
#include <cmath>
#include "Constants.h"

#define JUMP_INTERVAL 0.08
#define ANIMATION_INTERVAL 0.05

class AnimatedEntity : public DynamicObject
{
public:
    //constructs an animated object with given spriteshit and xml .plist file
    AnimatedEntity(std::string type);
    void jump();
    void runToTheLeft();
    void runToTheRight();
    void attack();
    virtual void shoot() {};
    virtual void dead() {};
    void stop();
    bool isInTheAir();
    void setJumpDuration(bool set);
    bool getJumpDuration();
    bool isFalling();

private:
    AnimatedEntity() {};
protected:
    //initializes animation with frameCount sprite frames named by /namePattern (frameNumber).png/
    void initializeAnimationVectors(cocos2d::Vector<cocos2d::SpriteFrame*> &vector, std::string namePattern);
    //starts the animation of a player based on animVector with given speed (animSpeed);
    //looped false means animation won't be looped
    void startAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> animVector, float animSpeed, bool looped = true);

protected:
    cocos2d::SpriteBatchNode* spritebatch;//loading animation spritesheet
    cocos2d::SpriteFrameCache* cache;
    cocos2d::Vector<cocos2d::SpriteFrame*> runFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> jumpFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> attackFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> shootFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> deadFrames;
    cocos2d::Size size;
    cocos2d::Vec2 origin;
    //gotta find better solution to this shit
    bool jumped;
    bool jumpDuration;
    float attackDuration;//shows when to switch to idle or run animation (simply counting down
    bool attacked;//shows whether player jumped or attacked
};