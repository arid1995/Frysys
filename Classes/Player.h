/*
 * Author - Farid
 * Not yet finished
*/
#pragma once

#include "cocos2d.h"
#include "AnimatedEntity.h"
#include <cmath>
#include "Constants.h"
#include "Bullet.h"
#include "ObjectList.h"

class Player : public AnimatedEntity
{
public:
    Player(cocos2d::Layer *layer, std::string playerType);
    void shoot();
    void update(float delta);
    void collide();
    void dead();
    void inflictDamage(int damage);
    int getDamage ();
private:
    cocos2d::Layer* layer;
    int lives;
    int damage;
};