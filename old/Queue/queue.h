#ifndef QUEUE_H
#define QUEUE_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>




typedef struct{
    char** list;
    int index_get;
    int index_insert;
    int size;
    int max_size;
} Queue;


typedef enum{
    false,
    true
}bool;


void init(Queue* q, int max_size);

bool is_empty(Queue* q);

bool is_full(Queue* q);
int next_index(int index, Queue* q);

bool push(Queue* q, char* element);

char* front(Queue* q);

void pop(Queue* q);

void print_element_queue(Queue* q);

void de_init (Queue *q);


#endif