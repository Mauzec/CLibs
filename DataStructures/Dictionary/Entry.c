//
//  Entry.c
//  DataStructure
//
//  Created by Timur Murzakov on 11/10/2022.
//

#include "Entry.h"

#include <stdlib.h>
#include <string.h>

struct Entry entryConstructor(void *key, unsigned long keySize, void *value, unsigned long valueSize) {
    struct Entry entry;
    entry.key = malloc(keySize);
    entry.value = malloc(valueSize);
    memcpy(entry.key, key, keySize);
    memcpy(entry.value, value, valueSize);
    
    return entry;
}

void entryDestructor(struct Entry *entryToRemove) {
    free(entryToRemove->key);
    free(entryToRemove->value);
    free(entryToRemove);
}
