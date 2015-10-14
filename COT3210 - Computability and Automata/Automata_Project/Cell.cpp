#include "Cell.h"

Cell::Cell(int row, int col) {
    this->isImmune = false;
    this->isInfected = false;
    this->isZombie = false;
    this->toBeInfected = false;
    this->isGroundZero = false;
    this->isVaccinated = false;
    this->row = row;
    this->col = col;
}
