#pragma once
#include "Tile.h"
class StageRow
{
public:
    StageRow(int amount);
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
    bool moving;
};

