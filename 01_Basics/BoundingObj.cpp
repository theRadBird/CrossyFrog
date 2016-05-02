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

    centroid = (minVert + maxVert) / 2.0f;
    m_v3HalfWidth = (maxVert - minVert) / 2.0f;

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
    
    //-------------------------------- Separation Axis Theorem -------------//
    /*
    | T • L | > | ( WA*Ax ) • L | + | ( HA*Ay ) • L | + |( DA*Az ) • L | + | ( WB*Bx ) • L | + |( HB*By ) • L | + |( DB*Bz ) • L |
    T = Cb-Ca
    L = normal axis
    formula from: http://www.jkh.me/files/tutorials/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf
    */

    vector3 planeNormals[15];

    //my three face normals
    planeNormals[0] = TransformLocalAxis(this, REAXISX);
    planeNormals[1] = TransformLocalAxis(this, REAXISY);
    planeNormals[2] = TransformLocalAxis(this, REAXISZ);

    //other's three face normals
    planeNormals[3] = TransformLocalAxis(other, REAXISX);
    planeNormals[4] = TransformLocalAxis(other, REAXISY);
    planeNormals[5] = TransformLocalAxis(other, REAXISZ);

    //cross product combinations of face normals
    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            int index = 3 * i + j + 3;
            planeNormals[index] = glm::cross(planeNormals[i], planeNormals[j]);
            if (planeNormals[index] != vector3(0.0f)) {
                planeNormals[index] = glm::normalize(planeNormals[index]);
            }
        }
    }

    vector3 t = other->centroid - this->centroid;

    for (int i = 0; i < 15; ++i) {
        vector3 n = planeNormals[i];
        float dist = glm::abs(glm::dot(n, t));
        float aDist = 0.0f;
        float bDist = 0.0f;
        for (int j = 0; j < 3; ++j) {
            aDist += glm::abs(glm::dot(this->m_v3HalfWidth[j] * planeNormals[j], n));	//my width,height,depth dot products
            bDist += glm::abs(glm::dot(other->m_v3HalfWidth[j] * planeNormals[j + 3], n));	//other width,height,depth,dot products			
        }
        if (dist > aDist + bDist) {
            //std::cout << dist << ": " << aDist+bDist << " - " << i << std::endl;
            float m = 0.5f * (dist + aDist - bDist);
            //DrawPlane(this->centroid + glm::sign(glm::dot(planeNormals[i], t))*planeNormals[i] * m, planeNormals[i], PlaneColor(i));
            return false;
        }
    }
    return status;
}

vector3 BoundingObj::TransformVector(matrix4 m, vector3 v) {
    return vector3(m * vector4(v, 1.f));
}

vector3 BoundingObj::TransformLocalAxis(BoundingObj* box, vector3 axis) {
    return glm::normalize(TransformVector(box->getModelToWorld(), axis + box->centroid) - box->centroid);
}
