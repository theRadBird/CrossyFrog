#pragma once
#include "Tile.h"

class StageRow
{
public:
    StageRow(int amount, bool isObstacle);
    ~StageRow();
    
    void setPosition(float rowPos);
    void updatePosition(vector3 moveDir);
    void update(double dt);
    void updateTiles();
    void draw();

private:
    std::vector<Tile*> tilesInRow;
    matrix4 position;
    vector3 pos;
    int rowPlace;
    bool moving;
    bool isObstacleLane = false;
    int random;
    int numObstacles = 0;
};

