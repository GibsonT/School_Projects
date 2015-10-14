#include "graph.h"

void breadthFirstSearch(Vertex* vertices[]) {
    Queue vertexQueue;
    Vertex* topVertex;
    Edge* nextEdge;
    vertexQueue.size = 0;

    printf("Breadth-First Search:\t");

    // Mark all vertices as unvisited
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        if (vertices[i]->letter == '?') {
            printf("%c", vertices[0]->letter);
            queueInsert(&vertexQueue, vertices[0]);
            break;
        }

        vertices[i]->isVisited = false;
    }

    while (vertexQueue.size != 0) {
        topVertex = queuePeekFront(&vertexQueue);
        nextEdge = topVertex->edges;

        // Were checking all adjacent vertices of the topVertex
        while (nextEdge != NULL) {

            // Is it unvisited? Mark it, push it in the queue, and move the edge marker
            if (!nextEdge->connectingVertex->isVisited) {
                nextEdge->connectingVertex->isVisited = true;
                queueInsert(&vertexQueue, nextEdge->connectingVertex);
                printf("%c", nextEdge->connectingVertex->letter);
            }

            nextEdge = nextEdge->nextEdge;
        }

        // All adjacent vertices have been checked, pull next vertex out of queue
        queueGetFront(&vertexQueue);
    }

    printf("\n");
}
