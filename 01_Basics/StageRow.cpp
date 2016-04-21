#include "StageRow.h"



StageRow::StageRow(int amount)
{
    int offSet = (amount - 1) / 2;
    for (int i = 0; i < amount; i++) {
        tilesInRow.push_back(new Tile());
        tilesInRow.back()->setPosition(i-offSet);
    }
}

StageRow::~StageRow()
{
    for (Tile* tile : tilesInRow) {
        tile->~Tile();
    }
}

void StageRow::setPosition(int setPos) {
	matrix2World = glm::translate(0.0f,0.0f,static_cast<float>(setPos));
    for(Tile* tile : tilesInRow) {
        tile->updatePosition(position);
    }
}

void StageRow::updatePosition(vector3 upPosition) {
	position *= upPosition;
	matrix2World = position;
	if()
}

void StageRow::update(double dt) {

}

void StageRow::draw() {

}