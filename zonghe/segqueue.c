#include "segqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SegQueue* init()
{
    SegQueue* list = malloc(sizeof(SegQueue));
    list->front = NULL;
    list->rear = NULL;
    list->size = 0;
    return list;
}

Node* create(char* value)
{
    Node* new = malloc(sizeof(Node));
    strcpy(new->data, value);
    new->next = NULL;
    return new;
}

void enqueue(SegQueue* list, char* value)
{
    if(list == NULL)
        return;
    
    Node* new = create(value);
    if(list->size == 0)
    {
        list->front = new;
        list->rear = new;
    }
    else
    {
        list->rear->next = new;
        list->rear = new;
    }
    list->size++;
}

void dequeue(SegQueue* list)
{
    if (list == NULL || list->size == 0)
        return;

    Node* p = list->front;
    if (list->size == 1)
    {
        free(list->front);
        list->front = NULL;
        list->rear = NULL;
    }
    else
    {
        list->front = list->front->next;
        p->next = NULL;
        free(p);
        p = NULL;
    }
    list->size--;
}

void print(SegQueue* list)
{
    if(list == NULL || list->size == 0)
    {
        printf("队列已空!");
    }
    else
    {
        Node* p = list->front;
        while(p != NULL)
        {       
            printf("%s\n",p->data);
            p = p->next;
        }
    }
    printf("\n");
}

char* func(SegQueue* list)
{
    return list->front->data;
}