## 数位分离

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220920191623810.png" alt="image-20220920191623810" style="zoom:80%;" />

**思路讲解**

将一个多位数转化为一个数字比较通常采用%来进行分割

以123为例

123 % 10 = 3     此时就获得最后一个数字，再将它与目标进行对比

之后把3丢弃，将三位数转化为两位数              123 /= 10       -> 12

之后在进行多次循环只到最后一位数丢弃

1 /=10  ->   0

**代码**

```c
#include<stdio.h>
int main()
{
    int L,R,count = 0;
    scanf("%d %d",&L,&R);
    for(int i = L ; i <= R ; i++){
        int k = i;
        while(k){
            if(k % 10 == 2)
               count++;
            k /= 10;
        }
    }
    printf("%d",count);
    return 0;
}
```

### 相似例题

**第一题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220920195328432.png" alt="image-20220920195328432" style="zoom:80%;" />



将数字反转过来可以先将数字用分割的方法储存在数组中，方便后续反转；

注：

因为新数的最高位不能为0           我们不能只考虑消去最后一个0，想1900，可能要消到不是0的位数，所以采用遍历的方法

有一个特殊数据，即0 ，遇到这个数据直接返回0即可



```c
#include<stdio.h>
int main()
{
    int num,count=0 ,arr[11],begin = 0;
    scanf("%d",&num);
    if (num == 0){    //考虑直接遇到0的情况
        printf("0");
        return 0;
    }
    int k = num;
    if(k < 0)    //如果是负数，会使存在数组里的数也是负数
        k=-k;
    while(k){
        arr[count] = k % 10;
        k /= 10;
        count++;
    }
    if(num < 0)   //打印出负号
       printf("-");
    for(int i = 0 ; i < count ; i++){   //逐级遍历直到找到不是0的位数并记录
        if(arr[i] == 0){
            begin++;
        }else 
            break;
    }
    for(int i = begin ; i < count ;i++)
        printf("%d",arr[i]);
    return 0;
}

```

**第二题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921092858137.png" alt="image-20220921092858137" style="zoom:80%;" />

```c
#include<stdio.h>
int main()
{
    int L,R,arr[10];
    scanf("%d %d",&L,&R);
    for(int i = 0 ; i < 10 ;i++)
       arr[i] = 0;
    for(int i = L ; i <= R ;i++){
        int k = i;
        while(k){
            arr[k % 10]++;
            k /= 10;
        }
    }
    for(int i = 0 ; i < 10 ;i++)
    printf("%d ",arr[i]);
    return 0;
}
```



## 低洼地积水

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220920204455922.png" alt="image-20220920204455922" style="zoom:80%;" />

**思路讲解**

要想形成低洼地有两个条件，即两条边要满足不同的情况

左边界需要左高右低，右边界需要右高左低

注： 如果在中间高度齐平也算可以形成一个低洼地

**代码**

```c
#include<stdio.h>
int main()
{
    int n,i = 1 ,ans = 0;
    scanf("%d",&n);
    int arr[n];
    for(int a = 0 ; a < n ; a++)
        scanf("%d",&arr[a]);
    while(i < n){
        while(arr[i] <= arr[i-1] && i < n)
            i++;
        while(arr[i] >= arr[i-1] && i < n)
            i++;
        ans++;
    }
    printf("%d",ans-2);//头和尾都进入了一次循环，所以要减去
    return 0;
```

### 相似例题

**第一题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921143438922.png" alt="image-20220921143438922" style="zoom:80%;" />

```c
#include<stdio.h>
int main()
{
    int day;
    scanf("%d",&day);
    if (day == 1){
        printf("1");
        return 0;
    }
    int arr[day];
for(int i = 0 ; i <= day ;i++)
    scanf("%d",&arr[i]);
    int k = 1,count1=1;
    while(k < day){   // k 不能等于day，如果等于数组会越界
        int count2=1;    //count2要从2开始，因为递增必须是要两个才能实现
        while(arr[k] > arr[k-1] && k<day){
            k++;
            count2++;
            if(count2 > count1)
               count1 = count2;
        }
        while(arr[k] <= arr[k-1] && k <day)  //注意一定要有这层循环，如果直接k++会遗漏数据
            k++;
    }
    printf("%d",count1);
    return 0;
}
```

**第二题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220922192806090.png" alt="image-20220922192806090" style="zoom:80%;" />

```c
#include<stdio.h>
int main()
{
    int num;
    scanf("%d",&num);
    if(num == 1){
        printf("1");
        return 0;
    }
    int arr[num];
    for(int i = 0 ;i < num ;i++)
        scanf("%d",&arr[i]);
    int k = 1,count1=1;    //count1初始化为1，避免输入全是一样的数的结果
    while(k < num){
        int count2 = 1;
        while(arr[k] == arr[k-1]+1 && k < num){
            count2++;
            if(count2>count1)
               count1 = count2;
            k++;
        }
        while(arr[k] != arr[k-1]+1 && k < num)
            k++;
    }
    printf("%d",count1);
    return 0;
}
```



## 单词覆盖还原

### 题目

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921090403068.png" alt="image-20220921090403068" style="zoom:80%;" />

### 思路讲解

因为这两个单词的字母都不一样，所以可以通过判断字符出现的个数来判断

如boy ，这三个字符连在一起出现的次数即为boy出现的次数

### 代码

````c
#include<stdio.h>
#include<string.h>
int main()
{
    int boy=0,girl=0,len;
    char arr[300];
    scanf("%s",arr);
    len = strlen(arr);
    for(int i = 0 ;i < len ;i++){
        if(arr[i] == 'b' || arr[i+1] == 'o' || arr[i+2] =='y')
           boy++;
        if(arr[i] == 'g' || arr[i+1] == 'i' || arr[i+2] == 'r' || arr[i+3] == 'l')
           girl++;
    }
    printf("%d\n%d",boy,girl);
    return 0;
}
````

## 未给详细输入数据个数

### 题目

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921143017070.png" alt="image-20220921143017070" style="zoom:80%;" />

### 思路

之后输入的数据之和等于变长的平方，可以将这个条件加入循环判断条件来控制

### 代码

```c
#include<stdio.h>
int main()
{
    int length;
    scanf("%d",&length);
    int num,pri=0,line=0,totel = 0;
    while(scanf("%d",&num) && totel < length*length){ //输入的数据之和等于变长的平方
        totel+=num;
        int count = 0;
        while(count!=num){
            if(line==length){
                printf("\n");
                line = 0;
            }
            printf("%d",pri);
            count++;
            line++;
        }
        if(pri == 0)
          pri = 1;
        else
          pri = 0;
    }
    return 0;
}
```

### 相似例题

## 轰炸问题

### 题目

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921152059780.png" alt="image-20220921152059780" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921152139453.png" alt="image-20220921152139453" style="zoom:80%;" />

### 思路

由于数据比较小，所以直接进行模拟，因为有两个数据，所以可以使用结构体来做，这是最直接的做法，重点是结构体的用法

### 代码

```c
#include<stdio.h>
struct Map{
  int last;
  int num;
};
int main()
{
    int L,R,bomb,look;
    scanf("%d %d %d %d",&L,&R,&bomb,&look);
    struct Map map[L][R];
    for(int a = 0 ; a < L ; a++){
        for(int b = 0 ; b < R ;b++){
            map[a][b].last=0;
            map[a][b].num =0;
        }
    }
    for(int i = 0;i < bomb ; i++){
        int x1,x2,y1,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        for(int a = x1-1 ; a < x2 ;a++){
            for(int b = y1-1 ;b < y2 ; b++){
                map[a][b].last = i+1;
                map[a][b].num++;
            }
        }
    }
    for(int i = 0 ;i < look ;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        if(map[x-1][y-1].last == 0)
          puts("N");
        else
          printf("Y %d %d\n",map[x-1][y-1].num,map[x-1][y-1].last);
    }
    return 0;
}
```

### 相似例题

## 确定正方形与长方形的个数

### 题目

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921155959340.png" alt="image-20220921155959340" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921160016083.png" alt="image-20220921160016083" style="zoom:80%;" />

### 思路

确定一个矩形可以使用左上角的坐标和右下角的坐标

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220921160429054.png" alt="image-20220921160429054" style="zoom:80%;" />

x2-x1可以获得矩形的长，y2-y1可以获得矩形的高，如果长和高相等，那么这个矩形就是一个正方形，反之则是一个长方形；

我们设a为左上角的坐标，b为右下角的坐标

可以使用双层循环使a在整的坐标范围内走一遍（注意，题目输入的是方格的数量，实际上的坐标个数为N+1，M+1）

要想构成矩形，b的坐标至少是a+1，所以再使用两层循环使b全部走一遍，就可以找出全部情况

### 代码

```c
#include<stdio.h>
int main()
{
    int count1=0,count2=0,n,m;
    scanf("%d %d",&n,&m);
    for(int a = 0 ;a <= n ;a++){   //<=控制循环的次数为n+1，b同理
        for(int b = 0 ;b <= m ;b++){
            for(int c = a+1 ; c <= n ;c++){   //<=控制当a，b在最后一格时不会参与累加
                for(int d = b+1 ;d <= m ;d++){
                    if(c-a == d-b)
                       count1++;
                    else
                       count2++;
                }
            }
        }
    }
    printf("%d %d",count1,count2);
    return 0;
}
```

### 相似例题

## 园相关

### 题目

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220922194914422.png" alt="image-20220922194914422" style="zoom:80%;" />

### 思路

园与两个点的关系只有三种

1.一个圆包含两个点  ---->穿过时必定不会与这个园相交

2.一个圆不包含两个点  ----->穿过时不会与两个圆相交

3一个圆只包含一个点   ----->穿过时会相交

所以答案就是3的个数

### 代码

```c
```

## 时间相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220924235558271.png" alt="image-20220924235558271" style="zoom:80%;" />

**思路**

对于月份来说，实际上只需要改一次，十位数a如果超过一必定不合法，个位数b如果是0有两种情况，如果

a也是零，那么不合法

1              00  --->   01  (最好将月份改为有31天的，方便后续检查日期)

2              63   --->  03

3              52   ---->  12  (一定要考虑这种情况，如果a超出，b等于二，将月份设为12，以防有22-31这种数据)

4               30   --->  10

对于日期来说

每个月的日期不一样，所以建立一个数组来储存天数

日期若超出一定只需要一次(因为不存在00情况)

65 ----> 05

60 -----> 10

**代码**

```c
#include<stdio.h>
int main()
{
    int a,b,c,d,count=0;
    int arr[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%1d%1d-%1d%1d",&a,&b,&c,&d);
    int month = a*10+b;
    if(month == 0){
        month = 1;
        count++;
    }else if(a > 1 && b == 0){
        month = 10;
        count++;
    }else if(a >1 && b != 0){
        if(b != 2){
            month = b;
            count++;
        }else{
            month = 12;
            count++;
        }
    }
    int day = c*10+d;
    if(day > arr[month-1])
        count++;
    printf("%d",count);
    return 0;
}
```

### 相似例题

**第一题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220925083252280.png" alt="image-20220925083252280" style="zoom:80%;" />

注意：闰年的判断

1.  能被4整除但不被100整除
2. 能被400整除

**代码**

```c
#include<stdio.h>
int main()
{
    int year,month;
    int arr[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d %d",&year,&month);
    if(((!(year % 4) && (year % 100)) || !(year % 400)) && month == 2)
       printf("29");
    else
       printf("%d",arr[month-1]);
    return 0;
}
```

**第二题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928083535585.png" alt="image-20220928083535585" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int year,month,day;
    scanf("%d %d %d",&year,&month,&day);
    int mon_day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year % 100 && ! (year % 4)) || !(year % 400))  //注意一定要加括号，！优先级较高
        mon_day[2] = 29;
    int count = 0;
    for(int temp = 1 ; temp < month; temp++)
        count+=mon_day[temp];
    count+=day;
    printf("%d",count);
    return 0;
}
```

**第三题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928084822092.png" alt="image-20220928084822092" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int year,done;
    scanf("%d %d",&year,&done);
    int mon_day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if((year % 100 && !(year % 4)) || !(year % 400))
        mon_day[2] = 29;
    int month = 0, day = 0;
    for(int temp = 1 ; day < done ; temp++){  //注意是 day < done，如果有等于那遇到2016 60 数据会错误
        day += mon_day[temp];
        month = temp;
    }
    day = done - (day - mon_day[month]);
    printf("%d %d",month, day);  //这里不用month - 1
    return 0;
}
```



## 阶乘相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220926192956053.png" alt="image-20220926192956053" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int n,all = 1,count = 0,totel = 0;
    scanf("%d",&n);
    while(totel < n){
        count++;
        all *= count;
        totel += all;
    }
    printf("%d",count-1);
    return 0;
}
```

## 最大公约数

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220926203557109.png" alt="image-20220926203557109" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int a ,b,t;
    scanf("%d %d",&a,&b);
    t = a < b ? a:b;
    while ((a % t) || (b % t))
        t--;
    printf("%d",t);
    return 0;
}
```

### 相似例题

**第一题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220927184736188.png" alt="image-20220927184736188" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int m;
    scanf("%d",&m);
    int arr1[100],count = 0,temp = m,temp2 = 1;
    while((temp /= temp2) != 1){
        for(int i = 2 ; i <= temp ; i++){
            if(!(temp % i)){
                arr1[count] = i;
                if (i != m)
                count++;
                temp2 = i;
                break;
            }
        }
    }
    if(count){
        int i = 0;
        printf("%d=%d",m,arr1[i]);
        i++;
        for(;i < count ;i ++)
            printf("*%d",arr1[i]);
        }else{
            printf("It is a prime number");
        }
        return 0;
}
```

**第二题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220927184906452.png" alt="image-20220927184906452" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
   int n;
   scanf("%d",&n);
   int temp = 0;
   for (int i = 2 ; i < n ;i++){
        if(!(n % i)){
            temp += i;
        }
   }
   if ((temp+1) == n)
       printf("true");
   else
       printf("false");
   return 0;
}
```

**第三题**

**问题**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220927185017803.png" alt="image-20220927185017803" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int n,count=0;
    scanf("%d",&n);
    for (int i = 1; i<= n ; i++){
        int judge = 1;
        for(int temp = 2 ; temp < i ;temp++){
            if(!(i % temp)){
                judge = 0;
                break;
            }
        }
         if (judge)
            count += i;
    }
    printf("sum=%d\n",count-1);
    return 0;
}
```



## 时间相关

**题目**

输入两个时间，求之间相差的时间；

**思路**

将两个时间转化为秒，然后相减，之后再转化为小时，分钟，秒的形式

**代码**

```c
#include<stdio.h>
int main()
{
    int hour1,minute1,second1,hour2,minute2,second2;
    scanf("%d:%d:%d",&hour1,&minute1,&second1); //第一个时间
    scanf("%d:%d:%d",&hour2,&minute2,&second2);  //第二个时间
    int temp1 = hour1*3600+minute1*60+second1;   //转化为秒
    int temp2 = hour2*3600+minute2*60+second2;
    int temp3 = temp1 - temp2;  
    temp3 = temp3 < 0 ? -temp3 : temp3;   //防止temp3小于0
    printf("相差%d小时%d分钟%d秒",temp3 / 3600 , (temp3 % 3600) / 60 ,(temp3 % 3600) % 60);
    return 0;
}
```

## 日期相关

**题目**

求两个日期之间的天数（在同一年内）

**代码**

```c
#include<stdio.h>
struct put{
    int month;
    int day;
}p1,p2;
int main()
{
    int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d %d",&p1.month,&p1.day);
    scanf("%d %d",&p2.month,&p2.day);
    struct put* temp1 = p1.month < p2.month ? &p1:&p2;
    struct put* temp2 = p1.month > p2.month ? &p1:&p2;
    int sum = 0; //计数
    for(int i = temp1->month +1 ; i < temp2->month ; i++){
        sum += day[i];
    }
    sum = sum + (day[temp1->month] - temp1->day) + (temp2->day);
    printf("%d",sum);
    return 0;
}
```

## 字符串相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928093458012.png" alt="image-20220928093458012" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928093518449.png" alt="image-20220928093518449" style="zoom:80%;" />

**思路**

**代码**

```c
#include<stdio.h>
#include<string.h>
struct map{
    char question[100][101];
    char answer[100][101];
}p1;
int main()
{
    int n ,q ;
    scanf("%d %d",&n,&q);
    char ans[q];
    for(int temp = 0 ;temp < n ;temp++){
        scanf("%s",p1.question[temp]);
        scanf("%s",p1.answer[temp]);
    }
    for(int temp = 0 ;temp < q ; temp ++){
        char arr[5][101];
        for(int put = 0 ;put < 5 ;put++)
            scanf("%s",arr[put]);
        for(int b = 0 ; b < n ;b ++){
            if( !(strcmp(p1.question[b],arr[0]))){
                for(int a = 1 ; a < 5 ;a++ ){
                    if(!(strcmp(p1.answer[b] , arr[a]))){
                        switch(a){
                            case 1:
                            ans[temp] = 'A';
                            break;
                            case 2:
                            ans[temp] = 'B';
                            break;
                            case 3:
                            ans[temp] = 'C';
                            break;
                            case 4:
                            ans[temp] = 'D';
                            break;
                        }
                    }
                }
            }
        }
    }
    for(int temp = 0; temp < q ;temp++)
        printf("%c\n",ans[temp]);
    return 0;
}

```

### 相关函数介绍

**1.strcat()**

**字符串拼接**

```c
#include<stdio.h>
#include<string.h>
int main()
{
    char arr1[100],arr2[100];
    scanf("%s\n",arr1);
    scanf("%s",arr2);
    strcat(arr1,arr2);
    printf("%s",arr1);
    return 0;
}
```

**2.strchr()**

**字符的搜索**

char *strchr (const char *str, int c);



**str:**str 表示要在其中搜索字符的原始字符串。

**ch:**ch 是字符类型变量，表示在字符串 str 中搜索的字符。

**返回值：**它返回一个指针值，其中包含给定字符串中第一次出现的字符。（即包含ch）

```c
#include <stdio.h>
#include <string.h>
int main ()
{
   char str[] = "http://www.runoob.com";
   char ch = '.';
   char *ret;   //注意一定是字符指针
   ret = strchr(str, ch);
   printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);
   return(0);
}
```

```c
|.| 之后的字符串是 - |.runoob.com|
```

**3.strstr()**

**字符串的搜索**

char str2 = “cdef”； 
char str1 = “abcdefgh”； 
则通过函数，将返回       strstr(str1,str2) = cdefgh；

如果str1不包含有str2。 
char str2 = “cxef”； 
char str1 = “abcdefgh”； 
则通过函数，将返回           strstr(str1,str2) = NULL；

```c
#include <stdio.h>
#include <string.h>
int main()
{
   char haystack[20] = "RUNOOBKKL";
   char needle[10] = "NOOB";
   char *ret; //返回指针
   ret = strstr(haystack, needle);
   printf("子字符串是： %s\n", ret);
   return(0);
}
```

```c
子字符串是： NOOBKKL
```

**4.strcpy**

**实现字符串的赋值或拷贝**

```c
#include<stdio.h>
#include<string.h>
int main()
{
    char arr1[100],arr2[100];
    scanf("%s\n%s",arr1,arr2);
    strcpy(arr1,arr2);
    printf("%s\n%s",arr1,arr2);
    return 0;
}
```

```c
abc
def
------
def
def
```



### 相似例题

**第一题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928141323366.png" alt="image-20220928141323366" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    char arr[100],ch,arr2[100];
    scanf("%s\n",arr);
    scanf("%c",&ch);
    for(int temp = 0 , temp2 = 0; arr[temp] != '\0' ; temp++){
        if(arr[temp] != ch){
            arr2[temp2] = arr[temp];
            temp2++;
        }
    }
    printf("Results: %s",arr2);
    return 0;
}
```

**第二题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928142743367.png" alt="image-20220928142743367" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    char arr[101];
    int num = 0;
    scanf("%s",arr);
    for(; arr[num] != '\0' ; num++);
    for(int temp = num-1 ; temp >= 0 ;temp --)
        printf("%c",arr[temp]);
    return 0;
}
```

**第三题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928154354015.png" alt="image-20220928154354015" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
#include<string.h>
int main()
{
    char arr[3][10]={{"zhang"},{"li"},{"wang"}};
    int count[3] = {0};
    char arr2[10][20];
    for(int temp = 0 ; temp < 10 ; temp ++){
        scanf("%s",arr2[temp]);
    }
    for(int a = 0 ; a < 10 ;a++){
        for(int b = 0 ; b < 3 ;b++){
            if(!(strcmp(arr[b] , strlwr(arr2[a])))){
                count[b]++;
            }
        }
    }
    for(int temp = 0 ; temp < 3 ;temp++){
        printf("%s\t%d",arr[temp],count[temp]);
        printf("\n");
    }
    return 0;
}
```

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221004115145996.png" alt="image-20221004115145996" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221004115602906.png" alt="image-20221004115602906" style="zoom:80%;" />

**代码**

```c
#include <stdio.h>
#include <string.h>
int main()
{
    int time,begin,end,index,length,number;
    char arr[200],arr2[200],arr3[200],arr4[200];
    scanf("%d\n%s",&time ,arr);
    char ans[time][200];
    for(int temp = 0 ; temp < time ; temp++){
        int number;
        scanf("%d",&number);
        switch(number){
    case(1):
        scanf("%s",arr2);
        strcat(arr , arr2);
        strcpy(ans[temp] , arr);
        break;
    case(2):
        scanf("%d %d",&begin,&end);
        int temp2 = 0;
        for(int temp = begin ; temp < end+begin ; temp++,temp2++){
            arr2[temp2] = arr[temp];
        }
        arr2[temp2] = '\0';
        strcpy(arr,arr2);
        strcpy(ans[temp] , arr);
        break;
    case(3):
        scanf("%d %s",&index,arr2);
        for(int temp = 0 ; temp < strlen(arr) ; temp++){
            if(temp < index)
                arr3[temp] = arr[temp];
            else
                arr4[temp -index] = arr[temp];
        }
        arr3[index] = arr4[strlen(arr) - index] = '\0';
        strcpy(arr , arr3);
        strcat(arr,arr2);
        strcat(arr,arr4);
        strcpy(ans[temp] , arr);
        break;
    case(4):{
        scanf("%s",arr2);
        char * pi ;
        pi = strstr(arr,arr2);
        if(pi){
            strcpy(arr3 , pi);
        int count =  strlen(arr) - strlen(arr3);
            sprintf(ans[temp] , "%d" ,count);
        }
        else{
            sprintf(ans[temp] , "-1");
        }
        break;
    }
        }
    }
    for(int temp = 0 ; temp < time ; temp++)
        printf("%s\n",ans[temp]);
    return 0;
}
```

**第四题**

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221006013225581.png" alt="image-20221006013225581" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
#include<string.h>
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    char arr1[n][m+1],arr2[n][m+1];
    getchar();
    for(int temp = 0 ; temp < n ; temp++){
            scanf("%s",arr1[temp]);
            strcpy(arr2[temp],arr1[temp]);
     }
    for(int temp = 0 ; temp < n ; temp++){
        for(int temp2 = 0 ; temp2 < m ; temp2++){
            if(arr1[temp][temp2] == '#'){
                arr2[temp][temp2+1] = arr2[temp+1][temp2] = arr2[temp+1][temp2+1] = '#';
            }
        }
    }
    for(int temp = 0 ; temp < n ; temp++){
        printf("%s\n",arr2[temp]);
    }
    return 0;
}
```



## 矩阵相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928145836938.png" alt="image-20220928145836938" style="zoom:80%;" />

**思路**

**代码**

```c
#include<stdio.h>
int main()
{
    int n,m;
    scanf("%d %d",&m,&n);
    int arr[n][m];
    int out = 0, in= 0;
    for(int temp = 0 ; temp < (n * m) ; temp++){
        if(out == n){
            out = 0;
            in++;
        }
        scanf("%d",&arr[out][in]);
        out++;
    }
    for(int out = 0 ; out < n ; out++){
        for(int in = 0 ; in < m ; in ++)
            printf("%d\t",arr[out][in]);
        printf("\n");
    }
    return 0
}
```

### 相似例题

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20220928151734140.png" alt="image-20220928151734140" style="zoom:80%;" />

**代码**

```c
#include<stdio.h>
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int arr[n][m];
    int out = 0, in = 0;
    for(int temp = 0 ; temp < (n*m) ; temp++){
        if(out == n){
            out = 0;
            in++;
        }
        scanf("%d",&arr[out][in]);
        out++;
    }
    int Max = 0 , hang = 0,lie = 0;
    for(int a = 0 ; a < n ; a++){
        for(int b = 0 ; b < m ; b++){
            hang = Max < arr[a][b] ? b:hang;
            lie = Max < arr[a][b] ? a: lie;
            Max = Max < arr[a][b] ? arr[a][b]:Max;
        }
    }
    printf("%d %d %d",Max,hang,lie);
    return 0;
}
```

## 浮点数输出相关

**1.保留位有效数字**

使用%.ng  ---> n为保留的有效数字数

```c
#include<stdio.h>
int main()
{
    float test =954.1255248954;
    printf("%.6g",test);
    return 0;
}
```

**2.规定整数p位，小数部分q位 **

使用%p.qf 输出

```c
#include<stdio.h>
int main()
{
    float test =954.1255248954;
    printf("%10.2f",test);
    return 0;
}
```

当整数部分不足时，用空格来补，如果p过小，则p不生效。

**3.四舍五入**

使用%.0f

```c
#include<stdio.h>
int main()
{
   float a = 1.4;
   printf("%.0f",a);
    return 0;
}
```

## 圆相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221006020840204.png" alt="image-20221006020840204" style="zoom:80%;" />

**思路**

**代码**

```c
#include<stdio.h>
int main()
{
    int time ;
    scanf("%d",&time);
    int arr[time];
    for(int temp = 0 ; temp < time ; temp++){
        int put;
        scanf("%d",&put);
        if(put == 1){
            arr[temp] = 0;
            continue;
        }
        if(put % 2){
            arr[temp] = (put+1) / 2;
        }else{
            arr[temp] = put /2;
        }
    }
    for(int temp = 0 ; temp < time ; temp++)
        printf("%d\n",arr[temp]);
    return 0;
}
```

## 数论相关

**题目**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221006162716010.png" alt="image-20221006162716010" style="zoom:80%;" />

**思路**



**代码**

```c
#include<stdio.h>
int main()
{
    long long int n,k,s,time;
    scanf("%lld",&time);
    int count[time];
    for (int temp = 0 ; temp < time ; temp++)
        count[temp] = 0;
    for(int temp = 0 ; temp < time ; temp++){
        scanf("%lld %lld %lld",&n,&k,&s);
        long long int min = ((1+k)*k) / 2;
        long long int max = ((2*n - k +1)* k) / 2;
        if(s >= min && s <= max)
            count[temp] = 1;
    }
    for(int temp = 0 ; temp <time ; temp ++){
        if(count[temp])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
```

## 高精度问题

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221021220029440.png" alt="image-20221021220029440" style="zoom:80%;" />



<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221021220043913.png" alt="image-20221021220043913" style="zoom:80%;" />



```c
#include <stdio.h>
#include <stdlib.h>
#define SIZE   51
int main(void)
{
int data[SIZE] = {0};/* 存储50位数，元素全部初始化为0，不使用data[0] */
int index = 1;        /* 数组元素个数，表示阶乘值的位数 */
int n;                  /* 准备计算的阶乘中的最大数 */
int i, j, k;
data[1] = 1;           /* 初始化，令1！=1 */
//printf("Input n:");
scanf("%d", &n);
for (i=1; i<=n; i++)   /* 计算从1到n之间所有数的阶乘值 */
{
	for (j=1; j<=index; j++) /* 计算阶乘i! */
	{
		data[j] = data[j] * i;/* 每一位数字都乘以i */
	}
	for (k=1; k<index; k++)
	{
		if (data[k] >= 10) /* 阶乘值的每位数字应在0~9之内，若>=10，则进位 */
		{
			data[k+1] = data[k+1] + data[k]/10; /* 当前位向前进位 */
			data[k] = data[k] % 10;  /* 进位之后的值 */
		}
	}
	/* 单独处理最高位，若计算之后的最高位>=10，则位数index加1 */
	while (data[index] >= 10 && index <= SIZE-1)
	{
		data[index+1] = data[index] / 10; /* 向最高位进位 */
		data[index] = data[index] % 10;    /* 进位之后的值 */
		index++;                               /* 位数index加1 */
	}
	if (index <= SIZE-1)        /* 检验数组是否溢出，若未溢出，则打印阶乘值 */
	{
		printf("%d! = ", i);
		for (j=index; j>0; j--) /* 从最高位开始打印每一位阶乘值 */
		{
			printf("%d", data[j]);
		}
		printf("\n");
	}
	else                            /* 若大于50，数组溢出，则提示错误信息 */
	{
		printf("Over flow!\n");
		exit(1);
	}
}
return 0;
}
```



我的代码

```c
#include<stdio.h>
int main()
{
    int remem[10000] = {0};
    int number;
    scanf("%d",&number);
    remem[0] = 1;
    int index = 0;
    for(int temp = 1 ; temp <=  number ; temp++){
        int up = 0;
        for(int step = 0 ; step <= index ; step++){
            int count = remem[step] * temp + up;
            remem[step] = count % 10;
            up = count / 10;
            if(step == index && up){
                while(up){
                    index++;
                    remem[index] = up % 10;
                    up /= 10;
                }
                break;
            }
        }
        printf("%d! = ",temp);
        for(int done = index ; done >= 0 ; done--){
            printf("%d",remem[done]);
        }
        printf("\n");
    }
}
```



## 均分问题

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221024102418245.png" alt="image-20221024102418245" style="zoom:80%;" />



```c
#include<stdio.h>
int main()
{
    long long int a , b;
    scanf("%lld %lld", &a,&b);
    b= b % 2;
    if(b && a >= 3 && (a-3)%2)
        printf("NO");
    else if(b && a < 3)
        printf("NO");
    else if(!b && a%2)
        printf("NO");
    else if(!b && !(a % 2))
        printf("YES");
    else if(b && !((a-3) % 2))
        printf("YES");
    return 0;
}
```





## C语言自我小tip

## 有意思的题

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221030193625738.png" alt="image-20221030193625738" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221030193642269.png" alt="image-20221030193642269" style="zoom:80%;" />



<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221030193719853.png" alt="image-20221030193719853" style="zoom:80%;" />

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int length,number;
    cin >> length >> number;
    int Max = 0 , Min = 0;
    for(int temp = 0 ; temp < number ; temp++){
        int index ;
        cin >> index;
        Max = max(Max , max(index , length - index + 1));
        Min = max(Min , min(index , length - index + 1));
    }
    cout << Min <<" " <<Max;
}
```



**第二次用递归，写的跟屎一样**

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221030205054586.png" alt="image-20221030205054586" style="zoom:80%;" />

```c++
#include<bits/stdc++.h>
int Day_down(int ,int ,int);
int Day_num(int,int,int);
int Day_up(int ,int,int);
using namespace std;
int main()
{
    int fir_up , num , fin ,target;
    cin >> fir_up >> num >> fin >>target;
    if(target == 1){
        cout << fir_up;
        return 0;
    }
    int flag = -1;
    for(int temp = 0 ; temp <= 1000000 ; temp++){
        if(Day_num(num - 1 , fir_up , temp) == fin){
            flag = temp;
            break;
        }
    }
    cout << Day_num(target , fir_up ,flag);
}

int Day_num(int day , int init ,int first){
    if(day == 1 || day == 2) return init;
    else
        return Day_num(day - 1 , init , first) + Day_up(day , init , first) - Day_down(day , init , first);
}

int Day_up(int day, int init , int first){
    if(day == 1) return init;
    else if(day == 2) return first;
    else
        return Day_up(day - 1 , init , first) + Day_up(day - 2 , init , first);
}

int Day_down(int day , int init , int first){
    if(day == 1) return 0;
    else if(day == 2) return first;
    else
        return Day_up(day - 1 , init ,first);
}
```



## 一些难题

### first：天空即为极限

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221010232037659.png" alt="image-20221010232037659" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221010232054590.png" alt="image-20221010232054590" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221010232112263.png" alt="image-20221010232112263" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221010232122571.png" alt="image-20221010232122571" style="zoom:80%;" />

```c
int count_distance(int x1, int y1, int x2, int y2){
    int Max_x = x1 >= x2 ? x1 : x2;
    int Min_x = x1 <= x2 ? x1 : x2;
    int Max_y = y1 <= y2 ? y2 : y1;
    int Min_y = y1 >= y2 ? y2 : y1;
    int distance = Max_x - Min_x + Max_y - Min_y;
    return distance;
}
int judge_dir(int x1,int y1, int x2, int y2){
    int Min =10000000000000,out = 0;
    int arr[8];
    arr[0] = count_distance(x1-1 , y1+1 ,x2 ,y2);
    arr[1] = count_distance(x1-1 , y1 ,x2,y2);
    arr[2] = count_distance(x1-1,y1-1,x2,y2);
    arr[3] = count_distance(x1,y1-1 ,x2,y2);
    arr[4] = count_distance(x1+1,y1-1,x2,y2);
    arr[5] = count_distance(x1+1,y1,x2,y2);
    arr[6] = count_distance(x1+1,y1+1,x2,y2);
    arr[7] = count_distance(x1,y1+1,x2,y2);
    for(int temp = 0 ; temp < 8 ; temp++){
        out = arr[temp] <= Min ? temp+1 : out;
        Min = arr[temp] <= Min ? arr[temp] : Min;
    }
    return out;
}
int X_change(int x , int judge){
    if(judge == 1 || judge == 2 || judge == 3)
        return x-1;
    else if(judge == 4 || judge == 8)
        return x;
    else
        return x+1;
}
int Y_change(int y , int judge){
    if(judge == 1 || judge == 7 || judge == 8)
        return y+1;
    else if(judge == 2 || judge == 6)
        return y;
    else
        return y-1;
}
#include<stdio.h>
# include<string.h>
int main()
{
//    输入基本信息
    int time;   //这是总共我要判断情况的数目
    scanf("%d",&time);
    char ans[time][1000];  //用来储存答案
    for(int done = 0 ; done < time ; done ++){    //循环time次
        int totel_time , fir_dir , fir_x , fir_y,dir_change_num;   //总共的时间 ， 第一次的方向 ，第一次的 x ， y 坐标  ，方向更改的次数
        scanf("%d %d %d %d %d",&totel_time  , &dir_change_num , &fir_dir , &fir_x , &fir_y);  //输入
        int member_t_d[dir_change_num][2];    //建立数组来储存方向改变时间和具体方向   ，0用来储存时间 ，1用来储存方向
        for(int temp = 0 ; temp < dir_change_num ; temp++)   //循环之前输入方向更改的次数，存入数组
            scanf("%d %d",&member_t_d[temp][0] , &member_t_d[temp][1]);
        int boss;  //幻翼的数目
        scanf("%d",&boss);
        int boss_info[boss][5];
        //关于幻翼的五个信息   0：x坐标  ，1：y坐标  ，2 ：血量  ，3：是否下一秒可以移动  ， 4 ：是否被启动
        for(int temp = 0 ; temp < boss ; temp++){
            scanf("%d %d",&boss_info[temp][0] , &boss_info[temp][1]);
            boss_info[temp][2] = 20;
            boss_info[temp][3] = 0;   //默认启动不可以移动
            boss_info[temp][4] = 0;  //默认没有 被启动
        }
//        正式开始判断
        int done_time = 0, made_injure = 0 , live = 20 , man_inj = 7 , boss_inj = 3;
        //变量意义分别是已经经历的秒数  ， 主角造成的伤害  ， 主角的血量  ，主角的伤害  ， 幻翼的伤害
        int dir_x = fir_x , dir_y = fir_y,dir = fir_dir,judge_win = 1;
        //变量意义分别是,主角的x坐标=初始x坐标,y坐标=初始y坐标，判断是否主角需要扣血,主角运动方向=初始方向,判断是否该结束游戏
        for(; done_time <= totel_time ; done_time++){//循环总时间秒数
            int judge_man_down = 0;
            for(int temp = 0 ; temp < boss ; temp++){   //依次判断每个幻翼的情况
                int distence = count_distance(dir_x , dir_y , boss_info[temp][0] , boss_info[temp][1]);  
                //算出主角与某一幻翼的距离
                if(distence <= 64 )   // <= 64 启动该幻翼
                    boss_info[temp][4] = 1;
                if(boss_info[temp][4] && boss_info[temp][3] && boss_info[temp][2] && !(boss_info[temp][0] == dir_x && boss_info[temp][1] == dir_y)){
                    //幻翼启动  ， 幻翼下一秒可以移动  ， 血量不为0   , 坐标不与主角重合
                    int dir = judge_dir(boss_info[temp][0], boss_info[temp][1] , dir_x , dir_y);  
                    //找出最佳方向
                    boss_info[temp][0] = X_change(boss_info[temp][0] , dir);  //改变x与y坐标
                    boss_info[temp][1] = Y_change(boss_info[temp][1] , dir);
                }
                if(!(boss_info[temp][3]))  //如果该幻翼在这一秒不能移动，那么让它下一秒移动
                    boss_info[temp][3] = 1;
                if(boss_info[temp][0] == dir_x && boss_info[temp][1] == dir_y && boss_info[temp][2] > 0){
                    //如果幻翼与主角坐标一样且幻翼血量> 0
                    judge_man_down = 1;   //判断主角将会受伤
                    int down;     //判断扣除幻翼血量
                    if(boss_info[temp][2] - man_inj >= 0)  //若按伤害量扣除后>=0 ， 那么计算伤害量直接用主角伤害
                        down = man_inj;
                    else // 如果扣除后 < 0 ，伤害量等于血量
                        down = boss_info[temp][2];
                    boss_info[temp][2] -= down;
                    made_injure += down;
                    boss_info[temp][3] = 0;  //使其下一秒不能再移动
                }
            }
            if(judge_man_down){  //如果主角要受伤
                live -= boss_inj;  //主角生命扣除
            }
            if(live <= 0){   //主角生命<= 0，即死亡
                sprintf(ans[done] , "lose %d" , done_time); //死亡时间写入记录答案的数组中
                judge_win = 0;  //  告诉之后的语句，主角死了
                break; //结束整个done的大循环
            }
            // 判断之后主角往那个方向移动
            for(int temp = 0 ; temp < dir_change_num ; temp++){ //遍历之前储存的改变方向数组
                if(done_time+1 == member_t_d[temp][0]){  //如果改变时间与当前下一秒重合，更改方向
                    dir = member_t_d[temp][1];
                    break; //不在遍历了
                }
            }
            dir_x = X_change(dir_x , dir);//开始改变
            dir_y = Y_change(dir_y , dir);
        }
        if(judge_win){  //如果total_time结束没死，写入成功
            sprintf(ans[done] ,"survive %d",made_injure);
        }
    }
    for(int temp = 0 ; temp < time ; temp ++){
        printf("%s\n",ans[temp]);
    }
    return 0;
}
```

