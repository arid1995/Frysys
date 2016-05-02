#include "Ground.h"
#include "Constants.h"

USING_NS_CC;

Ground::Ground(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    this->scheduleUpdate();
    this->resume();
}

void Ground::eGround(Player* playerTMP)
{
    CCLOG("GROUND");
    player = playerTMP;
    getSizes();
    walls = map->getLayer("wall");
    player->setPosition(this->positionForTileCoordinate(player->getContentSize(), Point(3,7)));
    getCollisionTiles();
    
}

TMXTiledMap* Ground::getMap(){
    return map;
}



Point Ground::positionForTileCoordinate(Size s, Point point){
    
    float x = floor(s.width/2 * scale + point.x * map->getTileSize().width * scale);
    float y = floor(s.height/2 * scale + point.y * map->getTileSize().height * scale);
    
    return Point(x,y);
    
}

void Ground::loadMap(const char* mapname){
    
    map = TMXTiledMap::create(mapname);
    
}

/*void Ground::falling(Point pt){
    step+=0.25;
    player_sprite-> setPosition(Point(pt.x, pt.y-step));
}*/

void Ground::getCollisionTiles(){
    
    int i = 0;
    int fromX = -1;
    int fromY = -1;
    Point posAtTile = getTilePosition(player);
    
    for (int a = fromX; a < 2; a++) {
        
        for (int b = fromY; b < 2; b++) {
            
            if(!(a == 0 && b == 0)){
                
                Sprite *tile = walls->getTileAt(Point(posAtTile.x + a, posAtTile.y + b));
                
                if (tile){
                    tailArr[i]=true;
                }
                else
                    tailArr[i]=false;
                i++;
            }
        }
    }
}

Point Ground::getTilePosition(Sprite* sprite){
    Point pos = sprite->getPosition();
    int posTileX = ((int)(pos.x/scale))/64;
    int posTileY = (mapRowCol.height - 1)-((int)(pos.y/scale))/64;
    return Point(posTileX, posTileY);
}

void Ground::getSizes(){
    mapContentSize = map->getContentSize();
    mapPosition = map->getPosition();
    tileSize = map->getTileSize();
    mapRowCol = map->getMapSize();
    scale = mapContentSize.width/(mapRowCol.width*tileSize.width);
}

void Ground::update(float dt){
    getCollisionTiles();
    if (tailArr[6])
        player->setStatus(5);
}

