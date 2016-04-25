#include "Tile.h"

Tile::Tile()
{
    position = IDENTITY_M4;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

Tile::~Tile()
{
}


void Tile::setPosition(int setPos) {
    pos = vector3(static_cast<float>(setPos), 0.0f, 0.0f);
    position = glm::translate(pos);
}

void Tile::updatePosition(matrix4 rowMat) {
    position = glm::translate(rowMat,pos);
}

void Tile::update(double dt) {

}

void Tile::draw() {
	m_pMeshMngr->SetModelMatrix(position, "tile");
	m_pMeshMngr->AddInstanceToRenderList("tile");
}