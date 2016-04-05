#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer){
    this->size = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
    
    this->skin = Sprite::create("man.jpg");
    this->skin->setPosition(Point(this->size.width / 2, this->size.height / 2));
    
    //setting player's physics parameters up
    this->skinBody = PhysicsBody::createBox(this->skin->getContentSize(),
            PhysicsMaterial(1, 0.5, 0.5));
    this->skinBody->setRotationEnable(false);//we don't need rotation, do we?
    this->skinBody->setMass(PLAYERS_MASS);
    this->skin->setPhysicsBody(this->skinBody);
    
    layer->addChild(this->skin);
}

void Player::jump(){
    if (isInTheAir()) return;
    this->skinBody->setVelocity(Vec2(this->skinBody->getVelocity().x,
            JUMP_VELOCITY));
}

void Player::runToTheLeft(){
    if (isInTheAir()) return;
    this->skinBody->setVelocity(Vec2(-RUN_VELOCITY, 
            this->skinBody->getVelocity().y));
}

void Player::runToTheRight(){
    //if (isInTheAir()) return;
    this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 
            this->skinBody->getVelocity().y));
}

void Player::stop() {
    //if (isInTheAir()) return;
    this->skinBody->setVelocity(Vec2(0, this->skinBody->getVelocity().y));
}

bool Player::isInTheAir() {
    if (abs(this->skinBody->getVelocity().y) > DELTA_Y_VELOCITY) return true;
    return false;
}