#include "Mover.h"



Mover::Mover(int _myID)
{
    position = vector3(10.f, 10.f, 10.f);
    speed = 3.f;
    traverseRunTime = 0.f;
    m_pMeshMngr = MeshManagerSingleton::GetInstance();
    bObjMan = BoundingObjectManagerSingleton::GetInstance();
    myIndex = _myID;
}


Mover::~Mover()
{
    bObjMan->RemoveBoundingObj(myIndex);
}

Mover::Mover(vector3 pos, float spd, int _myID) {
    position = pos;
    speed = spd;
    traverseRunTime = 0.f;
    m_pMeshMngr = MeshManagerSingleton::GetInstance();
    bObjMan = BoundingObjectManagerSingleton::GetInstance();
    myIndex = _myID;
}

void Mover::update(double dt) {
    if (!reverse) {
        lerpPos = vector3(-3.f, 0.5f, zPos);
        traverseRunTime += static_cast<float>(dt);

        float percent = MapValue(traverseRunTime, 0.f, speed, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, lerpPos, percent);

        if (moveForward) {
            forwardRunTime += static_cast<float>(dt);
            forwardVec = vector3(0.f, 0.f, otherPercent * moveDirZ);
            //std::cout << "forwardvec distance: " << forwardVec.z << std::endl;
            sidewaysPosChange += forwardVec;

            if (forwardRunTime >= 1.f) {
                zPos = roundf(sidewaysPosChange.z);
                position.z = zPos;
                moveForward = false;
                forwardRunTime = 0.f;
            }
        }

        if (traverseRunTime >= speed) {
            position = vector3(lerpPos.x, lerpPos.y, zPos);
            percent = 0.f;
            traverseRunTime = 0.f;
            reverse = true;
            
            m_pMeshMngr->SetModelMatrix(glm::translate(position), "mover");
            bObjMan->GetBoundingObj(myIndex)->setModelToWorld(glm::translate(position));
            m_pMeshMngr->AddInstanceToRenderList("mover");

        }
        else {
            m_pMeshMngr->SetModelMatrix(glm::translate(sidewaysPosChange), "mover");
            bObjMan->GetBoundingObj(myIndex)->setModelToWorld(glm::translate(sidewaysPosChange));
            m_pMeshMngr->AddInstanceToRenderList("mover");
        }
    }
    else {
        lerpPos = vector3(3.f, 0.5f, zPos);
        traverseRunTime += static_cast<float>(dt);

        float percent = MapValue(traverseRunTime, 0.f, speed, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, lerpPos, percent);

        if (moveForward) {
            forwardRunTime += static_cast<float>(dt);
            forwardVec = vector3(0.f, 0.f, otherPercent * moveDirZ);
            //std::cout << "forwardvec distance: " << forwardVec.z << std::endl;
            sidewaysPosChange += forwardVec;

            if (forwardRunTime >= 1.f) {
                zPos = roundf(sidewaysPosChange.z);
                position.z = zPos;
                moveForward = false;
                forwardRunTime = 0.f;
            }
        }

        if (traverseRunTime >= speed) {
            position = vector3(lerpPos.x, lerpPos.y, zPos);
            percent = 0.f;
            traverseRunTime = 0.f;
            reverse = false;
            m_pMeshMngr->SetModelMatrix(glm::translate(position), "mover");
            bObjMan->GetBoundingObj(myIndex)->setModelToWorld(glm::translate(position));
            m_pMeshMngr->AddInstanceToRenderList("mover");
        }
        else {
            m_pMeshMngr->SetModelMatrix(glm::translate(sidewaysPosChange), "mover");
            bObjMan->GetBoundingObj(myIndex)->setModelToWorld(glm::translate(sidewaysPosChange));
            m_pMeshMngr->AddInstanceToRenderList("mover");
        }
    }
}

void Mover::updatePosition(vector3 moveDir_, bool _moveForward, float percent_) {
    moveForward = _moveForward;
    moveDir = moveDir_;
    //std::cout << moveDir.z << std::endl;
    otherPercent = percent_;
    //if (moveDir.z < oldMoveDir.z) {
    //    moveDirZ = -1.f;
    //}
    moveDirZ = 1.f;
}

void Mover::setPosition(vector3 pos) {
    std::cout << "Z position in start of SetPosition (Mover): " << pos.z << std::endl;
    position = pos;
    zPos = position.z;
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

void Mover::setReverse() {
    reverse = true;
}