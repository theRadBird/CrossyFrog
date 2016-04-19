#include "Character.h"



Character::Character()
{
    position = vector3(0.f, 0.6f, 0.f);
    duration = 0.5f;
    jumpRunTime = 0.f;
    up = true;
    jumping = false;
}


Character::~Character()
{
}

//void Character::Update(double rt) {
//    if (jumping) {
//        vector3 playerMove = CharLerp(rt);
//        m_pMeshMngr->SetModelMatrix(glm::translate(playerMove), "character");
//    }
//}

vector3 Character::CharLerp(double rt) {
    if (jumping) {
        if (up) {
            vector3 lerpPos = vector3(0.f, 1.3f, 0.f);
            jumpRunTime += static_cast<float>(rt);

            float percent = MapValue(jumpRunTime, 0.f, duration, 0.f, 1.f);
            vector3 posChange = glm::lerp(position, lerpPos, percent);
            if (jumpRunTime >= duration) {
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
            vector3 lerpPos = vector3(0.f, 0.6f, 0.f);
            jumpRunTime += static_cast<float>(rt);

            float percent = MapValue(jumpRunTime, 0.f, duration, 0.f, 1.f);
            vector3 posChange = glm::lerp(position, lerpPos, percent);
            if (jumpRunTime >= duration) {
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