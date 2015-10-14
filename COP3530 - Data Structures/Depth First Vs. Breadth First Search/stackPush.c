#include "graph.h"

void stackPush(Stack *stack, Vertex *element) {
    if (stack->size < MAX_VERTICES) {
        stack->vertexStack[stack->size] = element;
        stack->size++;
    }
}

