#ifndef __BOUNDINGOBJECTMANAGERSINGLETON_H_
#define __BOUNDINGOBJECTMANAGERSINGLETON_H_

#pragma once
#include "BoundingObj.h"

class BoundingObjectManagerSingleton
{
    MeshManagerSingleton* m_pMeshMngr = nullptr;
    int objCount = 0;
    std::vector<BoundingObj*> boundingObjects; //list of BOs
    std::vector<std::vector<int>> collisions;
    std::map<String, uint> mapIndex;

private:
    static BoundingObjectManagerSingleton* instance;
    BoundingObjectManagerSingleton() {

    };
    BoundingObjectManagerSingleton(BoundingObjectManagerSingleton const& other) {
        instance = other.GetInstance();
    };
    BoundingObjectManagerSingleton& operator=(BoundingObjectManagerSingleton const& other) {
        instance = other.GetInstance();
    };
    void BoundingObjectManagerSingleton::CheckCollisions(void);

public:
    static BoundingObjectManagerSingleton* GetInstance() {
        if (instance == nullptr) {
            instance = new BoundingObjectManagerSingleton();
        }
        return instance;
    }
    static void ReleaseInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    // methods
    int AddBoundingObj(BoundingObj* obj);
    void SwitchVisibility(int index);
    int GetNumberBoundingObjects();
    void SetBoundingObjectColor(int index, vector3 color);
    void RenderBoundingObject(int index);
    void RenderAllBoundingObjects();
    bool CheckCollision(int objA, int objB);

    BoundingObj* GetBoundingObj(int index);
    void Update();

};

#endif //__BOUNDINGOBJECTMANAGERSINGLETON_H_