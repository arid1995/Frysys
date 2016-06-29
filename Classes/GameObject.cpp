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

//while setting sprite position also sets hitbox position
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
        if (i.operator*() == this) continue;
        Rect rct1 = hitBox;
        Rect rct2 = i.operator*()->hitBox;
        rct1.origin.y -= rct1.size.height / 2;
        rct2.origin.y -= rct2.size.height / 2;
        if (rct1.intersectsRect(rct2)) {
            GameObject *go = *i;
            collided.push_back(*i);
        }
    }
    return collided;
}

//clockwise: 1 - top, 2..3, 4 - left
int GameObject::getCollidedSide(GameObject* collidedObject) {
    float yIntersection = 0;
    float xIntersection = 0;
    //right
    float x1 = hitBox.origin.x;
    float y1 = hitBox.origin.y;
    float width1 = hitBox.size.width / 2;
    float height1 = hitBox.size.height / 2;
    float x2 = collidedObject->getHitBox().origin.x;
    float y2 = collidedObject->getHitBox().origin.y;
    float width2 = collidedObject->getHitBox().size.width / 2;
    float height2 = collidedObject->getHitBox().size.height / 2;

    //Think of it like 2 segments with known width/height and a middle point
    //horizontal (minus means left)
    if (x1 > x2) {
        if ((x1 + width1) > (x2 + width2)) {
            if ((x2 - width2) < (x1 - width1)) {
                xIntersection = x2 + width2 - (x1 - width1);
            }
            else {
                xIntersection = width2 * 2;
            }
        }
        else {
            xIntersection = width1 * 2;
        }
    }
    else {
        if ((x1 + width1) < (x2 + width2)) {
            if ((x2 - width2) > (x1 - width1)) {
                xIntersection = -(x1 + width1 - (x2 - width2));
            }
            else {
                xIntersection = -width1 * 2;
            }
        }
        else {
            xIntersection = -width2 * 2;
        }
    }

    //vertical (minus means bottom)
    if (y1 > y2) {
        if ((y1 + height1) > (y2 + height2)) {
            if ((y2 - height2) < (y1 - height1)) {
                yIntersection = y2 + height2 - (y1 - height1);
            }
            else {
                yIntersection = height2 * 2;
            }
        }
        else {
            yIntersection = height1 * 2;
        }
    }
    else {
        if ((y1 + height1) < (y2 + height2)) {
            if ((y2 - height2) > (y1 - height1)) {
                yIntersection = -(y1 + height1 - (y2 - height2));
            }
            else {
                yIntersection = -height1 * 2;
            }
        }
        else {
            yIntersection = -height2 * 2;
        }
    }

    //is intersection taking place in horizontal plane (left or right)
    bool horizontal = false;
    if (std::abs(xIntersection) > std::abs(yIntersection)) {
        horizontal = false;
    } else {
        horizontal = true;
    }
    if (horizontal) {
        if (xIntersection > 0) return 4;//right
        else return 2;//left
    } else {
        if (yIntersection > 0) return 3;//top
        else return 1;//bottom
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