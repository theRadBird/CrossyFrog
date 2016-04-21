#ifndef __BOUNDINGOBJ_H_
#define __BOUNDINGOBJ_H_

#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class BoundingObj
{
private:
    vector3 color;
    vector3 minVert, maxVert;
    //std::vector<vector3> verts;
    vector3 centroid;
    matrix4 m2World = IDENTITY_M4;
    bool visible;
    MeshManagerSingleton* mpMesh = nullptr;

public:
    BoundingObj(std::vector<vector3> modelVerts);
    ~BoundingObj();
    
    vector3 getMin();
    vector3 getMax();
    matrix4 getModelToWorld();
    vector3 getCentroid();

    void setCentroid(vector3 centerToSet);
    void setModelToWorld(matrix4 matToSet);
    void setColor(vector3 setColor);

    void toggleVisible();
    void draw();
    bool isColliding(BoundingObj* const other);
    
};

#endif //__BOUNDINGOBJ_H_