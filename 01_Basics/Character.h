#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Character
{
public:
    Character();
    ~Character();

    void Update(double rt);

    vector3 position;
    float duration;
    float jumpRunTime;
    bool up;
    vector3 CharLerp(double rt);
    void startJump();
    bool jumping;

};

#endif //__CHARACTER_H_