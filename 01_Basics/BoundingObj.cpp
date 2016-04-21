#include "BoundingObj.h"



BoundingObj::BoundingObj(std::vector<vector3> modelVects)
{
    //verts = modelVects;
    mpMesh = MeshManagerSingleton::GetInstance();

    int count = modelVects.size();

    if (count > 0) { 
        minVert = modelVects[0];
        maxVert = modelVects[0];
    }

    for (int i = 0; i < count; i++) {
        // X
        if (modelVects[i].x > maxVert.x) {
            maxVert.x = modelVects[i].x ;
        }else if(modelVects[i].x < minVert.x) {
            minVert.x = modelVects[i].x;
        }

        // Y
        if (modelVects[i].y > maxVert.y) {
            maxVert.y = modelVects[i].y;
        }else if(modelVects[i].y < minVert.y) {
            minVert.y = modelVects[i].y;
        }

        // Z
        if (modelVects[i].y > maxVert.y) {
            maxVert.y = modelVects[i].y;
        }else if(modelVects[i].y < minVert.y) {
            minVert.y = modelVects[i].y;
        }
    }

}


BoundingObj::~BoundingObj()
{

}

vector3 BoundingObj::getMin()
{
    return minVert;
}

vector3 BoundingObj::getMax()
{
    return maxVert;
}

matrix4 BoundingObj::getModelToWorld()
{
    return m2World;
}

vector3 BoundingObj::getCentroid()
{
    return vector3(m2World*vector4(centroid, 1.0f));
}

void BoundingObj::setCentroid(vector3 centerToSet)
{
    centroid = centerToSet;
}

void BoundingObj::setModelToWorld(matrix4 matToSet)
{
    m2World = matToSet;
}

void BoundingObj::setColor(vector3 setColor)
{
    color = setColor;
}

void BoundingObj::toggleVisible()
{
    visible ? visible = false : visible = true;
}

void BoundingObj::draw()
{
    mpMesh->AddCubeToQueue(m2World, color, WIRE);
}

bool BoundingObj::isColliding(BoundingObj* const other)
{
    bool status = true;
    vector3 wMme = vector3(m2World * vector4(centroid, 1.0f));
    vector3 wMother = vector3(other->getModelToWorld() * vector4(other->getCentroid(), 1.0f));

    vector3 wMmin1 = vector3(m2World * vector4(minVert, 1.0f));
    vector3 wMmax1 = vector3(m2World * vector4(maxVert, 1.0f));
    vector3 wMmin2 = vector3(other->getModelToWorld() * vector4(other->getMin(), 1.0f));
    vector3 wMmax2 = vector3(other->getModelToWorld() * vector4(other->getMax(), 1.0f));

    if (status && wMmax1.x < wMmin2.x || wMmin1.x > wMmax2.x) {
        status = false;
    }
    if (status && wMmax1.y < wMmin2.y || wMmin1.y > wMmax2.y) {
        status = false;
    }
    if (status && wMmax1.z < wMmin2.z || wMmin1.z > wMmax2.z) {
        status = false;
    }

    return status;
}
