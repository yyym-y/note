#include<stdio.h>
struct NodeList{
    int element;
    struct NodeList* next;
};

void InitList(struct NodeList* head){
    head->next = NULL;
}

void InsertList(struct NodeList* head , int element , int index){
    if(index < 0) return 0;
    while(index--){
        if(head->next == NULL) return 0;
        head = head->next;
    }
    struct NodeList* New = (struct NodeList *)malloc(sizeof(struct NodeList));
    if(New == NULL) return 0;
    struct NodeList* temp = head->next;
    head->next = New;
    New->element = element;
    New->next = temp;
}

void PrintList(struct NodeList* head){
    while(head->next  != NULL){
        head = head->next;
        printf("%d  ",head->element);
    }
    printf("\n");
}

void DeleteList(struct NodeList* head , int index){
    if(index < 0) return 0;
    while(--index){
        if(head->next == NULL) return 0;
        head = head->next;
    }
    struct NodeList* temp = head->next;
    head->next = head->next->next;
    free(temp);
}

int SearchElem(struct NodeList* head , int index){
    while(--index){
        if(head->next == NULL) return 0;
        head = head->next;
    }
    return head->next->element;
}

int SearchIndex(struct NodeList* head , int elememt){
    int index = 0;
    while(head->next != NULL){
        head = head->next;
        if(head->element == elememt)
            return index;
        index++;
    }
    return -1;
}

int LenList(struct NodeList* head){
    int length = 0;
    while(head->next != NULL){
        head = head->next;
        length++;
    }
    return length;
}
int main()
{
    struct NodeList head;
    InitList(&head);
    for(int temp = 0 ; temp < 10 ; temp++){
        InsertList(&head , temp ,temp);
        PrintList(&head);
    }
    InsertList(&head , -1,10);
    PrintList(&head);
    DeleteList(&head , 10);
    PrintList(&head);
    int ans = SearchElem(&head , 9);
    printf("%d\n",ans);
    ans = SearchIndex(&head ,5);
    printf("%d\n",ans);
    printf("%d\n",LenList(&head));
    return 0;
}
