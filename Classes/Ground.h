#pragma once

#include "cocos2d.h"

class Ground
{
public:
    Ground();
    
    void eGround( cocos2d::Layer *layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};