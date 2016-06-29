/*
 * Author - Farid
 * Base class for all "alive" objects
*/
#include "AnimatedEntity.h"

USING_NS_CC;

AnimatedEntity::AnimatedEntity(std::string type, Layer* _layer) {
    direction = 1;
    size = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    layer = _layer;

    cache = SpriteFrameCache::getInstance();

    initializeAnimationVectors(runFrames, type + "_Run");
    initializeAnimationVectors(jumpFrames, type + "_Jump");
    initializeAnimationVectors(idleFrames, type + "_Idle");
    initializeAnimationVectors(attackFrames, type + "_Attack");
    initializeAnimationVectors(shootFrames, type + "_Throw");
    initializeAnimationVectors(deadFrames, type + "_Dead");

    // FIXME: gotta find better solution for this shit
    jumped = false;
    jumpDuration = false;
    attackDuration = 0;
    attacked = false;
    setScale(1);


    initWithSpriteFrameName(type + "_Run (1).png");//assigning a skin to a player

    setHitBox(getTextureRect());
    startAnimation(idleFrames, 0.05f);
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
    stopAllActions();
    Animation* animation = Animation::createWithSpriteFrames(animVector, animSpeed);
    if (looped) {
        runAction(RepeatForever::create(Animate::create(animation)));
        
    } else
    {
        runAction(Animate::create(animation));
    }
}


void AnimatedEntity::jump() {
    if (isInTheAir()) return;
    jumpDuration = true;
    jumped = true;
    startAnimation(jumpFrames, JUMP_INTERVAL, false);
    setSpeedY(-7);
}

void AnimatedEntity::runToTheLeft() {
    if (isInTheAir()) return;
    direction = -1;
    startAnimation(runFrames, ANIMATION_INTERVAL);
    setSpeedX(-getVelocity());
}

void AnimatedEntity::runToTheRight() {
    if (isInTheAir()) return;
    direction = 1;
    startAnimation(runFrames, ANIMATION_INTERVAL);
    setSpeedX(getVelocity());
}

void AnimatedEntity::stop() {
    startAnimation(idleFrames, ANIMATION_INTERVAL);
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

void AnimatedEntity::collide(GameObject* object) {

}

std::list<GameObject*> AnimatedEntity::baseUpdate(float delta) {
    if (attackDuration > 0) {
        attackDuration -= delta;
    } else
    if (attacked) {
        attacked = false;
        if (getSpeedX() != 0)
            startAnimation(runFrames, ANIMATION_INTERVAL);
        else
            startAnimation(idleFrames, ANIMATION_INTERVAL);
    }

    std::list<GameObject*> collided = getCollidedObjects(ObjectList::getInstance()->getList());

    if (collided.size() != 0) {
        for (std::list<GameObject*>::iterator i = collided.begin(); i != collided.end(); i++) {

        }
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }

    setSpeed(Vec2(getSpeedX(), getSpeedY()));

    return collided;
}