#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

struct Queue {
    struct LinkedList list;

    void (*push)(void *data, struct Queue *queue, unsigned long size);
    void (*pop)(struct Queue *queue);
    void *(*peek)(struct Queue *queue);
};

struct Queue queueConstructor();

#endif /* QUEUE_H */