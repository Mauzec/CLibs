#include "Queue.h"

#include <string.h>

int main (void) {
    struct Queue list = queueConstructor();
    
    for (int i = 0; i < 10; i++) {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        list.push(x, &list, sizeof(int));
    }

    list.push("Lucky", &list, 5);

    for (int i = 0; i < 10; i++) {
        int x = *(int *)list.peek(&list);
        printf("%d\n", x);
        list.pop(&list);
    }

    char *x = (char *)list.peek(&list);
    printf("%s\t\t size: %lu\n", x, strlen(x));
    list.pop(&list);

    // it cause a warning (LinkedList is empty and head is NULL)
    list.pop(&list);
    // it cause error (LinkedList length is empty and head is NULL, no item to peek)
    list.peek(&list);
}