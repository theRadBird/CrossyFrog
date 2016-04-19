#pragma once
#include "StageRow.h"
class Stage
{
public:
    Stage();
    ~Stage();
    MoveForward();
    MoveBackward();

private:
    std::vector<StageRow> rowsInStage;
};

