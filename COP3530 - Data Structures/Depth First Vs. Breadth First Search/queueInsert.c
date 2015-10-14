#include "graph.h"

void queueInsert(Queue* vertexQueue, Vertex* vertex) {
    if (vertexQueue->size < MAX_VERTICES) {
        vertexQueue->vertexQueue[vertexQueue->size] = vertex;
        vertexQueue->size++;
    }
}
