# Educational Codeforces Round 142 (Rated for Div. 2)

[比赛地址](https://codeforces.com/contest/1792)

## A. GamingForces

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230127135501797.png" alt="image-20230127135501797" style="zoom:80%;" />


**题目大意**

现在给你一个数列 $p$ ，现在你可以进行以下两种操作：

* 在数列中挑选两个数，然后让这两个数都减$1$
* 随便挑选一个数，然后让这个数变为$0$

现在问最少需要多少次操作可以使数组中的数全部变为$0$



**思路/证明**

首先我们考虑到底什么时候第一次操作要优于第二种操作

当我们选择的数是两个$1$ 的时候，这个时候第一次操作优于第二次操作

选择两个$2$ 的时候，两种方式一样， 再大都是第二种方式优了

所以我们只需要统计 $1$出现的次数，然后 +1 /2 就是对于数字$1$最好的处理

其他的数全部采用第二种操作即可



**代码**
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, have;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> have;
        vector<lli> num(have + 10);
        lli Count = 0;
        for(int temp = 1 ; temp <= have ; temp++){
            cin >> num[temp];
            if(num[temp] == 1) Count++;
        }
        cout << (have - Count) + (Count + 1) / 2 << "\n";
    }
    return 0;
}
```
## B. Stand-up Comedian

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230127135600574.png" alt="image-20230127135600574" style="zoom:80%;" />


**题目大意**

现在有两个人，他们初始的情绪值为$0$

现在有四种笑话：

* 第一种笑话两个人的情绪值+1
* 第二种笑话第一个人情绪值+1，第二个人情绪值-1
* 第三种笑话第一个人情绪值-1，第二个人情绪值+1
* 第四种笑话两个人情绪值都-1

当两个人有一个人情绪值小于0的时候不再讲笑话了(给出四种笑话的个数)

问：最多可以讲多少个笑话

**思路/证明**
我们将这些笑话的数量定义为 $num1\quad num2 \quad num3 \quad num4$

首先：毋庸置疑的是第一种笑话肯定要全讲，所以$ans$ += $num1$

之后我们观察第二种和第三种笑话的性质，当第二种和第三种笑话讲的次数一样的时候，
两个人的情绪值是不变的，所以 $ans$ += $\mathrm{ min(num2,num3)}$

因为前面的操作，所以$num2$ 和 $num3$ 肯定有一个是等于$0$的,我们假设$num2$不等于 $0$, 且此时 $num2 = a$

那么现在问题就变成了有一个人情绪值为 $x$ ,现在有 $a + num4$个操作可以使$x$减一
，那么$ans$ += $\mathrm{min(x + 1, a + num4)}$

$x + 1$是因为为0的时候其实还可以再讲一个

注意 ：以上分析基于 $num1$ 不等于 $0$ ， 如果等于 $0$ ,直接输出 $1$

**代码**
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli total_ask, num1, num2, num3, num4;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> num1 >> num2 >> num3 >> num4;
        if(num1 == 0) {cout << "1\n"; continue;}
        lli ans = num1;
        ans += 2*min(num2, num3);
        ans += min(max(num3, num2) - min(num3, num2) + num4, num1 + 1);
        cout << ans << "\n";
    }
    return 0;
}
```

## C. Min Max Sort

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230127135707077.png" alt="image-20230127135707077" style="zoom:80%;" />

**题目大意**
现在给你一个排列 $p$, 你可以进行一下操作：

* 在排列中选出两个数，讲这两个数中较大的放在排列末尾，较小的放在排列前端

问：最少需要多少次操作可以使排列变成一个升序排列


**思路/证明**
我们举个例子：

$1 \quad 5 \quad 4 \quad 2 \quad 3$

我们需要达成的效果是 ： $1 \quad 2 \quad 3 \quad 4 \quad 5$

我们可以观察到实际上 $2$, $3$ 是不用被选中更改的，所以这个排列中需要更改的数有 $5-2 = 3$ 个，所以需要的次数是$\left \lceil 3 \div 2 \right \rceil = 2$

所以现在问题变成了寻找到底有多少个数是不需要修改的，首先要解决的是：只要连在一起的就一定不需要被选出来吗

举个例子 ： $3 \quad 1 \quad 2 \quad 4 \quad 5$

可以动手试试，$4$, $5$ 都被选中了，

观察，因为是放到两边，所以我们要寻找从最中间开始的某个数向两边扩散后到底有多少个连续对

举个例子： 现在有 $n$ 个数，下标从1开始， 在最中间的数一定是 n / 2 + 1 
和 (n-1) / 2 + 1

注意这种方法即考虑了奇数也考虑了偶数，假如 $n$ 为 4， 那么这两个数为 $2$,$3$
假如 $n$ 是 $5$, 那么这两个数为 $3$

切回正题，我们需要找到从(n-1) / 2 + 1开始向左的连续数的个数，从n / 2 + 1向右的连续数的个数， 然后两个数取最小值即为不需要选择的对数

具体如下：

**1 ==3== 2 ==4== 7 *~~5~~* *~~6~~***

注意，如果在一开始$4$ 在 $3$ 前，那么所有数都需要选择

**代码**
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 2e5 + 10;
lli total_ask, num;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> total_ask;
    while(total_ask--){
        cin >> num;
        vector<lli> arr(num + 10), index(num + 10);
        for(int temp = 1 ; temp <= num ; temp++){
            cin >> arr[temp];
            index[arr[temp]] = temp;
        }
        lli ans = 0;
        lli mid1 = (num-1) / 2 + 1, mid2 = num / 2 + 1, ind1 = index[mid1], ind2 = index[mid2];
        if(ind1 > ind2) ans = (num + 1) / 2;
        else{
            lli len1 = 0, len2 = 0;
            for(int temp = ind1 - 1; temp >= 1 ; temp--){
                if(arr[temp] == mid1 - len1 - 1) len1++;
            }
            for(int temp = ind2 + 1; temp <= num ; temp++){
                if(arr[temp] == mid2 + len2 + 1) len2++;
            }
            ans = (num + 1) / 2 - (min(len1, len2) + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
```
## D. Fixed Prefix Permutations

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230127135808061.png" alt="image-20230127135808061" style="zoom:80%;" />


**题目大意**

现在给你 $n$ 个长度为 $m$ 的排列

定义一个排列的 $beauty$ 为 $k$ 的最大值($a_1 = 1, a_2 = 2\dots a_k = k$)

现在在定义 $r = a_i * a_j\quad(r,a_i,a_j 为排列)$, $r$ = $a_{i_{a_j}}$

问,$n$ 个排列中可以达到的最大的 $beauty$值是多少

**思路/证明**
首先我们可以预处理出 $n$ 个排列达到的最大$beauty$所需要的排列是啥，然后将他们
一一存在一个 unsigned_set中，然后依次遍历每一个排列，看看排列的某个部分是否存在在这个set里面，然后取长度最大值即可

注意，本题因为$m$ 小，所以可以这样处理，如果更大则需要字典树


**代码**
```c++
#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
typedef long long int lli;
lli ask_time, m, n;
signed main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> ask_time;
    while(ask_time --){
        cin >> m >> n;
        vector<vector<lli>> info(m + 5, vector<lli>(n + 5));
        vector<vector<lli>> index(m + 5, vector<lli>(n + 5));
        unordered_set<string> Check;
        for(int temp = 1 ; temp <= m ; temp++){
            for(int temp2 = 1 ; temp2 <= n ; temp2++){
                cin >> info[temp][temp2];
                index[temp][info[temp][temp2]] = temp2;
            }
        }
        for(int temp = 1 ; temp <= m ; temp++){
            string put = "";
            for(int temp2 = 1 ; temp2 <= n ; temp2++){
                put += index[temp][temp2] + '0';
                Check.insert(put);
            }
        }
        for(int temp = 1 ; temp <= m ; temp++){
            string find = "";
            for( int temp2 = 1; temp2 <= n + 1 ; temp2++){
                find += info[temp][temp2] + '0';
                if(Check.count(find) == 0) {cout << temp2 - 1 << " "; break;}
            }
        }
        cout << "\n";
    }
    return 0;
}
```