#pragma once
#include "Tile.h"
class StageRow
{
public:
    StageRow(int amount);
    ~StageRow();
    
    void setPosition(int rowPos);
    void updatePosition(matrix4 stagePos);
    void update(double dt);
    void draw();

private:
    std::vector<Tile*> tilesInRow;
    matrix4 position;
};

