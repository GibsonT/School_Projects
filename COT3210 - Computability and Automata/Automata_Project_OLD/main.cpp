#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include "Cell.h"

#define ROWS 50
#define COLS 150

int main() {
    Cell* cells[ROWS][COLS];
    int immuneCounter = 0;
    int totalImmunes = ceil((double)(ROWS * COLS) * 0.01);
    int iterations = 0;
    srand(time(NULL));
    bool healthyExists = true;
    bool foundInfected = false;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cells[i][j] = new Cell();
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
            cells[i][j]->isInfected = true;
            foundInfected = true;
        }
    }

    while (healthyExists) {
        for (int i = 0; i < 100; i++) {
            std::cout << std::endl;
        }

        healthyExists = false;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (cells[i][j]->isImmune) {
                    std::cout << "O";
                }
                else if (cells[i][j]->isInfected) {
                    std::cout << "*";
                }
                else {
                    std::cout << "-";
                    healthyExists = true;
                }
            }

            switch (i) {
                case 0:
                    std::cout << "\tIteration: " << ++iterations;
                    break;
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

                if (!cells[i][j]->isInfected) {
                    continue;
                }

                // Check right side of infected cell
                if (rightOne < COLS) {
                    if (!cells[i][rightOne]->isInfected && !cells[i][rightOne]->isImmune) {
                        cells[i][rightOne]->toBeInfected = true;
                    }

                    if (upOne >= 0) {
                        if (!cells[upOne][rightOne]->isInfected && !cells[upOne][rightOne]->isImmune) {
                            cells[upOne][rightOne]->toBeInfected = true;
                        }
                    }

                    if (downOne < ROWS) {
                        if (!cells[downOne][rightOne]->isInfected && !cells[downOne][rightOne]->isImmune) {
                            cells[downOne][rightOne]->toBeInfected = true;
                        }
                    }
                }

                // Check left side of infected cell
                if (leftOne >= 0) {
                    if (!cells[i][leftOne]->isInfected && !cells[i][leftOne]->isImmune) {
                        cells[i][leftOne]->toBeInfected = true;
                    }

                    if (upOne >= 0) {
                        if (!cells[upOne][leftOne]->isInfected && !cells[upOne][leftOne]->isImmune) {
                            cells[upOne][leftOne]->toBeInfected = true;
                        }
                    }

                    if (downOne < ROWS) {
                        if (!cells[downOne][leftOne]->isInfected && !cells[downOne][leftOne]->isImmune) {
                            cells[downOne][leftOne]->toBeInfected = true;
                        }
                    }
                }

                // Straight up of infected cell
                if (upOne >= 0) {
                    if (!cells[upOne][j]->isInfected && !cells[upOne][j]->isImmune) {
                        cells[upOne][j]->toBeInfected = true;
                    }
                }

                // Straight down of infected cell
                if (downOne < ROWS) {
                    if (!cells[downOne][j]->isInfected && !cells[downOne][j]->isImmune) {
                        cells[downOne][j]->toBeInfected = true;
                    }
                }
            }
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (cells[i][j]->toBeInfected) {
                    cells[i][j]->toBeInfected = false;
                    cells[i][j]->isInfected = true;
                }
            }
        }

        // Sleep so the simulation doesn't go at superhuman speeds
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }


}