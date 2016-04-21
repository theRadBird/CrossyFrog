#include "Stage.h"

Stage::Stage() {
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	for (int i = 0; i < 3; i++) {
        rowsInStage.push_back(new StageRow(3));
        rowsInStage.back()->setPosition(i);
    }
}

Stage::Stage(int rowCount)
{
    for (int i = 0; i < rowCount; i++) {
        rowsInStage.push_back(new StageRow(rowCount));
        rowsInStage.back()->setPosition(i);
    }
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel("Crossy\\tile.obj", "tile");
}

Stage::~Stage()
{
    for (StageRow* row : rowsInStage) {
        row->~StageRow();
    }
}

void Stage::MoveForward() {

}

void Stage::MoveBackward() {

}

