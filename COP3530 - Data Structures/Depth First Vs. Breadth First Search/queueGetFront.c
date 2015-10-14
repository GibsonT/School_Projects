#include "graph.h"

Vertex* queueGetFront(Queue* queue) {
    if (queue->size > 0) {
        Vertex* frontVertex = queue->vertexQueue[0];
        queue->size--;

        int i;
        for (i = 0; i < queue->size; i++) {
            queue->vertexQueue[i] = queue->vertexQueue[i + 1];
        }
    }
}
