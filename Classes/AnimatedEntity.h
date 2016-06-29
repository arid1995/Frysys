/*
 * Author - Farid
 * Base class for all "alive" objects
*/
#pragma once

#include "cocos2d.h"
#include "DynamicObject.h"
#include <cmath>
#include "Constants.h"
#include "ObjectList.h"
#include "Bullet.h"

#define JUMP_INTERVAL 0.08
#define ANIMATION_INTERVAL 0.05

class AnimatedEntity : public DynamicObject
{
public:
    //constructs an animated object with given spriteshit and xml .plist file
    AnimatedEntity(std::string type, cocos2d::Layer *_layer);
    void jump();
    void runToTheLeft();
    void runToTheRight();

    virtual void attack() {
        if (isInTheAir()) return;
        attacked = true;
        attackDuration = ANIMATION_INTERVAL * 10;
        startAnimation(attackFrames, ANIMATION_INTERVAL, false);
    }

    virtual void shoot() {
        attackDuration = ANIMATION_INTERVAL * 10;
        startAnimation(shootFrames, ANIMATION_INTERVAL, false);
        Bullet* bullet = new Bullet(layer, getPosition().x + direction * (getContentSize().width*1.5), getPosition().y, direction, 5);
    };
    
    virtual int getVelocity() { return 0; };

    //defines sequence of actions when Entity is unalived
    virtual void dead() {};
    //basic actions that all animated entities must do (must be called from child's update method)
    std::list<GameObject*> baseUpdate(float delta);
    void collide(GameObject* object);
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
    cocos2d::Layer* layer;
    //gotta find better solution to this shit
    bool jumped;
    //initializes animation with frameCount sprite frames named by /namePattern (frameNumber).png/
    bool jumpDuration;
    float attackDuration;//shows when to switch to idle or run animation (simply counting down
    bool attacked;//shows whether player jumped or attacked
    int lives;
    int damage;
    bool isDamageInflicted;
};