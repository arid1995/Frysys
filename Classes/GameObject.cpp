/*
 * Author - Farid
 * Base class for all objects in the scene
*/

#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(int width, int height, int x, int y, const std::string &spriteFrameName) : isTransparent(false) {
    this->hitBox = Rect(x, y, width, height);
    this->initWithSpriteFrameName(spriteFrameName);
}

GameObject::GameObject(int width, int height, int x, int y, SpriteFrame *spriteFrame) : isTransparent(false) {
    this->hitBox = Rect(x, y, width, height);
    this->initWithSpriteFrame(spriteFrame);
}

GameObject::GameObject() : isTransparent(false) {
    this->hitBox = Rect(0, 0, 0, 0);
}

Size GameObject::getSize() {
    return this->hitBox.size;
}

Vec2 GameObject::getPosition() {
    return this->hitBox.origin;
}

void GameObject::setSize(int width, int height) {
    this->hitBox.size = Size(width, height);
}

void GameObject::setPosition(int x, int y) {
    Sprite::setPosition(x, y);
    this->hitBox.origin = Vec2(x, y);
}

void GameObject::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

//shows objects which are collided with THIS object in current moment
std::vector<GameObject*> GameObject::getCollidedObjects(const std::vector<GameObject*> &leveldObjects) {
    std::vector<GameObject*> collided;
    for (int i = 0; i < leveldObjects.size(); i++) {
        if (leveldObjects[i]->getPosition().x > this->hitBox.origin.x) {
            if ((leveldObjects[i]->getPosition().x - (this->hitBox.origin.x - this->hitBox.size.width)) >
                    (this->hitBox.size.width + leveldObjects[i]->getSize().width)) {
                continue;
            }
        } else {
            if ((this->hitBox.origin.x - (leveldObjects[i]->getPosition().x - leveldObjects[i]->getSize().width)) >
                (this->hitBox.size.width + leveldObjects[i]->getSize().width)) {
                continue;
            }
        }
        if (leveldObjects[i]->getPosition().y > this->hitBox.origin.y) {
            if (((leveldObjects[i]->getPosition().y + leveldObjects[i]->getSize().height) - this->hitBox.origin.y) >
                (this->hitBox.size.height + leveldObjects[i]->getSize().height)) {
                continue;
            }
        } else {
            if (((this->hitBox.origin.y + this->hitBox.size.height) - leveldObjects[i]->getPosition().y) >
                (this->hitBox.size.height + leveldObjects[i]->getSize().height)) {
                continue;
            }
        }
        collided.push_back(leveldObjects[i]);
    }
    return collided;
}

std::vector<std::list<GameObject*>::iterator> GameObject::getCollidedObjects(std::list<GameObject*> &leveldObjects) {
    std::vector<std::list<GameObject*>::iterator> collided;
    for (std::list<GameObject*>::iterator i = leveldObjects.begin(); i != leveldObjects.end(); i++) {
        if (i.operator*()->getPosition().x > this->hitBox.origin.x) {
            if ((i.operator*()->getPosition().x - (this->hitBox.origin.x - this->hitBox.size.width)) >
                (this->hitBox.size.width + i.operator*()->getSize().width)) {
                continue;
            }
        } else {
            if ((this->hitBox.origin.x - (i.operator*()->getPosition().x - i.operator*()->getSize().width)) >
                (this->hitBox.size.width + i.operator*()->getSize().width)) {
                continue;
            }
        }
        if (i.operator*()->getPosition().y > this->hitBox.origin.y) {
            if (((i.operator*()->getPosition().y + i.operator*()->getSize().height) - this->hitBox.origin.y) >
                (this->hitBox.size.height + i.operator*()->getSize().height)) {
                continue;
            }
        } else {
            if (((this->hitBox.origin.y + this->hitBox.size.height) - i.operator*()->getPosition().y) >
                (this->hitBox.size.height + i.operator*()->getSize().height)) {
                continue;
            }
        }
        collided.push_back(i);
    }
    return collided;
}

void GameObject::setHitBox(cocos2d::Rect hitbox) {
    this->hitBox = hitbox;
}

Rect GameObject::getHitBox() {
    return this->hitBox;
}

// TODO: add collision checker that works with std::list
// TODO:  add function that shows which side is collided

GameObject::~GameObject() {

};