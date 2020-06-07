#define _GNU_SOURCE
#include "queue.h"



void init(Queue* q, int max_size){
    q->list = (char **) malloc (sizeof(char*) * max_size + 1);
    q->index_get = 0;
    q->index_insert = 0;
    q->size = 0;
    q->max_size = max_size;
}

bool is_empty(Queue* q){
    return q->size == 0;
}

bool is_full(Queue* q){
    return q->size == q->max_size;
}

int next_index(int index, Queue* q){
    return (index+1) % q->max_size;
}

bool push(Queue* q, char* element){
    if (is_full(q)){
        printf("queue is full\n");
        return false;
    } else {
        asprintf(&q->list[q->index_insert], "%s", element);
        q->index_insert = next_index(q->index_insert, q);
        q->size++;
        return true;
    }
}

char* front(Queue* q){
    if (is_empty(q)){
        return NULL;
    } else {
        return q->list[q->index_get];
    }
}

void pop(Queue* q){
    //free(q->list[q->index_get]);
    free(q->list[q->index_get]);
    q->list[q->index_get]= NULL;
    q->index_get = next_index(q->index_get, q);
    q->size--;
}

void print_element_queue(Queue* q){
    int i = q->index_get;
    do {
        printf("element at \'%d\' =  \'%s\'\n", i, q->list[i]);
        i = next_index(i, q);
    } while (i != q->index_get);
    
}

void de_init (Queue *q){
    int i = q->index_get;
    while (i != q->index_insert){
        free(q->list[i]);
        i = next_index(i, q);
    }
    free(q->list);
    q->index_get = 0;
    q->index_insert = 0;
    q->size = 0;
    q->max_size = 0;
}

