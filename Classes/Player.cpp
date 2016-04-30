/*
 * Author - Farid
 * The architecture of this class is quite messy, even I can easily lose a track of this code
 * so don't delete, edit or add anything unless u r absolutely 100% sure about what u r doing
*/
#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer){
    this->size = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();

    this->spritebatch = SpriteBatchNode::create("knight.png");//loading animation spritesheet
    this->cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("knight.plist");

    initializeAnimationVectors(this->runFrames, 10, "Run");
    initializeAnimationVectors(this->jumpFrames, 10, "Jump");
    initializeAnimationVectors(this->idleFrames, 10, "Idle");

    this->skin = Sprite::createWithSpriteFrameName("Run (1).png");//assigning a skin to a player

    this->skin->setPosition(Point(this->size.width / 2, this->size.height / 2));

    //setting player's physics parameters up
    this->skinBody = PhysicsBody::createBox(this->skin->getContentSize(),
                                            PhysicsMaterial(1, 0.5, 0.5));
    this->skinBody->setRotationEnable(false);//we don't need rotation, do we? I think player can rotate when he jump!
    this->skinBody->setMass(PLAYERS_MASS);
    this->skin->setPhysicsBody(this->skinBody);

    layer->addChild(this->skin);

    startAnimation(idleFrames, 0.05f);
}

void Player::initializeAnimationVectors(Vector<SpriteFrame*> &vector, unsigned frameCount, char *namePattern) {
    //namePattern like "Run" or "Jump"
    char str[100] = {0};
    for(unsigned i = 1; i <= frameCount; i++)
    {
        sprintf(str, "%s (%d).png", namePattern, i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        Sprite *tmp = (Sprite*) frame;
        vector.pushBack(frame);
    }
}

//starts animation
void Player::startAnimation(Vector<SpriteFrame*> animVector, float animSpeed, bool looped) {
    this->skin->stopAllActions();
    Animation* animation = Animation::createWithSpriteFrames(animVector, animSpeed);
    if (looped) {
        this->skin->runAction(RepeatForever::create(Animate::create(animation)));
    } else
    {
        this->skin->runAction(Animate::create(animation));
    }
    this->skinBody->setVelocity(Vec2(0, this->skinBody->getVelocity().y));
}

void Player::jump() {
    if (isInTheAir()) return;
    startAnimation(jumpFrames, 0.08f, false);
    this->skinBody->setVelocity(Vec2(this->skinBody->getVelocity().x, JUMP_VELOCITY));
}

void Player::runToTheLeft() {
    if (isInTheAir()) return;
    startAnimation(runFrames, 0.05f);
    this->skinBody->setVelocity(Vec2(-RUN_VELOCITY, this->skinBody->getVelocity().y));
}

void Player::runToTheRight(){
    if (isInTheAir()) return;
    startAnimation(runFrames, 0.05f);
    this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 
            this->skinBody->getVelocity().y));
}

void Player::stop() {
    //if (isInTheAir()) return;
    startAnimation(idleFrames, 0.05f);
    this->skinBody->setVelocity(Vec2(0, this->skinBody->getVelocity().y));
}

bool Player::isInTheAir() {
    if (abs(this->skinBody->getVelocity().y) > DELTA_Y_VELOCITY) return true;
    return false;
}

cocos2d::Sprite* Player::getSkin(){
    return skin;
}