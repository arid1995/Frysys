//
// Created by farid on 09.05.16.
//

#include "Exit.h"
#include "ObjectList.h"

USING_NS_CC;

Exit::Exit(cocos2d::Layer* layer, cocos2d::Vec2 position) {
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    initWithSpriteFrameName("Flag.png");
    setHitBox(getTextureRect());
    setPosition(position);
    isTransparent = true;

    ObjectList::getInstance()->addObject(this);
    layer->addChild(this);
}