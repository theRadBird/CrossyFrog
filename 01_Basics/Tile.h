#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Tile
{
public:
    Tile();
    ~Tile();

    void setPosition(int pos);
    void updatePosition(matrix4 rowMat);
private:
    matrix4 position;
    bool collidable;
    //std::vector<Obstacle> Props;
    
};

