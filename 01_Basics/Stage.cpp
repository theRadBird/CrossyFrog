#include "Stage.h"

Stage::Stage() {
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
    float slideTime = 0.0f;
	for (int i = 0; i < 3; i++) {
        rowsInStage.push_back(new StageRow(3));
        rowsInStage.back()->setPosition(i);
    }
}

Stage::Stage(int rowCount)
{
    for (int i = 0; i < rowCount; i++) {
        rowsInStage.push_back(new StageRow(rowCount));
        rowsInStage.back()->setPosition(static_cast<float>(-i+1));
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
    if (!moveBack) {
        moveFor = true;
    }
}

void Stage::MoveBackward() {
    if (!moveFor) {
        moveBack = true;
    }
}

void Stage::update(double dt) {
    vector3 stagePos = vector3(0.0f);
    vector3 lerpPos;
    if (moveBack || moveFor) {

        slideTime += static_cast<float>(dt);
        if (slideTime >= 1.0f) {
            lerpPos = moveFor ? vector3(.0f, .0f, 1.0f) : vector3(.0f, .0f, -1.0f);
            moveBack = false;
            moveFor = false;
            slideTime = 0.0f;
        }
        else {
            float percent = MapValue(slideTime, 0.f, 1.0f, 0.f, 1.f);

            if (moveFor) {
                lerpPos = glm::lerp(stagePos, vector3(.0f, .0f, 1.0f), percent);
            }
            else {
                lerpPos = glm::lerp(stagePos, vector3(0.0f,0.0f,-1.0f), percent);
            }
        }
       std::cout << lerpPos.z << std::endl;
        for each(StageRow* sRow in rowsInStage) {
            sRow->updatePosition(lerpPos);
        }
    }
}

void Stage::draw()
{
    for each(StageRow* sRow in rowsInStage) {
        sRow->draw();
    }
}