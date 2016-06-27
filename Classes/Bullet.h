//
// Created by farid on 11.05.16.
//
#pragma once
#include "DynamicObject.h"

class Bullet : public DynamicObject {
public:
    Bullet(cocos2d::Layer *layer, float x, float y, float direction, float speed = 4);
    ~Bullet() {};
    void update(float delta);
};
