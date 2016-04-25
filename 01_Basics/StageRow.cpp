#include "StageRow.h"

StageRow::StageRow(int amount, bool obstacleLane)
{
    isObstacleLane = obstacleLane;
    int offSet = (amount - 1) / 2;
    for (int i = 0; i < amount; i++) {
        Tile* temp = new Tile();

        if (isObstacleLane) {
            random = rand() % 2;
            if (random == 0 && numObstacles < 5) {
                temp->setObstacleTile();
                numObstacles++;
            }
        }

        tilesInRow.push_back(temp);
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
    rowPlace = setPos;
    pos = vector3(0.0f, 0.0f, setPos);
    position = glm::translate(pos);
    updateTiles(); 
}

void StageRow::updatePosition(vector3 moveDir) {
    position = glm::translate(moveDir);
    position *= glm::translate(pos);
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