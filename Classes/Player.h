/*
 * Author - Farid
 * The architecture of this class is quite messy, even I can easily lose a track of this code
 * so don't delete or add anything unless u r absolutely 100% sure about what u r doing
*/
#pragma once

#include "cocos2d.h"
#include <cmath>
#include "Constants.h"

class Player: public cocos2d::Layer
{
public:
    Player(cocos2d::Layer *layer);
    void jump();
    void runToTheLeft();
    void runToTheRight();
    void stop();
    bool isInTheAir();
    cocos2d::Sprite* getSkin();

private:
    cocos2d::SpriteBatchNode* spritebatch;//loading animation spritesheet
    cocos2d::SpriteFrameCache* cache;
    cocos2d::Vector<cocos2d::SpriteFrame*> runFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> idleFrames;
    cocos2d::Vector<cocos2d::SpriteFrame*> jumpFrames;
    cocos2d::Size size;
    cocos2d::Vec2 origin;
    cocos2d::Sprite *skin;
    cocos2d::PhysicsBody *skinBody;
    //initializes vector with frameCount sprite frames named by /namePattern (frameNumber).png/
    void initializeAnimationVectors(cocos2d::Vector<cocos2d::SpriteFrame*> &vector,
                                            unsigned frameCount, char *namePattern);
    //starts the animation of a player based on animVector with given speed (animSpeed);
    // looped false means animation won't be looped
    void startAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> animVector, float animSpeed, bool looped = true);

};