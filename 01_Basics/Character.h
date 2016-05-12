#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

using namespace ReEng;

class Character
{
public:
    Character();
    ~Character();

    void Update(double rt);
    void IsDying();

    vector3 position;
    float jumpDuration;
    float jumpRunTime;
    float sidewaysDuration;
    float sidewaysRunTime;

    float gravity;
    float deadUpSpeed;
    float dyingUpRunTime;
    float dyingUpDuration;
    bool isDying;

    bool up;
    bool IsStill();
    vector3 CharLerp(double rt);
    vector3 CharSideways(double rt);
    void startJump();
    void startSidewaysR();
    void startSidewaysL();
    bool jumping;
    bool sidewaysRight;
    bool sidewaysLeft;

    float laneIncrement;

protected:
    MeshManagerSingleton* m_pMeshMngr;

};

#endif //__CHARACTER_H_