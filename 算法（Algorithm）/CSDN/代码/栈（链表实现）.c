#include<stdio.h>
struct StackNode{
    int element;
    struct StackNode* next;
};

void InitStack(struct StackNode* head){
    head->next = NULL;
}

void InsertStack(struct StackNode* head , int element){
    struct StackNode* temp = (struct StackNode*)malloc(sizeof(struct StackNode));
    if(temp == NULL) return 0;
    struct StackNode* remem = head->next ;
    head->next = temp;
    temp->element = element;
    temp->next = remem;
}

void DeleteStack(struct StackNode* head){
    struct StackNode* temp = head->next;
    head->next = head->next->next;
    free(temp);
}

void PrintStack(struct StackNode* head){
    while(head->next != NULL){
        printf("%d  ",head->next->element);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    struct StackNode test;
    InitStack(&test);
    for(int temp = 0 ; temp < 10 ; temp++){
        InsertStack(&test , temp);
        PrintStack(&test);
    }
    for(int temp = 0 ; temp < 10 ; temp++){
        DeleteStack(&test);
        PrintStack(&test);
    }
}
