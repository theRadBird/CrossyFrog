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
    vector3 stagePos;
    int random;
    bool wasObstacle = false;
    StageRow* temp;
};

