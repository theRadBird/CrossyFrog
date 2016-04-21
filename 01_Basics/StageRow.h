#pragma once
#include "Tile.h"
class StageRow
{
public:
    StageRow(int amount);
    ~StageRow();
    
    void setPosition(int rowPos);
    void updatePosition(vector3 upPosition);
    void update(double dt);
    void draw();

private:
    std::vector<Tile*> tilesInRow;
	vector3 position;
    matrix4 matrix2World;
};

