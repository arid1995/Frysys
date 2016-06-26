/*
 * Author - Farid
 * Base class for all objects in the scene
*/

#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(int width, int height, int x, int y, const std::string &spriteFrameName) : isTransparent(false) {
    hitBox = Rect(x, y, width, height);
    initWithSpriteFrameName(spriteFrameName);
}

GameObject::GameObject(int width, int height, int x, int y, SpriteFrame *spriteFrame) : isTransparent(false) {
    hitBox = Rect(x, y, width, height);
    initWithSpriteFrame(spriteFrame);
}

GameObject::GameObject() : isTransparent(false) {
    hitBox = Rect(0, 0, 0, 0);
}

Size GameObject::getSize() {
    return hitBox.size;
}

Vec2 GameObject::getPosition() {
    return hitBox.origin;
}

void GameObject::setSize(int width, int height) {
    hitBox.size = Size(width, height);
}

void GameObject::setPosition(int x, int y) {
    Sprite::setPosition(x, y);
    hitBox.origin = Vec2(x, y);
}

void GameObject::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

std::list<GameObject*> GameObject::getCollidedObjects(std::list<GameObject*> &leveldObjects) {
    std::list<GameObject*> collided;
    for (std::list<GameObject*>::iterator i = leveldObjects.begin(); i != leveldObjects.end(); i++) {
        if (i.operator*()->getPosition().x > hitBox.origin.x) {
            if ((i.operator*()->getPosition().x - (hitBox.origin.x - hitBox.size.width)) >
                (hitBox.size.width + i.operator*()->getSize().width)) {
                continue;
            }
        } else {
            if ((hitBox.origin.x - (i.operator*()->getPosition().x - i.operator*()->getSize().width)) >
                (hitBox.size.width + i.operator*()->getSize().width)) {
                continue;
            }
        }
        if (i.operator*()->getPosition().y > hitBox.origin.y) {
            if (((i.operator*()->getPosition().y + i.operator*()->getSize().height) - hitBox.origin.y) >
                (hitBox.size.height + i.operator*()->getSize().height)) {
                continue;
            }
        } else {
            if (((hitBox.origin.y + hitBox.size.height) - i.operator*()->getPosition().y) >
                (hitBox.size.height + i.operator*()->getSize().height)) {
                continue;
            }
        }
        collided.push_back(*i);
    }
    return collided;
}

//clockwise: 1 - top, 2..3, 4 - left, 0 - not collided
int GameObject::getCollidedSide(GameObject* collidedObject) {
    float yIntersection = 0;
    float xIntersection = 0;
    //left
    if (collidedObject->getPosition().x < hitBox.origin.x) {
        xIntersection = (collidedObject->getPosition().x - hitBox.origin.x) + collidedObject->getSize().width;
        if (xIntersection > hitBox.size.width) xIntersection = hitBox.size.width;
    }
    //right
    if (collidedObject->getPosition().x > hitBox.origin.x) {
        xIntersection = -((hitBox.origin.x - collidedObject->getPosition().x) + collidedObject->getSize().width);
        if (xIntersection > collidedObject->hitBox.size.width) xIntersection = -collidedObject->hitBox.size.width;
    }
    //bottom
    if (collidedObject->getPosition().y < hitBox.origin.y) {
        yIntersection = (collidedObject->getPosition().y - hitBox.origin.y) + collidedObject->getSize().height;
        if (yIntersection > hitBox.size.height) yIntersection = hitBox.size.height;
    }
    //top
    if (collidedObject->getPosition().y > hitBox.origin.y) {
        yIntersection = -((hitBox.origin.y - collidedObject->getPosition().y) + collidedObject->getSize().height);
        if (yIntersection > collidedObject->hitBox.size.height) yIntersection = -collidedObject->hitBox.size.height;
    }

    //is intersection taking place in horizontal plane (left or right)
    bool horizontal = false;
    if (std::abs(xIntersection) > std::abs(yIntersection)) {
        horizontal = false;
    } else {
        horizontal = true;
    }

    if (horizontal) {
        if (xIntersection > 0) return 2;//left
        else return 4;//right
    } else {
        if (yIntersection > 0) return 1;//bottom
        else return 3;//top
    }
}

void GameObject::setHitBox(cocos2d::Rect hitbox) {
    hitBox = hitbox;
}

Rect GameObject::getHitBox() {
    return hitBox;
}

GameObject::~GameObject() {

};