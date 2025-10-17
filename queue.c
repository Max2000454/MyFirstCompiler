#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "tokenizer.h"

#define MAX_QUEUE_SIZE 1024
#define ERR_EMPTY_QUEUE 1001

typedef enum token token;

typedef struct {
    int head;
    int tail;
    enum token data[MAX_QUEUE_SIZE];
} QueueInfo;

QueueInfo* create_queue() {
    QueueInfo q;
    q.head = 0;
    q.tail = 0;
    return &q;
}

int isFull(QueueInfo* q) {
    if ((q->tail + 1) % MAX_QUEUE_SIZE == q->head) {
        return 1;
    } else {
        return 0;
    }
}
int isEmpty(QueueInfo* q) {
    if (q->tail == q->head) {
        return 1;
    } else {
        return 0;
    }
}

int enqueue(QueueInfo* q, token elem) {
    if (isFull(q)) return -1;
    q->data[q->tail] = elem;
    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
    return 0;
}

token dequeue(QueueInfo* q) {
    if (isEmpty(q)) {
        errno = ERR_EMPTY_QUEUE;
        return -1;
    };
    token temp = q->data[q->head];
    q->data[q->head] = 0;
    q->head = (q->head + 1) % MAX_QUEUE_SIZE;
    return temp;
}

int main() {
    QueueInfo* q = create_queue();
    enqueue(q, CONSTANT);
    enqueue(q, OPERATOR_ASSIGNMENT);
    enqueue(q, IDENTIFIER);
    int res = enqueue(q, OPERATOR_DIVIDE);
    printf("%d\n", q->data[2]);
    //dequeue(q);


    /*
    token result = dequeue(q);
    if (result == -1) {
        char buffer[1024];
        snprintf(buffer, 1024, "Error<%s>: No elements on queue, cannot dequeue!\n", __func__);
        perror(buffer);
        exit(EXIT_FAILURE);
    }
    

    printf("%d\n", result);
    */

    exit(EXIT_SUCCESS);
}