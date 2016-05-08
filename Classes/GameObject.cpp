/*
 * Author - Farid
 * Base class for all objects in the scene
*/

#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(int width, int height, int x, int y, const std::string &spriteFrameName) {
    this->hitBox = new Rect(x, y, width, height);
    this->initWithSpriteFrameName(spriteFrameName);
}

GameObject::GameObject(int width, int height, int x, int y, SpriteFrame *spriteFrame) {
    this->hitBox = new Rect(x, y, width, height);
    this->initWithSpriteFrame(spriteFrame);
}

GameObject::GameObject() {
    this->hitBox = new Rect();
    this->hitBox->setRect(0, 0, 0, 0);
}

Size GameObject::getSize() {
    return this->hitBox->size;
}

Vec2 GameObject::getPosition() {
    return this->hitBox->origin;
}

void GameObject::setSize(int width, int height) {
    this->hitBox->size = Size(width, height);
}

void GameObject::setPosition(int x, int y) {
    Sprite::setPosition(x, y);
    this->hitBox->origin = Vec2(x, y);
}

void GameObject::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

//shows objects which are collided with THIS object in current moment
std::vector<GameObject*> GameObject::getCollidedObjects(std::vector<GameObject*> &leveldObjects) {
    std::vector<GameObject*> collided;
    for (int i = 0; i < leveldObjects.size(); i++) {
        if (leveldObjects[i]->getPosition().x > this->hitBox->origin.x) {
            if ((leveldObjects[i]->getPosition().x - (this->hitBox->origin.x - this->hitBox->size.width)) >
                    (this->hitBox->size.width + leveldObjects[i]->getSize().width)) {
                continue;
            }
        } else {
            if ((this->hitBox->origin.x - (leveldObjects[i]->getPosition().x - leveldObjects[i]->getSize().width)) >
                (this->hitBox->size.width + leveldObjects[i]->getSize().width)) {
                continue;
            }
        }
        if (leveldObjects[i]->getPosition().y > this->hitBox->origin.y) {
            if ((leveldObjects[i]->getPosition().y - (this->hitBox->origin.y - this->hitBox->size.height)) >
                (this->hitBox->size.height + leveldObjects[i]->getSize().height)) {
                continue;
            }
        } else {
            if ((this->hitBox->origin.y - (leveldObjects[i]->getPosition().y - leveldObjects[i]->getSize().height)) >
                (this->hitBox->size.height + leveldObjects[i]->getSize().height)) {
                continue;
            }
        }
        collided.push_back(leveldObjects[i]);
    }
    return collided;
}

GameObject::~GameObject() {
    delete this->hitBox;
};