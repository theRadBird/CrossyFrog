#include "BoundingObjectManagerSingleton.h"

int BoundingObjectManagerSingleton::AddBoundingObj(BoundingObj* obj) {
    boundingObjects.push_back(obj);
    objCount++;
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
    for (int i = 0; i < boundingObjects.size(); i++) {
        BoundingObj* a = boundingObjects[i];
        BoundingObj* b = boundingObjects[i + 1];
    }
}