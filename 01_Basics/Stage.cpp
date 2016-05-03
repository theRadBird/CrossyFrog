#include "Stage.h"

Stage::Stage() {
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
    float slideTime = 0.0f;
	for (int i = 0; i < 3; i++) {
        rowsInStage.push_back(new StageRow(i, 3, false, 4));
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
        if (random == 0 && wasObstacle == false) { // Generates obstacle lane
            wasObstacle = true;
            temp = new StageRow(i, rowCount, wasObstacle, 4);
        }
        else { // Generates mover lane
            wasObstacle = false; 
            random = rand() % 3;

            temp = new StageRow(i, rowCount, wasObstacle, random);
            std::cout << "Random for mover type: " << random << std::endl;

        }
        //std::cout << "Random: " << random << std::endl;
        //std::cout << "Was Obstacle: " << wasObstacle << std::endl;

        rowsInStage.push_back(temp);
        rowsInStage.back()->setPosition(static_cast<float>(-i+1));
    }
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	
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

                rowsInStage.erase(rowsInStage.begin());
                stagePosTracker--;
                if (rowsInStage[5]->getLaneType() == true) {
                    wasObstacle = true;
                }
                else { wasObstacle = false; }

                random = rand() % 2;
                if (random == 0 && wasObstacle == false) { // Generates obstacle lane
                    wasObstacle = true;
                    temp = new StageRow(7 + maxMoved, 7.f, wasObstacle, 4);
                }
                else { // Generates mover lane
                    wasObstacle = false;
                    random = rand() % 3;
                    temp = new StageRow(7 + maxMoved, 7.f, wasObstacle, random);
                }
                rowsInStage.push_back(temp);
                rowsInStage.back()->setPosition(stagePosTracker);
            }
            else moveCounter--;
            lerpPos = moveFor ? vector3(.0f, .0f, moveCounter) : vector3(.0f, .0f, moveCounter);
            moveBack = false;
            moveFor = false;
            slideTime = 0.0f;
            stagePos = lerpPos;
        }
        else {
            percent = MapValue(slideTime, 0.f, 1.0f, 0.f, 1.f);

            if (moveFor) {
                lerpPos = glm::lerp(stagePos, vector3(.0f, .0f, moveCounter + 1.f), percent);
            }
            else {
                lerpPos = glm::lerp(stagePos, vector3(0.0f,0.0f, moveCounter - 1.f), percent);
            }
        }
        //std::cout << lerpPos.z << std::endl;
        for each(StageRow* sRow in rowsInStage) {
            sRow->updatePosition(lerpPos, percent);
        }
    }
    for each(StageRow* sRow in rowsInStage) {
        sRow->update(dt);
    }
}

void Stage::draw()
{
    for each(StageRow* sRow in rowsInStage) {
        sRow->draw();
    }
}