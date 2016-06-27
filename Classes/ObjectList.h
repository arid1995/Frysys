/*
 * Author - Farid
 * Singleton. Contains all objects in the scene
*/
#pragma once

#include "GameObject.h"

class ObjectList {
private:
    static ObjectList* p_instance;
    ObjectList() {}
    ObjectList( const ObjectList& );
    ObjectList& operator=( ObjectList& );

private:
    std::list<GameObject*> objects;

public:
    static ObjectList* getInstance() {
        if(!p_instance)
            p_instance = new ObjectList();
        return p_instance;
    }

    void addObject(GameObject* object);
    std::list<GameObject*>& getList();
    void deleteObject(GameObject* object);
};

