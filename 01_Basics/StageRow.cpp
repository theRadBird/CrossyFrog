#include "StageRow.h"



StageRow::StageRow(int amount)
{
    for (int i = 0; i < amount; i++) {
        tilesInRow.push_back(Tile());
        tilesInRow.back().setPosition(i);
    }
}


StageRow::~StageRow()
{
}

void StageRow::setPosition(int setPos) {
    position = glm::translate(IDENTITY_M4 ,vector3(static_cast<float>(setPos), 0.0f, 0.0f));
}