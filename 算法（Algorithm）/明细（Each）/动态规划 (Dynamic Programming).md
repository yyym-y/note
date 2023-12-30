# 动态规划 (Dynamic Programming)

[toc]

## 0/1背包问题

**题目描述**

一共有 $N$ 个物品和一个容量为 $V$ 的背包，这 $N$ 个物品分别是 $n_i,n_2,\dots, n_i,\dots ,n_N$ 

现在对于物品 $n_i$ 来说，其所需的空间为 $W_i$ ，价值为 $V_i$ 

问 ： 现在在不超过容量$V$ 的情况下可以装下的最大价值是多少

### 基本思路

现在我们定义一个二维数组 $dp[i][j]$ ，其代表的含义是：当背包容量为 $i$ 的时候，我有前 $j$ 个物品，我可以获得的最大价值

对于当前物品 $j$， 我现在有两种选择，分别是选择物品 $j$， 另一种是不选择物品 $j$

* **==选择物品 $j$ ：==**物品 $j$ 所需的空间是 $W_j$ ,价值为 $V_j$ ，放入物品 $j$ ，那么背包的空间将会变成 $V-W_j$ ，

  那么你获得的价值将是（物品 $j$ 的价值加上（考虑前 $j-1$ 个物品且背包容量为 $V-W_j$ 时所能获得的最大价值））

  写成方程便是：
  $$
  dp[i][j] = dp[i-W_j][j-1] + V_j
  $$

* **==不选择物品 $j$ ：==**如果不选择物品 $j$， 那么此事你能获得的价值是（考虑前 $j-1$ 个物品且背包容量为 $V$ 时所能获得的最大价值）

  写成方程就是：
  $$
  dp[i][j] = dp[i][j-1]
  $$
  

因为只有这两种情况，所以只需要将两种情况的最大值求出，即是 $dp[i][j]$ 所可以达到的最大值

所以转移方程是：
$$
dp[i][j] = max\{dp[i][j-1] ,dp[i-W_j][j-1] + V_j \}
$$


**边界条件/初始化**

注意看，因为涉及到减号，那么就不得不考虑数组越界的情况了，我们可以让 $i$ , $j$ 都从1开始

但是等于0的时候怎么办，可以想象到如果背包容量为0，那么可以获得的最大价值也为0，没有物品那么可以获得的价值同为0

但边界条件不一定都是0，要具体看题目怎么说明

其次是初始化，初始化的内容留到下面讲   [背包完全装满的最大价值]

**例题**

这里给出一道模板题，来自洛谷[P1048 ](https://www.luogu.com.cn/problem/P1048)

现在给出代码：( $i$ , $j$ 含义如上所述)（因为定义dp是设为全局数组，所以并没有初始化）

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2000;
pair<int,int>info[N];
int have_time, total_info;
int dp[N][N];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin >> have_time >> total_info;
    for(int temp = 1 ; temp <= total_info ; temp++)
        cin >> info[temp].first >> info[temp].second;
    for(int i = 1 ; i <= have_time ; i++){
        for(int j = 1 ; j <= total_info ; j++){
            if(i >= info[j].first)
                dp[i][j] = max(dp[i][j-1],dp[i-info[j].first][j-1]+info[j].second);
            else
                dp[i][j] = dp[i][j-1];
        }
    }
    cout << dp[have_time][total_info];
    return 0;
}
```

### 优化一：滚动数组

我们将01背包的转移方程抄下
$$
dp[i][j] = max\{dp[i][j-1] ,dp[i-W_j][j-1] + V_j \}
$$
我们将转移方程中所需要的元素标出，发现箭头无非就两个方向，一个来自上方，一个来自左边

且左边的长度永远为1

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230111185145487.png" alt="image-20230111185145487" style="zoom:80%;" />

可以观察到他们都来自同一行，那么我们其实是可以用一个一维数组来取代二维数组的

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230111174112512.png" alt="image-20230111174112512" style="zoom:80%;" />

值得注意的是这样优化的化要从后向前遍历，这样才能成功使用 $dp[i-1][\dots]$的数据

由此，我们可以给出01背包一维dp的转移方程：
$$
dp[i] = max\{dp[i] ,dp[i-W_j] + V_j \}
$$


给出上述例题的优化一代码

**代码**

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

### 优化二：常数优化

我们将此优化方案放在二维dp上理解，之后再优化为一维

以下图为例：

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230113133207259.png" alt="image-20230113133207259" style="zoom:80%;" />

现在假设一共有 $j$ 个物品，编号为：$1,2,\cdots,j$ ，价值分别为：$v_1,v_2,\dots,v_j$， 质量分别为：$w_1,w_2,\dots,w_j$ , 拥有总容量为：$V$

对于最后一个格子来说，此时代表背包容量为$V$,且有$j$个物品所可以拥有的最大价值

仅对于这个格子来说，它的转移方程为：$dp[j][V] = max\{dp[j-1][V],dp[j-1][V-w_j]+v_j \}$

可以观察到它仅仅有两个地方的格子决定，那么当物品编号为$j-1$的时候，背包容量为$[1,V-w_j]$所代表的格子将不会被需要

也就是图上画了虚线的部分是可以不用求的，

其实也不用担心其他地方的格子会访问虚线地方，因为虚线前面的格子所访问的格子连成线是于黑色的箭头平行的

以此类推，实际上需要计算的格子数将会减少

对于编号为 a 的时候，边界条件就是 $\sum_{i=a}^{j} w_i$ , 注意要和背包总容量作比较 

给出用此方法解决洛谷[P1048 ](https://www.luogu.com.cn/problem/P1048)的代码

**代码1（二维）**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2000;
int dp[N][N], sum[N];
pair<int,int>info[N];
int have_time, total_info;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> have_time >> total_info; //最大容量 + 信息个数
    for(int temp = 1 ; temp <= total_info ; temp++)
        cin >> info[temp].first >> info[temp].second; // 
    for(int temp = 1 ; temp <= total_info ; temp++)
        sum[temp] = sum[temp - 1] + info[temp].first;
    for(int j = 1 ; j <= total_info ; j++){
        int tem = sum[total_info] - sum[j-1];
        int limit = have_time - tem < 0 ? 0 : have_time-tem;
        for(int i = have_time ; i >= limit ; i--){
            if(i >= info[j].first)
                dp[j][i] = max(dp[j-1][i], dp[j-1][i-info[j].first] + info[j].second);
            else
                dp[j][i] = dp[j-1][i];
        }
    }
    cout << dp[total_info][have_time];
    return 0;
}
```

**代码2（一维）**

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2000;
int dp[N], sum[N];
pair<int,int>info[N];
int have_time, total_info;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> have_time >> total_info;
    for(int temp = 1 ; temp <= total_info ; temp++)
        cin >> info[temp].first >> info[temp].second;
    for(int temp = 1 ; temp <= total_info ; temp++)
        sum[temp] = sum[temp - 1] + info[temp].first;
    for(int j = 1 ; j <= total_info ; j++){
        int tem = sum[total_info] - sum[j-1];
        int limit = have_time - tem < 0 ? 0 : have_time - tem;
        for(int i = have_time ; i >= limit ; i--){
            if(i >= info[j].first)
                dp[i] = max(dp[i], dp[i-info[j].first] + info[j].second);
        }
    }
    cout << dp[have_time];
    return 0;
}
```

## 多重背包问题

### 优化一：二进制拆分优化

首先我们要先记住：将 $n$ 拆分成二进制数后可以组成 1~ $n$中所有的数

所以我们可以将朴素的将 $m$ 个物品一一拆分的思想转化为拆分成一个又一个的物品快，这样就可以减少拆分的次数

说一下我最开始的困惑吧：

最开始很疑惑为什么仅仅拆分成这几个小块就可以确定是这么多物品所能获得的最优解。

其实这就是运用了动态规划的记忆化搜索的特性

比如说拿10来举例， 10 会给拆分成 1，2，4，3， 当我们考虑是否取3的时候，实际上考虑的是在1，2，4，3中能取出的最大价值

而1，2，4，3能组成1-10中所有的数，所以说仅仅通过这几个数就可以确定1~10中所能获得的最大价值

**代码（二进制优化+常数优化）**

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

### 优化二：单调队列优化

首先我们按照朴素算法的思路，将多重背包直接拆成01背包，即我们一个一个去分析

这样我们就可以写出这样一个三重循环：

```c++
for(int j = 1 ; j <= total_info ; j++){ // 物品数
    for(int i = have_size ; i >= 0 ; i++){ // 空间
        for(int temp = 0 ; temp <= M ; temp++) // 到底取多少个物品
            dp[i] = max{dp[i], dp[i-temp*W[j]] + temp*V[j]};
    }
}
```

但这样的复杂度十分高 $O(NM\sum s_i)$

经过二进制拆分优化，时间复杂度来到了$O(NM\log s_i)$

但这还远远不够，使用单调队列优化可以使时间复杂度来到$O(NM)$

首先我们来分析能否优化最内层循环

我们通过递推关系式可以知道：
$$
dp[i] = max\{dp[i], dp[i-w]+v, dp[i-2\times w]+2\times v \dots dp[i-k\cdot w] + k \cdot v \}
$$
也就是说 $dp[i]$ 是由之前一系列$dp[a] + b$ 来确定的，并且每个 $a$ 相差 $w$ 的整数倍， $b$ 相差 $v$ 的整数倍

我们先不关注 $b$ ，我们先仅仅考虑 下标 $a$

现在已知最后一项的值为 $i - k\cdot w$ ，我们不妨将其设为 $m$ ，那么$m$ 有哪些可能值呢

我们把 $m$ 从 $0$开始取，这样我们我们就得到了一系列数：$0,1,\dots,w-1$ 

注意要在$w-1$ 处停,因为如果等于$w$， 那么将和 $0$ 是同一种情况

这样我们将得到一组数：

>$dp[0]\quad dp[w]\quad dp[2\times w]\dots dp[(k-1)\cdot w]\quad dp[k \cdot w]$
>
>$dp[1]\quad dp[1+w]\quad dp[1+2\times w]\dots dp[1+(k-1)\cdot w]\quad dp[1+k \cdot w]$
>
>$dp[2]\quad dp[2+w]\quad dp[2+2\times w]\dots dp[2+(k-1)\cdot w]\quad dp[2+k \cdot w]$
>
>$\dots \dots\dots$
>
>$dp[(w-2)]\quad dp[(w-2)+w]\quad dp[(w-2)+2\times w]\dots dp[(w-2)+(k-1)\cdot w]\quad dp[(w-2)+k \cdot w]$
>
>$dp[(w-1)]\quad dp[(w-1)+w]\quad dp[(w-1)+2\times w]\dots dp[(w-1)+(k-1)\cdot w]\quad dp[(w-1)+k \cdot w]$

最后我们得出了这个结论:
$$
dp[j] \propto dp[w + j] + dp[2w + j] +\dots+dp[kw + j]  \quad j \in [0,w-1]
$$
也就是说 $dp[j]$ 仅仅于后面这一坨东西有关

也就是我们把 $dp$ 数组分成 $j$ 个类，每一类中的值，都是在同类之间转换得到的

现在我们就需要$dp[w + j] + dp[2w + j] +\dots+dp[kw + j]$ 中的可以让结果最大的值

同时有需要控制其中的个数，这样就转化成了单调队列的问题

接下来我们就要确定怎样才能让某个数达到单调队列的头部，也就是确定谁更加优先：

现在假设我们有两个下标为 $a$ , $b$ 的数， 他们在$dp$ 数组中的值为 $a^\prime$ , $b^\prime$

现在$a$ 在队列中，我们要判断 $b$ 是否能进入队列

 因为实际上需要的值是通过$dp[i-k\cdot w] + k \cdot v$ 求出来的，所以我们引入一个中间变量 $x$

对于一个下标为 $i$ 的数来说，放入它可以获得的价值是 $\frac{x-i}{m}\times v + i^\prime$

所以如果 $b$ 可以进入队列，则有：
$$
\begin{align}
	&\frac{x-a}{m}\times v + a^\prime < \frac{x-b}{m}\times v + b^\prime \\
	&进一步化简得:\\\\
	&b^\prime > a^\prime + \frac{(b-a)\times v}{m}
\end{align}
$$
所以这就是我们的进入条件

**代码**

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



## 完全背包问题

## 混合背包问题

## 二维费用背包

## 分组背包问题

## 有依赖背包问题

## 最长公共子序列

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        const int N = 1500;
        int dp[N][N];
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ; j < N ; j++) dp[i][j] = 0;
        }
        int ans = INT_MIN;
        for(int temp = 1 ; temp <= text1.size() ; temp++){
            for(int temp2 = 1 ; temp2 <= text2.size() ; temp2++){
                if(text1[temp-1] == text2[temp2 - 1])
                    dp[temp][temp2] = dp[temp - 1][temp2 - 1] + 1;
                else    
                    dp[temp][temp2] = max(dp[temp][temp2-1], dp[temp-1][temp2]);
                ans = max(ans, dp[temp][temp2]);
            }
        }
        return ans;
    }
};
```

## 最长递增子序列

**朴素dp做法**

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        const int N = 3000;
        int dp[N], ans = 1;
        for(int temp = 0 ; temp < N ; temp++) dp[temp] = 1;
        for(int temp = 1 ; temp < nums.size() ; temp++){
            for(int temp2 = 0 ; temp2 < temp ; temp2++){
                if(nums[temp2] < nums[temp])
                    dp[temp] = max(dp[temp], dp[temp2] + 1);
            }
            ans = max(ans, dp[temp]);
        }
        return ans;
    }
};
```

**单调栈做法**

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

## 最长连续递增子序列

```c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        const int N = 1e4 + 10;
        int dp[N];
        for(int temp = 0 ; temp < N ; temp++) dp[temp] = 1;
        int ans = 1;
        for(int temp = 1 ; temp < nums.size() ; temp++){
            if(nums[temp] > nums[temp - 1])
                dp[temp] = dp[temp - 1] + 1;
            ans = max(ans, dp[temp]);
        }
        return ans;
    }
};
```

## 最长重复子数组

```c++
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        const int N = 1500;
        int dp[N][N], ans = 0;
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ; j < N ; j++) dp[i][j] = 0;
        }
        for(int temp = 1 ; temp <= nums1.size() ; temp++){
            for(int temp2 = 1 ; temp2 <= nums2.size() ; temp2++){
                if(nums1[temp - 1] == nums2[temp2 - 1])
                    dp[temp][temp2] = dp[temp - 1][temp2 - 1] + 1;
                ans = max(ans, dp[temp][temp2]);
            }
        }
        return ans;
    }
};
```

## 编辑距离



## 最小划分

## 行走问题

## 矩阵最长递增路径

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 200;
int dp[N][N], map_[N][N];
int vertical, level, ans = 0;
int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int DFS(int x, int y){
    if(dp[x][y]) return dp[x][y];
    int ans = 1, tem = 0;
    for(int temp = 0 ; temp < 4 ; temp++){
        int X = dir[temp][0] + x;
        int Y = dir[temp][1] + y;
        if(X >= 1 && X <= vertical && Y >= 1 && Y <= level){
            if(map_[X][Y] < map_[x][y])
                tem = DFS(X,Y);
        }
        ans = max(ans , tem + 1);
    }
    return ans;
}

signed main()
{
    cin >> vertical >> level;
    for(int temp = 1 ; temp <= vertical ; temp++){
        for(int temp2 = 1 ; temp2 <= level ; temp2++)
            cin >> map_[temp][temp2];
    }
    for(int temp = 1 ; temp <= vertical ; temp++){
        for(int temp2 = 1 ; temp2 <= level ; temp2++){
            int tem = DFS(temp,temp2);
            dp[temp][temp2] = tem;
            ans = max(ans , tem);
        }
    }
    cout << ans;
    return 0;
}
```



## 子集和问题

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        const int N = 1e5 + 10;
        int ans = nums[0];
        int dp[N] = {0}; dp[0] = nums[0];
        for(int temp = 1 ; temp < nums.size() ; temp++){
            dp[temp] = max(dp[temp - 1] + nums[temp] , nums[temp]);
            ans = max(ans, dp[temp]);
        } 
        return ans;
    }
};
```



## 最优游戏策略

## 矩阵链乘法

## 布尔括号问题

## 最短公共超序集
