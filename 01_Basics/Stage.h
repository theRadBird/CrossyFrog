#pragma once
#include "StageRow.h"
#include "BoundingObjectManagerSingleton.h"

class Stage
{
public:
    Stage();
    Stage(int rowCount);
    ~Stage();
    bool CanMoveF();
    bool CanMoveL();
    bool CanMoveR();
    void MoveForward();
    void MoveBackward();
    void update(double dt);
    void draw();
    int playerLane; // Will track the players lane in the stage

protected:
	MeshManagerSingleton* m_pMeshMngr;
    BoundingObjectManagerSingleton* bObjMan;

private:
    std::vector<StageRow*> rowsInStage;
    bool moveFor, moveBack;
    float percent;
    float slideTime;
    float moveCounter;
    int maxMoved; // Can return this to tell player how far they got
    int stagePosTracker = -5;
    vector3 stagePos;
    int random;
    bool wasObstacle = false;
    StageRow* temp;
};

