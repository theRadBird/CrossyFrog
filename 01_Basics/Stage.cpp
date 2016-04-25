#include "Stage.h"

Stage::Stage() {
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
    float slideTime = 0.0f;
	for (int i = 0; i < 3; i++) {
        rowsInStage.push_back(new StageRow(3, false));
        rowsInStage.back()->setPosition(i);
    }
    moveCounter = 0.f;
    maxMoved = 0;
    stagePos = vector3(0.f);
}

Stage::Stage(int rowCount)
{
    for (int i = 0; i < rowCount; i++) {
        random = rand() % 2;
        if (random == 0 && wasObstacle == false) {
            wasObstacle = true;
            temp = new StageRow(rowCount, wasObstacle);
        }
        else { 
            wasObstacle = false; 
            temp = new StageRow(rowCount, wasObstacle);
        }
        
        std::cout << "Random: " << random << std::endl;
        std::cout << "Was Obstacle: " << wasObstacle << std::endl;

        rowsInStage.push_back(temp);
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
    vector3 lerpPos;
    if (moveBack || moveFor) {

        slideTime += static_cast<float>(dt);
        if (slideTime >= 1.0f) {
            if (moveFor) {
                moveCounter++;
                if (moveCounter > maxMoved) { // Maintains highest lane progress for player
                    maxMoved++;
                }
            }
            else moveCounter--;
            lerpPos = moveFor ? vector3(.0f, .0f, moveCounter) : vector3(.0f, .0f, moveCounter);
            moveBack = false;
            moveFor = false;
            slideTime = 0.0f;
            stagePos = lerpPos;
        }
        else {
            float percent = MapValue(slideTime, 0.f, 1.0f, 0.f, 1.f);

            if (moveFor) {
                lerpPos = glm::lerp(stagePos, vector3(.0f, .0f, moveCounter + 1.f), percent);
            }
            else {
                lerpPos = glm::lerp(stagePos, vector3(0.0f,0.0f, moveCounter - 1.f), percent);
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