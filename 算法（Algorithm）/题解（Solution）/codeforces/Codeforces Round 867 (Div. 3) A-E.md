![Image](https://pic4.zhimg.com/80/v2-f131d8d9a21b41c50fd9695a26115684.jpg)

# Codeforces Round 867 (Div. 3) A-E

好久没打过CF了，昨天突然心血来潮打了一场，发现码力下降了好多...

前几天兼班约谈了，让我抓紧时间放弃算法，赶紧做项目为考研复试做准备.....啊啊啊好烦......

无所谓，学校的校赛结束咯，全院第二，从现役的大二学长手中把名额抢了下来（队友牛逼！！！）

啊哈哈，要去深技大咯，第一次出去打比赛，怎么能不激动，哈哈，马上就能迎来第一件属于自己的XCPC纪念衣服咯~~

emmm，开始正题...



## A. TubeTube Feed

说实话，这题给我的最大教训就是，对于我来说，千万千万不要使用 `tuple`，三个参数意义老是记混，还不如结构体用的爽快

主要思路非常简单：

因为对于第 $i$ 个节目来说，想要看到它就必须多付出 $i-1$ 的时间代价，相当于所需要的时间增加了

所以我们把更新后的时间，价值，下标作为一个结构体，然后按照价值排序即可

取我能接受的最大时间的最大价值即可

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length, Limit;
vector<struct TYPE> arr(N);
//太痛了，一用tuple连A都过不了了
struct TYPE{
    lli time, value, index;
};
bool cmp(struct TYPE a, struct TYPE b){
    return a.value > b.value;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length >> Limit;
        for(int temp = 1 ; temp <= Length ; temp++){
            cin >> arr[temp].time;
            arr[temp].time += (temp - 1);
            arr[temp].index = temp;
        }
        for(int temp = 1 ; temp <= Length ; temp++)
            cin >> arr[temp].value;
        sort(arr.begin() + 1, arr.begin() + Length + 1, cmp);
        lli flag = 0;
        for(int temp = 1 ; temp <= Length ; temp++){
            if(arr[temp].time > Limit) continue;
            cout << arr[temp].index << "\n";
            flag = 1;
            break;
        }
        if(flag == 0) cout << "-1\n";
    }
    return 0;
}
```



## B. Karina and Array

思路简单，但竟然 `WA` 了一发，痛彻心扉

建议所有使用 `INT_MAX` 和 `INT_MIN` 的改成 `LONG_MAX` , `LONG_MIN`....... 太痛了......

我们将数组分成两部分，一部分是正数， 一部分是负数

然后正数从大到小排序， 负数从小到大排序，然后取两个部分的前两个相乘之后取最大值即可

如果输入只有两个数且一正一负， 那么只能这两个数相乘了

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
vector<lli> pos, nag;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length;
        for(int temp = 1 ; temp <= Length ; temp++) cin >> arr[temp];
        for(int temp = 1 ; temp <= Length ; temp++){
            if(arr[temp] > 0) pos.push_back(arr[temp]);
            else nag.push_back(arr[temp]);
        }
        sort(pos.begin(), pos.end(), greater<lli>());
        sort(nag.begin(), nag.end());
        lli ans = -lli(1e19);
        if(pos.size() >= 2)
            ans = max(ans, (pos[0] * pos[1]));
        if(nag.size() >= 2)
            ans = max(ans, nag[0] * nag[1]);
        if(pos.size() == 1 && nag.size() == 1)
            ans = max(ans, pos[0] * nag[0]);
        cout << ans << "\n";
        nag.clear(); pos.clear();
    }
    return 0;
}
```



### C. Bun Lover

![Image](https://pic4.zhimg.com/80/v2-ff8b5a0823d061977fe84fa3fabf6a1f.png)

图画的不好，见谅.....

主要是讲这个卷划分出来，发现通过移动一些边可以将它分成三个部分（啊啊啊！不知道怎么表述，大家自己试一下....）

然后你就会神奇的发现， $A$的边长是 $2\times (n + (n-1) + (n-2) + \dots + 1) = n(n + 1)$ 

然后 $B + C$ 的边长就是 $n + 2$

所以总长为 $n(n + 1) + n+2$

// 讲的真的不好.....

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length;
        cout << (Length + 1) * Length + Length + 2 << "\n";
    }
    return 0;
}
```



## D. Super-Permutation

神奇的一道题，我过了，但是不知道为什么可以过，不懂，来个大佬教我

做法如下：

对于长度 $n$ 为奇数来说，不可能

对于长度 $n$ 为偶数来说：第一个数肯定是 $n$ 

(这个我知道，如果放在其他位置，假设放在第 $i$ 位， 那么 $Sum_{i-1} \bmod n$ == $(Sum_{i-1} + n) \bmod n$ , 所以只能放在第一位)

后面的方法就很玄学了。

![Image](https://pic4.zhimg.com/80/v2-9062e7d24e68a8bf0a4c10c61b249eab.png)

简单来说就是，$1,3,5,7,9,\dots$ 从后往前每隔两个位置放置，$2，4，6，8，10,\dots$ 从前往后每隔两个位置放置

原因不明....

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length;
        if(Length == 1){
            cout << "1\n"; continue;
        }
        if(Length & 1) {cout << "-1\n"; continue;}
        vector<lli> ans(Length + 1);
        lli a = 1, b = 2;
        for(int temp = Length ; temp >= 0 ; temp-= 2){
            ans[temp] = a; a+= 2;
        }
        for(int temp = 3 ; temp <= Length ; temp+= 2){
            ans[temp] = b; b += 2;
        }
        ans[1] = Length;
        for(int temp = 1 ; temp <= Length ; temp++)
            cout << ans[temp] << " ";
        cout << "\n";
    }
    return 0;
}
```



## E. Making Anti-Palindromes

第二天早上英语课写的...昨天太晚顶不住了.....

思路是：

首先奇数长度肯定是不行的， 因为最中间自身肯定于自身相同。

然后考虑偶数，我们把字符串分为两部分，然后我们定义一个 $pair$ $<$ char $a$ , char $b$ $>$

$a$ 代表左半部分的字符，$b$ 代表右半部分的字符

我们要明白两个事实：

* 一、假设有 $<a,a>$  的个数为 5， $<b,b>$ 的个数为， 那么仅 $a,b$ 相互交换就可以消去 $a$ 的所有重复对

  但是对于 $b$ 来说， 只能消除 5 对， 还有5对需要另行处理

* 二、$<a,a>$ 想要被消除，必须要寻找一个 $<b,c>$ , 也就是说需要 $b$ , $c$ 不能为 $a$ 的对。

我们定义两个变量：

`can` 和 `add`  : 分别代表可以被相同对内部消化的个数以及需要单独处理的对数

对于每一部分相同对来说（相同的字符为一组，（$<a,a>$, $<a,a>$ 为一组））, 如果剩余的相同对数量大于等于这一组的数量，那么这一组是可以被内部消化的。参见事实一

否则，我们可以获得需要单独处理的数量。

接着就是判断该字符串时候可以消化这一部分，也就是事实二的表述。

所以最后的答案就是 `(can + ) / 2 + add `

注释见代码， 写法可能不清楚，见谅....

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, Length;
vector<lli> arr(N);
string put;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    //total_ask = 1;
    while(total_ask--){
        cin >> Length;
        cin >> put;
        if(Length & 1){
            cout << "-1\n";
            continue;
        }
        lli same = 0LL; // 一共有多少相同的对数
        map<char,lli> samePair; //具体他们的开头字符是什么，有多少对
        map<char, map<char,lli> > info; // <a,b> 字符有多少个
        //两个vector均是不包括相同对
        vector<lli> Count1(26, 0), Count2(26, 0); //以某个字符开头的对有多少个，以某个字符结尾的对有多少个
        for(int temp = 0 ; temp < (Length / 2) ; temp++){
            lli one = temp, two = Length - temp - 1;
            if(put[one] == put[two]){
                samePair[put[one]]++;
                same++; continue;
            }
            info[put[one]][put[two]]++;
            Count1[put[one] - 'a']++; Count2[put[two] - 'a']++;
        }
        lli can = 0LL, add = 0LL, flag = 1;
        for(auto pr : samePair){
            if(pr.second <= same - pr.second){
                can += pr.second; continue;
            }
            can += same - pr.second;
            lli need = pr.second - (same - pr.second);
            lli have = (Length / 2) - same - Count1[pr.first - 'a'] - Count2[pr.first - 'a'] + info[pr.first][pr.first];
            // 总共有(Length / 2) 个， 减去相同的对数， 然后减去左半部分包含pr.first的所有点，再减去结尾为pr.first的所有点
            //再加上开头和结尾都是pr.first的点。
            if(need <= have) add += need;
            else{
                flag = 0; break;
            }
        }
        if(flag == 0){
            cout << "-1\n"; continue;
        }
        lli ans = (can + 1) / 2 + add;
        cout << ans << "\n";
    }
    return 0;
}
```

后面还没补，大概率不补......









给你一个长度 $n$ , 问是否存在一个长度为 $n$ 的**排列** $p(p = [a_1, a_2, \dots, a_n])$ 使得 $\sum_\limits{i=1}^{n-1} ia_i \bmod n = 0$ 

如果存在输出任意一个符合条件的 $p$ , 不存在则输出 $-1$

**一个长度为 $n$ 的排列包含 $n$ 个整数，其中从 $1$ 到 $n$ 的每个整数正好出现一次。**

举个例子 $[1,2,5,4,3], [2,3,1]$ 是排列， $[0,1,2,3][1,1,3]$不是

样例：

```
17
```

```
4
```

输出

```
-1
```

```
4 3 2 1
```

