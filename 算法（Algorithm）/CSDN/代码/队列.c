#include<stdio.h>
struct Queue{
    int* array;
    int up;
    int down;
};

void InitQueue(struct Queue* queue){
    queue->array = (int*)malloc(sizeof(int) * 20);
    if(queue->array == NULL) return 0;
    queue->up = queue->down = -1;
}

void InsertQueue(struct Queue* queue, int element){
    queue->up++;
    if(queue->up == 20)
        queue->up = -1;
    int distence = queue->down - queue->up > 0 ? queue->down - queue->up : queue->up - queue->down;
    if(distence == 1)
        return 0;
    queue->array[queue->up] = element;
}

void PrintQueue(struct Queue* queue ){

}
