#include "Stage.h"

Stage::Stage() {
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
    bObjMan = BoundingObjectManagerSingleton::GetInstance();
    playerLane = 0;

    float slideTime = 0.0f;
	for (int i = 0; i < 3; i++) {
        
        random = rand() % 2;
        if (random == 0 && wasObstacle == false) { // Generates obstacle lane
            wasObstacle = true;
            temp = new StageRow(i, 3, wasObstacle, 4, 0);
        }
        else { // Generates mover lane
            wasObstacle = false;
            random = rand() % 3;
            int moverID = bObjMan->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("mover")));

            temp = new StageRow(i, 3, wasObstacle, random, moverID);
            std::cout << "Random for mover type: " << random << std::endl;

        }

        rowsInStage.push_back(temp);
        rowsInStage.back()->setPosition(static_cast<float>(-i + 1));
    }
    moveCounter = 0.f;
    maxMoved = 0;
    stagePos = vector3(0.f);
}

Stage::Stage(int rowCount)
{
    m_pMeshMngr = MeshManagerSingleton::GetInstance();
    bObjMan = BoundingObjectManagerSingleton::GetInstance();
    playerLane = 0;
    for (int i = 0; i < rowCount; i++) {
        random = rand() % 2;
        if (random == 0 && wasObstacle == false) { // Generates obstacle lane
            wasObstacle = true;
            temp = new StageRow(i, rowCount, wasObstacle, 4, 0);
        }
        else { // Generates mover lane
            wasObstacle = false; 
            random = rand() % 3;
            int moverID = bObjMan->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("mover")));

            temp = new StageRow(i, rowCount, wasObstacle, random, moverID);
            std::cout << "Random for mover type: " << random << std::endl;

        }
        //std::cout << "Random: " << random << std::endl;
        //std::cout << "Was Obstacle: " << wasObstacle << std::endl;

        rowsInStage.push_back(temp);
        rowsInStage.back()->setPosition(static_cast<float>(-i+1));
    }
		
}

Stage::~Stage()
{
    for (StageRow* row : rowsInStage) {
        row->~StageRow();
    }
}

bool Stage::CanMoveF() {
    bool temp = true;
    StageRow* row = rowsInStage[2];
    if (row->checkTile(playerLane)) {
        temp = false;
    }
    return temp;
}

bool Stage::CanMoveL() {
    bool temp = true;
    StageRow* row = rowsInStage[1];
    if (row->checkTile(playerLane-1)) {
        temp = false;
    }
    return temp;
}

bool Stage::CanMoveR() {
    bool temp = true;
    StageRow* row = rowsInStage[1];
    if (row->checkTile(playerLane+1)) {
        temp = false;
    }
    return temp;
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
    m_pMeshMngr->Print("Lanes Traversed:");
    m_pMeshMngr->Print(std::to_string(maxMoved), RERED);
    vector3 lerpPos;
    if (moveBack || moveFor) {

        slideTime += static_cast<float>(dt);
        if (slideTime >= 1.0f) {
            if (moveFor) {
                moveCounter++;

                if (moveCounter > maxMoved) { // Maintains highest lane progress for player
                    maxMoved++;
                }
                
                delete rowsInStage[0];
                rowsInStage.erase(rowsInStage.begin());

                stagePosTracker--;
                if (rowsInStage[5]->getLaneType() == true) {
                    wasObstacle = true;
                }
                else { wasObstacle = false; }

                random = rand() % 2;
                if (random == 0 && wasObstacle == false) { // Generates obstacle lane
                    wasObstacle = true;
                    temp = new StageRow(7 + maxMoved, 7.f, wasObstacle, 4, 0);
                }
                else { // Generates mover lane
                    wasObstacle = false;
                    random = rand() % 3;
                    int moverID = bObjMan->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("mover")));
                    temp = new StageRow(7 + maxMoved, 7.f, wasObstacle, random, moverID);
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