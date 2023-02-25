#include "LinkedList.h"
//Functions DEFINITION 

struct Node *createNode(void *data, unsigned long size);
void destroyNode(struct Node *node);

struct Node *iterateLinkedList(int index, struct LinkedList *linkedList);

void insertNode(int index, void *data, struct LinkedList *linkedList, unsigned long size);
void removeNode(int index, struct LinkedList *linkedList);
void *retrieveData(int index, struct LinkedList *linkedList);
//----//
//Functions DESCRIPTION

struct LinkedList linkedListConstructor() {
    struct LinkedList list;
    list.head = NULL;
    list.length = 0;

    list.insert = insertNode;
    list.remove = removeNode;
    list.retrieve = retrieveData;

    return list;
}

void linkedListDestructor(struct LinkedList *linkedList) {
    for (int i = 0; i < linkedList->length; i++)
        linkedList->remove(0, linkedList);
}

struct Node *createNode(void *data, unsigned long size) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    *node = nodeConstructor(data, size);
    return node;
}

void destroyNode(struct Node *nodeToDestroy) {
    nodeDestructor(nodeToDestroy);
}

struct Node *iterateLinkedList(int index, struct LinkedList *linkedList) {
    // it cause error with printing of 
    if (index < 0 || index >= linkedList->length) {
        printf("[Index %d]Index out of bound...\n", index);
        exit(10);
    }

    struct Node *cursor = linkedList->head;
    for(int i = 0; i < index; i++) {
        cursor = cursor->next;
    }
    return cursor;
}


/* Public methods */

void insertNode(int index, void *data, struct LinkedList *linkedList, unsigned long size) {
    struct Node *nodeToInsert = createNode(data, size);

    if (!index) {   
        nodeToInsert->next = linkedList->head;
        linkedList->head = nodeToInsert;
    } else {
        struct Node *cursor = iterateLinkedList(index - 1, linkedList);
        nodeToInsert->next = cursor->next;
        cursor->next = nodeToInsert;
        nodeToInsert->previous = cursor;

        if (linkedList->length != index)
            nodeToInsert->next->previous = nodeToInsert;
    }
    linkedList->length += 1;
}

void removeNode(int index, struct LinkedList *linkedList) {
    if (!index) {
        //List[index = 0] means head, so it need not to change previous item
        struct Node *nodeToRemove = linkedList->head;

        // if head is NULL, there'll be not error, just print warning
        // I don't think pop function have to be so picky, but the warning should be written
        if (nodeToRemove) {
            linkedList->head = nodeToRemove->next;
            destroyNode(nodeToRemove);
        } else
            printf("[Warning] Attempt of remove 1st item, that's NULL\n");
    } else {
        // get previous item
        struct Node *cursor = iterateLinkedList(index - 1, linkedList);
        /* [0]      [1]       [2] 
         cursor    nodeTR     nodeTr->next
        */
        struct Node *nodeToRemove = cursor->next;
        // cursor-> next is nodeTR->next now [index 2 in illustraion]
        cursor->next = nodeToRemove->next;
        // we change previous link for index 2
        cursor->next->previous = cursor;
        // so now we have only cursor and nodeTR->next [indexes 0 and 1];
        destroyNode(nodeToRemove);
    }
    linkedList->length -= 1;
}

void *retrieveData(int index, struct LinkedList *linkedList) {
    //get node using iteration
    struct Node *cursor = iterateLinkedList(index, linkedList);
    if (cursor)
        return cursor->data;
    else
        return NULL;
}
