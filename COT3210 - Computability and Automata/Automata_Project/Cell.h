#ifndef CELL_H
#define CELL_H


class Cell {
    public:
        bool isImmune;
        bool isInfected;
        bool toBeInfected;
        bool isGroundZero;
        bool isZombie;
        bool isVaccinated;
        int row;
        int col;

    public:
        Cell(int row, int col);
};


#endif
