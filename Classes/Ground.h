/*
 * Серег, впиши сюда себя.
 * И, я думаю, стоит этот класс перемименовать в Level,
 * так как это больше похоже на сцену
 */
#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

// FIXME: Consider using polymorphic list* for collision purposes. *refer to GameObject::getCollidedObjects
class Ground: public cocos2d::Layer
{
public:
    Ground();
    
    void eGround( Player* player );
    cocos2d::Point positionForTileCoordinate(cocos2d::Size s, cocos2d::Point point);
    cocos2d::TMXTiledMap* getMap();
    void loadMap(const char* name);
    void getCollisionTiles();
    cocos2d::Point getTilePosition(cocos2d::Sprite* sprite);
    void getSizes();
    void update(float dt);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* walls;
    cocos2d::TMXLayer* sky;
    Player* player;
    float scale;
    cocos2d::Size mapContentSize;
    cocos2d::Point mapPosition;
    cocos2d::Size tileSize;
    cocos2d::Size mapRowCol;
    cocos2d::Rect* tileArr = new cocos2d::Rect[8];
};