#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include "Cell.h"

int main(int argc, char* argv[]) {
    const int ROWS = atoi(argv[1]);
    const int COLS = atoi(argv[2]);
    double immunePercentage = atof(argv[3]);
    bool useVaccines;
    if (argc > 4 && argv[4][0] == 't') {
        useVaccines = true;
    }
    else {
        useVaccines = false;
    }

    if (argc > 5) {
        srand(atoi(argv[5]));
    }
    else {
        srand(time(NULL));
    }

    Cell* cells[ROWS][COLS];
    Cell* groundZeroCell;
    int immuneCounter = 0;
    int iterations = 0;
    bool infectionIsSpreading = true;
    bool foundInfected = false;
    int totalInfected = 0;
    int totalAlive = 0;
    int totalImmunes = std::ceil((double) (ROWS * COLS) * immunePercentage);
    int totalVaccinated = 0;
    int biggestQuad = 0;
    int vaccineIterations = 1;
    int vaccineIterationProcCounter = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cells[i][j] = new Cell(i, j);
            totalAlive++;
        }
    }

    while (immuneCounter < totalImmunes) {
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if (rand() % 100 == 0 && !cells[i][j]->isImmune) {
            cells[i][j]->isImmune = true;
            immuneCounter++;
        }
    }

    while (!foundInfected) {
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if (rand() % 100 == 0 && !cells[i][j]->isImmune) {
            groundZeroCell = cells[i][j];
            groundZeroCell->isInfected = true;
            groundZeroCell->isGroundZero = true;
            foundInfected = true;
            totalInfected++;
            totalAlive--;
        }
    }

    while (infectionIsSpreading) {
        for (int i = 0; i < 50; i++) {
            std::cout << std::endl;
        }

        infectionIsSpreading = false;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (cells[i][j]->isImmune) {
                    if (cells[i][j]->isVaccinated) {
                        std::cout << "V";
                    }
                    else {
                        std::cout << "!";
                    }
                }
                else if (cells[i][j]->isGroundZero) {
                    std::cout << "@";
                    if (iterations <= 1) {
                        infectionIsSpreading = true;
                    }
                }
                else if (cells[i][j]->isInfected) {
                    std::cout << "#";
                    infectionIsSpreading = true;
                    totalInfected++;
                    totalAlive--;
                }
                else if (cells[i][j]->isZombie) {
                    std::cout << ".";
                }
                else {
                    std::cout << "A";
                }
            }

            switch (i) {
                case 0:
                    std::cout << "\tIteration: " << ++iterations;
                    break;
                case 1:
                    std::cout << "\tTotal Alive: " << totalAlive;
                    break;
                case 2:
                    std::cout << "\tTotal Immune: " << totalImmunes;
                    break;
                case 3:
                    std::cout << "\tTotal Infected/Turned: " << totalInfected;
                    break;
                case 4:
                    std::cout << "\tPercent Alive: " << ((totalAlive / (double) (COLS * ROWS)) * 100);
                    break;
                case 5:
                    std::cout << "\tPercent Immune: " << ((totalImmunes / (double) (COLS * ROWS)) * 100);
                    break;
                case 6:
                    std::cout << "\tPercent Infected/Turned: " << ((totalInfected / (double) (COLS * ROWS)) * 100);
                    break;
                case 7:
                    std::cout << "\tUsing Vaccinations: " << useVaccines;
                    break;
                case 8:
                    if (useVaccines) {
                        std::cout << "\tTotal Vaccinated: " << totalVaccinated;
                        break;
                    }
                case 9:
                    if (useVaccines) {
                        std::cout << "\tPercent Vaccinated: " << ((totalVaccinated / (double) (COLS * ROWS)) * 100);
                    }
                default:
                    break;
            }

            std::cout << "\n";
        }



        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                int upOne = i - 1;
                int downOne = i + 1;
                int leftOne = j - 1;
                int rightOne = j + 1;
                Cell *topLeft = cells[upOne][leftOne];
                Cell *middleLeft = cells[i][leftOne];
                Cell *bottomLeft = cells[downOne][leftOne];
                Cell *topRight = cells[upOne][rightOne];
                Cell *middleRight = cells[i][rightOne];
                Cell *bottomRight = cells[downOne][rightOne];
                Cell *straightUp = cells[upOne][j];
                Cell *straightDown = cells[downOne][j];
                Cell *thisCell = cells[i][j];

                if (!cells[i][j]->isInfected) {
                    continue;
                }

                // Check right side of infected cell
                if (rightOne < COLS) {
                    if (!middleRight->isInfected && !middleRight->isImmune && !middleRight->isZombie) {
                        middleRight->toBeInfected = true;
                    }

                    if (upOne >= 0) {
                        if (!topRight->isInfected && !topRight->isImmune && !topRight->isZombie) {
                            topRight->toBeInfected = true;
                        }
                    }

                    if (downOne < ROWS) {
                        if (!bottomRight->isInfected && !bottomRight->isImmune && !bottomRight->isZombie) {
                            bottomRight->toBeInfected = true;
                        }
                    }
                }

                // Check left side of infected cell
                if (leftOne >= 0) {
                    if (!middleLeft->isInfected && !middleLeft->isImmune && !middleLeft->isZombie) {
                        middleLeft->toBeInfected = true;
                    }

                    if (upOne >= 0) {
                        if (!topLeft->isInfected && !topLeft->isImmune && !topLeft->isZombie) {
                            topLeft->toBeInfected = true;
                        }
                    }

                    if (downOne < ROWS) {
                        if (!bottomLeft->isInfected && !bottomLeft->isImmune && !bottomLeft->isZombie) {
                            bottomLeft->toBeInfected = true;
                        }
                    }
                }

                // Straight up of infected cell
                if (upOne >= 0) {
                    if (!straightUp->isInfected && !straightUp->isImmune && !straightUp->isZombie) {
                        straightUp->toBeInfected = true;
                    }
                }

                // Straight down of infected cell
                if (downOne < ROWS) {
                    if (!straightDown->isInfected && !straightDown->isImmune && !straightDown->isZombie) {
                        straightDown->toBeInfected = true;
                    }
                }

                // Cell's job is done. Turn it into a zombie.
                thisCell->isZombie = true;
                thisCell->isInfected = false;
            }
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                Cell *thisCell = cells[i][j];
                if (thisCell->toBeInfected) {
                    thisCell->toBeInfected = false;
                    thisCell->isInfected = true;
                }
            }
        }

        if (useVaccines && iterations >= 20) {
            int findCounter = 0;    // Will get stuck near end. Use this to time finding cell to vaccinate.
            if (biggestQuad == 0) {
                int quad1l = COLS - (groundZeroCell->col + 1);
                int quad1h = groundZeroCell->row;
                int quad2l = groundZeroCell->col;
                int quad2h = groundZeroCell->row;
                int quad3l = groundZeroCell->col;
                int quad3h = ROWS - (groundZeroCell->row + 1);
                int quad4l = COLS - (groundZeroCell->col + 1);
                int quad4h = ROWS - (groundZeroCell->row + 1);
                int quad1Area = quad1h * quad1l;
                int quad2Area = quad2h * quad2l;
                int quad3Area = quad3h * quad3l;
                int quad4Area = quad4h * quad4l;

                int maxOf1And2 = std::max(quad1Area, quad2Area);
                int maxOf3And4 = std::max(quad3Area, quad4Area);
                int biggestArea = std::max(maxOf1And2, maxOf3And4);

                if (biggestArea == quad1Area) {
                    biggestQuad = 1;
                }
                else if (biggestArea == quad2Area) {
                    biggestQuad = 2;
                }
                else if (biggestArea == quad3Area) {
                    biggestQuad = 3;
                }
                else {
                    biggestQuad = 4;
                }
            }

            while (true) {
                int row;
                int col;
                int groundZeroRow = groundZeroCell->row;
                int groundZeroCol = groundZeroCell->col;

                vaccineIterationProcCounter++;
                findCounter++;
                if (vaccineIterationProcCounter == 5) {
                    vaccineIterations++;
                    vaccineIterationProcCounter = 0;
                }
                if (biggestQuad == 1 || biggestQuad == 2) {
                    row = (rand() % vaccineIterations) % ROWS;
                }
                else {
                    row = std::abs(ROWS - (rand() % vaccineIterations) - 1) % ROWS;
                }

                if (biggestQuad == 2 || biggestQuad == 3) {
                    col = (rand() % vaccineIterations) % COLS;
                }
                else {
                    col = std::abs(COLS - (rand() % vaccineIterations) - 1) % COLS;
                }

                Cell* thisCell = cells[row][col];
                if (!thisCell->isInfected && !thisCell->isImmune && !thisCell->isZombie) {
                    thisCell->isVaccinated = true;
                    thisCell->isImmune = true;
                    totalImmunes++;
                    totalVaccinated++;
                    findCounter = 0;
                    break;
                }
                if (findCounter > 100000) {
                    break;
                }
            }
        }

        // Sleep so the simulation doesn't go at superhuman speeds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
