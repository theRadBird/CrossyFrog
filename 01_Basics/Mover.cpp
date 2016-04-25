#include "Mover.h"



Mover::Mover()
{
}


Mover::~Mover()
{
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