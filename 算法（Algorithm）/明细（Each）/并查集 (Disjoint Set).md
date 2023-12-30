# 并查集 (Disjoint Set)

[TOC]



## 基础并查集

并查集是用来处理不相交集合的合并及查询问题

可以用来判断一个森林里到底有几颗树，某个结点到底从属于那颗树。

通俗点理解就是讲一堆元素归类，判断到底他们之间有什么关系，或者查询他们之间有什么共同关系

### 并查集的基本操作

##### 并，查操作

并查集一般用数组来制造

pre[] 即是一个并查集

pre[i]是元素i的前驱结点

在最初的时候pre[i]是等于i本身的

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211170407948.png" alt="image-20221211170407948" style="zoom:80%;" />

然后我们给予关系

让（A，B）为一组

则：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211170511153.png" alt="image-20221211170511153" style="zoom:80%;" />

这个时候修改A的前驱结点为B

之后让（A，C）为一组

具体过程是：

A访问他的前驱结点B，发现A的前驱结点不等于自身，那么就搜索A的前驱结点，即B，发现B的前驱结点是本身，那么将B的前驱指向C

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211170822958.png" alt="image-20221211170822958" style="zoom:80%;" />

通过以上原理，我们可以写出两个函数对应并和查，分别是join_set， find_set

当然我们要先初始化

```c++
#include<bits/stdc++.h>
using namespace std;
#define Max 10
int pre[Max];

void Init_set(){
    for(int temp = 1 ; temp < Max ; temp++) //方便计数，从一开始
        pre[temp] = temp;
}
```



查找操作（find_set）

```c++
//这是个粗糙的版本
int find_set(int num){
    if(pre[num] != num){  // 如果前驱结点不等于自身，那么这个肯定不是开头的那个
        int root;
        root = find_set(pre[num]); // 找到开头那个
        return root;
    }
    return num;
}
//高端版本
int find_set(int num){
    return pre[num] == num ? num : find_set(pre[num]);
}
```



合并操作（join_set）

```c++
void join_set(int num1, int num2){
    // 找到两个元素的根节点
    int root1 = find_set(num1); 
    int root2 = find_set(num2);
    if(root1 != root2) //如果根节点不一样，说明他们不在一个集合里
        pre[root1] = pre[root2]; // 让某一个的根节点等于另一个
}
```



测试一下

```c++
signed main()
{
    Init_set();
    join_set(1,2);
    join_set(1,3);
    for(int temp1 = 1 ; temp1 < Max ; temp1++)
        cout << temp1 << "  ";
    cout << "\n";
    for(int temp1 = 1 ; temp1 < Max ; temp1++)
        cout << pre[temp1] << "  ";
    cout << "\n";
}
/*
1  2  3  4  5  6  7  8  9
2  3  3  4  5  6  7  8  9
*/
```



##### 优化操作

如果出现如图所示的情况，那么树将退化为链表，那么时间复杂度将会变为O（n），尤其是查询操作的时候

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211173043394.png" alt="image-20221211173043394" style="zoom:80%;" />

那么我们的优化将在合并的时候进行

两种合并方法：

**优化一（不常使用）**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211174208956.png" alt="image-20221211174208956" style="zoom:80%;" />

将矮树合并到高树中，这样查询方便

此时需要引入一个新的数组weight来储存树的深度

```c++
int weight[Max]; //全局变量初始就为0
void join_set(int num1, int num2){
    int root1 = find_set(num1);
    int root2 = find_set(num2);
    if(root1 == root2) return; 
    if(weight[root1] > weight[root2])  //如果num1对应的树是高树，那么让num2接到num1的根上
        pre[root2] = root1;
    else{
        if(weight[root1] == weight[root2]) //如果一样的化，接完之后树的高度会加一，我们只对顶部操作
            weight[root2] ++;
        pre[root1] = root2; //同理
    }
}
```

测试一下

```c++
结果为
1  2  3  4  5  6  7  8  9
2  2  2  4  5  6  7  8  9
```

与第一个不一样是因为过程不一样，并查集关心是否为一个集合，而判断标准只是顶部是否一样，而不关心插法

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211175719659.png" alt="image-20221211175719659" style="zoom:80%;" />

**优化2**

将一个集合的元素变为以下情况

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211175946437.png" alt="image-20221211175946437" style="zoom:80%;" />

要实现这种效果只需要在搜寻的时候就将前驱结点改为根节点

```c++
int find_set(int num){
    if(pre[num] != num)
        pre[num] = find_set(pre[num]); 
    return pre[num];
}
/*
1  2  3  4  5  6  7  8  9
3  2  3  4  5  6  7  8  9
*/
```

该算法存在一个缺陷：只有当查找了某个节点的根节点后，才能对该查找路径上的各节点进行路径压缩。换言之，第一次执行查找操作的时候是实现没有压缩效果的，只有在之后才有效。

## 带权并查集

带权并查集的核心能力就是维护多个元素之间的连通以及偏移关系，甚至可以维护多个偏移关系。

而偏移量可以理解为当前结点到根结点的距离之和。其核心运算是向量运算。



我们通常用一个新数组value来储存权值

这个权值代表当前结点到其前驱结点得价值，可以理解成每一根直线得价值

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211194039485.png" alt="image-20221211194039485" style="zoom:80%;" />

### 带权值得路径优化

我们所要实现得效果如下：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221211194125974.png" alt="image-20221211194125974" style="zoom:80%;" />

注意，此时得v[2]'等于v[2] + v[1]

实现这一具体的操作我们需要使用递归实现，即不断更新权值。

```c++
int value[Max];
int find_set(int num){
    if(pre[num] != num){
        int t = pre[num]; // 记录原本结点的前驱结点，因为如果进行后续操作，此节点会被更新
        pre[num] = find_set(pre[num]);
        value[num] += value[t]; // 不断于前驱结点的权值相加
        //值得关注的是：应为是递归，所以最开始的操作其实是从最顶部开始的
    }
    return num;
}
```

当然：joint_set也需要相应的修改。

## 并查集的使用

#### 并查集求最小环

我们用洛谷P2661做例子

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221221230413317.png" alt="image-20221221230413317" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221221230444875.png" alt="image-20221221230444875" style="zoom:80%;" />

首先这是一道带权并查集，我们的权值代表该节点到根节点的距离

注意：：**带权并查集要理解为向量，即有方向，带箭头，信息是单向传递的，传向根节点！！！！！**

在本题中，如果构成一个单向环，那么就可以符合条件结束游戏

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221221230923585.png" alt="image-20221221230923585" style="zoom:80%;" />

如上图：，1将信息传给2，2将信息传给3，3再将信息传给1，如此便能做到信息之间的传递，结束游戏

我们讲样例绘制出来：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221221231658186.png" alt="image-20221221231658186" style="zoom:80%;" />

可以很清楚的看到最终是构成了一个三元环，而环内元素的个数也就是游戏的轮数

可以想象，从3出发，经过三步后一定回到了3，同理2，4一样

那我们该如何判断是否成环呢

成环的最后一步时 4 -> 3，我们把这一步去掉，

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221221232205789.png" alt="image-20221221232205789" style="zoom:80%;" />

发现2的根节点是4，三的根节点也是4 ，所以判断是否成环的关键便是相连的两个结点的根节点是否一样

那到底该如何判断环内的元素个数呢，这个就需要我们边的值了，观察可知，3到根节点的距离为2，4的根节点就是4，所以距离为0

但是我们可以看到此时是少一条边的，所以需要加上1，把那一条边补上。

值得注意的是，

可以构成环的最后一条边就不要向连了，应为如果4->3连上，4的权值就+1了，4->4的距离不可能是1，这样会陷入死循环

然后只需要维护最小的元素即可。

最后附上带权优化的图像（到连成环的最后一步）

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20221221233012732.png" alt="image-20221221233012732" style="zoom:80%;" />

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int Max = 250000;
int pre[Max], value[Max], info[Max], total_people, Ans = INT_MAX;
void Init(){
    for(int temp = 1 ; temp <= total_people ; temp++)
        pre[temp] = temp;
}
int Find_set(int number){ // 基本的带权优化
    if(number != pre[number]){
        int t = pre[number];
        pre[number] = Find_set(pre[number]);
        value[number] += value[t];
    }
    return pre[number];
}
void Join_set(int num1, int num2){ //连边， 注意，这两个变量的意思是，num1将信息传递给num2
    int root1 = Find_set(num1), root2 = Find_set(num2); //分别寻找根节点
    if(root1 != root2){ //根节点不同，所以构成不了环
        pre[root1] = root2;
        value[num1] = value[num2] + 1; 
        //num1到num2的距离为1,num2到其根节点的距离是value[num2]，二者向连，num1与num2直接相连，则num1到num2根节点的距离		 //便是value[num2] + 1;
    }else Ans = min(Ans, value[num1] + value[num2] + 1);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_people;
    Init();
    for(int temp = 1 ; temp <= total_people ; temp++){
        cin >> info[temp];
        Join_set(temp, info[temp]);
    }
    cout << Ans;
    return 0;
}
```



## 并查集例题

### 洛谷 P3367（模板）

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214152715605.png" alt="image-20221214152715605" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214152730700.png" alt="image-20221214152730700" style="zoom:80%;" />

这是一道模板题，也就不过多解释了

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_num, ask_time;
lli pre[1000100];
tuple<int,int,int>info[1000100];
void Read(){
    cin >> total_num >> ask_time;
    for(int temp = 0 ; temp < ask_time ; temp++){
        int order, number1, number2;
        cin >> order >> number1 >> number2;
        info[temp] = make_tuple(order, number1, number2);
    }
}
void Init(){
    for(int temp = 1 ; temp <= total_num ; temp++)
        pre[temp] = temp;
}
lli find_set(int num){
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(int num1, int num2){
    int root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
bool Judge(int num1, int num2){
    int root1 = find_set(num1), root2 = find_set(num2);
    return root1 == root2;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    Read();
    Init();
    for(int temp = 0 ; temp < ask_time ; temp ++){
        if(get<0>(info[temp]) == 1)
            join_set(get<1>(info[temp]), get<2>(info[temp]));
        else{
            if(Judge(get<1>(info[temp]), get<2>(info[temp])))
                cout << "Y\n";
            else
                cout << "N\n";
        }
    }
    return 0;
}
```



### 洛谷 P2256

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214160959897.png" alt="image-20221214160959897" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214161024999.png" alt="image-20221214161024999" style="zoom:80%;" />

**思路**

这一题和模板题一样水，看代码行数就知道......值得提的是，我们在给名字编号的时候可以借助字典这一工具

直接通过名字来查询对该名字的编号

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_student, info_num, ask_time; //学生数量， 连通信息数， 询问次数
map<string, lli> people; // 通过map快速获得学生的编号， 其他没什么好说的，做不出来就是啥也不会
pair<string, string> info[1000010];
pair<string,string> ask[1000010];
lli pre[10010];
void Read(){
    cin >> total_student >> info_num;
    for(int temp = 1 ; temp <= total_student ; temp++){
        string name;
        cin >> name;
        people[name] = temp;
    }
    for(int temp = 0 ; temp < info_num ; temp++){
        string one, two;
        cin >> one >> two;
        info[temp] = make_pair(one, two);
    }
    cin >> ask_time;
    for(int temp = 0 ; temp < ask_time ; temp++){
        string one, two;
        cin >> one >> two;
        ask[temp] = make_pair(one, two);
    }
}
void Init(){
    for(int temp = 1 ; temp <= total_student ; temp++)
        pre[temp] = temp;
}
lli find_set(lli num){
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(lli num1,lli num2){
    lli root1 = find_set(num1),root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
bool Judge(int num1, int num2){
    lli root1 = find_set(num1), root2 = find_set(num2);
    return root1 == root2;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    Read();
    Init();
    for(int temp = 0 ; temp < info_num ; temp++)
        join_set(people[info[temp].first], people[info[temp].second]);
    for(int temp = 0 ; temp < ask_time ; temp++){
        if(Judge(people[ask[temp].first],people[ask[temp].second]))
            cout << "Yes.\n";
        else
            cout << "No.\n";
    }
    return 0;
}
```



### 洛谷 P8654

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214165008211.png" alt="image-20221214165008211" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214165053428.png" alt="image-20221214165053428" style="zoom:80%;" />

**思路**

依旧是一个模板题，虽然我写的时候调用函数漏了括号导致卡了一下，不过依然改变不了它就是一道模板题

而且， 有一说一，这是蓝桥杯国赛题....

**代码**

```c++
#include<bits/stdc++.h> //真 * 懒得解释
using namespace std;
typedef long long int lli;
lli vertical, level, info_num, total;
pair<lli,lli> info[100010];
lli pre[1000000];
void Read(){
    cin >> vertical >> level;
    total = vertical * level;
    cin >> info_num;
    for(lli temp = 0 ; temp < info_num ; temp++){
        lli num1, num2;
        cin >> num1 >> num2;
        info[temp] = make_pair(num1, num2);
    }
}
void Init(){
    for(lli temp = 1 ; temp <= total ; temp++)
        pre[temp] = temp;
}
lli find_set(lli num){
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(lli num1, lli num2){
    int root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
lli Union(){
    set<int>wipe;
    for(int temp = 1 ; temp <= total ; temp++)
        wipe.insert(find_set(temp));
    return wipe.size();
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout .tie(0);
    Read();
    Init();
    for(lli temp = 0 ; temp < info_num ; temp++)
        join_set(info[temp].first, info[temp].second);
    cout << Union();
    return 0;
}
```

### 洛谷 P2814

[题目链接](https://www.luogu.com.cn/problem/P2814)

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221220224512213.png" alt="image-20221220224512213" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221220224544648.png" alt="image-20221220224544648" style="zoom:80%;" />

**思路**

前面说过，对于并查集可以理解为向量，即指向某某某，我们这里设想儿子指向父亲，这样通过儿子们的不断指认，我们一定能找到最早的父亲，至于对字符串输入如何转化为编号，可以参考P2256

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
const int Max = 100000; //最大可能出现的数据量
int pre[Max], order = 1; //并查集数组， 用于给名字的编号
map<string, int> judge; //用map来快速获取该名字的编号，也可以通过编号获得名字
string father; //用于存储当前输入数据的祖先
void Init(){
    for(int temp = 0 ; temp < Max ; temp++) // 因为没有给具体的数值，所以我们按照最大的数据量初始化
        pre[temp] = temp;
}
int find_set(int number){ // 老样子
    if(pre[number] != number)
        pre[number] = find_set(pre[number]);
    return pre[number];
}
void join_set(string son, string father){
    int num_son = judge[son], num_father = judge[father];//通过名字获得编号
    int root1 = find_set(num_son), root2 = find_set(num_father); // 通过编号再获取其根节点
    if(root1 != root2)
        pre[root1] = root2; //值得注意的是，必须是pre[root1] = root2，应为儿子应该指向父亲
}
string Oldest(string son){ //寻找祖先
    int num_son = judge[son];
    int num_father = find_set(num_son); //这是输入数据的根节点
    for(auto pr : judge){ //依次遍历通过编号寻找名字
        if(pr.second == num_father)
            return pr.first;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    Init();
    string name;
    while(name != "$"){ //输入$时结束循环
        cin >> name;
        if(name[0] == '#'){
            name = name.substr(1); //用于去掉第一个字符，下同
            if(!judge.count(name)) // 如果这个名字从未出现，则给他编号， 下同
                judge[name] = order++;
            father = name;
        }else if(name[0] == '+'){
            name = name.substr(1);
            if(!judge.count(name))
                judge[name] = order++;
            join_set(name, father);
        }else if(name[0] == '?'){
            name = name.substr(1);
            cout << name << " " << Oldest(name) << "\n";
        }
    }
    return 0;
}
```



### 洛谷 P1656

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214180121353.png" alt="image-20221214180121353" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221214180149821.png" alt="image-20221214180149821" style="zoom:80%;" />

**思路**

这道题说实话不难想出来，就是一个一个去试，看哪条路不行，因为数据量并不是很大，所以可以枚举，这道题实际上还可以用Tarjan算法，但是并查集也是一个不错的选择。

不过这道题恶心人的并不是如何做出来，而是如何输出。

注意题目所述：输出时，所有的数对 <a,b> 必须按照 a 从小到大排序输出；如果a 相同，则根据 b从小到大排序。

也就是说哪怕输入的是<7,3>,我们输出的时候也得改成<3,7>; （1）

而且a 一样b也要从小到大输出。（2）

操作（1）可以在读取的时候完善，选择小的那个作为第一个

操作（2）可以借助字典+集合，因为集合本身就是从小到大排序的



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
int total_city, total_road; //城市数， 路的总数
pair<int,int> info[2000]; //存入信息
int pre[200]; //并查集
map<int, set<int>> ans; //用来存储答案并排序
bool cmp(pair<int,int>a, pair<int,int>b){ // 自定义排序函数，从小到大对输入信息排序
    return a.first < b.first;
}
void Read(){//读取
    cin >> total_city >> total_road;
    for(int temp = 0 ; temp < total_road ; temp++){
        int num1, num2;
        cin >> num1 >> num2;
        info[temp] = make_pair(min(num1,num2), max(num1,num2));
    }
    sort(info, info + total_road , cmp); //排序
}
void Init(){ //初始化
    for(int temp = 1 ; temp <= total_city ; temp++)
        pre[temp] = temp;
}
int find_set(int num){ // 寻找根节点
    if(pre[num] != num)
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(int num1, int num2){ //联合
    int root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
bool Judge(){ //判断是否可以分为两个及以上的连通块
    set<int> wipe; //使用集合可以自动判重
    for(int temp = 1 ; temp <= total_city ; temp++){
        int root = find_set(temp);
        if(!wipe.empty() && !wipe.count(root)) // 如果集合不为空且当前根节点在集合中不存在
            return 1;
        wipe.insert(root);
    }
    return 0;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    Read();
    for(int temp = 0 ; temp < total_road ; temp++){ //依次遍历每一条路不存在的情况
        Init();
        for(int temp2 = 0 ; temp2 < total_road ; temp2++){
            if(temp != temp2) //一样的化说明这条路就是我们要炸毁的路
                join_set(info[temp2].first, info[temp2].second);
        }
        if(Judge())
            ans[info[temp].first].insert(info[temp].second);
    }
    for(auto pr1 : ans){
        for(auto pr2 : pr1.second)
            cout << pr1.first << " " << pr2 << "\n";
    }
    return 0;
}
```



### hdu 3038//未完善

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221211194844278.png" alt="image-20221211194844278"  />

![image-20221211194919147](C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221211194919147.png)

**大意**

有M个数，不知道它们具体的值，但是知道某两个数之间（包括这两个数）的所有数之和，现在给出N个这样的区间和信息，需要判断有多少个这样的区间和与前边已知的区间和存在矛盾，例如给出区间和[1,5]为200 ，[1,2]为100，[2,5]为200，则为错误。

**思路**

首先，判断错误只有一个情况，就是能够具体的算出具体的一个区间的值，而且条件给的值于可以算出的值不同

所以说，就算[1，5] = 500， [1 , 3] = 1000 也是符合条件的，因为条件没有规定数一定为正数

所以我们就会有如下两种情况：

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212122247351.png" alt="image-20221212122247351" style="zoom:80%;" />

其中内含的情况于右边情况类似

我们能够确定错误的只有第一种情况

我们把第一种情况转化成向量：



AB可以看成A到B的距离，





### 洛谷 P1111

[题目链接](https://www.luogu.com.cn/problem/P1111)

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212151658055.png" alt="image-20221212151658055" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212151712225.png" alt="image-20221212151712225" style="zoom:80%;" />

**思路**

这是一道普通并查集的应用，我们需要判断两个村庄是否连通，那么这个时候并查集就可以派上用场

值得注意的是，本题中是所有的路一起修理，如果分开修理的化在合并的时候要判断是否已经连通，之后在累加

本题则不用那么麻烦，按照修理的时间从小到大排序，然后在判断连通块的个数，如果个数为1即为成功

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
int pre[1010]; //并查集核心数组
tuple<int,int,int> arr[100010]; // 储存连通信息
int total_road, total_v; //总共的路的数量， 总共村庄数量
bool cmp(tuple<int,int,int> a, tuple<int,int,int>b){ //对时间从小到大排序
    return get<2>(a) < get<2>(b); //想要什么效果就写什么表达式
}
void Init(){ //初始化
    for(int temp = 1 ; temp <= total_v ; temp++)
        pre[temp] = temp;
}
int find_set(int num){ //寻找根节点
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(int num1, int num2){ //合并
    int root1 = find_set(num1); int root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
bool judge(){ //判断连通块的数量
    set<int> del_; //我使用集合来判断
    for(int temp1 = 1 ; temp1 <= total_v ; temp1++){ //逐个遍历
        int root = find_set(temp1); //找到其根结点
        if(del_.size() == 1 && !del_.count(root)) // 如果集合里已经有一个结点了，但是这个元素不在此结点上
            return 1; //返回
        del_.insert(root); // 插入第一个结点
    }
    return 0;
}
void Read(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); //快读
    cin >> total_v >> total_road;
    for(int temp = 0 ; temp < total_road ; temp++)
        cin >> get<0>(arr[temp]) >> get<1>(arr[temp]) >> get<2>(arr[temp]);
    sort(arr, arr + total_road, cmp);
}
signed main()
{
    Read();
    Init();
    int ans = 0; //用来储存答案
    for(int temp = 0 ; temp < total_road && judge(); temp++){ //循环的过程中不断判断是否以满足条件
        ans = get<2>(arr[temp]); //更新
        join_set(get<0>(arr[temp]), get<1>(arr[temp])); //连接
    }
    if(judge()) cout << "-1"; //判断所有路都修好后是否所有都连通
    else cout << ans;
    return 0;
}
```

有一说一，要开启O2优化才可以AC，不然会有一个TLE。



### 洛谷 P3938

[题目链接](https://www.luogu.com.cn/problem/P3958)

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212210226879.png" alt="image-20221212210226879" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212210255570.png" alt="image-20221212210255570" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221212210314917.png" alt="image-20221212210314917" style="zoom:80%;" />

**思路**

这可以看成是一个连通块的问题，所以说BFS，DFS其实也可以，但并查集也是个不错的选择

我们可以先记录与顶部相交和与底部相交的的球，如果顶部的某一个球与底部的某一个球向连，那么符合条件

之后我们分析两两球之间的关系，如果可以连通，那么我们就将他们看成一个集合

至于如何判断：

若两个球的球心之间的距离小于等于两倍的半径，那么这两个球相切或相交。

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli; //一定记得要开long long int 不然会发生错误
lli pre[1010];
tuple<lli,lli,lli> info[1010];
lli ask_time, total_hole, r, h;
vector<lli>up, down; // 储存于上表面，下表面相交的点
set<lli>up_,down_; // 储存与上下表面相交的点的根结点，用于判断是否可以从下直接连通到上面
bool cmp(tuple<lli,lli,lli>a, tuple<lli,lli,lli>b){ //从小到大排序，方便确定是否与上下面相交
    return get<2>(a) < get<2>(b);
}
void Init(){ //初始化
    for(lli temp = 1 ; temp <= total_hole ; temp++)
        pre[temp] = temp;
    up.clear(); //注意清空
    down.clear();
    up_.clear();
    down_.clear();
}
lli find_set(lli num){ //搜寻
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
void join_set(lli num1, lli num2){ //连通
    lli root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
lli distance_(tuple<lli,lli,lli>a, tuple<lli,lli,lli>b){ //两点的距离
    lli x1 = get<0>(a), y1 = get<1>(a), z1 = get<2>(a);
    lli x2 = get<0>(b), y2 = get<1>(b), z2 = get<2>(b);
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2); //注意这里返回的是平方值
}
bool judge(tuple<lli,lli,lli>a, tuple<lli,lli,lli>b){ //判断是否要连通
    lli dis = distance_(a,b);
    if(dis > 4*r*r) return 0; //与平方作比较，可以写的更精简： return dis > 4*r*r;
    else return 1;
}
void Read(){
    cin >> total_hole >> h >> r;
    for(lli temp = 1 ; temp <= total_hole ; temp++)
        cin >> get<0>(info[temp]) >> get<1>(info[temp]) >> get<2>(info[temp]);
    sort(info + 1, info + total_hole + 1, cmp); //注意排序的时候前两个参数，本题开始是从1开始记录
}
void Re(){ //记录上下相交的点，因为排过序，所以不必全部遍历
    for(lli temp = 1 ; temp <= total_hole ; temp++){
        if(get<2>(info[temp]) <= r)
            down.push_back(temp);
        else break;
    }
    for(lli temp = total_hole ; temp >= 1 ; temp--){
        if(get<2>(info[temp]) >= h - r){
            up.push_back(temp);
        }
        else break;
    }
}
void Change(){ //确定上下相交点的根节点
    for(lli pr : up){
        lli root = find_set(pr);
        up_.insert(root);
    }
    for(lli pr : down){
        lli root = find_set(pr);
        down_.insert(root);
    }
}
bool judge_(){ // 判断是否有符合题意的情况
    Change();
    for(lli pr : up_){
        if(down_.count(pr)) return 1;
    }
    return 0;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> ask_time;
    for(lli tem = 0 ; tem < ask_time ; tem++){
        Read();
        Init();
        Re();
        for(lli temp1 = 1 ; temp1 < total_hole ; temp1++){
            for(lli temp2 = temp1 + 1 ; temp2 <= total_hole ; temp2++){
                if(judge(info[temp1], info[temp2]))
                    join_set(temp1, temp2);
            }
        }
        if(judge_()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```



### 洛谷 P1197//未完善



<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221213194938830.png" alt="image-20221213194938830" style="zoom:80%;" />

<img src="C:\Users\阴铭洋\AppData\Roaming\Typora\typora-user-images\image-20221213200133302.png" alt="image-20221213200133302" style="zoom:80%;" />



```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
int pre[100010],destroy_[100010]; //并查集， 摧毁的星球编号
list<pair<int,int> > info; //连通信息
list<int>ans; //储存答案
int star_num, joint_num, des_num; //星球数量， 通道数量， 摧毁数量
void Init(){ //初始化，编号从1开始
    for(int temp = 1 ; temp <= star_num ; temp++)
        pre[temp] = temp;
}
int find_set(int num){ //寻找根节点
    if(num != pre[num])
        pre[num] = find_set(pre[num]);
    return pre[num];
}
int join_set(int num1, int num2){ //连通
    int root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
bool Have(int num){ //判断这个星球是否在摧毁名单里
    for(int temp = 0 ; temp < des_num ; temp++){
        if(destroy_[temp] == num)
            return 0;
    }
    return 1;
}
void Find_joint(){ //寻找连通个数
    set<int> root;
    for(int temp = 1 ; temp <= star_num ; temp++){
        if(Have(temp))
            root.insert(find_set(temp));
    }
    ans.push_back(root.size());
}
void Read(){
    cin >> star_num >> joint_num;
    for(int temp = 0 ; temp < joint_num ; temp++){
        int first, second;
        cin >> first >> second;
        info.push_back(make_pair(first+1, second+1));
        //+1避开编号为0的情况，方便判断该星球是否被摧毁
    }
    cin >> des_num;
    for(int temp = 0 ; temp < des_num ; temp++){
        int num;
        cin >> num;
        destroy_[temp] = num+1;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    Read();
    Init();
    //Find_joint();
    //cout << "---------------\n";
    for(int temp = des_num - 1 ; temp >= -1 ; temp --){
        for(auto pr : info){
            if(Have(pr.first) && Have(pr.second)){
                //cout << pr.first << "  " << pr.second << "\n";
                join_set(pr.first, pr.second);
            }
        }
        //cout << "*********\n";
        Find_joint();
        if(temp >= 0)
            destroy_[temp] = 0;
    }
    //Find_joint();
    //cout << "======\n";
    info.reverse();
    for(int temp : ans)
        cout << temp << "\n";
    return 0;
}
```
