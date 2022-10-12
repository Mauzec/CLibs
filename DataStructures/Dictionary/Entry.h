//
//  Entry.h
//  DataStructure
//
//  Created by Timur Murzakov on 11/10/2022.
//

#ifndef Entry_h
#define Entry_h

struct Entry {
    void *key;
    void *value;
};

struct Entry entryConstructor(void *key, unsigned long keySize, void *value, unsigned long valueSize);
void entryDestructor(struct Entry *entryToRemove);

#endif /* Entry_h */
