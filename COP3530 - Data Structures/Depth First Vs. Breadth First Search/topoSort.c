#include "graph.h"

void topoSort(Vertex* vertices[]) {
    char sortedVertices[MAX_VERTICES];
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        sortedVertices[i] = '?';
    }

    printf("Topological Sort:\t");

    // While there are still edges in the start vertex
    while (vertices[0]->edges != NULL) {

        // Search the vertex array for the next vertex with no edges
        for (i = 0; i < MAX_VERTICES; i++) {
            if (vertices[i]->letter == '?') {
                break;
            }

            // Found one!
            if (vertices[i]->edges == NULL) {

                // Make sure it hasn't already been counted.
                // If it has, then continue.
                bool alreadyCounted = false;
                int j;
                for (j = 0; j < MAX_VERTICES; j++) {
                    if (sortedVertices[j] == '?') {
                        break;
                    }

                    if (sortedVertices[j] == vertices[i]->letter) {
                        alreadyCounted = true;
                        break;
                    }
                }
                if (alreadyCounted) {
                    continue;
                }

                // Place entry in next available spot in sortedVertices array
                for (j = 0; j < MAX_VERTICES; j++) {
                    if (sortedVertices[j] == '?') {
                        sortedVertices[j] = vertices[i]->letter;
                        break;
                    }
                }

                // Now remove all edge references to this vertex
                for (j = 0; j < MAX_VERTICES; j++) {
                    if (vertices[j]->letter == '?') {
                        break;
                    }

                    Edge** checkEdge = &(vertices[j]->edges);

                    while ((*checkEdge) != NULL) {
                        if ((*checkEdge)->connectingVertex->letter == vertices[i]->letter) {
                            if ((*checkEdge)->nextEdge == NULL) {
                                *checkEdge = NULL;
                            }
                            else {
                                *checkEdge = (*checkEdge)->nextEdge;
                            }

                            break;
                        }

                        checkEdge = &((*checkEdge)->nextEdge);
                    }
                }
            }
        }
    }

    // Finally, push the start vertex in last and print results.
    for (i = 0; i < MAX_VERTICES; i++) {
        if (sortedVertices[i] == '?') {
            sortedVertices[i] = vertices[0]->letter;
            printf("%c", sortedVertices[i]);
            break;
        }

        printf("%c", sortedVertices[i]);
    }

    printf("\n");
}
