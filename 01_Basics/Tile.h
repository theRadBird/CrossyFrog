#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include <string>

class Tile
{	
public:
    Tile(int num);
    ~Tile();

    void setPosition(int pos);
    void updatePosition(matrix4 rowMat);
    void update(double dt);
    void draw();
    void setObstacleTile();
    bool isObst();
protected:
	MeshManagerSingleton* m_pMeshMngr = nullptr;
private:
    matrix4 position;
    vector3 pos;
    bool collidable;
    bool isObstacleTile = false;
    String meshName;
    //std::vector<Obstacle> Props;
    
};

