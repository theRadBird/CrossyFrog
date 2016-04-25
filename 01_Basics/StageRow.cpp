#include "StageRow.h"

StageRow::StageRow(int amount)
{
    int offSet = (amount - 1) / 2;
    for (int i = 0; i < amount; i++) {
        tilesInRow.push_back(new Tile());
        tilesInRow.back()->setPosition(i-offSet);
    }
    bool moving = false;
}

StageRow::~StageRow()
{
    for (Tile* tile : tilesInRow) {
        tile->~Tile();
    }
}

void StageRow::setPosition(float setPos) {
    position = glm::translate(0.0f,0.0f,setPos);
    updateTiles(); 
}

void StageRow::updatePosition(vector3 moveDir) {
    
    position = glm::translate(moveDir);
    
    updateTiles();
}

void StageRow::updateTiles() {
    for (Tile* tile : tilesInRow) {
        tile->updatePosition(position);
    }
}

void StageRow::update(double dt) {
    
}

void StageRow::draw() {
    for each(Tile* t in tilesInRow) {
        t->draw();
    }
}