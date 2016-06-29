/*
 * Серег, впиши сюда себя. Этот класс за тобой.
 */
#include "Ground.h"
#include "Constants.h"

USING_NS_CC;

Ground::Ground(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    scheduleUpdate();
    resume();
}

void Ground::eGround(std::list<GameObject*> obj)
{
    CCLOG("GROUND");
    //player = playerTMP;
    //anusKnight = anusKnightTMP;
    map->setScale(SCALE_FACTOR);
    getSizes();
    walls = map->getLayer("wall");
    // FIXME: consider using getSize instead of getContentSize
    int pos = 10;
    
    for (std::list<GameObject*>::iterator it=ObjectList::getInstance()->getList().begin(); it != ObjectList::getInstance()->getList().end(); ++it){
        it.operator*()->setPosition(positionForTileCoordinate(it.operator*()->getContentSize(), Point(pos,10)));
        pos += 3;
    }

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


void Ground::getCollisionTiles(GameObject* player){

    int i = 0;
    int fromX = -1;
    int fromY = -1;
    Point posAtTile = getTilePosition(player);
    
    for (int a = fromX; a < 2; a++) {

        for (int b = fromY; b < 2; b++) {

            if(!(a == 0 && b == 0)) {
                Sprite *tile = walls->getTileAt(Point(posAtTile.x + a, posAtTile.y + b));

                if (tile){
                    Point tmp = tile->getPosition();
                    tileArr[i]=Rect(tmp.x, tmp.y, map->getTileSize().width*scale, map->getTileSize().height*scale);
                }
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
    
    for (std::list<GameObject*>::iterator it=ObjectList::getInstance()->getList().begin(); it != ObjectList::getInstance()->getList().end(); ++it){
    
    Rect player_rect = Rect(it.operator*()->getPosition().x - it.operator*()->getContentSize().width/2,
                        it.operator*()->getPosition().y - it.operator*()->getContentSize().height/2,
                        it.operator*()->getContentSize().width, it.operator*()->getContentSize().height);
    
    getCollisionTiles(it.operator*());
    
    if (player_rect.intersectsRect(tileArr[4]) && it.operator*()->isFalling()){
        it.operator*()->setSpeedY(0);
        it.operator*()->setJumpDuration(false);
        if (it.operator*()->getSpeedX() > 0){
            it.operator*()->runToTheRight();
            break;
        }
        if (it.operator*()->getSpeedX() < 0){
            it.operator*()->runToTheLeft();
        }
        else{
            it.operator*()->stop();
        }
    }
        
    if (!(player_rect.intersectsRect(tileArr[4]) || it.operator*()->getJumpDuration())){
        it.operator*()->setSpeedY(1);
    }
    if (player_rect.intersectsRect(tileArr[6]) && it.operator*()->getDirection()>0)
        it.operator*()->setSpeedX(0);
    if (player_rect.intersectsRect(tileArr[1]) && it.operator*()->getDirection()<0)
        it.operator*()->setSpeedX(0);
        
    }
}

