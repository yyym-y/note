#include<stdio.h>
struct Stack{
    int * array;
    int capacity;
    int top;
};

void InitStack(struct Stack* stack){
    stack->array = (int*)malloc(sizeof(int) * 10);
    if(stack->array == NULL) return 0;
    stack->capacity = 10;
    stack->top = -1;
}

void Insertstack(struct Stack* stack , int element){
    if(stack->top + 1 == stack->capacity){
        int* NewArray = (int*)realloc(stack->array , sizeof(int)*(stack->capacity + 10));
        if(NewArray == NULL) return 0;
        stack->array = NewArray;
        stack->capacity = stack->capacity + 10;
    }
    stack->array[stack->top + 1] = element;
    stack->top++;
}

void Deletestack(struct Stack* stack){
    if(stack->top == -1) return 0;
    stack->top--;
}

void Printstack(struct Stack* stack){
    for(int temp = 0 ; temp <= stack->top ; temp++){
        printf("%d  ",stack->array[temp]);
    }
    printf("\n");
}

int main()
{
    struct Stack test;
    InitStack(&test);
    for(int temp = 0 ; temp < 15 ; temp ++){
        Insertstack(&test , temp);
        Printstack(&test);
    }
    for(int temp = 0 ; temp < 20 ; temp ++){
        Deletestack(&test);
        Printstack(&test);
    }
    return 0;
}
