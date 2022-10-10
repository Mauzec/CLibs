#include "Queue.h"

void push(void *data, struct Queue *queue, unsigned long size);
void *peek(struct Queue *queue);
void pop(struct Queue *queue);

struct Queue queueConstructor() {
    struct Queue queueToCreate;
    queueToCreate.list = linkedListConstructor();

    queueToCreate.push = push;
    queueToCreate.pop = pop;
    queueToCreate.peek = peek;
    return queueToCreate;
}

void push(void *data, struct Queue *queue, unsigned long size) {
    queue->list.insert( queue->list.length, 
                        data, 
                        &queue->list,
                        size);
}
// Peek return the data from the 1st element
/* !!!! Don't use pop function if you want to get the current 1st element: it'll be free */
void *peek(struct Queue *queue) {
    void *data = queue->list.retrieve(0, &queue->list);
    return data;
    
}

// Pop removes the 1st element in the chain
void pop(struct Queue *queue) {
    queue->list.remove(0, &queue->list);
}