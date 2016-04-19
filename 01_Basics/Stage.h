#pragma once
#include "StageRow.h"
class Stage
{
public:
    Stage(int rowCount);
    ~Stage();
    void MoveForward();
    void MoveBackward();

private:
    std::vector<StageRow> rowsInStage;
};

