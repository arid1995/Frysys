#pragma once

#include "cocos2d.h"
#include "Ground.h"
#include "Player.h"
#include "Exit.h"
#include "ObjectList.h"
#include <map>
#include "Constants.h"
#include "GameObject.h"

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
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::PhysicsWorld *sceneWorld;
    cocos2d::SpriteFrameCache* cache;
    Ground* ground;
    Player *player;
    cocos2d::Follow *camera;
    cocos2d::Size visibleSize;
};