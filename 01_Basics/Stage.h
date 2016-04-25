#pragma once
#include "StageRow.h"

class Stage
{
public:
    Stage();
    Stage(int rowCount);
    ~Stage();
    void MoveForward();
    void MoveBackward();
    void update(double dt);
    void draw();

protected:
	MeshManagerSingleton* m_pMeshMngr;

private:
    std::vector<StageRow*> rowsInStage;
    bool moveFor, moveBack;
    float slideTime;
    float moveCounter;
    int maxMoved; // Can return this to tell player how far they got
    vector3 stagePos;
    int random;
    bool wasObstacle = false;
    StageRow* temp;
};

