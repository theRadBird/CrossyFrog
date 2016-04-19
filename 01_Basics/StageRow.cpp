#include "StageRow.h"



StageRow::StageRow(int amount)
{
    for (int i = 0; i < amount; i++) {
        tilesInRow.push_back(new Tile());
        tilesInRow.back()->setPosition(i);
    }
}

StageRow::~StageRow()
{
}

void StageRow::setPosition(int setPos) {
    position = glm::translate(0.0f,0.0f,static_cast<float>(setPos));
    for(Tile* tile : tilesInRow) {
        tile->updatePosition(position);
    }
}