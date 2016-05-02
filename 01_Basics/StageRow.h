#pragma once
#include "Tile.h"
#include "Mover.h"

class StageRow
{
public:
    StageRow(int amount, bool isObstacle, int type);
    ~StageRow();
    
    void setPosition(float rowPos);
    void updatePosition(vector3 moveDir, float percent);
    void update(double dt);
    void updateTiles();
    void updateMovers();
    void draw();

private:
    std::vector<Mover*> moversInRow;
    std::vector<Tile*> tilesInRow;
    matrix4 position;
    vector3 pos;
    vector3 _moveDirection;
    int rowPlace;
    bool moving;
    bool isObstacleLane = false;
    int whichType; // tracks which kind of moving lane it is. 0 for <>, 1 for ->, or 2 for <-. Pass in 4 for no movers
    int random;
    int numObstacles = 0;
    int numMovers = 0;
    float percent;
};

