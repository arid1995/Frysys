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
    died = false;

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

void AnimatedEntity::dead() {
    startAnimation(deadFrames, ANIMATION_INTERVAL, false);
    // TODO: write other stuff that needs to happen when player dies
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

bool AnimatedEntity::isAlive() {
    if (lives <= 0) {
        ObjectList::getInstance()->deleteObject(this);
        if(!died) {
            dead();
            died = true;
        }
        return false;
    }
    return true;
};

int AnimatedEntity::getDamage () {
    if (attacked) {
        int dmg = damage;
        damage = 0;
        isDamageInflicted = true;
        return dmg;
    }
    return 0;
}

std::list<GameObject*> AnimatedEntity::baseUpdate(float delta) {
    std::list<GameObject*> collided = getCollidedObjects(ObjectList::getInstance()->getList());

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

    if (collided.size() != 0) {
        for (std::list<GameObject*>::iterator i = collided.begin(); i != collided.end(); i++) {
            lives -= i.operator*()->getDamage();
        }
    }

    //mirror sprites if direction is left
    if (direction == -1) {
        setFlippedX(true);
    } else {
        setFlippedX(false);
    }

    setSpeed(Vec2(getSpeedX(), getSpeedY()));

    //for melee attack
    if (attacked && !isDamageInflicted) {
        isDamageInflicted = true;
        damage = 1;
    }

    if (!attacked) {
        isDamageInflicted = false;
    }

    return collided;
}

int AnimatedEntity::getLives(){
    return lives;
}