#include "StageRow.h"

StageRow::StageRow(int id, int amount, bool obstacleLane, int type, int moverID = 0)
{
    isObstacleLane = obstacleLane;
    int offSet = (amount - 1) / 2;
    for (int i = 0; i < amount; i++) {
        Tile* temp = new Tile((id*10)+i);

        if (isObstacleLane) {
            random = rand() % 2;
            if (random == 0 && numObstacles < 5) {
                temp->setObstacleTile();
                numObstacles++;
            }
        }

        if (type < 4 && !isObstacleLane && numMovers < 1) {
            Mover* tempMover = new Mover(moverID);
            random = rand() % 3 + 7.f;
            tempMover->setSpeed(random);
            moversInRow.push_back(tempMover);
            numMovers++;
        }

        tilesInRow.push_back(temp);
        tilesInRow.back()->setPosition(i-offSet);
    }
    bool moving = false;
}

StageRow::~StageRow()
{
    for (Tile* tile : tilesInRow) {
        tile->~Tile();
    }
    if (!isObstacleLane) {
        moversInRow[0]->~Mover();
    }  
}

void StageRow::setPosition(float setPos) {
    std::cout << "Z Position in start of Set Position (StageRow): " << setPos << std::endl;
    rowPlace = setPos;
    pos = vector3(0.0f, 0.0f, setPos);
    position = glm::translate(pos);
    updateTiles(); 
    for (Mover* temp : moversInRow) {
        random = rand() % 2;
        if (rowPlace <= -6.f) { rowPlace = -6.f; } // The bug is here
        if (random == 0) {
            temp->setPosition(vector3(3.f, 0.5f, rowPlace));
        }
        else { temp->setPosition(vector3(-3.f, 0.5f, rowPlace)); temp->setReverse(); }
    }
}

void StageRow::updatePosition(vector3 moveDir, float percent_) {
    _moveDirection = moveDir;
    percent = percent_;
    position = glm::translate(moveDir);
    position *= glm::translate(pos);
    updateTiles();
    updateMovers();
}

void StageRow::updateTiles() {
    for (Tile* tile : tilesInRow) {
        tile->updatePosition(position);
    }
}

void StageRow::updateMovers() {
    for each(Mover* temp in moversInRow) {
        temp->updatePosition(_moveDirection, true, percent);
    }
}

void StageRow::update(double dt) {
    for each(Mover* temp in moversInRow) {
        temp->update(dt);
    }
}

void StageRow::draw() {
    for each(Tile* t in tilesInRow) {
        t->draw();
    }
}

bool StageRow::getLaneType() {
    return isObstacleLane;
}

bool StageRow::checkTile(int pos) {
    bool temp = false;
    Tile* check = tilesInRow[pos+4];
    std::cout << pos + 4 << std::endl;
    if (check->isObst()) {
        temp = true;
    }
    return temp;
}

float StageRow::getZ() {
    float z = pos.z;
    return z;
}

void StageRow::deleteTiles() {
    tilesInRow.erase(tilesInRow.begin(), tilesInRow.begin() + 6);
}