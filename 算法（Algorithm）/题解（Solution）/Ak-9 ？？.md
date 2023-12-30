## 题面

桌子上从左到右放着 $n(1 \le n \le 10^5)$ 张牌， 每张牌都写有一个数字 $a_i(0 \le a_i \le n)$

初始时，只有第一张牌时正面，其余牌都是反面，初始时你的分数时 $0$

游戏规则如下：

每次你选取一张正面的牌，这张牌上的数字为 $v$，接下来你可以进行两项操作

* 从第一张反面牌开始，将 $v$ 张反面牌翻到正面，如果剩余的反面牌不足 $v$ 张，则全部翻成正面
* 你的分数增加 $v$

一旦你选取了某张牌进行了某种操作，这张牌不能进行另一操作

问你可以获得的最大分数是多少



## 输入

```
5
2 4 5 0 1
```

## 输出

```
9
```







## 题解

首先我们考虑什么时候这个游戏会结束

* $n$ 张牌都被移除了
* 不能再将反面的牌翻到正面了

我们假设当游戏结束的时候，我总共移除了 $x$ 张牌， 且这个时候场上还有剩余牌

此时可以得出：我们总共花费了 $x - 1$ 点数来解锁这 $x$ 张牌

所以这个时候我们获得的分数为 :
$$
ans = \sum_{i = 1}^x a_i - (x - 1) = \sum_{i = 1}^x a_i - x + 1
$$
那如果这个时候场上已经没有牌了呢？

我们不妨假设场上除了题目给的这 $n$ 张牌， 还另外多了 $n$ 张牌， 不过多出来的 $n$ 张牌的点数均为 $0$

因为 $0 \le a_i \le n$ ， 所以如果是最优情况， 那么 $x$ 的范围一定落在 $[1, 2n]$

> 假设 $x > 2n$ , 那么必然是使用了两张以上的正面牌去解锁反面牌
>
> 并且在使用最后一张正面牌去解锁的时候， $x$ 已经大于 $n$ 了，则最后一张牌便是多余的



接下来我们就需要枚举 $x$ 的取值， 然后算出每个 $x$ 对应的分数， 接着维护最大值即可

我们思考一下每一个 $x$ 是怎么来的

对于第 $i$ 张卡片来说，如果用它来解锁后面反面的卡片， 那么原本在 $[i, 2n]$ 范围内的 $x$ 加上 $a_i$ 就构成了新的 $x$

再形象一点可以表示为 $x^\prime = x + a_i$

我们考虑用 `bitset` 来实现这一过程 ， 转换为位运算为 `s |= (s >> i) << (i + a[i])`

我们稍微解释一下这个过程：

`bitset` 的每一位用来表示是否可以作为 $x$ ， $0$ 表示不可以，  $1$ 表示可以

`s >> i` 是将所有小于 $i$  的 $x$ 先排除掉， 之后 `<<(i + a[i])` 是先将第 $i$ 位回归原位再将所有大于等于 $i$ 的 $x$ 加上 $v$

最后的与运算则是将最开始排除的结果重新加上



```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, Limit, Num1, Num2, Num3;
vector<lli> arr(N), Sum(N);
bitset<N> info;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length;
    for(int temp = 1  ; temp <= Length ; temp++)
        cin >> arr[temp];
    for(int temp = 1 ; temp <= N - 1; temp++)
        Sum[temp] = Sum[temp - 1] + arr[temp];
    info[1] = 1; lli ans = 0;
    for(int temp = 1 ; temp <= Length ; temp++)
        info |= (info >> temp) << (arr[temp] + temp);
    for(int temp = 1 ; temp <= 2 * Length ; temp++){
        if(info[temp])
            ans = max(ans, Sum[temp] - (temp - 1));
    }
    cout << ans;
    return 0;
}
```

