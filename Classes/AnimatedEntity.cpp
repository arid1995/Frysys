/*
 * Author - Farid
 * Base class for all "alive" objects
*/
#include "AnimatedEntity.h"

USING_NS_CC;

AnimatedEntity::AnimatedEntity(std::string type) {
    this->direction = 1;
    this->size = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();

    this->cache = SpriteFrameCache::getInstance();

    initializeAnimationVectors(this->runFrames, type + "_Run");
    initializeAnimationVectors(this->jumpFrames, type + "_Jump");
    initializeAnimationVectors(this->idleFrames, type + "_Idle");
    initializeAnimationVectors(this->attackFrames, type + "_Attack");
    initializeAnimationVectors(this->shootFrames, type + "_Throw");
    initializeAnimationVectors(this->deadFrames, type + "_Dead");

    // FIXME: gotta find better solution for this shit
    this->jumped = false;
    this->jumpDuration = false;
    this->attackDuration = 0;
    this->attacked = false;
    this->setScale(1);


    this->initWithSpriteFrameName(type + "_Run (1).png");//assigning a skin to a player

    this->setHitBox(this->getTextureRect());
    startAnimation(this->idleFrames, 0.05f);
}

void AnimatedEntity::initializeAnimationVectors(Vector<SpriteFrame*> &vector, std::string namePattern) {
    //namePattern like "Run" or "Jump"
    char str[100] = {0};
    //loop until there are frames responding to the pattern
    for(unsigned i = 1; true; i++)
    {
        std::string frameName = namePattern + " (" + std::to_string(i) + ")" + ".png";
        SpriteFrame* frame = cache->getSpriteFrameByName(frameName);
        Sprite *tmp = (Sprite*) frame;
        if (!tmp) {
            break;
        }
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