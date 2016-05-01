/*
 * Author - Farid
 * The architecture of this class is quite messy, even I can (and did) easily lose a track of this code
 * so don't delete, edit or add anything unless u r absolutely 100% sure about what u r doing
*/
#include "Player.h"

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

    //gotta find better solution for this shit
    this->jumpDuration = 0;
    this->attackDuration = 0;
    this->jumped = false;
    this->attacked = false;

    this->initWithSpriteFrameName("Run (1).png");//assigning a skin to a player

    this->setPosition(Point(this->size.width / 2, this->size.height / 2));

    //setting player's physics parameters up
    this->skinBody = PhysicsBody::createBox(this->getContentSize(),
                                            PhysicsMaterial(1, 0.5, 0.5));
    this->skinBody->setRotationEnable(false);//we don't need rotation, do we? I think player can rotate when he jump!
    this->skinBody->setMass(PLAYERS_MASS);
    this->setPhysicsBody(this->skinBody);

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
    this->jumped = true;
    this->jumpDuration = JUMP_INTERVAL * 10;
    startAnimation(this->jumpFrames, JUMP_INTERVAL, false);
    this->skinBody->setVelocity(Vec2(this->skinBody->getVelocity().x, JUMP_VELOCITY));
}

void Player::runToTheLeft() {
    if (isInTheAir()) return;
    this->direction = -1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    this->skinBody->setVelocity(Vec2(-RUN_VELOCITY, 0));
}

void Player::runToTheRight() {
    if (isInTheAir()) return;
    this->direction = 1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 0));
}

void Player::attack() {
    if (isInTheAir()) return;
    this->attacked = true;
    this->attackDuration = ANIMATION_INTERVAL * 10;
    startAnimation(this->attackFrames, ANIMATION_INTERVAL, false);
    this->skinBody->setVelocity(Vec2(0, 0));
}

void Player::stop() {
    //if (isInTheAir()) return;
    startAnimation(this->idleFrames, ANIMATION_INTERVAL);
    this->skinBody->setVelocity(Vec2(0, this->skinBody->getVelocity().y));
}

bool Player::isInTheAir() {
    if (abs(this->skinBody->getVelocity().y) > DELTA_Y_VELOCITY) return true;
    return false;
}

void Player::update(float delta) {
    //mirror sprites if direction is left
    //this is totally fucked up
    if (this->attackDuration > 0) {
        this->attackDuration -= delta;
    } else {
        if (attacked) {
            attacked = false;

            if (abs(this->skinBody->getVelocity().x) > DELTA_Y_VELOCITY)
                this->startAnimation(runFrames, ANIMATION_INTERVAL);
            else
                this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        }
    }

    if (this->jumpDuration > 0) {
        this->jumpDuration -= delta;
    } else {
        if (jumped) {
            jumped = false;

            if (abs(this->skinBody->getVelocity().x) > DELTA_Y_VELOCITY)
                this->startAnimation(runFrames, ANIMATION_INTERVAL);
            else
                this->startAnimation(idleFrames, ANIMATION_INTERVAL);
        }
    }

    if (direction == -1) {
        this->setFlippedX(true);
    } else {
        this->setFlippedX(false);
    }
}