#ifndef NODE_H
#define NODE_H

struct Node {
    void *data;
    struct Node *next;
    struct Node *previous;
};

struct Node nodeConstructor(void *data, unsigned long size);
void nodeDestructor(struct Node *node);

#endif /* NODE_H */