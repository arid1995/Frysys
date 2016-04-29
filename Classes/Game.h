#pragma once

#include "cocos2d.h"
#include "Ground.h"
#include "Player.h"
#include <map>

#define GRAVITY -1000

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    
    
    
private:
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    
    void eGround( float dt);
    
    static std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> keys;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    cocos2d::PhysicsWorld *sceneWorld;
    
    Ground ground;
    
    Player *player;
    
    cocos2d::Size visibleSize;
};