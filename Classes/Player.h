/*
 * Author - Farid
 * Not yet finished
*/
#pragma once

#include "cocos2d.h"
#include "AnimatedEntity.h"
#include <cmath>
#include "Constants.h"

class Player : public AnimatedEntity
{
public:
    Player(cocos2d::Layer *layer, std::string spriteSheetPath, std::string plistPath, int frameCount);
    void update(float delta);
private:
    int lives;
    int damage;
};