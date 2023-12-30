# yyym_'s formwork

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/R.jpg" alt="R" style="zoom: 50%;" />



## Dijkstra算法（$m + n\log n$）

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli Length, vertex1, vertex2, distance_;
vector<pair<lli,lli>> graph[10];
vector<lli> dis(10), path(10); // dis存储起始点到现在点的距离， path表示上一个点是什么
// 自定义优先队列的排序法则，我们让路径更短的排在前面
struct cmp{
    bool operator()(pair<lli, lli> a, pair<lli,lli> b){
        return a.second > b.second;
    }
};
priority_queue<pair<lli,lli>,vector<pair<lli,lli>>, cmp> Check;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length;
    //存入图
    for(int temp = 0 ; temp < Length ; temp++){
        cin >> vertex1 >> vertex2 >> distance_;
        graph[vertex1].push_back(make_pair(vertex2, distance_));
    }
    // 算法开始
    // 将初始的最短距离定义为最大值
    for(int temp = 1 ; temp < 10 ; temp++) dis[temp] = INT_MAX;
    //放入初始点，并将自己的距离置为0
    Check.push(make_pair(3,0)); dis[3] = 0;
    while(!Check.empty()){
        lli now = Check.top().first, length = Check.top().second;
        for(auto pr : graph[now]){ // 遍历这个点能到的所有点
            if(pr.second + length < dis[pr.first]){ //如果到这个点的最新距离比记录的要短
                dis[pr.first] = pr.second + length; // 更新
                path[pr.first] = now;
                // 它的值更新可能会影响它经过的点，所以再次放入
                Check.push(make_pair(pr.first, pr.second + length));
            }
        }
        Check.pop(); //顶端出队列
    }
    return 0;
}
```



## 快速幂（$\log n$）

**不带取余**

```c++
typedef long long int lli;
lli fast_pow(lli number, lli power){ // 计算number的power次幂
    lli ans = 1;
    while(power){ //如果power没有置为0
        // 如果power是奇数，那就让ans*number，相当于把奇数-1变为偶数
        if(power & 1) ans *= number;
        // 将number置为两倍
        number *= number;
        // power除于2
        power >>= 1;
    }
    return ans;
}
```

**取模求幂**

```c++
typedef long long int lli;
const lli P = 1e9 + 7;
lli fast_pow(lli number, lli power){
    number %= P;
    lli ans = 1;
    while(power){
        if(power & 1) ans = (ans * number) % P;
        number = (number * number) % P;
        power >>= 1;
    }
    return ans;
}
```



## 欧拉筛（$n$）

```c++
typedef long long int lli;
vector<lli>info;
bitset<lli(1e8 + 10)> Check;
void Euler_sieve(lli Limit){ //筛选出[2,Limit]中所有的素数
    for(lli temp = 2 ; temp <= Limit ; temp++){ // 遍历这个区间内所有的数
        // 如果这个数没有被标记过，那必然是一个素数，将它存入
        if(Check[temp] == 0) info.push_back(temp);
        //遍历所有已经筛出来的素数，当然，如果这个数超过范围就结束循环
        for(lli temp2 = 0 ; temp*info[temp2] <= Limit ; temp2++){
            // temp*info[temp2]必然是 temp的倍数
            Check[temp*info[temp2]] = 1;
            //如果不是这个数的最小素因数，就结束循环
            if(temp % info[temp2] == 0) break;
        }
    }
}
```



## 费马小定理（$\log n$）

**前提：P为素数**

> $b_{inv} = b^{p-2}$

```c++
// 照搬前面的带余快速幂
typedef long long int lli;
const lli P = 1e9 + 7;
lli fast_pow(lli number, lli power){
    number %= P;
    lli ans = 1;
    while(power){
        if(power & 1) ans = (ans * number) % P;
        number = (number * number) % P;
        power >>= 1
    }
    return ans;
}
lli inv(lli number){
    return fast_pos(number, P-1);
}
```



## 拓展欧几里得定理（$\log n$）

```c++
typedef long long int lli;
const int P = 1e9 + 7;
void exgcd(lli a, lli b, lli& x, lli& y){
    if(b == 0) {
        x = 1; y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}
lli inv(lli number, lli p){
    lli x = 1, y = 0;
    exgcd(number, p, x, y);
    return (x % p + p) % p;
}
```



## 快速求组合数-公式法（$n$）

> $C_m^n = \frac{m!}{(m - n)! n!}$

```c++
typedef long long int lli;
const int P = 1e9 + 7;
lli mod(lli n) {return (n % P + P) % P;}
lli fast_pow(lli number, lli power){
    number %= P;
    lli ans = 1;
    while(power){
        if(power & 1) ans = (ans * number) % P;
        number = (number * number) % P;
        power >>= 1
    }
    return ans;
}
lli Compute(lli m, lli n){ // 计算C_m^n
    vector<lli> info(m + 10, 0), rev(m + 10, 0);
    info[0] = 1; rev[0] = 1;
    for(int temp = 1 ; temp <= m + 1 ; temp++){
        info[temp] = mod(info[temp - 1] * temp);
        rev[temp] = mod(rev[temp - 1] * fast_pow(temp, P - 2));
    }
    return info[m] * rev[n] % P * rev[m - n] % P;
}
```



## 树状数组（$\log n$）

### 单点修改+区间查询

```c++
typedef long long int lli;
const lli Length = 1e5 + 10;
lli lowbit(lli n) {return n & (-n);}

void update(int index, int d){ //修改元素， arr[index] = arr[index] + d;
    while(index <= length){
        tree[index] += d;
        index += lowbit(index);
    }
}

int sum(int number){ //查询区间[1，number]的和
    int ans = 0;
    while(number > 0){
        ans += tree[number];
        number -= lowbit(number);
    }
    return ans;
}
//具体使用
/*
    for(int temp = 0 ; temp < Length ; temp++)
        update(temp+1,arr[temp]); 
*/
```

### 区间修改+单点查询

> 差分的应用

```c++
const int N = 200000;
lli lowbit(lli n) {return n & (-n);}
int tree[N];
int total;
void update(int index, int d){
    while(index <= N){
        tree[index] += d;
        index += lowbit(index);
    }
}
int sum(int index){
    int ans = 0;
    while(index > 0){upda
        ans += tree[index];
        index -= lowbit(index);
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    while(cin >> total){
        for(int temp = 0 ; temp < total ; temp++){
            int left, right;
            cin >> left >> right;
            update(left, 1); //起始端点加一
            update(right + 1, -1); // 结尾端点的后一个减一，与差分数组操作完全一致
        }
        for(int temp = 1 ; temp <= total ; temp++)
            cout << sum(temp) << " ";
        cout << "\n";
    }
    return 0;
}
```

### 区间修改+区间查询

```c++
lli lowbit(lli n) {return n & (-n);}
typedef long long int lli;
const lli total = 100010; 
lli tree1[total], tree2[total];  //D, (i-1)D
lli total_num, total_oper;
void update1(int i, int d){while(i <= total){tree1[i] += d; i += lowbit(i);}} //分别处理两颗树
void update2(int i, int d){while(i <= total){tree2[i] += d; i += lowbit(i);}}
lli sum1(int i){lli ans = 0; while(i > 0){ans += tree1[i];i -= lowbit(i);}return ans;}
lli sum2(int i){lli ans = 0; while(i > 0){ans += tree2[i]; i -= lowbit(i);}return ans;}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_num >> total_oper;
    lli old = 0, a;
    for(int temp = 1 ; temp <= total_num ; temp++){ //求差分，以及（i-1）D
        cin >> a;
        update1(temp, a-old);
        update2(temp, (temp - 1)*(a - old));
        old = a;
    }
    int order, num1, num2, div_;
    for(lli temp = 0 ; temp < total_oper ; temp++){
        cin >> order >> num1 >> num2;
        if(order == 1){
            cin >> div_;
            update1(num1, div_);
            update1(num2 + 1, -div_);
            update2(num1, (num1 - 1)*div_); //注意要乘上（i-1）
            update2(num2 + 1, num2*-div_);
        }else{
            lli tot1 = (num1 - 1)*sum1(num1 - 1) - sum2(num1 - 1);
            lli tot2 = num2*sum1(num2) - sum2(num2);
            cout << tot2 - tot1 << "\n";
        }
    }
    return 0;
}
```



## 线段树（$\log n$）

### 单点修改+区间查询

```c++
typedef long long int lli;
const lli N = 1000000;
lli total_num, total_order;
lli arr[N];
struct Tree{
    int sum;
    int left, right;
}seg[4*N];
void Build(lli l, lli r, lli i){
    seg[i].left = l; seg[i].right = r;
    if(l == r){
        seg[i].sum = arr[l];
        return ;
    }
    lli mid = (l + r) >> 1;
    Build(l, mid, i << 1);
    Build(mid + 1, r, i << 1 | 1);
    seg[i].sum = seg[i << 1].sum + seg[i << 1 | 1].sum;
    return ;
}
int Search(lli l, lli r, lli i){
    if(seg[i].right == r && seg[i].left == l)
        return seg[i].sum;
    if(seg[i << 1].right >= r) return Search(l,r, i << 1);
    else if(seg[i << 1 | 1].left <= l) return Search(l,r,i << 1 | 1);
    else{
        lli num1 = Search(l, seg[i << 1].right, i << 1);
        lli num2 = Search(seg[i << 1 | 1].left, r, i << 1 | 1);
        return num1 + num2;
    }
}
void Change_point(lli target, lli d, lli i){
    if(seg[i].left == seg[i].right){
        seg[i].sum += d;
        return ;
    }
    if(seg[i << 1].right >= target) Change_point(target, d, i << 1);
    if(seg[i << 1 | 1].left <= target) Change_point(target, d, i << 1 | 1);
    seg[i].sum = seg[i << 1].sum + seg[i << 1 | 1].sum;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0),cout.tie(0);
    cin >> total_num >> total_order;
    for(int temp = 1; temp <= total_num ; temp++)
        cin >> arr[temp];
    Build(1, total_num, 1);
    for(int temp = 0 ; temp < total_order ; temp++){
        lli order, one, two;
        cin >> order >> one >> two;
        if(order == 1)
            Change_point(one, two ,1);
        else
            cout << Search(one, two, 1) << "\n";
    }
    return 0;
}
```



### 区间修改 + 区间查询

```c++
typedef long long int lli;
const lli N = 100010;
lli total_num, total_oper;
lli arr[N];
struct Tree{
    lli sum, Lazy;
    lli left, right;
}seg[N << 2];
void Build(lli l, lli r, lli i){
    seg[i].left = l, seg[i].right = r, seg[i].Lazy = 0;
    if(l == r){
        seg[i].sum = arr[l];
        return ;
    }
    lli mid = (l + r) >> 1;
    Build(l, mid, i << 1);
    Build(mid + 1, r, i << 1 | 1);
    seg[i].sum = seg[i << 1].sum + seg[i << 1 | 1].sum;
}
void Push_down(lli i, lli Lazy){
    seg[i << 1].Lazy += Lazy;
    seg[i << 1 | 1].Lazy += Lazy;
    seg[i].Lazy = 0;
}
void push_up(lli i){
    lli one = seg[i<<1].sum + (seg[i<<1].right - seg[i << 1].left + 1)*seg[i << 1].Lazy;
    lli two = seg[i<<1|1].sum + (seg[i<<1|1].right - seg[i << 1|1].left + 1)*seg[i << 1|1].Lazy;
    seg[i].sum = one + two;
}
void modify(lli l, lli r, lli d, lli i){
    if(seg[i].left == l && seg[i].right == r){
        seg[i].Lazy += d;
        return;
    }
    Push_down(i, seg[i].Lazy);
    if(seg[i << 1].right >= r) modify(l, r, d, i << 1);
    else if(seg[i << 1 | 1].left <= l) modify(l, r, d, i <<1 | 1);
    else{
        modify(l, seg[i << 1].right , d, i << 1);
        modify(seg[i << 1 | 1].left, r, d, i << 1 | 1);
    }
    push_up(i);
}
lli query(lli l, lli r, lli i){
    if(seg[i].left == l && seg[i].right == r)
        return seg[i].sum + seg[i].Lazy * (seg[i].right - seg[i].left + 1);
    Push_down(i, seg[i].Lazy);
    lli ans = 0;
    if(seg[i << 1].right >= r) ans = query(l, r, i << 1);
    else if(seg[i << 1 | 1].left <= l) ans = query(l, r, i <<1 | 1);
    else{
        lli one = query(l, seg[i << 1].right , i << 1);
        lli two = query(seg[i << 1 | 1].left, r, i << 1 | 1);
        ans = one + two;
    }
    push_up(i);
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0), cout.tie(0);
    cin >> total_num >> total_oper;
    for(int temp = 1 ; temp <= total_num ; temp++)
        cin >> arr[temp];
    Build(1,total_num,1);
    lli order, one,two,there;
    for(int temp = 0 ; temp < total_oper ; temp++){
        cin >> order;
        if(order == 1){
            cin >> one >> two >> there;
            modify(one,two,there,1);
        }else{
            cin >>one >> two;
            cout << query(one, two, 1) << "\n";
        }
    }
    return 0;
}
```



## Prime算法（$m\log n$）

> 点寻找

```c++
typedef long long int lli;
lli RoadNum, NodeNum, Begin;
const int N = 10000;
vector<pair<lli,lli>> graph[N];
bitset<N> Check;
struct cmp{
    bool operator() (pair<lli,lli>a, pair<lli,lli>b){
        return a.second > b.second;
    }
};
priority_queue<pair<lli,lli>, vector<pair<lli,lli>>, cmp> Find;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> NodeNum >> RoadNum;
    //存图
    for(lli temp = 1, num1 ,num2, num3; temp <= RoadNum ; temp++){
        cin >> num1 >> num2 >> num3;
        graph[num1].push_back(make_pair(num2, num3));
        graph[num2].push_back(make_pair(num1, num3));
        Begin = num1;
    }
    //算法开始
    //从Begin这个开始寻找，后面的值代表到这里所需要的值，初始为0
    Find.push(make_pair(Begin, 0));
    // ans表示最小生成树的值， Count计算点集的个数，判断是否都包含
    lli ans = 0LL, Count = 0LL;
    while(!Find.empty()){
        auto node = Find.top(); Find.pop();
        if(Check[node.first]) continue; // 如果这个点已经在点集内，不加入
        Count++;
        Check[node.first] = 1;
        ans += node.second;
        for(auto pr : graph[node.first]){
            if(Check[pr.first]) continue;
            // 将这个点所有的连通点且未在点集的加入优先队列
            Find.push(make_pair(pr.first, pr.second));
        }
    }
    if(Count == NodeNum) cout << ans; //如果最小生成树不包含所有的点，不连通
    else cout << "orz";
    return 0;
}
```



## Kruskal算法（$m\log m$）

> 边寻找

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 10000;
lli NodeNum, RoadNum;
vector<tuple<lli,lli,lli>> road;
vector<lli> pre(N);
void init(){
    for(int temp = 1 ; temp <= NodeNum + 10 ; temp++)
        pre[temp] = temp;
}
lli Find_set(lli index){
    if(index == pre[index]) return index;
    pre[index] = Find_set(pre[index]);
    return pre[index];
}
bool Join_set(lli one, lli two){
    // 返回类型为bool用于判断
    lli root1 = Find_set(one), root2 = Find_set(two);
    if(root1 == root2) return 0;
    pre[root1] = root2;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> NodeNum >> RoadNum;
    init();
    //存图
    for(lli temp = 1, num1, num2, num3; temp <= NodeNum ; temp++){
        cin >> num1 >> num2 >> num3;
        road.push_back(make_tuple(num2, num1, num3));
        road.push_back(make_tuple(num1, num2, num3));
    }
    //算法开始
    auto cmp = [](tuple<lli,lli,lli>a, tuple<lli,lli,lli>b) {return get<2>(a) < get<2>(b);};
    //将边权从小到大排序
    sort(road.begin(), road.end(), cmp);
    // 统计最小生成树的权值，并且记录包含的点的数量，为了方便计算，从1开始
    lli ans = 0LL, Node = 1LL;
    for(auto pr : road){
        if(Node == NodeNum) break; //如果所需点数够了，结束
        lli one = get<0>(pr), two = get<1>(pr), there = get<2>(pr);
        if(Join_set(one, two)){ // 如果边两边链接的并未包含在一起， 链接
            Node++;
            ans += there;
        }
    }
    if(Node != NodeNum) cout << "orz"; //不够点就是图不连通
    else cout << ans;
    return 0;
}

```



## 并查集

```c++
typedef long long int lli;
lli total_num;
lli pre[1000100];
void Init(){
    //初始皆为自己
    for(int temp = 1 ; temp <= total_num ; temp++)
        pre[temp] = temp;
}
lli find_set(int num){
    if(num != pre[num])
        pre[num] = find_set(pre[num]); //查找的同时赋值
    return pre[num];
}
void join_set(int num1, int num2){ //链接
    int root1 = find_set(num1), root2 = find_set(num2);
    if(root1 != root2)
        pre[root1] = root2;
}
```



## BKDRHash函数

```c++
typedef unsigned long long int ull;
const int N = 2e5 + 10;
ull BKDRHash(string put){
    ull P = 131, H = 0;
    for(int temp = 0 ; temp < put.size() ; temp++)
        H = H * P + put[temp];
    return H;
}
```



## Manacher算法（$n$）

```c++
typedef long long int lli;
string Change(string put){ //修改原字符串，同时处理奇数和偶数字符串
    string ans = "$";
    for(auto pr : put){
        ans += "#"; ans += pr;
    }
    ans += "#&";
    return ans;
}
lli Manacher(string put){
    lli Length = put.size();
    vector<lli> info(Length + 10, 0);
    lli R = 0, pos; // R为半径， pos为此R的坐标
    for(int temp = 1 ; temp < Length ; temp++){
        if(temp < R) info[temp] = min(info[(pos << 1) - temp], R - temp); //同时处理两种情况
        else info[temp] = 1;
        //暴力中心拓展
        while(put[temp + info[temp]] == put[temp - info[temp]]) info[temp]++;
        if(info[temp] + temp > R){ //更新
            R = info[temp] + temp;
            pos = temp;
        }
    }
    lli ans = INT_MIN;
    for(int temp = 1 ; temp < Length ; temp++) ans = max(ans, info[temp]);
    return ans - 1;
}
```



## 字典树（$m$）

```c++
typedef long long int lli;
const int N = 2e5 + 10;
struct TREE{
    int son[26]; //存储26个字母
    lli num; //从开头到这里这个字符出现的次数
}tree[N];
lli index_ = 1; //索引
void insert(string put){
    lli now = 0; //从根节点寻找
    for(int temp = 0 ; temp < put.size() ; temp++){
        int pos = put[temp] - 'a';
        if(tree[now].son[pos] == 0) //如果没出现
            tree[now].son[pos] = index_ ++; //开启新索引
        now = tree[now].son[pos];
    }
    tree[now].num++; //结束的时候计数
}
lli Find(string put){
    lli now = 0;
    for(int temp = 0 ; temp < put.size() ; temp++){
        int pos = put[temp] - 'a';
        if(tree[now].son[pos] == 0) return 0; //如果没找到一个字母就返回0
        now = tree[now].son[pos];
    }
    return tree[now].num; //返回总数
}
```



## KMP算法（$n$）

**获取$Next$数组**

```c++
typedef long long int lli;
const int N = 2e5 + 10;
vector<lli> Next(N);
string put1, put2;
void Get_Next(string put){
    Next[0] = 0; // 初始值为 0
    lli point = 0;
    //求取从第二个字符到最后的最长公共前后缀
    for(int temp = 1; temp < put.size() ; temp++){
        while(point > 0 && put[temp] != put[point]) //一直不能匹配则返回之前求得值
            point = Next[point - 1]; //注意是point-1
        if(put[temp] == put[point]) point++;
        Next[temp] = point; //更新
    }
}
```

**求第一个匹配位置**

```c++
lli KMP1(string put, string target){
    Get_Next(target);
    lli point = 0;
    for(int temp = 0 ; temp < put.size() ; temp++){
        while(point > 0 && put[temp] != target[point])
            point = Next[point - 1];
        if(put[temp] == target[point]) point++;
        if(point == target.size())
            return temp - target.size() + 1;
    }
}
```

**求出现的次数**

```c++
lli KMP2(string put, string target){
    Get_Next(target);
    lli point = 0, Count = 0;
    for(int temp = 0 ; temp < put.size() ; temp++){
        while(point > 0 && put[temp] != target[point])
            point = Next[point - 1];
        if(put[temp] == target[point]) point++;
        if(point == target.size())
            Count++;
    }
    return Count;
}
```

## 后缀自动机

## AC自动机

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 3e5 + 10;
lli point = 1;
struct TREE{
    lli son[26];
    lli fail;
    vector<lli> End;
}tree[N];
inline void Clean(int x)
{
       memset(tree[x].son,0,sizeof(tree[x].son));
       tree[x].fail=0;
       tree[x].End.clear();
}
void BuildTree(string put, lli index){
    lli now_ = 0;
    for(int temp = 0 ; temp < put.size() ; temp++){
        lli pos = put[temp] - 'a';
        if(tree[now_].son[pos] == 0)
            tree[now_].son[pos] = point++;
        now_ = tree[now_].son[pos];
    }
    tree[now_].End.push_back(index);
}
void GetFail(){
    queue<lli> Find;
    for(int temp = 0 ; temp < 26 ; temp++){
        if(tree[0].son[temp]){
            tree[tree[0].son[temp]].fail = 0;
            Find.push(tree[0].son[temp]);
        }
    }
    while(!Find.empty()){
        lli one = Find.front(); Find.pop();
        lli fafail = tree[one].fail;
        for(int temp = 0 ; temp < 26 ; temp++){
            if(tree[one].son[temp]){
                tree[tree[one].son[temp]].fail = tree[tree[one].fail].son[temp];
                Find.push(tree[one].son[temp]);
                //for(auto pr : tree[tree[tree[one].son[temp]].fail].End)
                    //tree[tree[one].son[temp]].End.push_back(pr);
            }else
                tree[one].son[temp] = tree[tree[one].fail].son[temp];
        }
    }
}
void AC_automaton(lli time_){
    string put, target;
    vector<lli> Count(time_ + 10, 0);
    vector<string> info(time_ + 10);
    for(int temp = 1 ; temp <= time_ ; temp++)
        cin >> info[temp];
    for(int temp = 1 ; temp <= time_ ; temp++)
        BuildTree(info[temp], temp);
    GetFail();
    cin >> put;
    lli now = 0LL;
    for(int temp = 0 ; temp < put.size() ; temp++){
        lli index = put[temp] - 'a';
        now = tree[now].son[index];
        for(int To = now ; To ; To = tree[To].fail){
            for(auto pr : tree[To].End)
                Count[pr] ++;
        }
    }
    for(int temp = 1 ; temp <= time_ ; temp++) cout << Count[temp] << "\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    lli time_;
    cin >> time_;
    AC_automaton(time_);
    return 0;
}
```

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 3e5 + 10;
vector<lli> degree(N);
vector<lli> root(N);
lli point = 0;
struct TREE{
    lli son[26];
    lli fail;
    vector<lli> End;
}tree[N];
void BuildTree(string put, lli index){
    lli now_ = 0; //从第0个节点开始排查
    for(int temp = 0 ; temp < put.size() ; temp++){
        lli pos = put[temp] - 'a'; //这个字母对应的坐标
        if(tree[now_].son[pos] == 0) //如果没有这个字母存在
            tree[now_].son[pos] = ++point; //给这个新的字母附上一个新的坐标，此时point是最大达到的坐标
        now_ = tree[now_].son[pos];//此时排查的点来到了刚刚判断的点那里
    }
    tree[now_].End.push_back(index); //End数组记录以这个字符结尾的模式串的索引
    root[index] = now_; //root数组记录索引为index的模式串最后一个字母坐标是什么
    
    //cout << root[index] << " " << index << "**\n";
}
void GetFail(){
    queue<lli> Find;
    // 预处理第二层
    for(int temp = 0 ; temp < 26 ; temp++){
        if(tree[0].son[temp]){
            tree[tree[0].son[temp]].fail = 0;
            Find.push(tree[0].son[temp]);
        }
    }
    while(!Find.empty()){
        lli one = Find.front(); Find.pop(); //取出第一个元素
        for(int temp = 0 ; temp < 26 ; temp++){
            if(tree[one].son[temp]){
                tree[tree[one].son[temp]].fail = tree[tree[one].fail].son[temp];
                Find.push(tree[one].son[temp]);
                degree[tree[tree[one].son[temp]].fail] ++;
            }else
                tree[one].son[temp] = tree[tree[one].fail].son[temp];
        }
    }
}
void topu(vector<lli> Count, lli have){
    //for(int temp = 0 ; temp <= 20 ; temp++) cout << Count[temp] << " ";
    //cout << "\n";
    queue<lli> Find;
    vector<lli> Ans(N, 0);
    //如果某个节点的入度为0，那么就将这个节点塞入队列
    //for(int temp = 0 ; temp <= 20 ; temp++) cout << degree[temp] << " ";
    for(int temp = 0 ; temp <= point ; temp++){
        if(degree[temp] == 0)
            Find.push(temp);
    }
    while(!Find.empty()){
        lli one = Find.front(); Find.pop();
        Ans[one] = Count[one];
        Count[tree[one].fail] += Count[one];
        degree[tree[one].fail] --;
        if(degree[tree[one].fail] == 0) Find.push(tree[one].fail);
    }
    //for(int temp = 0 ; temp <= 20 ; temp++) cout << Ans[temp] << " ";
    //cout << "\n";
    for(int temp = 1 ; temp <= have ; temp++) cout << Ans[root[temp]] << "\n";
}
void AC_automaton(string put, lli have){
    vector<lli> Count(N, 0);
    lli now = 0LL;
    for(int temp = 0 ; temp < put.size() ; temp++){
        lli index = put[temp] - 'a';
        now = tree[now].son[index];
        Count[now] ++;
    }
    topu(Count, have);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    lli time_; string put;
    cin >> time_;
    vector<string> info(time_ + 10);
    for(int temp = 1 ; temp <= time_ ; temp++){
        cin >> info[temp];
        BuildTree(info[temp], temp);
    }
    GetFail();
    cin >> put;
    AC_automaton(put, time_);
    return 0;
}
```

## 0-1背包问题 $(n^2)$

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2000;
pair<int,int>info[N];
int have_time, total_info;
int dp[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> have_time >> total_info;
    for(int temp = 1 ; temp <= total_info ; temp++)
        cin >> info[temp].first >> info[temp].second;
    for(int j = 1 ; j <= total_info ; j++){
        for(int i = have_time ; i >= 1 ; i--){
            if(i >= info[j].first)
                dp[i] = max(dp[i], dp[i - info[j].first] + info[j].second);
        }
    }
    cout << dp[have_time];
    return 0;
}
```

## 多重背包 $(MN)$/$(NM\log s_i)$

**二进制优化 + 常数优化$(NM\log s_i)$**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5;
pair<int,int>info[N];
int have_size, total_info, Count_ = 1;
int dp[N], sum[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_info >> have_size;
    for(int temp = 1; temp <= total_info ; temp++){
        int num1,num2,num3;
        cin >> num1 >> num2 >> num3;
        for(int temp2 = 1 ; temp2 <= num3 ; temp2 <<= 1){
            info[Count_].first = num1*temp2;
            info[Count_++].second = num2*temp2;
            num3-=temp2;
        }
        if(num3){
            info[Count_].first = num1*num3;
            info[Count_++].second = num2*num3;
        }
    }
    for(int temp = 1 ; temp < Count_ ; temp++)
        sum[temp] = sum[temp - 1] + info[temp].second;
    for(int j = 1 ; j < Count_ ; j++){
        int tem = sum[Count_ - 1] - sum[j-1];
        int limit = have_size - tem < 0 ? 0 : have_size - tem;
        for(int i = have_size ; i >= limit ; i--){
            if(i >= info[j].second)
                dp[i] = max(dp[i], dp[i-info[j].second] + info[j].first);
        }
    }
    cout << dp[have_size];
    return 0;
}
```

**单调队列优化 $(MN)$**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5;
int have_size, total_info;
int V[N], W[N], M[N];
int dp[N], pre[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_info >> have_size;
    for(int temp = 1 ; temp <= total_info ; temp++)
        cin >> V[temp] >> W[temp] >> M[temp];
    for(int temp = 1 ; temp <= total_info ; temp++){
        memcpy(pre, dp, sizeof(dp));
        for(int temp2 = 0 ; temp2 < W[temp] ; temp2++){
            deque<int>tem;
            for(int temp3 = temp2 ; temp3 <= have_size ; temp3 += W[temp]){
                while(!tem.empty() && tem.front() < temp3 - M[temp]*W[temp])
                    tem.pop_front();
                if(!tem.empty())
                    dp[temp3] = max(pre[temp3], pre[tem.front()] + (temp3 - tem.front())/ W[temp]*V[temp]);
                while(!tem.empty() && pre[temp3] >= pre[tem.back()] + (temp3 - tem.back())/ W[temp]*V[temp])
                    tem.pop_back();
                tem.push_back(temp3);
            }
        }
    }
    cout << dp[have_size];
    return 0;
}
```



## 最长递增子序列 $(n)$

**单调栈优化**

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        const int N = 3000;
        vector<int> use;
        use.push_back(nums[0]);
        for(int temp = 1 ; temp < nums.size() ; temp++){
            if(nums[temp] > use.back())
                use.push_back(nums[temp]);
            else
                *lower_bound(use.begin(), use.end(), nums[temp]) = nums[temp];
        }
        return use.size();
    }
};
```

