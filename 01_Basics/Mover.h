#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Mover
{
public:
    Mover();
    ~Mover();
    Mover(vector3 pos, float spd);

    void update(double dt);
    void updatePosition(vector3 moveDir_, bool moveForward, float percent);

    void setPosition(vector3 pos);
    vector3 getPosition();
    
    void setRadius(float rad);
    float getRadius();

    void setSpeed(float speed);
    float getSpeed();

    void setLerpPos(vector3 lerpPos_);
    vector3 getLerpPos();

    void setReverse();

protected:
    MeshManagerSingleton* m_pMeshMngr;

private:
    vector3 forwardVec;
    vector3 position;
    vector3 lerpPos;
    vector3 moveDir;
    vector3 oldMoveDir = vector3(0.f, 0.f, 0.f);
    float moveDirZ;
    float zPos;
    float speed;
    float radius;
    float traverseRunTime;
    float forwardRunTime;
    float otherPercent;
    bool reverse = false;
    bool moveForward = false;
};

