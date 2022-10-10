//
//  BinSearchTree.c
//  DataStructure
//
//  Created by Timur Murzakov on 10/10/2022.
//

#include "BinSearchTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private Methods
struct Node *createNode(void *data, unsigned long size);
void destroyNode(struct Node *node);

// Constuctors
struct BinSearchTree binSearchTreeConsructor(
    int (*compare)(void *dataA, void *dataB)) {
        struct BinSearchTree tree;
        tree.head = NULL;
        tree.compare = compare;
        tree.search = searchBinTree;
        tree.insert = insertBinTree;
        return tree;
}



void recursiveTreeDestruct(struct Node *node) {
    if (node->previous)
        recursiveTreeDestruct(node->previous);
    if (node->next)
        recursiveTreeDestruct(node->next);
    destroyNode(node);
}
void binSearchTreeDestructor(struct BinSearchTree *tree) {
    recursiveTreeDestruct(tree->head);
}


// Private Methods
struct Node *createNode(void *data, unsigned long size) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    *node = nodeConstructor(data, size);
    return node;
}

void destroyNode(struct Node *nodeToDestroy) {
    nodeDestructor(nodeToDestroy);
}

// Recursive function that move left or right using compare function
// Compare function becomes 1 if data > returned node, -1 if data < returned node, 0 if data and returned node are equal
// This function change value by pointer [direction] to returned value of compare function
struct Node *iterate(void *data, int *direction, struct BinSearchTree *tree, struct Node *cursor) {
    int comp = tree->compare(cursor->data, data);
    if (comp == 1) {
        if (cursor->next) {
            return iterate(data, direction, tree, cursor->next);
        } else {
            *direction = 1;
            return cursor;
        }
    } else if (comp == -1) {
        if (cursor->previous) {
            return iterate(data, direction, tree, cursor->previous);
        } else {
            *direction = -1;
            return cursor;
        }
    } else {
        *direction = 0;
        return cursor;
    }

}

// Public methods

// Search function uses iterate
// direction = 0 --> found it
// direction!= 0 --> not found it
void *searchBinTree(void *data, struct BinSearchTree *tree) {
    int direction = 0;
    struct Node *cursor = iterate(data, &direction, tree, tree->head);
    if (direction == 0) {
        return cursor->data;
    } else {
        return NULL;
    }

}

void insertBinTree(void *data, struct BinSearchTree *tree, unsigned long size) {
    if (!tree->head) {
        tree->head = createNode(data, size);
    } else {
        int direction = 0;
        struct Node *cursor = iterate(data, &direction, tree, tree->head);
        if (direction == 1)  {
            cursor->next = createNode(data, size);
        } else if (direction == -1) {
            cursor->previous = createNode(data, size);
        }

    }
}

// Public helpers
int intCompare(void *dataA, void *dataB) {
    int a = *(int *)(dataA), b = *(int *)(dataB);
    if (b > a)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
}
int floatCompare(void *dataA, void *dataB) {
    float a = *(float *)(dataA), b = *(float *)(dataB);
    if (b > a)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
}
int charCompare(void *dataA, void *dataB) {
    char a = *(char *)(dataA), b = *(char *)(dataB);
    if (b > a)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
}
int strCompare(void *dataA, void *dataB) {
    int comp = strcmp(dataA, dataB);
    if (comp > 0)
        return 1;
    else if (comp < 0)
        return -1;
    else
        return 0;
}

