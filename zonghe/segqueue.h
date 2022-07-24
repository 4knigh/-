#ifndef SEGQUEUE_H
#define SEGQUEUE_H

typedef struct Node
{
    char data[300];
    struct Node* next;
}Node;

typedef struct SegQueue
{
    int size;
    struct Node* front;
    struct Node* rear;
}SegQueue;

SegQueue* init();

Node* create(char* value);

void enqueue(SegQueue* list, char* value);

void dequeue(SegQueue* list);

void print(SegQueue* list);

char* func(SegQueue* list);

#endif