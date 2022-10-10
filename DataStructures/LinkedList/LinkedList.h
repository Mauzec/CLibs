#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

struct LinkedList {
    struct Node *head;
    int length;

    void (*insert)(int index, void *data, struct LinkedList *linkedList, unsigned long size);
    void (*remove)(int index, struct LinkedList *linkedList);
    void *(*retrieve)(int index, struct LinkedList *linkedList);
};

struct LinkedList linkedListConstructor(void);
void linkedListDestructor(struct LinkedList *linkedList);

struct Node *retrieveNode(int index, struct LinkedList *linkedList);

#endif /* LINKEDLIST_H */