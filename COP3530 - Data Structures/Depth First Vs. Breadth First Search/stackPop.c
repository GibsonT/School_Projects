#include "graph.h"

Vertex* stackPop(Stack *stack) {
    if (stack->size > 0) {
        stack->size--;
        return stack->vertexStack[stack->size];
    }
}