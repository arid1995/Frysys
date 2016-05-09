/*
 * Серег, впиши сюда себя. Этот класс за тобой.
 */
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
    map->setScale(SCALE_FACTOR);
    getSizes();
    walls = map->getLayer("wall");
    // FIXME: consider using getSize instead of getContentSize
    player->setPosition(this->positionForTileCoordinate(player->getContentSize(), Point(16,5)));
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
    if (posAtTile.x < 1)
        player->setPosition(this->positionForTileCoordinate(player->getContentSize(), Point(1,posAtTile.y)));
    if (posAtTile.x > 18)
        player->setPosition(this->positionForTileCoordinate(player->getContentSize(), Point(posAtTile.y,1)));

    for (int a = fromX; a < 2; a++) {

        for (int b = fromY; b < 2; b++) {

            if(!(a == 0 && b == 0)) {
                Sprite *tile = walls->getTileAt(Point(posAtTile.x + a, posAtTile.y + b));

                if (tile){
                    Point tmp = tile->getPosition();//(Point((posAtTile.x + a)*scale*64, (posAtTile.y + b)*scale*64));
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
    Rect player_rect = player->getTextureRect();
    // FIXME: consider using hitBox (GameObject class) instead of player_rect, and try to avoid hardcoded numbers
    player_rect.setRect(player->getPosition().x - player->getContentSize().width/4,
                        player->getPosition().y - player->getContentSize().height+50,
                        player_rect.size.width-10, player_rect.size.height+50);
    getCollisionTiles();
        /*if (player_rect.intersectsRect(tileArr[i])) {
            //CCLOG("OOOOOOOOKKKKKKKKKK!!!!!!!!!!");
            switch(i){
                case 3:
                    if(player->getDirection()<0)
                        player->stop();
                case 4:
                    if(player->getDirection()>0)
                        player->stop();
                case 6:
                    if(player->isFalling()){
                        player->setSpeedY(0);
                        player->setJumpDuration(false);
                    }
            }
        }*/
    /*if (player_rect.intersectsRect(tileArr[3]))
        //CCLOG("OK!");
    else
        //CCLOG("FAIL!");*/

    if (player_rect.intersectsRect(tileArr[4]) && player->isFalling()){
        player->setSpeedY(0);
        player->setJumpDuration(false);
    }
    if (!(player_rect.intersectsRect(tileArr[4]) || player->getJumpDuration())){
        player->setSpeedY(1);
    }
    if (player_rect.intersectsRect(tileArr[6]) && player->getDirection()>0)
        player->setSpeedX(0);
    if (player_rect.intersectsRect(tileArr[1]) && player->getDirection()<0)
        player->setSpeedX(0);
}
