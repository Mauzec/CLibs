//
//  Dict.c
//  DataStructure
//
//  Created by Timur Murzakov on 11/10/2022.
//

#include "Dict.h"

#include <stdlib.h>
#include <string.h>


// Private methods
void insertDictItem(void *key, unsigned long keySize, void *value, unsigned long valueSize, struct Dict *dict);
void *searchDictItem(void *key, unsigned long keySize, struct Dict *dict);
void recursiveDestruct(struct Node *cursor);


// Public methods
struct Dict dictConsructor(int (*compare)(void *keyA, void *keyB)) {
    struct Dict dictToCreate;
    dictToCreate.binSearchTree = binSearchTreeConsructor(compare);
    dictToCreate.keys = linkedListConstructor();
    dictToCreate.insert = insertDictItem;
    dictToCreate.search = searchDictItem;
    return dictToCreate;
}

void dictDestructor(struct Dict *dictToRemove) {
    linkedListDestructor(&dictToRemove->keys);
    recursiveDestruct(dictToRemove->binSearchTree.head);
}

// Private methods
void recursiveDestruct(struct Node *cursor) {
    if (cursor->previous)
        recursiveDestruct(cursor->previous);
    if (cursor->next)
        recursiveDestruct(cursor->next);
    entryDestructor((struct Entry *)cursor->data);
    free(cursor);
}

void insertDictItem(void *key, unsigned long keySize, void *value, unsigned long valueSize, struct Dict *dict) {
    struct Entry entry = entryConstructor(key, keySize, value, valueSize);
    dict->binSearchTree.insert(&entry, &dict->binSearchTree, sizeof(entry));
    dict->keys.insert(dict->keys.length, key, &dict->keys, keySize);
}
void *searchDictItem(void *key, unsigned long keySize, struct Dict *dict) {
    short nullValue = 0;
    struct Entry searching = entryConstructor(key, keySize, &nullValue, sizeof(nullValue));
    void *resultBinTree = dict->binSearchTree.search(&searching, &dict->binSearchTree);
    if (resultBinTree) {
        return ((struct Entry *)resultBinTree)->value;
    }
    return NULL;
}

// Public helpers
int compareStringKeys(void *entryA, void *entryB) {
    int comparable = strcmp((char *)(((struct Entry *)entryA)->key), (char *)(((struct Entry *)entryB)->key));
    if (comparable > 0) {
        return 1;
    } else if (comparable < 0) {
        return -1;
    } else {
        return 0;
    }
}
