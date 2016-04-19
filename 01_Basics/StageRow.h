#pragma once
#include "Tile.h"
class StageRow
{
public:
    StageRow(int amount);
    ~StageRow();
private:
    std::vector<Tile> tilesInRow;
    float position;
};

