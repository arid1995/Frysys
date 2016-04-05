#include "Ground.h"

USING_NS_CC;

Ground::Ground(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Ground::eGround(cocos2d::Layer *layer)
{
    CCLOG("GROUND");
    
    auto bottomGround = Sprite::create( "grass.jpg" );
    auto bottomGroundBody = PhysicsBody::createBox(bottomGround->getContentSize(),
            PhysicsMaterial(1, 0, 0));

    bottomGround->setPhysicsBody(bottomGroundBody);
    bottomGround->setPosition(visibleSize.width / 2, -100);
    layer->addChild(bottomGround);
}