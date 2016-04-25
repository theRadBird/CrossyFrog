#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Mover
{
public:
    Mover();
    ~Mover();

    void update(double dt);

    void setPosition(vector3 pos);
    vector3 getPosition();

    void setRadius(float rad);
    float getRadius();

    void setSpeed(float speed);
    float getSpeed();

    void setLerpPos(vector3 lerpPos_);
    vector3 getLerpPos();

protected:
    MeshManagerSingleton* m_pMeshMngr;

private:
    vector3 position;
    vector3 lerpPos;
    float speed;
    float radius;
    float traverseRunTime;
    bool reverse = false;
};

