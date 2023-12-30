# Codeforces Round #852 (Div. 2)

[toc]

**写在前面**

好吧，我拖更很久了，人懒了.....

不想写题目大意了，好浪费时间，相信各位英语肯定比我好太多，也就不献丑了

D题我等别人清晰的题解，看懂了思路代码不会写的痛谁懂，有空补补F，听说是5年前的原题。

## A. Yet Another Promotion

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230213142050901.png" alt="image-20230213142050901" style="zoom:80%;" />



**思路/证明**

由题意得，如果我们买$m$个$a$，那么这个时候$a$的性价比是最高的，所以我们以这个性价比讨论情况。

为了方便表示，我们设$a$的原本单价为$A$，$b$原本单价为$B$，买$m$个$a$时$a$的单价为$C$。

* 如果 $C \ge B$，那么不用说，肯定是全用$b$买。
* 如果 $C < B$ ：分成两种情况：
  * 第一种 ：全用$a$买，但这个时候$a$的数量是$m$的整数倍，这个时候可能会超过需求量，但问题不大。
  * 第二种：部分用$a$买，这时候的$a$是$m$的整数倍，注意不要超过需求量，之后剩余的我们通过$min\{A, B\}$来决定用$a$买还是用$b$。



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, a, b, need, m;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> a >> b >> need >> m;
        double new_ = (m / ((m + 1)*1.0)) * a; // 算出a的最小单价
        if(b <= new_) cout << need * b << "\n";
        else{
            lli one = ceil(need / ((m + 1)*1.0)); //第一种
            lli two = floor(need / ((m + 1)*1.0)); //第二种
            lli one_pri =one * m * a;
            lli two_pri = two * m * a + (min(a, b) * (need - two*(m + 1)));
            cout << min(one_pri, two_pri) << "\n";
        }
    }
    return 0;
}
```

## B. Fedya and Array

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230213142129881.png" alt="image-20230213142129881" style="zoom:80%;" />



**思路/证明**

这一题实际上是一道思维题。

我们可以这样想，既然是所有 *local maximum* 的和，为什么不能是整个数组中只有一个 *local maximum* ，然后它的值是这个和。

同理，*local minimum*也可以这样想。

所以我们可以从 *local maximum*开始递减， 减到*local miniximum*，之后再递增到*local maximum*。

也就是说， 假如 *local maximum* = $a$， *local minimum* = $b$：

那么这个环形数组长这个样子：
$$
a, a-1,a-2,\dots,b+1,b,b + 1,\dots,a-1
$$
**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, a, b;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> a >> b;
        cout << 2*(a - b) << "\n";
        for(lli temp = a ; temp > b ; temp--)
            cout << temp << " ";
        for(lli temp = b ; temp < a ; temp++)
            cout << temp << " ";
        cout << "\n";
    }
    return 0;
}
```



## C. Dora and Search

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230213142159660.png" alt="image-20230213142159660" style="zoom:80%;" />

**思路/证明**

好吧我承认这题赛时我没有做出来......

其实本题可以采用贪心的思想，题目中说了，多个解可以输入任意解，所以我们可以从数组两端考虑。

我们维护一段区间的最大值与最小值，并且用 `left`， `right` 两个变量维护区间的左端点和右端点

如果`arr[left]` 等于最大值，那么让`left++`，同时`max--`。

如果`arr[left]` 等于最小值，那么让`left++`， 同时`min++`。

同理，`right`的操作与之类似，不过`right`的操作是`right--`。

如果最后数组被删完，那么无解。



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, Length;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> Length;
        vector<lli> arr(Length + 10);
        lli Max = INT_MIN, Min = INT_MAX;
        for(int temp = 1 ; temp <= Length ; temp++){
            cin >> arr[temp];
            Max = max(Max, arr[temp]); Min = min(Min, arr[temp]);
        }
        lli left = 1, right = Length, flag = 0;
        while(left < right){
            if(arr[left] == Min) {left++; Min++; continue;}
            if(arr[left] == Max) {left++; Max--; continue;}
            if(arr[right] == Min) {right--; Min++; continue;}
            if(arr[right] == Max) {right--; Max--; continue;}
            flag = 1; break;
        }
        if(flag) cout << left << " " << right << "\n";
        else cout << "-1\n";
    }
    return 0;
}
```



## D. Moscow Gorillas

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230213161320438.png" alt="image-20230213161320438" style="zoom:80%;" />



**思路/代码**

先来推荐一篇博客，本思路受其启发：[Codeforces Round #852(Div. 2) D(枚举+分类讨论) - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/605710274?utm_campaign=&utm_medium=social&utm_oi=1121457896646451200&utm_psn=1608187914634137600&utm_source=qq)。

好吧，我承认我懒了，不想自己写了，所以我就简单说说思路，图就不画了，必进那篇博客有（~~别骂了~~）

主要是分情况讨论：

如果$MEX$值是 $a$， 那么区间就不能包括 $a$， 同时我们可以确定一段区间是必选的，所以我们可以求出漂浮不定可选可不选的区间，然后将他们的个数乘在一起，那么相加后就是答案。



**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli Length;
lli Get(lli number) {return (number*(number + 1)) / 2;}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> Length;
    vector<lli> p(Length + 10), q(Length + 10), pos_p(Length + 10), pos_q(Length + 10);
    for(int temp = 1 ; temp <= Length ; temp++){
        cin >> p[temp]; pos_p[p[temp]] = temp;
    }
    for(int temp = 1 ; temp <= Length ; temp++){
        cin >> q[temp]; pos_q[q[temp]] = temp;
    }
    lli L = min(pos_p[1], pos_q[1]), R = max(pos_p[1], pos_q[1]);
    lli ans = Get(L - 1) + Get(Length - R) + Get(max(0LL, R - L - 1));
    for(int temp = 2 ; temp <= Length ; temp++){
        lli index1 = pos_p[temp], index2 = pos_q[temp];
        if(index1 > index2) swap(index1, index2);
        if((index1 > L && index1 < R) || (index2 > L && index2 < R)) {;}
        else if(index1 < L && index2 < L)
            ans += (Length - R + 1) * (L - index2);
        else if(index1 > R && index2 > R)
            ans += (index1 - R) * L;
        else if(index1 < L && index2 > R)
            ans += (L - index1) * (index2 - R);
        L = min(index1, L); R = max(index2 , R);
    }
    cout << ans + 1;
    return 0;
}
```

