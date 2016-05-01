/*
 * Author - Farid
 * The architecture of this class is quite messy, even I can (and did) easily lose a track of this code
 * so don't delete or add anything unless u r absolutely 100% sure about what u r doing
*/
#pragma once

#include "cocos2d.h"
#include <cmath>
#include "Constants.h"

#define JUMP_INTERVAL 0.08
#define ANIMATION_INTERVAL 0.05

class Player : public cocos2d::Sprite
{
public:
    Player(cocos2d::Layer *layer);
    void jump();
    void runToTheLeft();
    void runToTheRight();
    void attack();
    void stop();
    bool isInTheAir();
    void update(float delta);

private:
    cocos2d::SpriteBatchNode* spritebatch;//loading animation spritesheet
    cocos2d::SpriteFrameCache* cache;
    cocos2d::Vector<cocos2d::SpriteFrame*> runFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> jumpFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> attackFrames;
    cocos2d::Size size;
    cocos2d::Vec2 origin;
    cocos2d::PhysicsBody *skinBody;
    cocos2d::Action *currentAction;
    //gotta find better solution to this shit
    float jumpDuration;
    float attackDuration;//shows when to switch to idle or run animation (simply counting down
    bool jumped;
    bool attacked;//shows whether player jumped or attacked

    short direction;//-1 - left, 1 - right
    //initializes animation with frameCount sprite frames named by /namePattern (frameNumber).png/
    void initializeAnimationVectors(cocos2d::Vector<cocos2d::SpriteFrame*> &vector,
                                    unsigned frameCount, char *namePattern);
    //starts the animation of a player based on animVector with given speed (animSpeed);
    // looped false means animation won't be looped
    void startAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> animVector, float animSpeed, bool looped = true);
};