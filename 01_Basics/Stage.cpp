#include "Stage.h"

Stage::Stage(int rowCount)
{
    for (int i = 0; i < rowCount; i++) {
        rowsInStage.push_back(StageRow(rowCount));
        rowsInStage.back().setPosition(i);
    }
}

Stage::~Stage()
{
}

void Stage::MoveForward() {}
void Stage::MoveBackward() {}

