//
//  Dict.h
//  DataStructure
//
//  Created by Timur Murzakov on 11/10/2022.
//

#ifndef Dict_h
#define Dict_h

#include "../Trees/BinSearchTree.h"
#include "../LinkedList/LinkedList.h"
#include "Entry.h"

struct Dict {
    struct BinSearchTree binSearchTree;
    struct LinkedList keys;
    
    void (*insert)(void *key, unsigned long keySize, void *value, unsigned long valueSize, struct Dict *dict);
    void *(*search)(void *key, unsigned long keySize, struct Dict *dict);
};

// Constructors
struct Dict dictConsructor(int (*compare)(void *keyA, void *keyB));
void dictDestructor(struct Dict *dictToRemove);

// Helpers
int compareStringKeys(void *entryA, void *entryB);

#endif /* Dict_h */
