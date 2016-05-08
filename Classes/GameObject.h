/*
 * Author - Farid
 * Base class for all objects in the scene
 */
#pragma once

#include "cocos2d.h"

class GameObject : public cocos2d::Sprite {
public:
    GameObject();//creates default object with all members set to 0
    //Creates object with defined hitBox and with texture using the name of a SpriteFrame
    GameObject(int width, int height, int x, int y, const std::string &spriteFrameName);
    //Creates object with defined hitBox and with texture using the SpriteFrame
    GameObject(int width, int height, int x, int y, cocos2d::SpriteFrame *spriteFrame);
    cocos2d::Size getSize();
    cocos2d::Vec2 getPosition();
    void setSize(int width, int height);
    void setPosition(const cocos2d::Vec2& position);
    void setPosition(int x, int y);
    std::vector<GameObject*> getCollidedObjects(std::vector<GameObject*> &levelObjects);
    ~GameObject();
private:
    cocos2d::Rect *hitBox;//for collision check
};