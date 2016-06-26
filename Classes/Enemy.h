/*
 * Author - Farid
 * Not yet finished
*/
#pragma once

#include "cocos2d.h"
#include "AnimatedEntity.h"
#include <cmath>
#include "Constants.h"

#define JUMP_INTERVAL 0.08
#define ANIMATION_INTERVAL 0.05

class Enemy : public AnimatedEntity
{
public:
    Enemy(cocos2d::Layer *layer, std::string enemyType);
    void update(float delta);
    void collide();
    void inflictDamage(int damage);
    int getDamage();

private:
    int lives;
    int damage;
};