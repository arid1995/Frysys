/*
 * Author - Farid
 * Singleton. Contains all objects in the scene
*/

#include "ObjectList.h"

ObjectList* ObjectList::p_instance = 0;

void ObjectList::addObject(GameObject* object) {
    objects.push_back(object);
}

std::list<GameObject*>& ObjectList::getList() {
    return objects;
}

void ObjectList::deleteObject(GameObject* object) {
    objects.remove(object);
}