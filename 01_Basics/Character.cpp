#include "Character.h"



Character::Character()
{
    m_pMeshMngr = MeshManagerSingleton::GetInstance();
    position = vector3(0.f, 0.6f, 0.f);
    sidewaysDuration = 1.f;
    sidewaysRunTime = 0.f;
    jumpDuration = 0.5f;
    jumpRunTime = 0.f;
    up = true;
    jumping = false;
    sidewaysRight = false;
    sidewaysLeft = false;
    laneIncrement = 0.f;
}


Character::~Character()
{
}

void Character::Update(double rt) {
    if (jumping) {
        vector3 playerJump = CharLerp(rt);
        m_pMeshMngr->SetModelMatrix(glm::translate(playerJump), "character");
    }
    if (sidewaysRight || sidewaysLeft) {
        vector3 playerMove = CharSideways(rt);
        m_pMeshMngr->SetModelMatrix(glm::translate(playerMove), "character");
    }
    m_pMeshMngr->AddInstanceToRenderList("character");
}

bool Character::IsStill() {
    bool temp = true;
    if (sidewaysLeft || sidewaysRight || jumping) {
        temp = false;
    }
    return temp;
}

vector3 Character::CharSideways(double rt) {
    if (sidewaysRight && laneIncrement < 3.f) {
        vector3 sidewaysLerpPos = vector3(laneIncrement + 1.f, 0.6f, 0.f);
        sidewaysRunTime += static_cast<float>(rt);

        float percent = MapValue(sidewaysRunTime, 0.f, sidewaysDuration, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, sidewaysLerpPos, percent);
        

        if (sidewaysRunTime >= sidewaysDuration) {
            position = sidewaysLerpPos;
            percent = 0.f;
            sidewaysRunTime = 0.f;
            sidewaysRight = false;
            laneIncrement += 1.f;
            //std::cout << laneIncrement << std::endl;
            return position;
        }
        else return sidewaysPosChange;
    }
    if (sidewaysLeft && laneIncrement > -3.f) {
        vector3 sidewaysLerpPos = vector3(laneIncrement - 1.f, 0.6f, 0.f);
        sidewaysRunTime += static_cast<float>(rt);

        float percent = MapValue(sidewaysRunTime, 0.f, sidewaysDuration, 0.f, 1.f);
        vector3 sidewaysPosChange = glm::lerp(position, sidewaysLerpPos, percent);

        if (sidewaysRunTime >= sidewaysDuration) {
            position = sidewaysLerpPos;
            percent = 0.f;
            sidewaysRunTime = 0.f;
            sidewaysLeft = false;
            laneIncrement -= 1.f;
            //std::cout << laneIncrement << std::endl;
            return position;
        }
        else return sidewaysPosChange;
    }


    return position;
}

vector3 Character::CharLerp(double rt) {
    if (jumping) {
        if (up) {
            vector3 lerpPos = vector3(laneIncrement, 1.3f, 0.f);
            jumpRunTime += static_cast<float>(rt);
            
            float percent = MapValue(jumpRunTime, 0.f, jumpDuration, 0.f, 1.f);
            vector3 posChange = glm::lerp(position, lerpPos, percent);

            if (jumpRunTime >= jumpDuration) {
                up = false;
                position = lerpPos;
                percent = 0.f;
                jumpRunTime = 0.f;
                return position;
            }
            else {
                return posChange;
            }
        }
        if (!up) {
            vector3 lerpPos = vector3(laneIncrement, 0.6f, 0.f);
            jumpRunTime += static_cast<float>(rt);

            float percent = MapValue(jumpRunTime, 0.f, jumpDuration, 0.f, 1.f);
            vector3 posChange = glm::lerp(position, lerpPos, percent);

            if (jumpRunTime >= jumpDuration) {
                up = true;
                position = lerpPos;
                percent = 0.f;
                jumpRunTime = 0.f;
                jumping = false;
                return position;
            }
            else {
                return posChange;
            }
        }
    }
    return position;
}

void Character::startJump() {
    jumping = true;
}

void Character::startSidewaysR() {
    if (!sidewaysLeft && laneIncrement < 3.f) {
        sidewaysRight = true;
    }
    else sidewaysRight = false;
}

void Character::startSidewaysL() {
    if (!sidewaysRight && laneIncrement > -3.f) {
        sidewaysLeft = true;
    }
    else sidewaysLeft = false;
}