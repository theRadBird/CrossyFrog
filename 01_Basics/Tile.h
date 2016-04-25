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
    void update(double dt);
    void draw();
    void setObstacleTile();

protected:
	MeshManagerSingleton* m_pMeshMngr = nullptr;
private:
    matrix4 position;
    vector3 pos;
    bool collidable;
    bool isObstacleTile = false;
    //std::vector<Obstacle> Props;
    
};

