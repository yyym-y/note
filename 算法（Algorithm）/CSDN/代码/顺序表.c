#include<stdio.h>
struct ArrList{
    int* arr;
    int capacity;
    int size;
};

void InitList(struct ArrList* Arr , int space){
    Arr->capacity = space;
    Arr->arr = (int *)malloc(sizeof(int)*Arr->capacity);
    if(Arr->arr == NULL) return 0;
    Arr->size = 0;
}

void InsertList(struct ArrList * Arr , int element , int index){
    if(index < 0) return 0;
    if(index > Arr->size)
        index = Arr->size;
    if(Arr->size == Arr->capacity){
        int newcapacity = Arr->capacity + 10;
        int * NewArr = (int*)realloc(Arr->arr , sizeof(int) * newcapacity);
//        printf("--------%d",newcapacity);
        if(NewArr == NULL) return 0;
        Arr->capacity = newcapacity;
        Arr ->arr = NewArr;
//        printf("~~~~%d",newcapacity);
    }
    for(int temp = Arr->size ; temp >= index ; temp--){
        Arr->arr[temp + 1] = Arr->arr[temp];
    }
    Arr->arr[index] = element;
    Arr->size++;
}

void DeleteList(struct ArrList* Arr , int index){
    if(index < 0 || index >= Arr -> size) return 0;
    for(int temp = index + 1 ; temp < Arr->size ; temp++)
        Arr->arr[temp - 1] = Arr->arr[temp];
    Arr->size--;
}

void PrintList(struct ArrList*Arr){
    for(int temp = 0 ; temp < Arr->size ; temp++)
        printf("%5d",Arr->arr[temp]);
    printf("\n");
}

int LenList(struct ArrList* Arr){
    return Arr->size;
}

int SearchElem(struct ArrList* Arr , int elememt){
    int index = 0;
    int flag = 0;
    while(index < Arr->size){
        if(Arr->arr[index] == elememt){
            flag = 1;
            break;
        }
        index++;
    }
    if(flag)
        return index;
    else
        return -1;
}

int Searchindex(struct ArrList * Arr , int index){
    if(index < 0 || index >= Arr->size) return 0;
    int elememt = Arr->arr[index];
    return elememt;
}
int main()
{
    struct ArrList Test;
    InitList(&Test ,5);
    int number , index;
    for(int temp = 0 ; temp < 10 ; temp ++)
        InsertList(&Test , temp , temp);
    PrintList(&Test);
    scanf("%d",&number);
    int ans = Searchindex(&Test , number);
    printf("%d-----\n",ans);
    scanf("%d",&number);
    ans = SearchElem(&Test , number);
    printf("%d-----\n",ans);
    ans = LenList(&Test);
     printf("%d-----\n",ans);
    return 0;
}
