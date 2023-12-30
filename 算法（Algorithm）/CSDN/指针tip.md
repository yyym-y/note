## 指针tip

首先化名感谢b站鹏哥，痛苦，指针这个痛点终于在上完鹏哥的课之后解决了，手动@一下他，不容易，感恩。

这篇博客是我第二篇博客，主要是用来自我复习，顺便普惠众生......

说一句，刚理解指针，可能在内容中有些不严谨，欢迎各路大神帮忙指点，不甚感激！！！

说实话，有些过于基础的我就一句话带过了，毕竟我懒得敲.....相信各位都能完美理解，有所收获



### 先上基础

**指针是啥**

说白了指针就是地址

#### 内存中的单位排行

bit  （比特）----->   byte （字节）------>   KB ------> MB ------>GB ------>TB

1 byte = 8 bit

1 KB = 1024 byte

1 MB = 1024KB

1 GB = 1024MB



每一个字节赋予一个内存地址



#### 32位与64位的区别

32位代表有32根地址线，64位代表有64根地址线，每根地址线在通电时产生的高低电频分别代表着1和0

这些0，1的组合代表着地址，所以32位与64位在指针大小中是不相等的

32位：  指针大小为 4个字节

64位： 指针大小为  8个字节



#### 指针类型及其意义

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221016105727439.png" alt="image-20221016105727439" style="zoom:80%;" />

当时上课时老师提出一个疑问

为什么指针大小都一样，还要区分指针指向的类型，大小一样肯定可以存的下去？

实际上，指针指向类型不同决定了指针的权限

**1.在递增或递减中的跨度不同**

（指针 + - 整数）

```c
// %p是专门用来打印地址的占位符
#include<stdio.h>
int main()
{
    int number = 10;
    int * pi = &number;
    char* pc = (char*)&number;
    printf("%p\n",pi);
    printf("%p\n",pi + 1);
    printf("%p\n",pc);
    printf("%p\n",pc + 1);
    return 0;
}
```

<img src="C:\Users\阴铭洋\Desktop\3" alt="image-20221016111249194" style="zoom:80%;" />

**解引用时的解引权限不同**

```c
#include<stdio.h>
int main()
{
    int number1 = 0x11223344;
    int number2 = 0x11223344;
    int * pi = &number1;
    char* pc = (char*)&number2;
    *pi = 0;
    *pc = 0;
    printf("%x\n",number1);
    printf("%x",number2);
}
/*
结果为
0
11223300
*/
```



pi在解引的时候，将整个4个比特全部解引出来，然后把这整一个内存赋值为0

pc因为char大小是int的四分之一，所以只能解引后四分之一部分并将那一部分赋值为0

**注：为什么要用16进制表示地址**

在2进制中，1111代表15 ，比16要小，所以用16进制可以减少观看的时候的数字多少

#### 野指针

1.未初始化

2.指针越界访问

3.指针指向空间释放

```c
// 1
#include<stdio.h>
int main()
{
    int* pl;
    *pl = 20;
    return 0;
}
// 2
#include<stdio.h>
{
    int arr[10] = {0};
    int* p = arr;
    *(arr + 11) = 20;
    return 0;
}
// 3
#include<stdio.h>
int* test(void){
    int temp = 0;
    int * ptr = &temp;
    return ptr;
}
int main()
{
    int* pi = test();
    *pi = 20;
    return 0;
}
```

**注：如果定义指针变量的时候不知道具体指向哪，先赋值为NULL**

```c
int* ptr = NULL;
```

#### 指针-指针

**指针-指针返回的是一个int ，即两个地址的距离**

基于此，我们可以自己写一个strlen函数

```c
#include<stdio.h>
int my_strlen1(char* arr){
    int length = 0 ;
    while(*(arr+length) != '\0')
        length++;
    return length;
}

int my_strlen2(char* arr){
    char* ptr = arr;
    while(*ptr != '\0'){
        ptr++;
    }
    return ptr - arr;
}

int main()
{
    char arr[] = {"this is a test array"};
    int length1 = my_strlen1(arr);
    int length2 = my_strlen2(arr);
    printf("%d    %d",length1 , length2);
    return 0;
}

// 20    20
```



#### 指针与数组

数组名实际上就是数组首元素的地址

```c
int arr[5] = {1,2,3,4,5};
int* ptr = &arr[0];
// ptr == arr
```

ptr = arr[0]         ptr+1 = arr[1]          ptr+2 = arr[2]       ptr + 3 = arr[3]

#### 二级指针

二级指针简单来说就是指针的指针，即它是指向一个指针变量的指针，存着指针变量的地址

```c
int number = 20;
int* ptr1 = &number;
int** ptr2 = &ptr1;
*ptr1 == 20;
*ptr2 ==  &ptr1;
**ptr2 == 20;
```



#### 指针数组

人如其名，是一个存放指针的数组，本质上还是一个数组

```c
int* arr[5];
```

代表着这是一个指针数组，里面存着int* 一共可以存五个int*类型的指针变量

其实和数组的定义差不多

类型  数组名[容量]



### 来个进阶

#### 字符指针

一般有两种形式

```c
#include<stdio.h>
int main()
{
    char ch = 'w';
    char* ptr1 = "this is a string";  //   1
    char* ptr2 = &ch;  //2
    char* ptr3 = "this is a string";
}
```



**注**

ptr1中并不是将整个字符串存入指针中，而是将字符串的首元素的地址存入

"this is a string" 是一个字符常量，不允许修改，同时，ptr1和ptr3是相等的，因为

双方同为字符常量，同时也相等所以双方同时使用该内存。



```c
#include<stdio.h>
int main()
{
    char arr1[] = {"this is a string"};
    char arr2[] = {"this is a string"};
    char* ptr1 = "this is a string";
    char* ptr2 = "this is a string";
    printf("%p\n",arr1);
    printf("%p\n",arr2);
    printf("%p\n",ptr1);
    printf("%p\n",ptr1);
    return 0;
}
/*
000000000060FDE0  数组之间地址不同
000000000060FE00
0000000000404004  字符常量之间地址相同
0000000000404004
*/
```



#### 数组指针（重要，重要！）

顾名思义，这是一个指针，只不过这是一个指向数组的指针

```c
int (*ptr)[5] ; //这是一个指向有五个int类型数组的数组指针
```

区分

```c
int* ptr[5]; //指针数组
int (*ptr2)[]; //数组指针
```



#### &数组名  VS  数组名

先看一段代码

```c
#include<stdio.h>
int main()
{
    char arr[] = {"a string"};
    printf("arr = %p \n&arr = %p",arr , &arr);
    return 0;
}
/*
arr = 000000000060FE17
&arr = 000000000060FE17
*/
```

神奇的是，这两个地址是相同的，但实际上他们的意义不同

举个例子

```c
char temp = 'a';  // 存储时为97
int temp2 = 97;   //存的值也为97
```

虽然二者的值相同，但是意义不同，一个是字符类型，一个是整型

这里也是一样

arr是指向首元素的地址，本质上是指向一个字符的，是一个字符指针

而&arr是指向这个数组的，本质上是一个数组指针

所以存储时：

```c
char* ptr1 = arr;
char (*ptr2)[8] = &arr;
```

再来看看指针的加减法

```c
#include<stdio.h>
int main()
{
    char arr[] = {"a string"};
    char* ptr1 = arr;
	char (*ptr2)[8] = &arr;
    printf("%p\n",ptr1);
    printf("%p\n",ptr1+1);
    printf("%p\n",ptr2);
    printf("%p\n",ptr2+1);
    return 0;
}
/*
000000000060FE17   //只跳过了一个字节
000000000060FE18
000000000060FE17   //跳过了八个字节，即整个数组
000000000060FE1F
*/
```



#### 函数数组参数，指针参数

**注**

一维数组可以省略省略方括号里的数，因为此时数组被弱化为指针，但是二维数组中不可以省略第二个方括号，因为如果省略，那么编译器就不知道该如何分配内存

**一维数组**

```c
#include <stdio.h>
void test(int arr[])//  可以，省略了里面的数字
{}
void test(int arr[10])//  可以
{}
void test(int *arr)//   可以，数组名本身就是int 类型的指针
{}
void test2(int *arr[20])//  可以，相当于int* arr[]
{}
void test2(int **arr)//  可以，此时的数组名是int类型的二维指针
{}
int main()
{
    int arr[10] = {0};
    int *arr[20] = {0};
    test(arr);
    test(arr2);
    return 0;
}
```

**二维数组**

```c
void test(int arr[3][5])// 可以，但没有必要
{}
void test(int arr[][])//  不可以，省略了过多参数
{}
void test(int arr[][5])//   可以，标准
{}
//总结：二维数组传参，函数形参的设计只能省略第一个[]的数字。
//因为对一个二维数组，可以不知道有多少行，但是必须知道一行多少元素。
//这样才方便运算。
void test(int *arr)//  不可以，此时传入的是int类型的指针
{}
void test(int* arr[5])//  不可以，这是指针数组
{}
void test(int (*arr)[5])//  可以，此时传入的是一个数组指针
{}
void test(int **arr)//  不可以，这传入的是二级数组
{}
int main()
{
 int arr[3][5] = {0};
 test(arr);
}
```

