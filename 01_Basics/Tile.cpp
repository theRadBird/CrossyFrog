#include "Tile.h"



Tile::Tile()
{
    position = IDENTITY_M4;
}


Tile::~Tile()
{
}


void Tile::setPosition(int setPos) {
    position = glm::translate(static_cast<float>(setPos), 0.0f, 0.0f);
}

void Tile::updatePosition(matrix4 rowMat) {
    position *= rowMat;
}

void Tile::update(double dt) {

}

void Tile::draw() {
    
}