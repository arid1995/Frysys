/*
 * Author - Farid
*/
#include "AnimatedEntity.h"

USING_NS_CC;

//please don't use this constructor

// FIXME: Somehow only the first loaded spritesheet is used, others are ignored
AnimatedEntity::AnimatedEntity(std::string spriteSheetPath, std::string plistPath, int frameCount) {
    this->direction = 1;
    this->size = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();

    this->spritebatch = SpriteBatchNode::create(spriteSheetPath);//loading animation spritesheet
    this->cache = SpriteFrameCache::getInstance();
    this->cache->addSpriteFramesWithFile(plistPath);

    initializeAnimationVectors(this->runFrames, frameCount, "Run");
    initializeAnimationVectors(this->jumpFrames, frameCount, "Jump");
    initializeAnimationVectors(this->idleFrames, frameCount, "Idle");
    initializeAnimationVectors(this->attackFrames, frameCount, "Attack");

    // FIXME: gotta find better solution for this shit
    this->jumped = false;
    this->jumpDuration = false;
    this->attackDuration = 0;
    this->attacked = false;
    this->setScale(1);


    this->initWithSpriteFrameName("Run (1).png");//assigning a skin to a player


    startAnimation(this->idleFrames, 0.05f);
}

void AnimatedEntity::initializeAnimationVectors(Vector<SpriteFrame*> &vector, unsigned frameCount, char *namePattern) {
    //namePattern like "Run" or "Jump"
    char str[100] = {0};
    for(unsigned i = 2; i <= frameCount; i++)
    {
        sprintf(str, "%s (%d).png", namePattern, i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        Sprite *tmp = (Sprite*) frame;
        vector.pushBack(frame);
    }
}

//starts animation
void AnimatedEntity::startAnimation(Vector<SpriteFrame*> animVector, float animSpeed, bool looped) {
    this->stopAllActions();
    Animation* animation = Animation::createWithSpriteFrames(animVector, animSpeed);
    if (looped) {
        this->runAction(RepeatForever::create(Animate::create(animation)));
    } else
    {
        this->runAction(Animate::create(animation));
    }
}


void AnimatedEntity::jump() {
    if (isInTheAir()) return;
    jumpDuration = true;
    jumped = true;
    startAnimation(this->jumpFrames, JUMP_INTERVAL, false);
    setSpeedY(-7);
}

void AnimatedEntity::runToTheLeft() {
    if (isInTheAir()) return;
    this->direction = -1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    setSpeedX(-2);
}

void AnimatedEntity::runToTheRight() {
    //if (isInTheAir()) return;
    this->direction = 1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    //this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 0));
    setSpeedX(2);
}

void AnimatedEntity::attack() {
    if (isInTheAir()) return;
    this->attacked = true;
    this->attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(this->attackFrames, ANIMATION_INTERVAL, false);
}

void AnimatedEntity::stop() {
    //if (isInTheAir()) return;
    startAnimation(this->idleFrames, ANIMATION_INTERVAL);
    setSpeedX(0);
}

bool AnimatedEntity::isInTheAir() {
    if (getSpeedY() != 0) return true;
    return false;
}

bool AnimatedEntity::isFalling() {
    if ((getSpeedY() + gravityA) > 0)
        return true;
    return false;
}

void AnimatedEntity::setJumpDuration(bool set){
    jumpDuration = set;
}

bool AnimatedEntity::getJumpDuration(){
    return jumpDuration;
}