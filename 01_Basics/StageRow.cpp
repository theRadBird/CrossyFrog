#include "StageRow.h"

StageRow::StageRow(int amount, bool obstacleLane, int type)
{
    isObstacleLane = obstacleLane;
    int offSet = (amount - 1) / 2;
    for (int i = 0; i < amount; i++) {
        Tile* temp = new Tile();

        if (isObstacleLane) {
            random = rand() % 2;
            if (random == 0 && numObstacles < 5) {
                temp->setObstacleTile();
                numObstacles++;
            }
        }

        if (type < 4 && !isObstacleLane && numMovers < 1) {
            Mover* tempMover = new Mover();
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
}

void StageRow::setPosition(float setPos) {
    rowPlace = setPos;
    pos = vector3(0.0f, 0.0f, setPos);
    position = glm::translate(pos);
    updateTiles(); 
    for (Mover* temp : moversInRow) {
        random = rand() % 2;
        if (random == 0) {
            temp->setPosition(vector3(3.f, 0.5f, rowPlace));
        }
        else { temp->setPosition(vector3(-3.f, 0.5f, rowPlace)); temp->setReverse(); }
        std::cout << "Mover position set: " << rowPlace << std::endl;
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
    for (Mover* temp : moversInRow) {
        temp->updatePosition(_moveDirection, true, percent);
    }
}

void StageRow::update(double dt) {
    for (Mover* temp : moversInRow) {
        temp->update(dt);
    }
}

void StageRow::draw() {
    for each(Tile* t in tilesInRow) {
        t->draw();
    }
}