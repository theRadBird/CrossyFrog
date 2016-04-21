#ifndef __OBSTACLE_H_
#define __OBSTACLE_H_

#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

using namespace ReEng;

class Obstacle
{
public:
    Obstacle();
    ~Obstacle();

    vector3 position;
    float radius;

    void setPosition(vector3 pos);
    vector3 getPosition();

    void setRadius(float rad);
    float getRadius();

};

#endif //__OBSTACLE_H_