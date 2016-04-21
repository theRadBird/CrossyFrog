#include "Obstacle.h"



Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::setPosition(vector3 pos) {
    position = pos;
}
vector3 Obstacle::getPosition() {
    return position;
}

void Obstacle::setRadius(float rad) {
    radius = rad;
}
float Obstacle::getRadius() {
    return radius;
}
