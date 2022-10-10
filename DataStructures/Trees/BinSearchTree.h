//
//  BinSearchTree.h
//  DataStructure
//
//  Created by Timur Murzakov on 10/10/2022.
//

#ifndef BinSearchTree_h
#define BinSearchTree_h

#include "../Node/Node.h"

struct BinSearchTree {
    struct Node *head;

    int (*compare)(void *dataA, void *dataB);
    void *(*search)(void *data, struct BinSearchTree *tree);
    void (*insert)(void *data, struct BinSearchTree *tree, unsigned long size);
};

// Constructors
struct BinSearchTree binSearchTreeConsructor(int (*compare)(void *dataA, void *dataB));
void binSearchTreeDestructor(struct BinSearchTree *tree);

// Helpers [compare functions]
int intCompare(void *dataA, void *dataB);
int floatCompare(void *dataA, void *dataB);
int charCompare(void *dataA, void *dataB);
int strCompare(void *dataA, void *dataB);

// Public
void *searchBinTree(void *data, struct BinSearchTree *tree);
void insertBinTree(void *data, struct BinSearchTree *tree, unsigned long size);


#endif /* BinSearchTree_h */
