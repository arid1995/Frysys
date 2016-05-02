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

    //gotta find better solution for this shit
    this->jumpDuration = 0;
    this->attackDuration = 0;
    this->jumped = false;
    this->attacked = false;

    this->initWithSpriteFrameName("Run (1).png");//assigning a skin to a player

    

    //setting player's physics parameters up
    /*this->skinBody = PhysicsBody::createBox(this->getContentSize(),
                                            PhysicsMaterial(1, 0.5, 0.5));
    this->skinBody->setRotationEnable(false);//we don't need rotation, do we? I think player can rotate when he jump!
    this->skinBody->setMass(PLAYERS_MASS);
    this->setPhysicsBody(this->skinBody);*/

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
    status = 3;
}

void Player::runToTheLeft() {
    if (isInTheAir()) return;
    this->direction = -1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    status=2;
}

void Player::runToTheRight() {
    //if (isInTheAir()) return;
    this->direction = 1;
    startAnimation(this->runFrames, ANIMATION_INTERVAL);
    //this->skinBody->setVelocity(Vec2(RUN_VELOCITY, 0));
    status=1;
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
    status=4;
}

bool Player::isInTheAir() {
    if (vY!=0) return true;
    return false;
}

void Player::setStatus(int s){
    status = s;
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
        if(this->jumpDuration < delta){
                this->startAnimation(this->idleFrames, ANIMATION_INTERVAL);
        }
    } else {
        if (jumped) {
            jumped = false;
            //if (abs(this->skinBody->getVelocity().x) > DELTA_Y_VELOCITY)
            this->startAnimation(runFrames, ANIMATION_INTERVAL);
        }
    }

    if (direction == -1) {
        this->setFlippedX(true);
    } else {
        this->setFlippedX(false);
    }
    switch(status){
        case 1: vX=2; break;            //press right
        case 2: vX=-2; break;           //press left
        case 3: vY=-7; break;           //press up
        case 4: vX=0; break;            //release right or left or tileLeft or tileRight
        case 5: vY=0; break;            //tileDown
        case 6: vY=1; break;            //notTileDown
    }
    this->setSpeed(Vec2(vX,vY));
    
}

void Player::setSpeed(Vec2 v){
    if (v.y == 0)
        gravityA=0;
    else
        gravityA+=0.25;
    Point pos = this->getPosition();
    this->setPosition(Point(pos.x + v.x, pos.y - v.y - gravityA));
}
