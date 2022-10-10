#include "Node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node nodeConstructor(void *data, unsigned long size) {
    if (size < 1) {
        printf("Invalid data size to create node...\n");
        exit(9);
    }

    struct Node nodeToCreate;
    nodeToCreate.data = malloc(size);
    memcpy(nodeToCreate.data, data, size);

    nodeToCreate.next = NULL;
    nodeToCreate.previous = NULL;
    return nodeToCreate;
}

void nodeDestructor(struct Node *node) {
    free(node->data);
    free(node);
}
