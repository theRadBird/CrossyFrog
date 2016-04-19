#pragma once
#include "Tile.h"
class StageRow
{
public:
    StageRow(int amount);
    ~StageRow();
    
    void setPosition(int rowPos);

private:
    std::vector<Tile*> tilesInRow;
    matrix4 position;
};

