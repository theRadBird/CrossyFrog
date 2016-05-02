#include "BoundingObjectManagerSingleton.h"

BoundingObjectManagerSingleton* BoundingObjectManagerSingleton::instance = nullptr;

int BoundingObjectManagerSingleton::AddBoundingObj(BoundingObj* obj) {
   boundingObjects.push_back(obj);
    objCount++;
    std::vector<int> lVector;
    collisions.push_back(lVector);
    return objCount - 1;
}

void BoundingObjectManagerSingleton::SwitchVisibility(int index) {
    boundingObjects[index]->toggleVisible();
}

int BoundingObjectManagerSingleton::GetNumberBoundingObjects() {
    return boundingObjects.size();
}

void BoundingObjectManagerSingleton::SetBoundingObjectColor(int index, vector3 color) {
    boundingObjects[index]->setColor(color);
}

void BoundingObjectManagerSingleton::RenderBoundingObject(int index) {
    boundingObjects[index]->draw();
}

void BoundingObjectManagerSingleton::RenderAllBoundingObjects() {
    for (int i = 0; i < boundingObjects.size(); i++) {
        boundingObjects[i]->draw();
    }
}

bool BoundingObjectManagerSingleton::CheckCollision(int objA, int objB) {
    BoundingObj* a = boundingObjects[objA];
    bool collide = a->isColliding(boundingObjects[objB]);
    return collide;
}

BoundingObj* BoundingObjectManagerSingleton::GetBoundingObj(int index) {
    BoundingObj* obj = boundingObjects[index];
    return obj;
}

void BoundingObjectManagerSingleton::Update() {
    for (uint nObject = 0; nObject < objCount; nObject++)
    {
        collisions[nObject].clear();
    }
    CheckCollisions();
}

void BoundingObjectManagerSingleton::CheckCollisions(void)
{
    for (uint nObjectA = 0; nObjectA < objCount - 1; nObjectA++)
    {
        for (uint nObjectB = nObjectA + 1; nObjectB < objCount; nObjectB++)
        {
            if (boundingObjects[nObjectA]->isColliding(boundingObjects[nObjectB]))
            {
                collisions[nObjectA].push_back(nObjectB);
                collisions[nObjectB].push_back(nObjectA);
            }
        }
    }
}