#include "graph.h"


int main(int argc, char* argv[]) {
    FILE* inputFile;
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Unable to open file!");
        return(1);
    }

    Vertex* vertices[MAX_VERTICES];
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        vertices[i] = (Vertex*)malloc(sizeof(Vertex));
        vertices[i]->letter = '?';
    }

    createAdjList(vertices, inputFile);
    depthFirstSearch(vertices);
    breadthFirstSearch(vertices);
    topoSort(vertices);

    return(0);
}