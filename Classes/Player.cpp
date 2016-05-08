/*
 * Author - Farid
 * The architecture of this class is quite messy, even I can (and did) easily lose a track of this code
 * so don't delete, edit or add anything unless u r absolutely 100% sure about what u r doing
*/
#include "Player.h"
#include "Ground.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer){
    this->direction = 1;
    this->size = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();

    this->spritebatch = SpriteBatchNode::create("knight.png");//loading animation spritesheet
    this->cache = SpriteFrameCache::getInstance();
    this->cache->addSpriteFramesWithFile("knight.plist");

    initializeAnimationVectors(this->runFrames, 10, "Run");
    initializeAnimationVectors(this->jumpFrames, 10, "Jump");
    initializeAnimationVectors(this->idleFrames, 10, "Idle");
    initializeAnimationVectors(this->attackFrames, 10, "Attack");

    // FIXME: gotta find better solution for this shit
    this->jumped = false;
    this->jumpDuration = false;
    this->attackDuration = 0;
    this->attacked = false;
    this->setScale(1);
    

    this->initWithSpriteFrameName("Run (1).png");//assigning a skin to a player

    layer->addChild(this);

    startAnimation(this->idleFrames, 0.05f);
    this->scheduleUpdate();
    this->resume();
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
    this->stopAllActions();
    Animation* animation = Animation::createWithSpriteFrames(animVector, animSpeed);
    if (looped) {
        this->runAction(RepeatForever::create(Animate::create(animation)));
    } else
    {
        this->runAction(Animate::create(animation));
    }
}


void Player::jump() {
    if (isInTheAir()) return;
    jumpDuration = true;
    jumped = true;
    startAnimation(this->jumpFrames, JUMP_INTERVAL, false);
    setSpeedY(-7);
}

void Player::runToTheLeft() {
    if (isInTheAir()) return;
    this->direction = -1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    setSpeedX(-2);
}

void Player::runToTheRight() {
    //if (isInTheAir()) return;
    this->direction = 1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    //this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 0));
    setSpeedX(2);
}

void Player::attack() {
    if (isInTheAir()) return;
    this->attacked = true;
    this->attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(this->attackFrames, ANIMATION_INTERVAL, false);
}

void Player::stop() {
    //if (isInTheAir()) return;
    startAnimation(this->idleFrames, ANIMATION_INTERVAL);
    setSpeedX(0);
}

bool Player::isInTheAir() {
    if (getSpeedY() != 0) return true;
    return false;
}

bool Player::isFalling() {
    if ((getSpeedY() + gravityA) > 0)
        return true;
    return false;
}

void Player::update(float delta) {
    //FIXME: A big perfomance issue, has to be fixed
    if (this->attackDuration > 0) {
        this->attackDuration -= delta;
    } else
        if (attacked) {
            attacked = false;
            this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        }

    if (jumped && !jumpDuration){
        this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        jumped = false;
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        this->setFlippedX(true);
    } else {
        this->setFlippedX(false);
    }
    this->setSpeed(Vec2(getSpeedX(), getSpeedY()));
}

void Player::setJumpDuration(bool set){
    jumpDuration = set;
}

bool Player::getJumpDuration(){
    return jumpDuration;
}
