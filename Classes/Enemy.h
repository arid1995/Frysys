/*
 * Author - Farid
 * Not yet finished
*/
#pragma once

#include "cocos2d.h"
#include "AnimatedEntity.h"
#include <cmath>
#include "Constants.h"
#include "ObjectList.h"

#define JUMP_INTERVAL 0.08
#define ANIMATION_INTERVAL 0.05

class Enemy : public AnimatedEntity
{
public:
    Enemy(cocos2d::Layer *layer, std::string enemyType);
    void update(float delta);
    void inflictDamage(int damage);
    int getLives();
    void run(cocos2d::Point enemyPosition, cocos2d::Point playerPosition);
    void fight(cocos2d::Point enemyPosition, cocos2d::Point playerPosition);

private:
    bool startRun = false;
    bool startFight = false;
};