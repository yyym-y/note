# SLT容器

## vector

使用vector必须包含头文件< vector >

```c++
#include<vector>
```

### **建立一个vector**

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
struct Test{
  int first;
  int second;
};
int main()
{
    int arr[5] = {1,2,3,4,5};
	vector<int>vec1;  //vector<数据类型>变量名
    vector<struct Test>vec2;  //数据类型可以是结构体
    vector<int>vec3{1,2,3,4,5,6}; //创建vector的同时给其赋值
    vector<int>vec4(5 , 1); //vector<数据类型>变量名（vector大小  ， 初始值）
    vector<int>vec5(arr+1 , arr+4) ;//vector<数据类型>变量名（数组地址1，数组地址2） ，复制[数组地址1，数组地址2）
    vector<int>vec6 = vec5;
    vector<int>vec7(vec5);  //和上面的一样，直接复制
}
```

### **vector传引用**

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
void Print_vector(vector<int>& arr){  //vector在传引用的时候参数类型是vector<数据类型>&
    for(auto temp : arr)
        cout << temp << " ";
}
int main()
{
    vector<int>vec1 = {1,2,3,4,5,6};
    auto& a_try = vec1; //当然也可以使用auto
    Print_vector(a_try);
}
```

### **vector元素插入操作**

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
void Print_vector(auto& arr){
    for(auto temp : arr)
        cout << temp << " ";
    cout << endl;
}
int main()
{
    struct Test stc = {8,9};
    vector<int>vec1 = {1,2,3,4,5,6};
    vector<int>vec2 = {10,20,30,40,50};
    auto& a_try = vec1;
    vec1.push_back(9);  // 在vector后面插入元素   vector名.push_back(要插入的元素)；
    Print_vector(a_try);
    vec1.insert(vec1.begin() + 2 , 11);  // vector名.insert(迭代器坐标 ， 插入的元素)
    //迭代器相当于指针，vector名.begin()是获得首元素的迭代器 ， vector名.end()是获得末尾元素的迭代器
    Print_vector(a_try);
    vec1.insert(vec1.begin() + 2 , 5 , 0);  // 在vec1.begin() + 2 位置插入5个0
    Print_vector(a_try);
    vec1.insert(vec1.begin() + 2 , vec2.begin() + 1 , vec2.begin() + 4); 
    //在vec1.begin()位置插入vec2.begin()+1到vec2.begin() + 4的元素 [ vec2.begin() + 1 , vec.begin() + 4)
    Print_vector(a_try);
}
```

结果为

```c++
1 2 3 4 5 6 9
1 2 11 3 4 5 6 9
1 2 0 0 0 0 0 11 3 4 5 6 9
1 2 20 30 40 0 0 0 0 0 11 3 4 5 6 9
```



### **vector元素删除操作**

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
void Print_vector(vector<int>& arr){
    for(auto temp : arr)
        cout << temp <<" ";
    cout << endl;
}
int main()
{
    vector<int>vec1 = {1,2,3,4,5,6,7};
    auto& poin = vec1;
    Print_vector(poin);
    vec1.pop_back();  // pop_backd代表删除vector最后一个元素
    Print_vector(poin);
    vec1.erase(vec1.begin()); //erase(指定要删除的迭代器)
    Print_vector(poin);
    vec1.erase(vec1.end() - 1); // 如果是用erase删除最后一个元素的话要用end()-1
    /*
    end()返回的是最后一个位置的迭代器，但是插入会在迭代器的后一个插入，删除也是在迭代器后一个删除，但是后一个实际上是没有元素		的，所以不可以
    */
    Print_vector(poin);
    vec1.erase(vec1.begin() + 2 , vec1.end() - 1); //删除迭代器1-迭代器2 ，[迭代器1 ， 迭代器2)
    Print_vector(poin);
    vec1.clear(); //直接清空vector
    Print_vector(poin);
}
```

结果为

```c++
1 2 3 4 5 6 7
1 2 3 4 5 6
2 3 4 5 6
2 3 4 5
2 3 5
2 3
```



### **vector其他操作**

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
void Print_vector(vector<int>& arr){
    for(auto temp : arr)
        cout << temp <<" ";
    cout << endl;
}
int main()
{
    vector<int>vec = {1,2,3,4,5,6,7};
    vector<int>vec2 = {10,20,30,40,50,60};
    auto& poin = vec;
    auto& poin2 = vec2;
    cout << vec.empty() <<endl; //判断vector是否为空
    cout << vec.size() << endl; //当前vector的大小
    cout << vec.max_size() << endl; //vector所可以容纳的最大值
    cout << vec.capacity() <<endl;
    vec.erase(vec.begin());
    Print_vector(poin);
    cout << vec.capacity() << endl; //删除元素后，其实vector的容量没有发生变化
    int& a = vec.at(2); //下标从0开始
    cout << a << endl;  //获得相应位置的传引用
    int& last = vec.back(); //获得最后一个元素的传引用
    int& first = vec.front(); //获得第一个元素的传引用
    cout << first <<"  " << last << endl;
    vec.assign(4 , 0); //重置vector 并为其重新赋值，之前的的将会消失
    Print_vector(poin);
    vec.assign(vec2.begin() + 1 , vec2.end());
    Print_vector(poin);
    vec.assign(vec.begin() + 1 , vec.end() - 1);  //可以用这个方法留取一段连续的值
    Print_vector(poin);
    vec.swap(vec2); //交换两个vector的值
    Print_vector(poin);
    Print_vector(poin2);
    reverse(vec.begin() , vec.end() - 2); //将两个vec.begin() 到 vec.end() 的值翻转过来
    Print_vector(poin);
    sort(vec.begin() , vec.end()); //对vector进行排序，默认是从小到大
    Print_vector(poin);
    sort(vec.rbegin() , vec.rend()); //有两种方法可以实现从小到大，1.使用rbigin 和 rend
    Print_vector(poin);
    sort(vec.begin() , vec.end() ,[ ](int x , int y) {return x > y;}); //2.自己创建一个匿名函数
    Print_vector(poin);
}
```

结果为

```
0
7
4611686018427387903
7
2 3 4 5 6 7
7
4
2  7
0 0 0 0
20 30 40 50 60
30 40 50
10 20 30 40 50 60
30 40 50
40 30 20 10 50 60
10 20 30 40 50 60
60 50 40 30 20 10
60 50 40 30 20 10
```





## pair

pair是将2个数据组合成一组数据，当需要这样的需求时就可以使用pair,pair的实现是一个结构体

可以将pair理解为是一个只有两个元素的结构体

### 建立一个pair

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main()
{
    pair <int , int> test1 = {3,4}; //pair<数据类型1 ， 数据类型2> 变量名 = {值1 ， 值2}
    pair <int ,char> test2(5 , 'a'); //pair<数据类型1 ， 数据类型2> 变量名 (值1 ， 值2) 注意这里没有等号
    pair <int , vector<int>> test3;  //数据类型可以是其他STL ，可以不提前赋值
    pair <int ,int >test4 = make_pair(1 , 2); //亦可以多此一举的使用make_pair
    make_pair(3,4); //这通常情况下是使用在函数返回值上
    pair<int , int> test5;
    test5 = test1; //也可以用另一个pair来给当前pair赋值
}
```



### pair的函数操作

```c++
#include<bits/stdc++.h>
#include<vector>
using namespace std;
auto Test_Pair(void){
    int a = 10 , b = 20;
    return make_pair(a, b); //将函数的返回值用pair来封装
}
int main()
{
    int first_element , second_element;
    tie(first_element , second_element) = Test_Pair();  //使用tie来接收pair顺便进行拆包 ，某个值不想要要用ignore占位
    cout << first_element << "   " << second_element;
    return 0;
}
```

结果为

```c++
10   20
```



### pair的其他操作

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    pair<int , int >test1 = {3 , 4};
    pair<int , int>test2(5,6);
    int first_ele,second_ele;
    first_ele = test1.first; // 变量名.begin 获取第一个元素
    second_ele = test1.second; //变量名.end 获取第二个元素
    cout << first_ele << "  " << second_ele;
    return 0;
}
```

结果为

```c++
3  4
```



## string

### 建立一个string

````c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string sample = "0123456789";
    char arr[] = "a_string_in_C_menager";
    cout << sample << endl;
    string test1(sample); //定义一个string并将内容于sample一样
    cout << test1 << endl;
    string test2(sample , 5); //将string初始化为sample从下标为5的地方开始的内容
    cout << test2 <<endl;
    string test3(sample , 3 , 2); //第三个参数代表最多可以拷贝多少个字符
    cout << test3 << endl;
    string test4(sample ,7 , 4); // 如果超出字符串范围，则取到最后一个字符为止
    cout << test4 << endl;
    string test5(arr); //将c风格的字符串转化为string
    cout << test5 << endl;
    string test6(arr , 10); //取前10个字符
    cout << test6 <<endl;
    string test7(5 , 'a'); //将内容初始化为5个a
    cout << test7 << endl;
}
````

结果为

```
0123456789
0123456789
56789
34
789
a_string_in_C_menager
a_string_i
aaaaa
```



### string基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string sample1 = "the_first_string_/";
    string sample2 = "the_second_string_\\" ;
    string space;
    space = "put"; //直接给一个string赋值
    cout << space <<endl;
    space.assign("rput"); //将string的值重置为assign里面的值
    cout << space << endl;
    space = sample1 + sample2; //将string的内容设为两个字符串拼接后的内容
    cout << space << endl;
    sample1.swap(sample2); //交换两个string的内容
    cout << "sample1 = " << sample1  << "   sample2 = " <<sample2 <<endl;
    space += 'p'; // space.push_back('p')(不推荐）在后面加上一个字符
    cout << space << endl;
    space.insert(0 , "must_a_string_//////"); //在下标为0 的地方插入一个字符串 ！！必须为字符串
    cout << space << endl;
    space.erase(0 , 14);  //删除string中下标由0-14的内容
    cout << space <<endl;
    cout << count(space.begin(), space.end(), '/') << endl;  //计算某某字符在string出现的次数，前两个参数为迭代器
    cout << count(space.begin() , space.begin() + 3 , '/') <<endl; 
    //xxx.begin() , xxx.end()分别获得string的前后迭代器
    cout << (sample1 == sample2) <<endl; //判断两个字符串是否相等
    cout << (sample1 > sample2) << endl; //按照字典序进行比较
    cout << (sample1 <= sample2) <<endl;
    cout << space.empty() <<endl;//判断字符串是否为空
    cout << sample1.size() << endl; //获取字符串的长度，下文一样
    cout << sample1.length() << endl;
    space.clear(); //清空字符串
    cout << space <<endl;
    space = "01_23_45_67";
    cout <<space.find('_') << endl;  //返回第一个要寻找字符的下标
    cout << space.find('_' , 4) << endl; //返回从指定位置开始的第一个要寻找字符的下标
	cout << space[3] << endl; //用[]访问字符，可修改
    cout <<space.at(6) << endl; //于[]类似，越界会报错，效率不如[]
    string temp = space.substr(2,2); //xxx.substr(begin , len) 返回[begin ， begin + len)的子串
    cout << temp << endl;
    temp = space.substr(2); //没有第二个参数默认取到最后一个
    cout << temp <<endl;
    string used = "abc";
    for(auto temp : used) //用这种方法获得string的每个元素
        cout << temp << endl;
}
```

结果为

```
put
rput
the_first_string_/the_second_string_\
sample1 = the_second_string_\   sample2 = the_first_string_/
the_first_string_/the_second_string_\p
must_a_string_//////the_first_string_/the_second_string_\p
//////the_first_string_/the_second_string_\p
7
3
0
1
0
0
19
19

2
5
2
4
_2
_23_45_67
a
b
c
```



## tuple

tuple于pair十分类似

### tuple操作

```c++
#include<bits/stdc++.h>
using namespace std;
auto Test_return(void){
    int first = 1;
    int second = 2;
    char third = 'z';
    return make_tuple(first , second , third); //使用make_tuple将返回值包装为tuple供后续使用
}
int main()
{
    tuple<int,int,char>sample1 = {1,2,'a'};  //创建一个tuple ，不用那么花里胡哨了
    tuple<int ,int , int, int> sample2 = {1,2,3,4}; //tuple内的元素是三个及三个以上
    tuple<int , int, int,int>sample3 = {6,7,8,9};
    int first,second;
    char third;
    tie(first , second , third) = Test_return(); //依旧使用tie进行接包
    cout << first << "  " << second << "  " << third << endl;
    tie(second , first , ignore) = Test_return(); //如果不想使用某个值用ignore占位
    cout << first << "  " << second << endl;
    cout << get<0>(sample1) << "  " << get<3>(sample2) << endl; //使用get<下标>(tuple名)来访问元素
    sample2.swap(sample3); //交换两个tuple的值，注意类型必须完全一样
    auto sample4 =tuple_cat(sample1 , sample2); //使用tuple_cat拼接两个tuple ，最好使用auto
    cout << (sample2 == sample3) << endl; //tuple之间可以比较，注意两个tuple元素个数要一样，要具有可比性
    //注意，tuple不具有迭代器特性，所以for-echo不可以使用
}
```

结果为

```c++
1  2  z
2  1
1  4
0
```



## stack

stack即为栈，符合FILO原则(first in last out)

### stack基本操作

```c++
#include<bits/stdc++.h>
#include<stack>
using namespace std;
int main()
{
    stack<int> sample1;
    sample1.push(6); //将元素放入栈
    sample1.push(2);
    sample1.pop(); //将元素取出栈
    cout << sample1.top() << endl; //获得栈最顶部的值
    cout << sample1.size() << endl; // 获得栈的元素个数
    cout << (sample1.empty()) <<endl; // 判断栈是否为空
}
// stack没有迭代器，所以不可以用for-each遍历
```

结果为

```c++
6
1
0
```



## queue

queue即队列，符合FIFO原则 (first in first out)

### queue基本操作

```c++
#include<bits/stdc++.h>
#include<queue>
using namespace std;
int main()
{
    queue<int>sample; //定义一个queue ，不能在初始化的时候赋值
    sample.push(3); //使用push在末尾放入一个元素
    cout << sample.empty() << endl; //判断queue是否为空
    sample.push(4);
    cout << sample.front() << endl; //查看队列第一个元素
    cout << sample.back() << endl;  //查看队列最后一个元素
    cout << sample.size() << endl;  //查看队列的大小
    sample.pop(); //将queue第一个元素删除
    //queue没有迭代器
    //队列本身就是一种先进先出的限制性数据结构，因此只能通过 front（）来访问队首元素，或是通过 back（）来访问队尾元素。
}
```

结果为

```c++
0
3
4
2
```



## map



map中所有元素都是pair

pair中第一个元素为key（键值），起到索引作用，第二个元素为value（实值）

所有元素都会根据元素的键值自动排序

**字典**

可以将map的键理解为数组的下标，即从int类型扩大到了全体类型map基本操作

### map基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
void Print_map(auto put){
    for(auto temp : put)
        cout << "<" << temp.first << "," << temp.second << "> ";
    cout << endl;
}
int main()
{
    map<string , int> sample1; //建立一个字典，标识符是字符串
    map<int , string> sample2;
    map<int ,string> swap_use; 
    swap_use.insert(make_pair(10 , "swap_use_only")); //插入一个元素，位置是插入的标识符在标识符中的字典序
    sample1.insert(pair<string , int>("first" , 1));
    sample1.insert(make_pair("forth" , 4));
    sample1.insert(make_pair("fifth" , 5));
    sample1.insert(make_pair("sixth" , 6));
    sample1.insert(make_pair("siventh" , 7));
    Print_map(sample1);
    sample1.insert(make_pair("siventh" , 8));
    Print_map(sample1);
    sample1["siventh"] = 8;  //和数组访问一样，只是数组是以下标查找，而map是以传入的标识符为依据
    Print_map(sample1);
    sample2[2] = "two"; //也可以这样快速添加元素，map名[标识符] = 内容
    sample2[1] = "one";
    Print_map(sample2);
    cout << sample1.count("second") <<endl; // 是否存在该标识符 ， 返回值为0 或 1
    cout <<sample1.count("fifth") <<endl; // 如果没有找到返回0，找到了就返回1
    sample2.swap(swap_use); // 交换两个map的值
    Print_map(swap_use);
    Print_map(sample2);
    cout << sample1.size() << endl; // size获取map中的元素个数
    cout << sample1.empty() << endl; //判断map是否为空
    cout << sample1.erase("first") << endl; // 删除“first”标识符以及内容，删除成功返回1
    Print_map(sample1);
    cout << sample1.erase("first") << endl; //删除失败返回0
    sample1.erase(sample1.find("forth"), sample1.end()); //删除一段区间，依旧是左闭右开
    Print_map(sample1);
    sample1.erase(sample1.find("fifth")); // find会返回那个元素的迭代器
    Print_map(sample1);
    // sample1.erase(sample1.find("askl")); 不可以删除一个本来就没有的元素
}
```

结果为

```c++
<fifth,5> <first,1> <forth,4> <siventh,7> <sixth,6>
<fifth,5> <first,1> <forth,4> <siventh,7> <sixth,6>
<fifth,5> <first,1> <forth,4> <siventh,8> <sixth,6>
<1,one> <2,two>
0
1
<1,one> <2,two>
<10,swap_use_only>
5
0
1
<fifth,5> <forth,4> <siventh,8> <sixth,6>
0
<fifth,5>


```

  

## set

注意：

1、set中的元素都是排好序的 (默认从小到大)

2、set集合中没有重复的元素

### set基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
void Print_set(auto sample){
    for(auto temp : sample)
        cout << temp <<" ";
    cout << endl;
}
int main()
{
    set<int> sample1; //set与vector的定义类似
    set<int> test[10];//
    for(int temp = 0 ; temp < 10 ; temp ++)
        sample1.insert(temp);
    Print_set(sample1);
    sample1.erase(sample1.find(1));
    Print_set(sample1);
    sample1.erase(sample1.find(3) , sample1.find(5));
    Print_set(sample1);
    cout << sample1.size() << endl;
    for(int temp = 0 ; temp < 20 ; temp+=2)
        sample1.insert(temp);
    Print_set(sample1);
    sample1.erase(sample1.begin());
    Print_set(sample1);
    cout << sample1.count(5) <<endl;
    cout << sample1.count(1000) <<endl;
    sample1.clear();
    Print_set(sample1);
    cout <<sample1.empty() << endl;
}
```

结果为

```c++
0 1 2 3 4 5 6 7 8 9
0 2 3 4 5 6 7 8 9
0 2 5 6 7 8 9
7
0 2 4 5 6 7 8 9 10 12 14 16 18
2 4 5 6 7 8 9 10 12 14 16 18
1
0

1

```



## list

### list基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
void Print_list(auto list_){
    for(auto temp : list_)
        cout << temp << " ";
    cout <<endl;
}
int main()
{
    list<int>sample(3 , 4); //list的建立方式与vector相似
    Print_list(sample);
    sample.push_back(10); // 在list的末尾添加元素
    sample.push_front(7); // 在list的前面添加元素
    Print_list(sample);
    sample.pop_back(); //删除最后一个元素
    sample.pop_front(); //删除第一个元素
    Print_list(sample);
    sample.insert(++sample.begin(), 5); //在指定迭代器位置插入元素
    Print_list(sample);
    //sample.insert(sample.begin() + 2, 5); 注意list的迭代器只可以进行++ 或 -- 操作 ，+3等操作不支持
    auto sam = sample.begin();
    for(int temp = 0 ; temp < 2 ; temp++) sam++;
    sample.insert(sam , 8);
    Print_list(sample);
    sample.erase(--sam); //注意迭代器失效
    Print_list(sample);
    cout << sample.size() << endl; //输出list的大小
    cout << sample.empty() << endl; //判断list是否为空
    sample.sort(); //排序，注意只能使用list下的sort函数，一般的不支持
    Print_list(sample);
    sample.sort([](int a , int b){return a > b;}); //可以重写排序方法
    Print_list(sample);
    sample.reverse(); //将list翻转
    Print_list(sample);
    list<int>sample2(2,1);
    sample.swap(sample2); //交换两个list内容
    Print_list(sample);
    sample.clear(); //清空list
    return 0;
}
```

结果为

```c++
4 4 4
7 4 4 4 10
4 4 4
4 5 4 4
4 5 8 4 4
4 5 4 4
4
0
4 4 4 5
5 4 4 4
4 4 4 5
1 1
```



## deque

Vector容器是单向开口的连续内存空间，deque 则是一种双向开口的连续线性空间。所谓的双向开口，意思是可以在头尾两端分别做元素的插入和删除操作，当然，vector 容器也可以在头尾两端插入元素，但是在其头部操作效率奇差，无法被接受。

理解为队列与栈的结合体

### deque的基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
void Print_deque(auto deque_){
    for(auto temp : deque_)
        cout << temp << " ";
    cout << endl;
}
int main()
{
    deque<int>sample(5,1); //建立方式与其他STL一致
    Print_deque(sample);
    deque<int>sample2(sample.begin()+ 2 , sample.begin() + 4); //如果是迭代器则内容是其区间内的内容
    Print_deque(sample2);
    cout << sample.empty() << endl; //是否为空
    cout << sample.size() << endl;//大小
    sample.push_back(10); //在末尾插入元素
    sample.push_front(11); // 在最前面插入元素
    Print_deque(sample);
    cout << sample.front() << endl; //获取第一个元素
    cout << sample.back() <<endl; //获取最后一个元素
    cout << sample.at(5) << endl; //返回指定下标的元素
    sample.pop_back(); //删除最后一个元素
    sample.pop_front(); //删除第一个元素
    Print_deque(sample);
    sample.insert(sample.begin() + 2, 10); //在指定位置插入元素
    Print_deque(sample);
    sample.insert(sample.begin() + 3 ,  3 ,5); // 在指定位置插入相等的几个元素
    Print_deque(sample);
    sample.erase(sample.begin() + 3); //删除指定位置元素
    Print_deque(sample);
    sort(sample.begin() , sample.end()); //sort ， reverse ， swap 与其他一致
    Print_deque(sample);
    sample.clear();
}
```

结果为

```c++
1 1 1 1 1
1 1
0
5
11 1 1 1 1 1 10
11
10
1
1 1 1 1 1
1 1 10 1 1 1
1 1 10 5 5 5 1 1 1
1 1 10 5 5 1 1 1
1 1 1 1 1 5 5 10

```



## bitset

`bitset` 就相当于一个 只能存储二进制，也就是 0 和 1 的 bool 数组

如果直接用 bool 数组存储二进制每一位的话，n 位存储复杂度为 O(n)，但是用 `bitset` 的话复杂度会减少到 O(n/32)。

所以一般用二进制状态压缩时就会用 `bitset`

### bitset基本操作

```c++
#include<bits/stdc++.h>
using namespace std;
void Print_bitset(auto put){
    for(int temp = 0 ; temp < put.size() ; temp++)
        cout <<put[temp] << " ";
    cout << endl;
}
signed main()
{
    bitset<10>sample; //bitset<长度>名字 初始全部是0 长度不能是变量 不可以sample = “1010...”
    Print_bitset(sample);
    sample[0] = 1;
    Print_bitset(sample);
    cout << sample <<endl; //直接cout是逆序
    sample.flip(5); //将下标为5的地方取反
    Print_bitset(sample);
    sample.flip(); // 全部取反
    Print_bitset(sample);
    cout <<sample.count() << endl; //统计1的个数
    cout << sample.any() <<endl; //判断是否有1
    cout <<sample.none() <<endl; //判断是否没1
    sample.reset(); //全部设为0
    Print_bitset(sample);
    sample.set(); //全部设为1
    Print_bitset(sample);
    bitset<10>sample2;
    sample &= sample2; // 可以与位运算结合
    Print_bitset(sample);
    sample^=sample2;
    Print_bitset(sample);
}
```

