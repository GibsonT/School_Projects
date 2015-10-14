#include "graph.h"

void depthFirstSearch(Vertex* vertices[]) {
    Stack vertexStack;
    Vertex* topVertex;
    Edge* nextEdge;
    vertexStack.size = 0;

    printf("Depth-First Search:\t");

    // Mark all vertices as unvisited
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        if (vertices[i]->letter == '?') {
            vertices[0]->isVisited = true;
            printf("%c", vertices[0]->letter);
            stackPush(&vertexStack, vertices[0]);
            break;
        }

        vertices[i]->isVisited = false;
    }


    while (vertexStack.size != 0) {
        topVertex = stackPeek(&vertexStack);
        nextEdge = topVertex->edges;

        // Visit the next unvisited adjacent vertex
        while (nextEdge != NULL) {

            // Not visited? Mark it visited, push it into the stack, and set it as the top vertex
            if (!nextEdge->connectingVertex->isVisited) {
                nextEdge->connectingVertex->isVisited = true;
                printf("%c", nextEdge->connectingVertex->letter);
                stackPush(&vertexStack, nextEdge->connectingVertex);
                topVertex = nextEdge->connectingVertex;
                nextEdge = topVertex->edges;
            }
            else {
                nextEdge = nextEdge->nextEdge;
            }
        }

        // Vertex has no unvisited neighbors, pop the next one off of the stack
        stackPop(&vertexStack);
    }

    printf("\n");
}
