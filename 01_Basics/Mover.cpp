#include "Mover.h"



Mover::Mover()
{
    position = vector3(3.f, 0.5f, 0.f);
    speed = 3.f;
    traverseRunTime = 0.f;
    m_pMeshMngr = MeshManagerSingleton::GetInstance();
}


Mover::~Mover()
{
}

void Mover::update(double dt) {
    if (!reverse) {
        lerpPos = vector3(-3.f, 0.5f, 0.f);
        traverseRunTime += static_cast<float>(dt);

        float percent = MapValue(traverseRunTime, 0.f, speed, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, lerpPos, percent);

        if (traverseRunTime >= speed) {
            position = lerpPos;
            percent = 0.f;
            traverseRunTime = 0.f;
            reverse = true;
            m_pMeshMngr->SetModelMatrix(glm::translate(position), "obstacle");
            m_pMeshMngr->AddInstanceToRenderList("obstacle");
        }
        else {
            m_pMeshMngr->SetModelMatrix(glm::translate(sidewaysPosChange), "obstacle");
            m_pMeshMngr->AddInstanceToRenderList("obstacle");
        }
    }
    else {
        lerpPos = vector3(3.f, 0.5f, 0.f);
        traverseRunTime += static_cast<float>(dt);

        float percent = MapValue(traverseRunTime, 0.f, speed, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, lerpPos, percent);

        if (traverseRunTime >= speed) {
            position = lerpPos;
            percent = 0.f;
            traverseRunTime = 0.f;
            reverse = false;
            m_pMeshMngr->SetModelMatrix(glm::translate(position), "obstacle");
            m_pMeshMngr->AddInstanceToRenderList("obstacle");
        }
        else {
            m_pMeshMngr->SetModelMatrix(glm::translate(sidewaysPosChange), "obstacle");
            m_pMeshMngr->AddInstanceToRenderList("obstacle");
        }
    }
}

void Mover::setPosition(vector3 pos) {
    position = pos;
}

vector3 Mover::getPosition() {
    return position;
}

void Mover::setRadius(float rad) {
    radius = rad;
}

float Mover::getRadius() {
    return radius;
}

void Mover::setSpeed(float speed_) {
    speed = speed_;
}

float Mover::getSpeed() {
    return speed;
}

void Mover::setLerpPos(vector3 lerpPos_) {
    lerpPos = lerpPos_;
}

vector3 Mover::getLerpPos() {
    return lerpPos;
}