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
    Enemy(cocos2d::Layer *layer, std::string spriteSheetPath, std::string plistPath, int frameCount);
    void update(float delta);
private:
    int lives;
    int damage;
};