#pragma once

#include "cocos2d.h"
#include "Ground.h"
#include "Enemy.h"
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
    
    bool isTouching;
    cocos2d::Point touchPosition;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    
    void menuCloseCallback(Ref* pSender);
    cocos2d::Menu *menu;
    void Play(cocos2d::Ref *pSender);
    void Highscores(cocos2d::Ref *pSender);
    void Settings(cocos2d::Ref *pSender);

private:
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
    void eGround( float dt);
    
    static std::map<cocos2d::EventKeyboard::KeyCode,
      std::chrono::high_resolution_clock::time_point> keys;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMove(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    cocos2d::PhysicsWorld *sceneWorld;
    cocos2d::SpriteFrameCache* cache;
    
    Ground* ground;
    Player *player;
    Enemy *anusKnight;
    cocos2d::Follow *camera;
    cocos2d::Size visibleSize;
    cocos2d::Sprite** heartPlayer = NULL;
    cocos2d::Sprite** heartEnemy = NULL;
    
};