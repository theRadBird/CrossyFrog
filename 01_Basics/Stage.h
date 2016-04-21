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

protected:
	MeshManagerSingleton* m_pMeshMngr;

private:
    std::vector<StageRow*> rowsInStage;
};

