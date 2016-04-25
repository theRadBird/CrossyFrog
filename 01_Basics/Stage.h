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
};

