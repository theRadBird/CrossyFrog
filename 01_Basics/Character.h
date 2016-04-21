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

    vector3 Update(double rt);

    vector3 position;
    float jumpDuration;
    float jumpRunTime;
    float sidewaysDuration;
    float sidewaysRunTime;
    bool up;
    
    vector3 CharLerp(double rt);
    vector3 CharSideways(double rt);
    void startJump();
    void startSidewaysR();
    void startSidewaysL();
    bool jumping;
    bool sidewaysRight;
    bool sidewaysLeft;

    float laneIncrement;

};

#endif //__CHARACTER_H_