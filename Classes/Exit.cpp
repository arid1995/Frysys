//
// Created by farid on 09.05.16.
//

#include "Exit.h"

USING_NS_CC;

Exit::Exit(cocos2d::Layer* layer, cocos2d::Vec2 position) {
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    this->initWithSpriteFrameName("Flag.png");
    this->setHitBox(this->getTextureRect());
    this->setPosition(position);
    this->isTransparent = true;

    layer->addChild(this);
}
